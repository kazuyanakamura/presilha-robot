/*******************************************************************************
 *
 * INCLUDES
 *
 ******************************************************************************/

// Include Arduino.h, necessaria para as funcoes
#include <Arduino.h>
#include "./robo_mov.h"

/*******************************************************************************
 *
 * FUNCTIONS
 *
 ******************************************************************************/

// Inicializa as rodas, todas paradas
void StartMovement(void){
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
void DisableMovement(void){
  digitalWrite(RIGHT_WHEEL_PIN_1, LOW);
  digitalWrite(RIGHT_WHEEL_PIN_2, LOW);
  digitalWrite(LEFT_WHEEL_PIN_1, LOW);
  digitalWrite(LEFT_WHEEL_PIN_2, LOW);
}

// Esta funcao faz as rodas girarem para a frente
void MoveFoward(void){
  digitalWrite(RIGHT_WHEEL_PIN_1, HIGH);
  digitalWrite(RIGHT_WHEEL_PIN_2, LOW);
  digitalWrite(LEFT_WHEEL_PIN_1, HIGH);
  digitalWrite(LEFT_WHEEL_PIN_2, LOW);
}

// Esta funcao faz as rodas girarem para tras
void MoveBack(void){
  digitalWrite(RIGHT_WHEEL_PIN_1, LOW);
  digitalWrite(RIGHT_WHEEL_PIN_2, HIGH);
  digitalWrite(LEFT_WHEEL_PIN_1, LOW);
  digitalWrite(LEFT_WHEEL_PIN_2, HIGH);
}

// Esta funcao alterna o giro das rodas, fazendo o robo girar em seu proprio
// eixo no sentido horario
void MoveRight(void){
  digitalWrite(RIGHT_WHEEL_PIN_1, HIGH);
  digitalWrite(RIGHT_WHEEL_PIN_2, LOW);
  digitalWrite(LEFT_WHEEL_PIN_1, LOW);
  digitalWrite(LEFT_WHEEL_PIN_2, HIGH);
}

// Esta funcao alterna o giro das rodas, fazendo o robo girar em seu proprio
// eixo no sentido anti-horario
void MoveLeft(void){
  digitalWrite(RIGHT_WHEEL_PIN_1, LOW);
  digitalWrite(RIGHT_WHEEL_PIN_2, HIGH);
  digitalWrite(LEFT_WHEEL_PIN_1, HIGH);
  digitalWrite(LEFT_WHEEL_PIN_2, LOW);
}
