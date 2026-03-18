if(pm.sp.txt!="J")
{
  if(qInfo.picc==0)
  {
    qInfo.picc=1
  }
  if(vDecodeVisible.val==1)
  {
    vis tDecode1,0
    vDecodeVisible.val=0
  }
  sNewMax.txt=""
  sys2=0
  sys1=0
  nTemp0.val=0
  for(sys0=0;sys0<62;sys0++)
  {
    substr pm.sp.txt,sTemp0.txt,sys0*2,2
    covx sTemp0.txt,sys2,2,2
    sys2/=2
    if(sys1<sys2)
    {
      sys1=sys2
      nTemp0.val=sys0
    }
    if(sys2<0)
    {
      sys2=0
    }
    if(sys2>70)
    {
      sys2=70
    }
    substr sMax.txt,sTemp1.txt,sys0*2,2
    covx sTemp1.txt,nTemp1.val,2,2
    if(nTemp1.val<sys2)
    {
      nTemp1.val=sys2
    }else
    {
      nTemp1.val*=9
      nTemp3.val=sys2*1
      nTemp1.val+=nTemp3.val
      nTemp1.val/=10
    }
    covx nTemp1.val,sTemp1.txt,2,2
    substr sTemp1.txt,sTemp1.txt,2,2
    sNewMax.txt+=sTemp1.txt
    if(sys0<18)
    {
      if(sys2>52)
      {
        sys2=52
      }
      if(nTemp1.val>52)
      {
        nTemp1.val=52
      }
      fill sys0*2+1,238-nTemp1.val,2,nTemp1.val,1342	//1500+sys1*2046
      fill sys0*2+1,238-sys2,2,sys2,57343	//1500+sys1*2046
      fill sys0*2+1,186,2,52-nTemp1.val,7		//1500+sys1*2046
    }else
    {
      fill sys0*2+1,238-nTemp1.val,2,nTemp1.val,1342	//1500+sys1*2046
      fill sys0*2+1,238-sys2,2,sys2,57343	//1500+sys1*2046
      fill sys0*2+1,168,2,70-nTemp1.val,7		//1500+sys1*2046
    }
    //if(sys1>nADCDisVal.val)					//maximum adc dccharget
    //{
    //  sys2=sys1-nADCDisVal.val
    //}
    //sys2=sys1*90	//80%
    //sys2/=100
  }
  sMax.txt=sNewMax.txt
  if(sys1>50)
  {
    sys1=63488
  }else if(sys1>40)
  {
    sys1=64528
  }else if(sys1>30)
  {
    sys1=58584
  }else if(sys1>20)
  {
    sys1=39566
  }else if(sys1>10)
  {
    sys1=33549
  }else
  {
    sys1=31727
  }
  //nTemp0.val=nTemp0.val*47
  //nTemp0.val=nTemp0.val+30
  nTemp0.val=nTemp0.val*50
  nTemp0.val=nTemp0.val+50
  cov nTemp0.val,sTemp0.txt,0
  //xstr 1,170,90,18,0,WHITE,10565,0,1,1,sTemp0.txt
  xstr 1,170,37,18,0,sys1,7,2,1,1,sTemp0.txt
  pm.sp.txt="J"
}
if(pm.sb.txt!="^")
{
  if(vDecodeVisible.val==0)
  {
    vis tDecode1,1
    vDecodeVisible.val=1
  }
  strlen tDecode1.txt,sys0
  if(sys0>22)
  {
    substr tDecode1.txt,tDecode1.txt,1,sys0-1
  }
  tDecode1.txt=tDecode1.txt+pm.sb.txt
  pm.sb.txt="^"
}
