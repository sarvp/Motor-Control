/*
 * BLDC.c
 *
 *  Created on: 07-Sep-2023
 *      Author: Sarvjit
 */

/*
 * All pins have logically inverted operation (Active LOW)
 * when corresponding pin is LOW, it is said to be ACTIVE
 *
 * (M2 is DIR pin)
 *
 * M2       M1      M0      Operation Data
 * OFF      OFF     OFF             0               Speed control through external setting device/ PWM
 * OFF      OFF     ON              1               Speed control - VR1
 * OFF      ON      OFF             2               Digital
 * OFF      ON      ON              3
 * ON       OFF     OFF             4
 * ON       OFF     ON              5
 * ON       ON      OFF             6
 * ON       ON      ON              7
 *
 * */
#include"BLDC.h"

#ifndef GPIO_H_
#include"GPIO.h"
#endif

#ifndef PWM_H_
#include"PWM.h"
#endif

void BLDC_INIT(int mode)
{
    GPIOB_INIT();
    set_Mode(mode);
    GPIO_PORTB_DATA_R |= (START | BRAKE);
}

void Inst_Stop()
{
//    GPIO_PORTB_DATA_R &= ~ (START)
    GPIO_PORTB_DATA_R |= (BRAKE);
    M0PWM4_stop();
    M0PWM5_stop();
}

void Dec_Stop()
{
    GPIO_PORTB_DATA_R |= (START);
    M0PWM4_stop();
    M0PWM5_stop();
}

void Start()
{
    GPIO_PORTB_DATA_R &= ~ (START | BRAKE);
    M0PWM4_start();
    M0PWM5_start();
}

void Brake()
{
    GPIO_PORTB_DATA_R |= (START | BRAKE);
    M0PWM4_stop();
    M0PWM5_stop();
}

void Run_FW()
{
    GPIO_PORTB_DATA_R &= ~ (START | BRAKE | DIR);
    M0PWM4_start();
    M0PWM5_start();
}

void Run_RV()
{
    GPIO_PORTB_DATA_R &= ~ (START | BRAKE);
    GPIO_PORTB_DATA_R |= (DIR);
    M0PWM4_start();
    M0PWM5_start();
}

void Change_DIR(int dir)
{
    Dec_Stop();
    if(dir)
    {
        GPIO_PORTB_DATA_R &= ~ (DIR) ;
    }
    else
    {
        GPIO_PORTB_DATA_R |= (DIR) ;
    }
//    GPIO_PORTB_DATA_R = ~ (dir << 3) ;
    Start();
}

void set_Mode(int mode)
{
    switch(mode)
    {
    case 0:
        GPIO_PORTB_DATA_R |=  (M0 | M1) ;
        break;

    case 1:
        GPIO_PORTB_DATA_R &= ~ (M0) ;
        GPIO_PORTB_DATA_R |=  (M1) ;
        break;

    case 2:
        GPIO_PORTB_DATA_R &= ~ (M1) ;
        GPIO_PORTB_DATA_R |=  (M0) ;
        break;

    case 3:
        GPIO_PORTB_DATA_R &= ~ (M0 | M1) ;
        break;

    case 4:
        break;

    case 5:
        break;

    case 6:
        break;


    case 7:
        break;

    }

}
