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
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
}

// Desativa as pontes H, impedindo o motor de girar
void DisableMovement(void){
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  delay(100);
}

// Esta funcao faz as rodas girarem para a frente
void MoveFoward(void){
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
}

// Esta funcao faz as rodas girarem para tras
void MoveBack(void){
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
}

// Esta funcao alterna o giro das rodas, fazendo o robo girar em seu proprio
// eixo no sentido horario
void MoveRight(void){
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
}

// Esta funcao alterna o giro das rodas, fazendo o robo girar em seu proprio
// eixo no sentido anti-horario
void MoveLeft(void){
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
}
