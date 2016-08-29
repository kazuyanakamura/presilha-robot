#ifndef _ROBO_MOV_H_
#define _ROBO_MOV_H_

/*
 * Notas:
 *   -As funcoes permitem ativar e desativar o giro do motor, e controlar o sentido
 * para onde as rodas giram, mas nao a duracao que elas permanecem girando
 *
 */

#include <Arduino.h>

/*******************************************************************************
 *
 * DEFINES
 *
******************************************************************************/

// Definicoes sobre os pinos que ativam as rodas
#define LEFT_WHEEL_PIN_1 1
#define LEFT_WHEEL_PIN_2 0
#define RIGHT_WHEEL_PIN_1 8
#define RIGHT_WHEEL_PIN_2 9

/*******************************************************************************
 *
 * FUNCTIONS
 *
 ******************************************************************************/

// Estas funcoes controlam o sentido de giro das rodas, mas nao controlam a
// duracao do giro
void WHEEL_Start(void);
void WHEEL_DisableSpin(void);
void WHEEL_SpinAhead(void);
void WHEEL_SpinBack(void);
void WHEEL_SpinRight(void);
void WHEEL_SpinLeft(void);

#endif
