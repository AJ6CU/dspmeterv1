sys2=0
if(nBefore1.val!=nBand1.val)
{
  sys2++
}
if(nBefore2.val!=nBand2.val)
{
  sys2++
}
if(nBefore3.val!=nBand3.val)
{
  sys2++
}
if(nBeforePos.val!=h1.val)
{
  sys2++
}
if(sys2>0)
{
  nBefore1.val=nBand1.val
  nBefore2.val=nBand2.val
  nBefore3.val=nBand3.val
  nBeforePos.val=h1.val
  //BAND1
  fill 1,51,245,9,10565
  sys0=h1.val-2
  sys0=sys0*1000
  sys1=sys0+nBand1.val
  n0.val=sys1
  fill h1.val,52,3,8,64520
  //BAND2
  fill 1,111,245,9,10565
  sys1=sys0+nBand2.val
  n1.val=sys1
  fill h1.val,112,3,8,64520
  sys1=sys0+nBand3.val
  n2.val=sys1
}
if(nBeforeBand.val!=nBand.val)
{
  sys2++
  nBeforeBand.val=nBand.val
  n0.bco=8
  n1.bco=8
  n2.bco=8
  n0.pco=54970
  n1.pco=54970
  n2.pco=54970
  if(nBeforeBand.val==1)
  {
    n0.bco=64520
    n0.pco=BLACK
  }else if(nBeforeBand.val==2)
  {
    n1.bco=64520
    n1.pco=BLACK
  }else if(nBeforeBand.val==3)
  {
    n2.bco=64520
    n2.pco=BLACK
  }
}
if(sys2>0)
{
  bBand0.txt="Exit"
  bBand1.txt="Exit"
  bBand2.txt="Exit"
  if(nBand.val==1)
  {
    bBand0.txt="Apply"
  }
  if(nBand.val==2)
  {
    bBand1.txt="Apply"
  }
  if(nBand.val==3)
  {
    bBand2.txt="Apply"
  }
  if(nNowState.val==99)
  {
    sys0=0
    if(nBand.val==1)
    {
      sys0=n0.val
    }else if(nBand.val==2)
    {
      sys0=n1.val
    }else if(nBand.val==3)
    {
      sys0=n2.val
    }
    if(sys0>350000)
    {
      if(sys0<57000000)
      {
        printh 59										//MAGIC
        printh 58										//MAGIC
        printh 68										//MAGIC
        prints 2,1									//Set Frequency
        print sys0									//VALUE
        printh FF										//MAGIC
        printh FF										//MAGIC
        printh 73										//ETX
      }
    }
  }
}
