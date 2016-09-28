#include "robo_mov.h"
#include "robo_sensors.h"
#include "TimerOne.h"

#define DELAY_FAILURE 0
#define DELAY_SUCCESS 1

#define LINHA_BRANCA_FRENTE_ENCONTRADA 0
#define LINHA_BRANCA_ATRAS_ENCONTRADA 1
#define ALVO_ENCONTRADO 2
#define PROCURANDO_ALVO 3

// Esse delay pode parar a qualquer instante caso a variavel de controle nao
// bata com o estado correto da maquina de estados. Ex: o Arduino tava no estado
// procurando,mas achou linha branca, entao tem que mudar o estado 'procurando'
// pra 'recuando'
char StateBasedDelay(int delay, volatile char *state_variable, char correct_state);

char Think(volatile sensors_t *valores);
void Move(volatile char *estado);

// Funcao a ser executada quando o timer estourar
void Timer1Callback(void);

/*******************************************************************************
 *
 * VARIABLES
 *
 ******************************************************************************/

volatile sensors_t sensores;
volatile char estado_robo;

int black_floor, white_line;

void setup() {
  // Periodo para o timer, em us (100 ms)
  Timer1.initialize(100000);
  // Informa ao timer para executar a funcao callback() periodicamente
  Timer1.attachInterrupt(Timer1Callback);

  // Inicializa os pinos das rodas e dos sensores, e calibra os sensores de
  // acordo com o que foi lido no piso, para evitar erros
  StartMovement();
  StartSensors();
  CalibrateLineSensor(&black_floor, &white_line);

  // Tempo de espera obrigatório
  delay(5000);
  /*
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(9, LOW);
  digitalWrite(8, LOW);
  delay(5000);
  */
}

void loop() {
  MoveFoward();
  delay(3000);
  MoveBack();
  delay(3000);
  /*
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
  digitalWrite(9, HIGH);
  digitalWrite(8, LOW);
    
  delay(5000);

  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(9, LOW);
  digitalWrite(8, LOW);

  delay(100);
  
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(8, HIGH);
  
  delay(5000);
  */
}

// Funcao que e executada dentro do timer periodicamente
void Timer1Callback(void){
  CheckAllSensors(&sensores);
  estado_robo = Think(&sensores);
}

// Delay capaz de parar a si mesmo. Utilizar a seguinte sintaxe
//
// if(StateBasedDelay(arg1, arg2, arg3) == DELAY_FAILURE)
char StateBasedDelay(int delay, volatile char *state_variable, char correct_state){
  int i;
  for(i = 0; i < delay; i++){
    if(*state_variable != correct_state){
      return DELAY_FAILURE;
    }
  }

  return DELAY_SUCCESS;
}

// Funcao responsavel pela logica da maquina de estados do robo
char Think(volatile sensors_t *valores){
  // A prioridade maior deve ser para a linha branca do ringue, e depois para o resto
  
  // Verifica se encontrou a linha branca na frente do robo
  if((valores->line_fr <= white_line) || (valores->line_fl <= white_line)){
    return LINHA_BRANCA_FRENTE_ENCONTRADA;

  // Verifica se encontrou a linha branca atras do robo
  }else if((valores->line_br <= white_line) || (valores->line_bl <= white_line)){
    return LINHA_BRANCA_ATRAS_ENCONTRADA;
    
  // Verifica se o sensor retornou um valor alto, ou seja, 
  }else if(valores->ir == IR_FOUND_OBJECT){
    return ALVO_ENCONTRADO;

  // Se tudo falhar, deve voltar a procurar o alvo
  }else{
    return PROCURANDO_ALVO;
  }
}

void Move(volatile char *estado){
  switch(*estado){
    case LINHA_BRANCA_FRENTE_ENCONTRADA:
      break;

    case LINHA_BRANCA_ATRAS_ENCONTRADA:
      break;

    // Ao encontrar o alvo, o robo deve se mover indefinidamente para frente,
    // ate que o estado atual mude
    case ALVO_ENCONTRADO:
      MoveFoward();
      while(StateBasedDelay(100, estado, ALVO_ENCONTRADO) != DELAY_FAILURE);

      // ALVO_ENCONTRADO
      break;

    // Para procurar o alvo, o robo fara um movimento de zigue-zague no ringue
    case PROCURANDO_ALVO:
      // Move pra frente
      MoveFoward();
      if(StateBasedDelay(1000, estado, PROCURANDO_ALVO) == DELAY_FAILURE){
        break;
      }

      // Se nao achar nada, procura pra direita
      MoveRight();
      if(StateBasedDelay(200, estado, PROCURANDO_ALVO) == DELAY_FAILURE){
        break;
      }

      // Move pra frente
      MoveFoward();
      if(StateBasedDelay(1000, estado, PROCURANDO_ALVO) == DELAY_FAILURE){
        break;
      }
      
      // Se nao achar nada, procura pra esquerda
      MoveRight();
      if(StateBasedDelay(200, estado, PROCURANDO_ALVO) == DELAY_FAILURE){
        break;
      }
      
      // PROCURANDO_ALVO
      break;

    default:
      *estado = PROCURANDO_ALVO;
      break;
  }
}
