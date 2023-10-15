>#  Various Motor Control mini Projects
>
>* Some of them are part of courses and some are from MTech major project

>## Stepper Motor Drive

* Drive
  
  * Full Step Drive - Timer / SysTick
  * Half Step Drive - Timer / SysTick
  * Micro Step Drive - PWM Vector control
* Control
  * Open Loop
    * RPM - set by Timer / SysTick
  * Closed Loop
    * Torque - set by adjusting phase current using digital comparators of ADC module and signal conditioning circuits - ON/OFF control
    * Position - Incremental Quadrature Rotary Encoder Interface

>##  BLDC Drive

* BLH2D-15KD Motor Driver
  * BLDC control using the motor drive from the motor manufacturer.
    * Direction change
    * Stop with brakes
    * Stop without brakes
    * Speed control
    * Torque control
  
* Open Loop Drive in full bridge mode (using H-bridge L298N)
  * 6-step drive without any feedback

># Intruder Detection System
* Smart Password Protected Mat
* [ReadMe](https://github.com/sarvp/All-Projects/blob/main/ReadMe-Intruder%20Detection%20Mat.md) 
* [Presentation Slides](https://github.com/sarvp/All-Projects/blob/main/Intruder%20Detection%20Mat.pptx)

># Other Projects

### Selective Laser Sintering Additive Manufacturing Machine (MTech Major Project) (June 23-Present)
* Key Terms: Laser-Galvo, Scan-head, Scan Card, Powder Hopping and Recoating, Build Chamber
* This 3D printing machine will be designed with SLS Additive Manufacturing process which includes various subsystems like Optics and Laser, Build Chamber, Mechanical Assembly, etc. 
* The work emphasizes developing software for each subsystem controller to work in fail-safe mode considering all interlocks in the additive manufacturing process.
  
### Embedded Software/Firmware for 3D Printer (MAR 23-APR 23)
  * Key Terms: Stepper motor drivers, Auto-homing, parallel drive
  
* Developed and implemented firmware for a 3D printer using the ARM Cortex-M4 series microcontroller (TM4C123GH6PM) on the Code Composer Studio platform.
* Utilized hardware PWM to optimize motor control and achieve smoother movement of the XY table to enhance printing precision and reduce layer imperfections for complex models. 
* Designed and integrated auto-homing routines to automate the calibration process, minimizing the need for manual adjustments and reducing setup time.
  
### Digital Soil Testing Device	(BE Major Project)(OCT 18-MAR 19)   
* Key Terms: NPK-Detection, VIS Spectroscopy, Sensor Development
* Every solution with different concentrations has different behavior to the different wavelengths of light. 
* Using this principle with Beer-Lambert Law we can measure the percentage of light absorbed by the solution when applied to the different wavelengths of light in the visible spectrum and the percentage of N, P, and K in that solution can be found.

### Universal Remote	(FEB 18 –MAR 18)   
* Key Terms: IR code decoding, Save-n-Use & Training-mode
* Universal Remote is a device that is used to operate all the home appliances that are generally operated by standard IR remote.  
* Smartphone controls the device through Bluetooth connection. The app has frequently used remote buttons of all appliances which sends a unique code when pressed. Thus, the device on receiving code controls the appliances. 
* This Universal Remote can control TV, STB, A/C, DVD, Projector, Fan etc. We can also save the unique codes of various remotes using the training mode of Universal Remote.
