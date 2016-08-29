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

void SENSORS_Start(void){
  pinMode(IR_PIN, INPUT);
}

// Pega os valores lidos por cada porta e atribui os valores aos
// devidos ponteiros
void SENSORS_CheckAll(sensors_t* get_value){
  get_value->line_fr = analogRead(LINE_FR_PIN);
  get_value->line_fl = analogRead(LINE_FL_PIN);
  get_value->line_br = analogRead(LINE_BR_PIN);
  get_value->line_bl = analogRead(LINE_BL_PIN);
  get_value->ir = digitalRead(IR_PIN);
}

// Importante chamar essa funcao no comeco do codigo para ter uma ideia da
// do sensor e calibrar qual a tolerancia maxima (sujeira pode interferir na
// leitura), para evitar leituras erradas
void SENSORS_CalibrateLineSensor(int* min, int* max){
  *min = analogRead(LINE_FR_PIN);
  *max = (*min) * 2;
}
