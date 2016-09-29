#ifndef _ROBO_SENSORS_TYPEDEFS_H_
#define _ROBO_SENSORS_TYPEDEFS_H_

#include <Arduino.h>

/*******************************************************************************
 *
 * TYPEDEFS
 *
******************************************************************************/

/* sensors_t: tipo de struct para armazenar valores dos sensores
 *
 * line_fr: sensor de linha da frente (front) da direita (right)
 * line_fr: sensor de linha da frente (front) da esquerda (left)
 * line_fr: sensor de linha de tras (back) da direita (right)
 * line_fr: sensor de linha de tras (back) da esquerda (left)
 * ir: sensor de infravermelho (infrared)
 *
 * TODO: adicionar depois acelerometro e giroscopio
 */
typedef struct{
  int line_fr;
  int line_fl;
  int line_br;
  int line_bl;
  char ir;
#if ULTRASONIC
  int us;
#endif
}sensors_t;

#endif
