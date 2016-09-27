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
#define LEFT_WHEEL_PIN_1 10
#define LEFT_WHEEL_PIN_2 11
#define RIGHT_WHEEL_PIN_1 8
#define RIGHT_WHEEL_PIN_2 9

/*******************************************************************************
 *
 * FUNCTIONS
 *
 ******************************************************************************/

// Estas funcoes controlam o sentido de giro das rodas, mas nao controlam a
// duracao do giro
void StartMovement(void);
void DisableMovement(void);
void MoveFoward(void);
void MoveBack(void);
void MoveRight(void);
void MoveLeft(void);

#endif
