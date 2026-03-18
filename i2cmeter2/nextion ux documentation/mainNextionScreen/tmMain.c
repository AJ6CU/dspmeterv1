//===================================
// Nextion LCD -> Process for MCU
//===================================
//===================================
//SEND COMMAND STX(3BYTE) + COMMAND + DATA (4byte) + ETX(3BYTE)
//===================================
if(rSendNeed.val==1)				//Check Need transsfer
{
  printh 59										//MAGIC
  printh 58										//MAGIC
  printh 68										//MAGIC
  prints rSendCommand.val,1	//MODE CHANGE
  print rSendData.val				//VALUE
  printh FF										//MAGIC
  printh FF										//MAGIC
  printh 73										//ETX
  rSendNeed.val=0
  if(rSendCommand.val==1)
  {
    //Hide Mode Buttons
    page px
  }else if(rSendCommand.val==17)
  {
    //Hide Tune Step Buttons
    page px
  }
}
//===================================
// Process for MCU -> Nextion LCD
//===================================
// Always display (Graphic or Text Mode)
//===================================
// Check condition for Frequency Shift display (CWL, CWU)
// if changed Current Frequency, Mode, sys2 = 1
sys2=0
// Current FREQ Display
if(pm.vc.val!=-1)
{
  if(nTemp4.val!=1)
  {
    //Save Last received Freq
    nLastFreq.val=pm.vc.val
    //if changed vfo, replace vlMainVFO Value
    //Display Hz
    nTemp0.val=pm.vc.val%1000
    cov nTemp0.val,txtFreqHz.txt,3
    //Display Khz
    pm.vc.val/=1000
    nTemp0.val=pm.vc.val%1000
    cov nTemp0.val,txtFreqKHz.txt,3
    //Display Mhz
    pm.vc.val/=1000
    cov pm.vc.val,txtFreqMHz.txt,0
    pm.vc.val=-1
    sys2=1
  }
}
//TX/RX Status
if(pm.ct.val!=-1)
{
  if(pm.ct.val==0)
  {
    //RX
    qInTX.picc=0
    vis swr,0
    vis pwr,0
    TxMode.val=0
    pswr.fwdPowerSave.val=0
    pswr.swrSave.val=10
    pswr.SWRBarSave.val=0
  }else
  {
    //TX
    qInTX.picc=1
    vis swr,1
    vis pwr,1
    TxMode.val=1
  }
  pm.ct.val=-1
}
//TX STOP Status
if(pm.cx.val!=-1)
{
  if(pm.cx.val==0)
  {
    //TX
    qTXStop.picc=0
  }else
  {
    //RX
    qTXStop.picc=1
  }
  pm.cx.val=-1
}
//Display Active A/B
if(pm.cv.val!=-1)
{
  if(pm.cv.val==0)
  {
    bVFOAB.txt="VFO.A"
  }else
  {
    bVFOAB.txt="VFO.B"
  }
  nActiveVFO.val=pm.cv.val
  pm.cv.val=-1
}
//Display Current Mode
if(pm.cc.val!=-1)
{
  //Save Last received Freq
  nLastMode.val=pm.cc.val
  if(pm.cc.val==2)
  {
    bMode.txt="LSB"
  }else if(pm.cc.val==3)
  {
    bMode.txt="USB"
  }else if(pm.cc.val==4)
  {
    bMode.txt="CWL"
  }else if(pm.cc.val==5)
  {
    bMode.txt="CWU"
  }
  pm.cc.val=-1
  sys2=1
}
//Display Dial Lock
if(pm.cl.val!=-1)
{
  if(pm.cl.val==0)
  {
    //UnLock
    qLock.picc=0
    //UnLock all Thouch area
    tsw 255,1
  }else
  {
    //Lock
    qLock.picc=1
    tsw 255,0
    tsw qLock,1
  }
  pm.cl.val=-1
}
//SDR Mode
if(pm.cj.val!=-1)
{
  if(pm.cj.val==0)
  {
    //RX
    bSDR.txt="SPK"
    bSDR.picc=0
  }else
  {
    //TX
    bSDR.txt="SDR"
    bSDR.picc=1
  }
  pm.cj.val=-1
}
//IFS Graph
if(pm.vi.val!=-1)
{
  //Display IFS Graph
  //Offset change, range -20000 ~ +20000 => 0 ~ 4000
  nIFS.val=pm.vi.val
  if(pm.vi.val<-2000)
  {
    pm.vi.val=-2000
  }else if(pm.vi.val>2000)
  {
    pm.vi.val=2000
  }
  pm.vi.val+=2000	//0~4000
  hIFS.val=pm.vi.val
  pm.vi.val=-1
  vis hIFS,1
}
//===========================================
//Display CW Options
//===========================================
if(pm.vt.val!=-1)
{
  nTone.val=pm.vt.val
  pm.vt.val=-1
  sys2=1
}
if(pm.ck.val!=-1)
{
  if(pm.ck.val==0)
  {
    tKey.txt="Straight"
  }else if(pm.ck.val==1)
  {
    tKey.txt="IAMBICA"
  }else if(pm.ck.val==2)
  {
    tKey.txt="IAMBICB"
  }
  tQKeyType.txt=tKey.txt
  pm.ck.val=-1
}
if(pm.vs.val!=-1)
{
  nWPM.val=1200/pm.vs.val
  nQWPM.val=nWPM.val
  pm.vs.val=-1
}
if(pm.vy.val!=-1)
{
  nDelay.val=pm.vy.val*10
  pm.vy.val=-1
}
if(pm.ve.val!=-1)
{
  nSDelay.val=pm.ve.val*2
  pm.ve.val=-1
}
//========================================
//Display Boot Message
//========================================
if(pm.cm.val==1)
{
  pm.cm.val=-1
  tCallSign.txt=pm.sc.txt
  tVersion.txt=pm.sv.txt
}
//===================================
// Select Graphic Mode / Text Mode
//===================================
if(pm.c0.val!=nDispStatus.val)
{
  if(pm.c0.val==1)	//Text Mode
  {
    vis t0,1
    vis t1,1
  }else
  {
    vis nCWNum,0
    vis tCWText,0
    vis t0,0
    vis t1,0
    vis bAction,0
    t1.txt=""
  }
  nDispStatus.val=pm.c0.val
}
//========================================
//Text Line Mode for compatible with Character LCD
//========================================
if(nDispStatus.val==1)
{
  //CW Text Mode Check
  if(pm.cy.val!=-1)
  {
    //CW Text Mode
    if(pm.cy.val==1)
    {
      vis nCWNum,1
      vis tCWText,1
    }else
    {
      //Normal Text Mode
      vis nCWNum,0
      vis tCWText,0
    }
    pm.cy.val=-1
  }
  if(pm.cw.val!=-1)
  {
    nCWNum.val=pm.cw.val
    pm.cw.val=-1
  }
  if(pm.sa.txt!="JJ")
  {
    tCWText.txt=pm.sa.txt
    pm.sa.txt="JJ"
  }
  if(pm.s0.txt!="JJ")
  {
    t0.txt=pm.s0.txt
    pm.s0.txt="JJ"
  }
  if(pm.s1.txt!="JJ")
  {
    t1.txt=pm.s1.txt
    pm.s1.txt="JJ"
    substr t1.txt,sTemp0.txt,0,4
    if(sTemp0.txt=="PTT-")
    {
      vis bAction,1
    }else
    {
      vis bAction,0
    }
  }
  //===========================================
  //ATT, IFS
  //===========================================
  //ATT Changing from Text Mode
  if(pm.vf.val!=-1)
  {
    hATT.val=pm.vf.val
    nATT.val=pm.vf.val
  }
  //IFS Changing from Text Mode
  if(pm.ci.val!=-1)
  {
    if(pm.ci.val==0)
    {
      vis hIFS,0
    }else
    {
      vis hIFS,1
    }
  }
}else
{
  //========================================
  //Graphic Mode
  //========================================
  nTemp0.val=-1
  nTemp1.val=-1
  //Display Other VFO
  if(nActiveVFO.val==0)
  {
    //Other VFO is B
    nTemp0.val=pm.vb.val
    nTemp1.val=pm.cb.val
  }else
  {
    //Other VFO is A
    nTemp0.val=pm.va.val
    nTemp1.val=pm.ca.val
  }
  if(nLastSubFreq.val!=nTemp0.val)
  {
    nLastSubFreq.val=nTemp0.val
    nSubFreq.val=nTemp0.val
  }
  //Other VFO is B
  if(nLastSubMode.val!=nTemp1.val)
  {
    nLastSubMode.val=nTemp1.val
    if(nTemp1.val==2)
    {
      tSubMode.txt="LSB"
    }else if(nTemp1.val==3)
    {
      tSubMode.txt="USB"
    }else if(nTemp1.val==4)
    {
      tSubMode.txt="CWL"
    }else if(nTemp1.val==5)
    {
      tSubMode.txt="CWU"
    }
  }
  //Draw Smeter
  if(pm.cp.val!=-1)
  {
    jSMeter.val=pm.cp.val
    //jSMeter.val=pm.cp.val*10
    pm.cp.val=-1
  }
  //Display tune step
  if(pm.cn.val!=-1)
  {
    if(pm.cn.val==1)
    {
      nTuneStep.val=pm.v1.val
    }else if(pm.cn.val==2)
    {
      nTuneStep.val=pm.v2.val
    }else if(pm.cn.val==3)
    {
      nTuneStep.val=pm.v3.val
    }else if(pm.cn.val==4)
    {
      nTuneStep.val=pm.v4.val
    }else if(pm.cn.val==5)
    {
      nTuneStep.val=pm.v5.val
    }
    pm.cn.val=-1
  }
  //Option Display
  //Split
  if(pm.cs.val!=-1)
  {
    if(pm.cs.val==0)
    {
      qSPL.picc=0
    }else
    {
      qSPL.picc=1
    }
    pm.cs.val=-1
  }
  //RIT
  if(pm.cr.val!=-1)
  {
    if(pm.cr.val==0)
    {
      qRIT.picc=0
    }else
    {
      qRIT.picc=1
    }
    pm.cr.val=-1
  }
  //===========================================
  //ATT, IFS
  //===========================================
  //ATT
  if(pm.vf.val!=-1)
  {
    if(pm.vf.val==0)
    {
      qATT.picc=0
    }else
    {
      qATT.picc=1
    }
    hATT.val=pm.vf.val
    nATT.val=pm.vf.val
    pm.vf.val=-1
  }
  //IFS
  if(pm.ci.val!=-1)
  {
    if(pm.ci.val==0)
    {
      qIFS.picc=0
      vis hIFS,0
    }else
    {
      qIFS.picc=1
      vis hIFS,1
    }
    pm.ci.val=-1
  }
}
//Frequency Shift display for CWL, CWU
if(sys2==1)
{
  //Changed Frequency or Mode
  if(pm.ch.val==1)				//Frequency Shiftdisplay
  {
    if(nLastMode.val==4)	//CWL
    {
      sys2=nLastFreq.val-nTone.val
      sys2+=pm.vh.val			//Find adjust frequency for cwl, cwu by user's configuration
    }else if(nLastMode.val==5)	//CWU
    {
      sys2=nLastFreq.val+nTone.val
      sys2+=pm.vh.val			//Find adjust frequency for cwl, cwu by user's configuration
    }else
    {
      sys2=nLastFreq.val
    }
  }
  if(sys2!=1)	//applied shift value
  {
    nTemp0.val=sys2%1000
    cov nTemp0.val,txtFreqHz.txt,3
    //Display Khz
    sys2/=1000
    nTemp0.val=sys2%1000
    cov nTemp0.val,txtFreqKHz.txt,3
    //Display Mhz
    sys2/=1000
    cov sys2,txtFreqMHz.txt,0
  }
  sys2=-1
}
