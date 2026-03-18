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
    nRecvCount.val--
    sys2=0
    for(sys0=1;sys0<120;sys0++)
    {
      substr pm.sh.txt,sTemp0.txt,sys0*2,2
      covx sTemp0.txt,sys1,2,2
      //if(sys2>sys1)	//
      sys2=sys1-sys2
      if(sys2<0)
      {
        sys2=0
      }
      if(sys2>50)
      {
        sys2=50
      }
      nTemp0.val=sys2/2
      if(nNowState.val==101)	//Band1
      {
        nTemp0.val=25-nTemp0.val
      }else if(nNowState.val==102)	//Band2
      {
        nTemp0.val=85-nTemp0.val
      }else if(nNowState.val==103)	//Band3
      {
        nTemp0.val=145-nTemp0.val
      }
      //fill sys0*2,nTemp0.val,2,sys2,YELLOW//1500+sys1*2046
      fill sys0*2,nTemp0.val,2,sys2,YELLOW//1500+sys1*2046
      if(sys1>nADCDisVal.val)	//maximum adc dccharget
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
