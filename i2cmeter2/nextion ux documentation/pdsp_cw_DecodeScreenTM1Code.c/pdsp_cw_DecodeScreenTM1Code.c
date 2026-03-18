if (pm.sp.txt != "J") {                         //If not "J", indicates buffer to be processed, J=74 or 4A
  sys1 = nDecodeFreq.val / 50                   // example = 800/50 = 16
  sys1 = sys1 + 1 
  vSelectMin.val = sys1 - 1                     //16
  vSelectMax.val = sys1 + 1                     //18
  sys1 = sys1* 4                                //17*4= 68 
  sys2 = 0 
  for (sys0 = 0; sys0 < 62; sys0++) {            //Signals mapped to constrained to 0-255. Above 255 is 255
    substr pm.sp.txt, sTemp0.txt, sys0 * 2, 2   //From sys0*2, take 2 characters and store in sTemp0.txt
    covx sTemp0.txt, sys2, 2, 2                 //Convert sTemp0.txt to number, 2 bytes, leading zeros 2
    sys2 /= 2                             // With ADC 0-255, further divide by 2 and max at 70 (i.e., 200/2 -> 70) 
    if (sys2 < 0) {
      sys2 = 0
    }
    if (sys2 > 70) {
      sys2 = 70
    }

    // fill is upper_left_of_x, upper_Left_of_y, width-of-x, height-of-y, color
    // So 110-sys2 defines left most x with height of s2 (value of fft)
    // the second fill just puts black above the yellow so that the background is black
    //
    
    fill sys0*4+9, 110-sys2, 4, sys2, YELLOW  //1500+sys1*2046                                              
    fill sys0*4+9, 39, 4, 71-sys2, BLACK    //1500+sys1*2046

    // this just puts a red vertical bar at plus/minus one slot (there are 62)
    // current freq target (decoded)

    if (sys0 > vSelectMin.val) {            //only 17 qualifies
      if (sys0 < vSelectMax.val) {
        line sys1, 40, sys1, 109, RED       //68 first line 
        line sys1+4, 40, sys1+4, 109, RED   //72 second line
      }
    }
  }
  pm.sp.txt = "J"                                   //Reset flag to indicated all spectrum values processed

} else if (pm.sb.txt != "^") {                      //pm.sb.txt contains decoded cw. 
                                                    //if not "^" then there are chars to print
    //
    //most of the complexity of the following code is just to deal with adding character to display
    //that does not scroll itself.
    //Basically, all we reall want to do is concatenate pm.sb.txt to the end of the text and have
    //the display widget deal with everything
    //

    if (vLineIndex.val == 0) {                      
      tDecode1.txt = tDecode1.txt + pm.sb.txt 
      strlen tDecode1.txt, sys0 
      if (sys0 > 23) {
        vLineIndex.val = 1
      }
    } else if (vLineIndex.val == 1) {
        tDecode2.txt = tDecode2.txt + pm.sb.txt 
        strlen tDecode2.txt, sys0 
        if (sys0 > 23) {
          vLineIndex.val = 2
        }
    } else if (vLineIndex.val == 2) {
        strlen tDecode3.txt, sys0 
        if (sys0 > 23){
          tDecode1.txt = tDecode2.txt
          tDecode2.txt = tDecode3.txt
          tDecode3.txt = ""
        } 
        tDecode3.txt = tDecode3.txt + pm.sb.txt
    }
  pm.sb.txt = "^"                             // reset pm.sb.txt to '^' to indicate ccw chars have been printed
} else if (vReadStep.val == 0) {              // vReadStep.val indicates whether we have read the DSP config
                                              // from EEPROM. It is initialized to 0 by UX. This forces the EEPROM
                                              // to be read once. Afterwards, set to 0 indicating the data has
                                              // been read
  vReadStep.val = 1 
  pm.vv.val = -1                              // These two statements clear out the Spectrum and CW Buffers
  pm.vg.val = 0

  //Read Configuration from DSP
  //The command comes back in a pm.vv.val, followed by pm.vg.val=0x6A
  //3 bytes:
  //1: DSP state - 94=None, 95=Spectrum, otherize cwDecodeHZ =100+cwDecodeHz
  //2: SmeterToUART 0=0ff, 1=0n
  //3: High limit (h0)
  randset 5,255                               //Sets random number generator to generate a number between 5 and 255
                                              //Not clear what function this provides as this is thrown away
                                              //by the DSP function when the command goes thru loopback
  nMyAddr.val = rand
  printh 59               //MAGIC
  printh 58               //MAGIC
  printh 68               //MAGIC
  prints 74,1             //Command : LOOP BACK
  prints nMyAddr.val,1    //Loop Sender :
  prints 2,1              //Loop Command1 : Command Type / 1~5: Read Configuration
  prints 0x6A,1           //Loop Command2 : Command Value / 0x6A to DSP
  sys0 = nMyAddr.val + 2 + 0x6A  //Byte0 + Byte1 + Byte2 % 256 = Checksum
  sys0 = sys0 % 256 
  prints sys0,1                //Loop Command3 : Command Value / CheckSum
  printh FF               //MAGIC
  printh FF               //MAGIC
  printh 73               //ETX
  
} else if (vReadStep.val == 1) {            //vReadStep.val==1 indicates we requested the data from EEPROM
                                            //And now will process it

  if (pm.vg.val == 0x6A)  //Response from DSP
  {
    vReadStep.val = 2                       //Set state to 2 indicating we got valid data 
    sys0 = pm.vv.val& 0xFF                  //Least significant byte indiates the high value of the Spectrum
    sys1 = pm.vv.val >> 8 
    sys1 = sys1& 0xFF                       //sys1 holds whether the DSP is enabled
    sys2 = pm.vv.val >> 16 
    sys2 = sys2 & 0xFF                      //sys2 now holds the state of the DSP (none, FFT,CW)                                                                                                               if (sys0 > 100){ sys0 = 100 } n1.val = sys0
    sys0 = sys0 / 10 
    h0.val = sys0                           //Normalize to 0-10
    
    if (sys1 == 1) {
      cSmeterToUart.val = 1
    }
    else {
      cSmeterToUart.val = 0
    }

    if (sys2 == 95) {           //95 indicates in Spectrum/FFT mode
      //Little weird using two flags for same thing. Guess both rFFT and rMorse = 0 means nothing is going on
      //rFFT=1 indicates we are in FFT mode
      //rMorse=0 indicates CW mode is off
      //
      rFFT.val = 1 
      rMorse.val = 0         
    } else if (sys2 >= 100) {     //Get the tone value for the slider. Not really a cw sidereal tone, just a freq offset
                                  //Note that the third byte does double duty by having a +100 offset
      if (sys2 < 146) {
        rFFT.val = 0 
        rMorse.val = 1 
        hCWTone.val = sys2 - 100
        //nDecodeFreq.val=sys2
        click nDecodeFreq,1
      }
    }
  pm.vv.val = -1                              // These two statements clear out the Spectrum and CW Buffers
  pm.vg.val = 0
  } 
}
