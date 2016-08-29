#ifndef _ROBO_SENSORS_H_
#define _ROBO_SENSORS_H_

// Nota: 
// - O sensor de infravermelho tem valor 0 (LOW) quando detecta um obstaculo
// - Criar variavel para armazenar leitura de preto, e poder calibrar a leitura
// do sensor

#include <Arduino.h>
#include "./robo_sensors_typedefs.h"

/*******************************************************************************
 *
 * DEFINES
 *
******************************************************************************/

#define IR_FOUND_OBJECT LOW
#define IR_NOTHING_FOUND HIGH

#define LINE_FR_PIN A0
#define LINE_FL_PIN A1
#define LINE_BR_PIN A2
#define LINE_BL_PIN A3
#define IR_PIN 4

/*******************************************************************************
 *
 * FUNCTIONS
 *
 ******************************************************************************/

void SENSORS_Start(void);

void SENSORS_CheckAllSensors(sensors_t* get_value);

void SENSORS_CalibrateLineSensor(int* min, int* max);

#endif
