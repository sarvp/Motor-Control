/*
 * BLDC.h
 *
 *  Created on: 07-Sep-2023
 *      Author: Sarvjit
 */

#ifndef BLDC_H_
#define BLDC_H_





#endif /* BLDC_H_ */

//#include <stdint.h>

//#include <string.h>

//#include <stdlib.h>

#include "D:/ti/TivaWare_C_Series-2.2.0.295/TivaWare_C_Series-2.2.0.295/inc/tm4c123gh6pm.h"

#define START 0x00000020

#define BRAKE 0x00000010

#define DIR 0x00000008

#define M0 0x00000004

#define M1 0x00000002

#define ALMRST 0x00000001


void BLDC_INIT(int mode);

void Inst_Stop();

void Dec_Stop();

void Start();

void Brake();

void Run_FW();

void Run_RV();

void Change_DIR(int dir);

void set_Mode(int mode);
