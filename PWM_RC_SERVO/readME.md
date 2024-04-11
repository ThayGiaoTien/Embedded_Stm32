#CAUTION: You have to do the test by yourself. 
- The freq that we need to provide for Servo is 50Hz, so i choocse fSTM32 = 3MHz, and AAR = 60000.
- The dutyCycle by testing is 1950/60000 - 8000/60000  = 0.316 - 0.133
- Setup PWM pin using timers in PWN Generation mode. We have to invoke function to start couting.
- Create function to calculate compare output value based on theta angle of the servo:
    compValue= (fAngle/(fAngleMax-fAngleMin)*(fCompValueMax-fCompValueMin)) +fCompValueMin;
