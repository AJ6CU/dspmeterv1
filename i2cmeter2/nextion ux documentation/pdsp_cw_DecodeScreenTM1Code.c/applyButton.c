randset 5,255
nMyAddr.val=rand
//Send
pm.vv.val=-1
pm.vg.val=0
if(rFFT.val==1)	//Spctrum Mode
{
  sys1=95
}else if(rMorse.val==1)
{		//Morse Decode
sys1=nDecodeFreq.val-300
sys1/=50
sys1+=100										//Decode Morse 100~129
}else
{
sys1=94
}
printh 59										//MAGIC
printh 58										//MAGIC
printh 68										//MAGIC
prints 74,1									//Command : LOOP BACK
prints nMyAddr.val,1				//Loop Sender :
prints sys1,1								//Loop Command1 : Command Type / 100~129: Decode Morse
prints 0x6A,1								//Loop Command2 : Command Value / 0x6A to DSP
sys0=nMyAddr.val+sys1+0x6A
sys0=sys0%256
prints sys0,1								//Loop Command3 : Command Value / CheckSum
printh FF										//MAGIC
printh FF										//MAGIC
printh 73										//ETX
