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

//#include"PWM.h"

//#ifndef ADC_H_
//#include"ADC.h"
//#endif

#include"GPIO.h"

#ifndef UART_H_
#include"UART.h"
#endif

//#ifndef QEI_H_
//#include "QEI.h"
//#endif

// #include"LCD.h"

// #include"utils.h"

//#ifndef TIMER_H_
//#include"timer.h"
//#endif

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

const int step_seq[6] = {0x000000A0, 0x00000080, 0x000000C0, 0x00000040, 0x00000060, 0x00000020} ;

extern unsigned long h_us_bldc_counter ;

/* Set RPM */
int RPM = 480 ;

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

//    float set_duty = 0.2 ;

//    M0PWM4_init(PWM_FRE);       /* PWM is used as it triggers the ADC */
//    M0PWM2_init(PWM_FRE);

//    M0PWM5_init(PWM_FRE);
//    M0PWM4_set(set_duty);
//    M0PWM2_set(set_duty);

//    M0PWM5_set(set_duty);

//    ADC_0_SS_3_INIT() ;

//    ADC_0_SS_0_INIT();

//    ADC_0_SS_1_INIT();

//    ADC_1_SS_1_INIT();

    int DIR = -1 ;

    while(1)
    {
        if ( h_us_bldc_counter > (250000/RPM) )
        {
            h_us_bldc_counter = 0 ;

            sequence = sequence + DIR;
            if( sequence > 5 )
            {
                sequence = 0 ;
            }
            else if( sequence < 0 )
            {
                sequence = 5 ;
            }

        }

        GPIO_PORTB_DATA_R = step_seq[sequence] ;

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
