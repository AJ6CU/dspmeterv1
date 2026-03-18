pm.vv.val=-1      //Used to return command data. In this case the right 3 bytes contain EEPROM settings
                  //But also used in Screen Dim (10=off,11=on). "-1" indicates empty
pm.vg.val=0       //Used for a Command sent back by Loopback. 
                  //"0x6A" indicates that we have EEPROM Data from DSP. Actual data is in pm.vv.val
                  //74 indicates backlight command dim. If vv.val=10. off, 11=on
pm.sp.txt="J"     //Buffer for FFT values to plot.  "J" indicates none"
pm.sb.txt="^"     //Buffer for decoded morse code characters. "^" indicates none