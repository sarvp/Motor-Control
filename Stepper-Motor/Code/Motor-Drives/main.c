/*
 * L298N H Bridge Driver using PWM
 * Sarvjit Ajit Patil 20862
 * Date : 08/08/2023
 * Microstepping
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

#ifndef STEPPER_H_
#include"stepper.h"
#endif

//#define DEBUG

// #include"ultrasonic.h"

void delayMs(int n);

#define PWM_FRE 20000

extern char RX1_BUF[200], RX0_BUF[200], RX1_CMD[200] ;

extern int rx0_command_flag ;

extern unsigned long ms_counter, h_us_cnt ;

extern int dir, done_flag ;

volatile int ADC_Voltage, ADC_Current ;

extern int ADC_Sel_cnt ;

float pos = 0 ;
long cur_cnt = 0 ;
char str[100] ;

//const int half_step_seq[8] = {0x00000080, 0x000000C0, 0x00000040, 0x00000060, 0x00000020, 0x00000030, 0x00000010, 0x00000090} ;
const int half_step_seq[8] = {0x00000080, 0x000000A0, 0x00000020, 0x00000060, 0x00000040, 0x00000050, 0x00000010, 0x00000090} ;
const int full_step_seq[4] = {0xA0, 0x60, 0x50, 0x90 } ;

extern unsigned long h_us_stepper_counter ;

extern void PWM_Start(void);

/* Set Phase currents (in Amps) */

#define SET_CURR_A 1.5

#define SET_CURR_B 1.5

/* Set RPM */
int RPM = 150 ;

float set_Curr_A_ADC = ((SET_CURR_A * 4095) / 3.3);

float set_Curr_B_ADC = ((SET_CURR_B * 4095) / 3.3);

int I_Set = 0 ;

volatile int sequence = 0;

float Voltage, Current, R_RPM, Position;

/* Set sampling time Ts for PWM */
#define Ts 500

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

    QEI_0_INIT();

    /* Init PWM for micro-stepping */

    //    float set_duty = 0.5 ;
//    PWM_0_SYNC() ;

    M0PWM2_init(Ts);
    M0PWM3_init(Ts);       /* PWM is used as it triggers the ADC */
    M0PWM4_init(Ts);
    M0PWM5_init(Ts);

    PWM_Start();

//    M0PWM5_init(PWM_FRE);
//    M0PWM4_set(set_duty);
//    M0PWM2_set(set_duty);
    PWM_0_SYNC();
//
//    update_PWM(45,2);


//    M0PWM5_set(set_duty);

//    ADC_0_SS_3_INIT() ;

//    ADC_0_SS_0_INIT();

//    ADC_0_SS_1_INIT();

//    ADC_1_SS_1_INIT();

    int DIR = 1 ;

    for( int i = 0; i < 360 ; i++)
    {
        update_PWM(i, 2) ;
    }

    while(1)
    {
        if ( rx0_command_flag )
        {
            I_Set = atoi(RX0_BUF);

            update_PWM(I_Set, 2) ;
            RPM = I_Set ;

//            delayMs(20) ;
//
            sprintf(str,"Set Position = %d.%d\n", I_Set, 0);
            uart0_send_str(str);

            for(int i = 0; i< 318000; i++);

            Position = ( QEI0_POS_R * 360 ) / ( 8192 ) ;
            Position = Position * 1000 ;

            int P_i = (int)(Position) / 1000;
            int P_f = (int) (Position) % 1000 ;
            sprintf(str,"Read Position = %d.%d\n", P_i, P_f);
            uart0_send_str(str);

            rx0_command_flag = 0 ;

        }

        /* Full Step revolution */
        for(int i = 0; i < 360; i++)
        {
            update_PWM(i,2);
        }

        /* Half Step/ Full Step */ /*Dont uncomment if want to use General Purpose Timer instead of SysTick*/
//        if ( h_us_stepper_counter > (15000/RPM) )
//        {
//            h_us_stepper_counter = 0 ;
//
//            sequence = sequence + DIR;
//            if( sequence > 7 )
//            {
//                sequence = 0 ;
//            }
//            else if( sequence < 0 )
//            {
//                sequence = 7 ;
//            }
//
//        }
//
//        GPIO_PORTB_DATA_R = half_step_seq[sequence] ;

        /* Display Parameters */
//        if(h_us_cnt > 10000)
//        {
//            h_us_cnt = 0 ;
//            float rpm = (100 * ( (QEI0_SPEED_R) ) * 60) / (2048 * 4);
////            rpm = rpm * 1000 ;
//
////            int R_i = (int)(rpm) / 1000;
////            int R_f = (int) (rpm) % 1000 ;
////            sprintf(str,"RPM = %d.%d\n", R_i, R_f);
//            sprintf(str,"RPM = %d\n", (int)rpm);
////            sprintf(str,"RPM = %ld\n", QEI0_SPEED_R);
//            uart0_send_str(str);
//        }
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
