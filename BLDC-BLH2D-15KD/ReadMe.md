>#  BLDC Motor Control

* Driver
  * BLH2D-15KD
    * RPM Control
    * Brake Control
    * Torque Control
    * Acceleration, deceleration time control

* Torque Setting
    - Not Implemented (not required)

* RPM Setting
    - Using PWM
    - Feedback (not implemeted, not required)

* Hardware
  * TIVA-C: TM4C123GH6PM
  * BLH2D-15KD


* Peripherals Interfaced
  * GPIOs
  * PWM (RPM)
  * UART (GUI Commands)
  * SysTick

* GUI
  * Start
  * Instantaneous Stop (Brakes)
  * Decelerated Stop (No Brakes)
  * RPM Setting
  * Forward (Clockwise)
  * Reverse (Counter Clockwise)  
