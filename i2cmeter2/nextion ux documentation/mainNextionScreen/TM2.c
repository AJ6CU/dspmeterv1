//If Graphic mode
if(nDispStatus.val==0)
{
  add 17,0,jSMeter.val/3
}
sys2=pm.vq.val&0x07
if(sys2>0)
{
  //check Now condition
  //if(dim==0)
  if(nSaverCount.val==-10)				//Screen Saver Mode
  {
    //Screen Saver Mode
    if(nLastFreq.val!=nSaverFreq.val)
    {
      dim=dims
      nSaverCount.val=0
    }
  }else if(nSaverCount.val!=-20)	//Screen off by remote control -> disabled screen saver, always backlight off
  {
    //Running Mode
    if(nLastFreq.val!=nSaverFreq.val)
    {
      nSaverFreq.val=nLastFreq.val
      nSaverCount.val=0
    }else
    {
      nSaverCount.val++
      if(sys2==1)
      {
        if(nSaverCount.val>=180)	//3 Min
        {
          dim=0
          nSaverCount.val=-10
        }
      }else if(sys2==2)
      {
        if(nSaverCount.val>=600)		//10 Min
        {
          dim=0
          nSaverCount.val=-10
        }
      }else if(sys2==3)
      {
        if(nSaverCount.val>=1200)		//20 Min
        {
          dim=0
          nSaverCount.val=-10
        }
      }
    }
  }
}
if(pm.vg.val==74)				//Loopback Process
{
  pm.vg.val=-1
  //sys0 : Sender, sys1 : Command
  sys2=pm.vv.val				//Loop back Value
  pm.vv.val=0						//Init value for Next Receive process
  sys0=sys2&0xFF				//Sender
  //Loopback Signal
  if(sys0>4)						//Sender < 5, ignore
  {
    sys2=sys2>>8
    sys1=sys2&0xFF			//Command
    if(sys1==10)				//Command : Backlight Off
    {
      sys2=sys2>>8			//
      sys1=sys2&0xFF		//Data1
      sys2=sys2>>8			//Data2 (Checksum
      sys2=sys2&0xFF
      sys0=sys0+sys1+10	//sender + command(10) + data1
      sys0=sys0%256
      if(sys0==sys2)		//Check Checksum
      {
        //Backlight Off
        nSaverCount.val=-20	//Backlight off by Remote control
        dim=0
      }
    }else if(sys1==11)		//Command : Backlight On
    {
      sys2=sys2>>8			//
      sys1=sys2&0xFF		//Data1
      sys2=sys2>>8			//Data2 (Checksum
      sys2=sys2&0xFF
      sys0=sys0+sys1+11	//sender + command(10) + data1
      sys0=sys0%256
      if(sys0==sys2)		//Check Checksum
      {
        //Backlight Off
        dim=dims
        nSaverCount.val=0
      }
    }
  }
}
