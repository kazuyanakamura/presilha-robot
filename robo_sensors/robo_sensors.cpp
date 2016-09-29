/*******************************************************************************
 *
 * INCLUDES
 *
 ******************************************************************************/
#include <Arduino.h>
#include "./robo_sensors.h"

/*******************************************************************************
 *
 * FUNCTIONS
 *
 ******************************************************************************/

void StartSensors(void){
  pinMode(IR_PIN, INPUT);
  pinMode(US_TRIGGER_PIN, OUTPUT);
  pinMode(US_ECHO_PIN, INPUT);
}

// Pega os valores lidos por cada porta e atribui os valores aos
// devidos ponteiros
void CheckAllSensors(volatile sensors_t* get_value){
  get_value->line_fr = analogRead(LINE_FR_PIN);
  get_value->line_fl = analogRead(LINE_FL_PIN);
  get_value->line_br = analogRead(LINE_BR_PIN);
  get_value->line_bl = analogRead(LINE_BL_PIN);
  get_value->ir = digitalRead(IR_PIN);
  get_value->us = ReadUltrasonicSensor(US_TRIGGER_PIN, US_ECHO_PIN);
}

// Importante chamar essa funcao no comeco do codigo para ter uma ideia da
// do sensor e calibrar qual a tolerancia maxima (sujeira pode interferir na
// leitura), para evitar leituras erradas
void CalibrateLineSensor(int* black, int* white){
  *black = analogRead(LINE_FR_PIN);
  *white = *black - 300;
}

int ReadUltrasonicSensor(char trigg, char echo){
  int ultrasonic_response_time;

  digitalWrite(US_TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(US_TRIGGER_PIN, LOW);

  ultrasonic_response_time = pulseIn(US_ECHO_PIN,HIGH);

  ultrasonic_response_time /= 58.0;

  return ultrasonic_response_time;
}
