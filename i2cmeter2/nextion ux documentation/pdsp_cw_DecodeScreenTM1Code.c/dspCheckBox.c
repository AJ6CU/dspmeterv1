randset 5,255
nMyAddr.val=rand
//Send
pm.vn.val=-1
pm.vx.val=0
printh 59										//MAGIC
printh 58										//MAGIC
printh 68										//MAGIC
prints 74,1									//Command : LOOP BACK
prints nMyAddr.val,1				//Loop Sender :
sys0=50+cSmeterToUart.val		//SMeterToUart
prints sys0,1									//Loop Command1 : Command Type / 95: Spectrum Mode
prints 0x6A,1								//Loop Command2 : Command Value / 0x6A to DSP
sys0=nMyAddr.val+sys0+0x6A
sys0=sys0%256
prints sys0,1										//Loop Command3 : Command Value / CheckSum
printh FF										//MAGIC
printh FF										//MAGIC
printh 73										//ETX
