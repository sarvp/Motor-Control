/*
 * L298N H Bridge Driver using PWM
 * Sarvjit Ajit Patil 20862
 * Date : 08/08/2023
 */



/*
 * main.c
 */
#include <stdio.h>

#include <stdint.h>

#include <string.h>

#include <stdlib.h>

#include "D:/ti/TivaWare_C_Series-2.2.0.295/TivaWare_C_Series-2.2.0.295/inc/tm4c123gh6pm.h"

#include"SysTick.h"

#include"PWM.h"

#ifndef ADC_H_
#include"ADC.h"
#endif

#include"GPIO.h"

#ifndef UART_H_
#include"UART.h"
#endif

#ifndef QEI_H_
#include "QEI.h"
#endif

// #include"LCD.h"

// #include"utils.h"

#ifndef TIMER_H_
#include"timer.h"
#endif

// #include"ultrasonic.h"

void delayMs(int n);

#define PWM_FRE 40000

extern char RX1_BUF[200], RX0_BUF[200], RX1_CMD[200] ;

extern int rx0_command_flag ;

extern unsigned long ms_counter ;

extern int dir, done_flag ;

volatile int ADC_Voltage, ADC_Current ;

extern int ADC_Sel_cnt ;

float pos = 0 ;
long cur_cnt = 0 ;
char str[100] ;

//const int half_step_seq[8] = {0x00000080, 0x000000C0, 0x00000040, 0x00000060, 0x00000020, 0x00000030, 0x00000010, 0x00000090} ;
const int half_step_seq[8] = {0x00000080, 0x000000A0, 0x00000020, 0x00000060, 0x00000040, 0x00000050, 0x00000010, 0x00000090} ;
const int full_step_seq[7] = {0xA0, 0x60, 0x50, 0x90, 0x50, 0x60, 0xA0 } ;

extern unsigned long h_us_stepper_counter ;

/* Set Phase currents (in Amps) */

#define SET_CURR_A 1.5

#define SET_CURR_B 1.5

/* Set RPM */
int RPM = 30 ;

float set_Curr_A_ADC = ((SET_CURR_A * 4095) / 3.3);

float set_Curr_B_ADC = ((SET_CURR_B * 4095) / 3.3);

int I_Set = 0 ;

volatile int sequence = 0;

int main(void)
{
    EnableInterrupts() ;

    Systick_init();
//    GPIOA_INIT();
    GPIOB_INIT();
//    GPIOC_INIT();
//    GPIOD_INIT();
//    GPIOE_INIT();
    GPIOF_INIT();

//    TIMER0_INIT();

    uart0_init();
//    uart1_init();

    uart0_send_str("Welcome to UART0\n");
    uart0_send_str("This is for debugging.\n");

//    QEI_0_INIT();

    float set_duty = 0.2 ;
    M0PWM4_init(PWM_FRE);       /* PWM is used as it triggers the ADC */
//    M0PWM2_init(PWM_FRE);

//    M0PWM5_init(PWM_FRE);
    M0PWM4_set(set_duty);
//    M0PWM2_set(set_duty);

//    M0PWM5_set(set_duty);

//    ADC_0_SS_3_INIT() ;

//    ADC_0_SS_0_INIT();

    ADC_0_SS_1_INIT();

    ADC_1_SS_1_INIT();

    int DIR = -1 ;

    while(1)
    {
        if ( rx0_command_flag )
        {
            I_Set = atoi(RX0_BUF);

            int set_Curr_ADC = ((I_Set * 4.095) / 3.3);

            ADC0_DCCMP1_R   = ((int)set_Curr_ADC<<16);    // Set high region threshold for DC1
            ADC1_DCCMP2_R   = ((int)set_Curr_ADC<<16);    // Set high region threshold for DC2

//            sprintf(str,"Set Current = %d mA\n", I_Set);
//            uart0_send_str(str);
            rx0_command_flag = 0 ;

        }

        if ( h_us_stepper_counter > (15000/RPM) )
        {
            h_us_stepper_counter = 0 ;

            sequence = sequence + DIR;
            if( sequence > 7 )
            {
                sequence = 0 ;
            }
            else if( sequence < 0 )
            {
                sequence = 7 ;
            }

        }

        GPIO_PORTB_DATA_R = half_step_seq[sequence] ;

        WaitForInterrupt();

    }
}

void delayMs( int n )
{
    int i, j ;

    for(i = 0; i < n ; i ++)
    {
        for(j = 0; j < 2000; j++);
    }
}
