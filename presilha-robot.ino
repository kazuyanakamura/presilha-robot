#include "robo_sensors.h"
#include "robo_mov.h"

#define DELAY_FAILURE 0
#define DELAY_SUCCESS 1

// Esse delay pode parar a qualquer instante caso a variavel de controle nao bata com
// o estado correto da maquina de estados. Ex: o Arduino tava no estado procurando,
// mas achou linha branca, entao tem que mudar o estado 'procurando' pra 'recuando'
char StateBasedDelay(int delay, char state_variable, char correct_state);

sensors_t sensores;

int black_value, white_value;

void setup(){
  WHEEL_Start();
  SENSORS_Start();
  SENSORS_CalibrateLineSensor(&black_value, &white_value);
  delay(5000);
}

void loop(){

}

char StateBasedDelay(int delay, char state_variable, char correct_state){
  int i;
  for(i = 0; i < delay; i++){
    if(state_variable != correct_state){
      return DELAY_FAILURE;
    }
  }

  return DELAY_SUCCESS;
}

