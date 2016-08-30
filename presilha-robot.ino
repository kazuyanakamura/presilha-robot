#include <TimerOne.h>
#include "robo_sensors.h"
#include "robo_mov.h"


#define DELAY_FAILURE 0
#define DELAY_SUCCESS 1

// Esse delay pode parar a qualquer instante caso a variavel de controle nao bata com
// o estado correto da maquina de estados. Ex: o Arduino tava no estado procurando,
// mas achou linha branca, entao tem que mudar o estado 'procurando' pra 'recuando'
char StateBasedDelay(int delay, char* state_variable, char correct_state);

void timer_callback(void);

sensors_t sensores;

int black_floor, black_floor_limit;

void setup(){
  // Periodo para o timer, em us (50 ms)
  Timer1.initialize(50000);
  // Informa ao timer para executar a funcao callback() periodicamente
  Timer1.attachInterrupt(timer_callback);
  
  // Inicializa os pinos das rodas e dos sensores, e calibra os sensores devidamente
  WHEEL_Start();
  SENSORS_Start();
  SENSORS_CalibrateLineSensor(&black_floor, &black_floor_limit);

  // Tempo de espera obrigatório
  delay(5000);
}

void loop(){

}

// Delay capaz de parar a si mesmo. utilizar a sintaxe
//
// if(StateBasedDelay(arg1, arg2, arg3) == DELAY_FAILURE)
char StateBasedDelay(int delay, char* state_variable, char correct_state){
  int i;
  for(i = 0; i < delay; i++){
    if(*state_variable != correct_state){
      return DELAY_FAILURE;
    }
  }

  return DELAY_SUCCESS;
}

// Funcao que e executada dentro do timer periodicamente
void timer_callback(void){
  SENSORS_CheckAll(&sensores);
}

