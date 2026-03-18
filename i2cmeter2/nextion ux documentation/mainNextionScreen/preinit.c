if(TxMode.val==0)
{
  vis swr,0
  vis pwr,0
  pswr.fwdPowerSave.val=0
  pswr.swrSave.val=10
  pswr.SWRBarSave.val=0
}else
{
  vis swr,1
  vis pwr,1
}

//Hide Mode Buttons
vis bLSB,0
vis bUSB,0
vis bCWL,0
vis bCWU,0

//Hide IFS
vis hIFS,qIFS.picc //found bug by VE1BWV

//Hide Text Line for compatiable with Character LCD
vis t0,0
vis t1,0
vis nCWNum,0
vis tCWText,0
vis bAction,0

//Added Version 1.1
vis bStep1,0
vis bStep2,0
vis bStep3,0
vis bStep4,0
vis bStep5,0
pm.vv.val=-1
pm.vg.val=0
pm.sp.txt="J"
pm.sb.txt="^"
vis tDecode1,0
vDecodeVisible.val=0

if(nQuickMenu.val==1)
{
  //CW Menu
  qKey.picc=1
  vis nQWPM,1
  vis tQKeyType,1
  vis b0,1
  vis b1,1
  vis b2,1
  vis hATT,0
  vis hIFS,0
  vis nATT,0
  vis nIFS,0
}else
{
  //Normal
  qKey.picc=0
  vis nQWPM,0
  vis tQKeyType,0
  vis b0,0
  vis b1,0
  vis b2,0
  vis hATT,1
  vis hIFS,qIFS.picc
  vis nATT,1
  vis nIFS,1
}
