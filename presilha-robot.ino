#include <MsTimer2.h>
#include "robo_sensors.h"
#include "robo_mov.h"

/*******************************************************************************
 *
 * DEFINES
 *
 ******************************************************************************/
#define DEBUG 0

#define DELAY_FAILURE 0
#define DELAY_SUCCESS 1

#define LINHA_BRANCA_FRENTE_ENCONTRADA 0
#define LINHA_BRANCA_ATRAS_ENCONTRADA 1
#define ALVO_ENCONTRADO_IR 2
#define PROCURANDO_ALVO 3
#define RECUANDO 4
#define AVANCANDO 5
#define ALVO_ENCONTRADO_US 6

/*******************************************************************************
 *
 * PROTOTYPES
 *
 ******************************************************************************/

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

/*******************************************************************************
 *
 * VOID SETUP
 *
 ******************************************************************************/

void setup(){
#if DEBUG
  Serial.begin(9600);
  for(int i = 0; i < 10; i++) Serial.println("BIRL!");
#endif
  
  // Periodo para o timer, em us (100 ms)
  //Timer1.initialize(10000);
  // Informa ao timer para executar a funcao callback() periodicamente
  //Timer1.attachInterrupt(Timer1Callback);
   MsTimer2::set(10, Timer1Callback); // 500ms period
  MsTimer2::start();
  
  // Inicializa os pinos das rodas e dos sensores, e calibra os sensores de
  // acordo com o que foi lido no piso, para evitar erros
  StartMovement();
  StartSensors();
  CalibrateLineSensor(&black_floor, &white_line);
  
  // Tempo de espera obrigatório
  //delay(3500);
}

/*******************************************************************************
 *
 * VOID LOOP
 *
 ******************************************************************************/

void loop(){
  Move(&estado_robo);
  /*
  MoveFoward();
  delay(2000);
  MoveBack();
  delay(2000);
  */
}

/*******************************************************************************
 *
 * FUNCTIONS
 *
 ******************************************************************************/

// Funcao que e executada dentro do timer periodicamente
void Timer1Callback(void){
  CheckAllSensors(&sensores);
  estado_robo = Think(&sensores, &estado_robo);
}

// Delay capaz de parar a si mesmo. Utilizar a seguinte sintaxe
//
// if(StateBasedDelay(arg1, arg2, arg3) == DELAY_FAILURE)
char StateBasedDelay(int delay_in, volatile char *state_variable, char correct_state){
  int i;
  for(i = 0; i < delay_in; i++){
    if(*state_variable != correct_state){
      return DELAY_FAILURE;
    }
    delay(1);
  }

  return DELAY_SUCCESS;
}

// Funcao responsavel pela logica da maquina de estados do robo
char Think(volatile sensors_t *valores, volatile char *status){
  // A prioridade maior deve ser para a linha branca do ringue, e depois para o resto

#if DEBUG
  Serial.print("br: ");
  Serial.print(valores->line_fr);
  Serial.print(" | bl: ");
  Serial.print(valores->line_fl);
  Serial.print(" | fr: ");
  Serial.print(valores->line_br);
  Serial.print(" | fl: ");
  Serial.print(valores->line_bl);
  Serial.print(" | us: ");
  Serial.print(valores->us);
  Serial.print("\n\n");
#endif
  
  if(*status == RECUANDO){
#if DEBUG
  Serial.println("recuando\n");
#endif
    return RECUANDO;
    
  }else if(*status == AVANCANDO){
#if DEBUG
  Serial.println("avancando\n");
#endif
    return AVANCANDO;
  }
  // Verifica se encontrou a linha branca na frente do robo
  else if((valores->line_fr <= white_line) || (valores->line_fl <= white_line)){
#if DEBUG
  Serial.print("linha frente");
#endif
    return LINHA_BRANCA_FRENTE_ENCONTRADA;

  // Verifica se encontrou a linha branca atras do robo
  }else if((valores->line_br <= white_line) || (valores->line_bl <= white_line)){
#if DEBUG
  Serial.print("linha atras\n");
#endif
    return LINHA_BRANCA_ATRAS_ENCONTRADA;
    
  // Verifica se o sensor retornou um valor alto, ou seja, 
  }else if(valores->ir == IR_FOUND_OBJECT){
#if DEBUG
  Serial.print("alvo_ir\n");
#endif
    return ALVO_ENCONTRADO_IR;

  }else if((valores->us <= 60) && valores->us > 0){
#if DEBUG
  Serial.println("alvo_us\n");
#endif
    return ALVO_ENCONTRADO_US;

  // Se tudo falhar, deve voltar a procurar o alvo
  
  }else{
#if DEBUG
  Serial.print("procurando\n");
#endif
    return PROCURANDO_ALVO;
  }
}

void Move(volatile char *estado){
  switch(*estado){
    case LINHA_BRANCA_FRENTE_ENCONTRADA:
      *estado = RECUANDO;
      MoveLeft();
      if(StateBasedDelay(250, estado, RECUANDO) == DELAY_FAILURE){
        break;
      }
      MoveFoward();
      if(StateBasedDelay(500, estado, RECUANDO) == DELAY_FAILURE){
        break;
      }
      *estado = PROCURANDO_ALVO;
      
      break;

    case LINHA_BRANCA_ATRAS_ENCONTRADA:
      MoveFoward();
      *estado = AVANCANDO;
      if(StateBasedDelay(500, estado, AVANCANDO) == DELAY_FAILURE){
        break;
      }
      MoveLeft();
      if(StateBasedDelay(50, estado, AVANCANDO) == DELAY_FAILURE){
        break;
      }
      *estado = PROCURANDO_ALVO;

      break;

    // Ao encontrar o alvo, o robo deve se mover indefinidamente para frente,
    // ate que o estado atual mude
    case ALVO_ENCONTRADO_IR:
      MoveFoward();
      while(StateBasedDelay(1000, estado, ALVO_ENCONTRADO_IR) != DELAY_FAILURE);

      // ALVO_ENCONTRADO
      break;

    case ALVO_ENCONTRADO_US:
      MoveFoward();
      while(StateBasedDelay(1000, estado, ALVO_ENCONTRADO_US) != DELAY_FAILURE);
      
      break;

    // Para procurar o alvo, o robo fara um movimento de zigue-zague no ringue
    case PROCURANDO_ALVO:
      // Move pra frente
      MoveFoward();
      if(StateBasedDelay(1000, estado, PROCURANDO_ALVO) == DELAY_FAILURE){
        break;
      }

      // Se nao achar nada, procura pra direita
      MoveLeft();
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
