pm.vn.val=-1
pm.vx.val=0
//nStep.val=2000		//2Kh
//nADCCount.val=120	//MAX : 120
printh 59										//MAGIC
printh 58										//MAGIC
printh 68										//MAGIC
prints 15,1									//Command : Spectrum Option
prints 3,1									//Send Count (Scan Set Count)
printh 00										//ADC Value Offset (Spectrum Value = ADC Value - (Offset * 3)
prints 120,1								//ADC Scan Count (120 - MAX Value)
sys0=2000/20
prints sys0,1								//Increase Step * 20 (ex 100 = 2Khz Step Scan)
printh FF										//MAGIC
printh FF										//MAGIC
printh 73										//ETX
//tm0.en=1
