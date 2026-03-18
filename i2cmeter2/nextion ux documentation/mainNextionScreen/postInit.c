pm.cm.val=99 // causes timer to update the swr/pwr display
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
