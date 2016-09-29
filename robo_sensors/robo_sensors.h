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

#define LINE_FR_PIN A2
#define LINE_FL_PIN A3
#define LINE_BR_PIN A0
#define LINE_BL_PIN A1
#define IR_PIN 4
#define US_TRIGGER_PIN 3
#define US_ECHO_PIN 2

/*******************************************************************************
 *
 * FUNCTIONS
 *
 ******************************************************************************/

void StartSensors(void);

void CheckAllSensors(volatile sensors_t* get_value);

void CalibrateLineSensor(int* black, int* white);

#if ULTRASONIC
int ReadUltrasonicSensor(char trigg, char echo);
#endif

#endif
