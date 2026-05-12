//First Start
if(nNowState.val==1)
{
  //BAND1
  draw 0,0,245,50,WHITE
  fill 1,1,243,48,BLACK
  line 2,15,244,15,31727
  line 2,25,244,25,RED
  line 2,35,244,35,31727
  //BAND2
  draw 0,60,245,110,WHITE
  fill 1,61,243,48,BLACK
  line 2,75,244,75,31727
  line 2,85,244,85,RED
  line 2,95,244,95,31727
  //BAND3
  draw 0,120,245,170,WHITE
  fill 1,121,243,48,BLACK
  line 2,135,244,135,31727
  line 2,145,244,145,RED
  line 2,155,244,155,31727
}
//Need Send Command
if(nNowState.val<10)
{
  printh 59										//MAGIC
  printh 58										//MAGIC
  printh 68										//MAGIC
  prints 16,1									//Command : Start Spectrum
  if(nNowState.val==1)
  {
    sys0=nBand1.val-2000				  // dummy 2Khz (1Step)
  }else if(nNowState.val==2)
  {
    sys0=nBand2.val-2000				  // dummy 2Khz (1Step)
  }else if(nNowState.val==3)
  {
    sys0=nBand3.val-2000				  // dummy 2Khz (1Step)
  }
  print sys0									//Start Frequency
  printh FF										//MAGIC
  printh FF										//MAGIC
  printh 73										//ETX
  nNowState.val+=100
  nRecvCount.val=3
}
if(nNowState.val>100)
{
  if(pm.sh.txt!="J")
  {
    nRecvCount.val--                // default is to run the scan 3x for each band
    sys2=0
    for(sys0=1;sys0<120;sys0++)     //sys0 is x position on graph. There are 120 values
    {
      substr pm.sh.txt,sTemp0.txt,sys0*2,2      // pull off next 2 bytes of data and place them in sTemp0.txt (hex characters)
      covx sTemp0.txt,sys1,2,2                  // Convert the hex characters into a 2 byte hex integer (i.e. 0x35, 0xff, etc) in sys1
      //if(sys2>sys1)	//
      sys2=sys1-sys2                            // apply offset to sys1 to get sys2
      if(sys2<0)                                // keeps sys2 between 0 and 50
      {
        sys2=0
      }
      if(sys2>50)
      {
        sys2=50
      }
      nTemp0.val=sys2/2                         // Divide offset sys2 by 2.  This is probably being done to scale to the size of the graph
      if(nNowState.val==101)	//Band1
      {
        nTemp0.val=25-nTemp0.val                // Since nTemp0.val is being used as the Y height (magnitude) of the scale, need to offset for each scale
                                                // each scale is 25 hight (hence the divide by 2) and the bottom is 60 appart
      }else if(nNowState.val==102)	//Band2
      {
        nTemp0.val=85-nTemp0.val
      }else if(nNowState.val==103)	//Band3
      {
        nTemp0.val=145-nTemp0.val
      }
      //fill sys0*2,nTemp0.val,2,sys2,YELLOW//1500+sys1*2046
      fill sys0*2,nTemp0.val,2,sys2,YELLOW//1500+sys1*2046    //sys0*2 is x offset where each bar is 2 wide on x
                                                              //nTemp0 is the top of the bar, 2 is width
                                                              //sys2 is the height, but really the bottom. nTemp0.val is the height thinking top down
      if(sys1>nADCDisVal.val)	//maximum adc dccharget         //Here is where sys2 is adjusted by the ADC discharge constant. Default is 6
                                                              //So if sys1(remember this is picked out of the ADC data returned by the DSP), is greater than this
                                                              //ADC discharge, we now set the offset (sys2) = value just read - the discharge rate.
                                                              //This has the effect of reducing the next value. Effectively damping the effects of spikes.
                                                              //This is because it takes time for the ADC to discharge its value
      {
        sys2=sys1-nADCDisVal.val
      }
      //sys2=sys1*90	//80%
      //sys2/=100
    }
    if(nNowState.val==101)	//Band1
    {
      if(nRecvCount.val<1)	//Next Band
      {
        nNowState.val=2
      }
    }else if(nNowState.val==102)	//Band2
    {
      if(nRecvCount.val<1)	//Next Band
      {
        nNowState.val=3
      }
    }else if(nNowState.val==103)	//Band3
    {
      if(nRecvCount.val<1)	//Finish
      {
        nNowState.val=99
      }
    }
    pm.sh.txt="J"
  }
}
