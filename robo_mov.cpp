/*******************************************************************************
 *
 * INCLUDES
 *
 ******************************************************************************/

// Include Arduino.h, necessaria para as funcoes
#include <Arduino.h>
#include "./robo_mov.h"
#include "../../robo_sensors/src/robo_sensors.h"

/*******************************************************************************
 *
 * FUNCTIONS
 *
 ******************************************************************************/

// Inicializa as rodas, todas paradas
void WHEEL_Start(void){
  pinMode(RIGHT_WHEEL_PIN_1, OUTPUT);
  pinMode(RIGHT_WHEEL_PIN_2, OUTPUT);
  pinMode(LEFT_WHEEL_PIN_1, OUTPUT);
  pinMode(LEFT_WHEEL_PIN_2, OUTPUT);

  digitalWrite(RIGHT_WHEEL_PIN_1, LOW);
  digitalWrite(RIGHT_WHEEL_PIN_2, LOW);
  digitalWrite(LEFT_WHEEL_PIN_1, LOW);
  digitalWrite(LEFT_WHEEL_PIN_2, LOW);
}

// Desativa as pontes H, impedindo o motor de girar
void WHEEL_DisableSpin(void){
  digitalWrite(RIGHT_WHEEL_PIN_1, LOW);
  digitalWrite(RIGHT_WHEEL_PIN_2, LOW);
  digitalWrite(LEFT_WHEEL_PIN_1, LOW);
  digitalWrite(LEFT_WHEEL_PIN_2, LOW);
}

// Esta funcao faz as rodas girarem para a frente
void WHEEL_SpinAhead(void){
  digitalWrite(RIGHT_WHEEL_PIN_1, HIGH);
  digitalWrite(RIGHT_WHEEL_PIN_2, LOW);
  digitalWrite(LEFT_WHEEL_PIN_1, HIGH);
  digitalWrite(LEFT_WHEEL_PIN_2, LOW);
}

// Esta funcao faz as rodas girarem para tras
void WHEEL_SpinBack(void){
  digitalWrite(RIGHT_WHEEL_PIN_1, LOW);
  digitalWrite(RIGHT_WHEEL_PIN_2, HIGH);
  digitalWrite(LEFT_WHEEL_PIN_1, LOW);
  digitalWrite(LEFT_WHEEL_PIN_2, HIGH);
}

// Esta funcao alterna o giro das rodas, fazendo o robo girar em seu proprio
// eixo no sentido horario
void WHEEL_SpinRight(void){
  digitalWrite(RIGHT_WHEEL_PIN_1, HIGH);
  digitalWrite(RIGHT_WHEEL_PIN_2, LOW);
  digitalWrite(LEFT_WHEEL_PIN_1, LOW);
  digitalWrite(LEFT_WHEEL_PIN_2, HIGH);
}

// Esta funcao alterna o giro das rodas, fazendo o robo girar em seu proprio
// eixo no sentido anti-horario
void WHEEL_SpinLeft(void){
  digitalWrite(RIGHT_WHEEL_PIN_1, LOW);
  digitalWrite(RIGHT_WHEEL_PIN_2, HIGH);
  digitalWrite(LEFT_WHEEL_PIN_1, HIGH);
  digitalWrite(LEFT_WHEEL_PIN_2, LOW);
}
