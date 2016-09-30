#include <MsTimer2.h>
#include "robo_sensors.h"
#include "robo_mov.h"

/*******************************************************************************
 *
 * DEFINES
 *
 ******************************************************************************/

// DEFINES TO DEBUG PRINTS
#define DEBUG_SETUP_PRINT 0
#define DEBUG_SENSOR_IR   0
#define DEBUG_SENSOR_US   0
#define DEBUG_SENSOR_LN   0
#define DEBUG_STATUS      0
#define DEBUG_FOUND_LN    0

// DEFINE DISPATCH EVENTS
#define DISPATCH_FRONT_RIGHT  1
#define DISPATCH_FRONT_LEFT   2
#define DISPATCH_BACK_RIGHT   3
#define DISPATCH_BACK_LEFT    4

#define DELAY_FAILURE 0
#define DELAY_SUCCESS 1

// DEFINE STATE MACHINE
#define LINHA_BRANCA_FRENTE_ENCONTRADA_LAST_LEFT  0
#define LINHA_BRANCA_FRENTE_ENCONTRADA_LAST_RIGHT 1
#define ALVO_ENCONTRADO_IR                        2
#define PROCURANDO_ALVO                           3
#define RECUANDO                                  4
#define AVANCANDO                                 5
#define ALVO_ENCONTRADO_US                        6
#define LINHA_BRANCA_ATRAS_ENCONTRADA_LAST_LEFT   7
#define LINHA_BRANCA_ATRAS_ENCONTRADA_LAST_RIGHT  8

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

short int buffer_dispatch_event;
int black_floor, white_line;

/*******************************************************************************
 *
 * VOID SETUP
 *
 ******************************************************************************/

void setup(){
  #if DEBUG_SETUP_PRINT
  Serial.begin(2400);
  Serial.println("BIRL!");
  #endif

  // Periodo para o timer, em us (10 ms)
  MsTimer2::set(10, Timer1Callback); // 500ms period
  MsTimer2::start();

  // Inicializa os pinos das rodas e dos sensores, e calibra os sensores de
  // acordo com o que foi lido no piso, para evitar erros
  StartMovement();
  StartSensors();
  CalibrateLineSensor(&black_floor, &white_line);

  // Tempo de espera obrigatório
  // delay(3500);
}

/*******************************************************************************
 *
 * VOID LOOP
 *
 ******************************************************************************/

void loop(){
  Move(&estado_robo);
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

  #if DEBUG_SENSOR_LN
  Serial.print("Front Right: ");
  Serial.println(valores->line_fr);
  Serial.print("Front Left: ");
  Serial.println(valores->line_fl);
  Serial.print("Back Right: ");
  Serial.println(valores->line_br);
  Serial.print("Back Left: ");
  Serial.println(valores->line_bl);
  #endif

  #if DEBUG_SENSOR_US
  Serial.print("Ultrassonic Sensor: ");
  Serial.println(valores->us);
  #endif

  #if DEBUG_SENSOR_IR
  Serial.print("Infrared Sensor: ");
  Serial.println((int) valores->ir);
  #endif

  if (*status == RECUANDO) {
    #if DEBUG_STATUS
    Serial.println("recuando\n");
    #endif

    return RECUANDO;
  } else if (*status == AVANCANDO) {
    #if DEBUG_STATUS
    Serial.println("avancando\n");
    #endif

    return AVANCANDO;

  } else if (valores->line_fl <= white_line) {
    #if DEBUG_FOUND_LN
    Serial.println("found linha frente left");
    #endif

    if (buffer_dispatch_event == DISPATCH_FRONT_RIGHT) {
      #if DEBUG_FOUND_LN
      Serial.println("DISPATCH SECOND FRONT LEFT");
      #endif
      buffer_dispatch_event = 0;

      return LINHA_BRANCA_FRENTE_ENCONTRADA_LAST_LEFT;
    } else {
      #if DEBUG_FOUND_LN
      Serial.println("DISPATCH FIRST FRONT LEFT");
      #endif
      buffer_dispatch_event = DISPATCH_FRONT_LEFT;
      return PROCURANDO_ALVO;
    }

  } else if (valores->line_fr <= white_line) {
    // Verifica se encontrou a linha branca na frente do robo);
    #if DEBUG_FOUND_LN
    Serial.println("found linha frente right");
    #endif

    if (buffer_dispatch_event == DISPATCH_FRONT_LEFT) {
      #if DEBUG_FOUND_LN
      Serial.println("DISPATCH SECOND FRONT RIGHT");
      #endif
      buffer_dispatch_event = 0;

      return LINHA_BRANCA_FRENTE_ENCONTRADA_LAST_RIGHT;
    } else {
      #if DEBUG_FOUND_LN
      Serial.println("DISPATCH FIRST FRONT RIGHT");
      #endif
      buffer_dispatch_event = DISPATCH_FRONT_RIGHT;
      return PROCURANDO_ALVO;
    }

    // Verifica se encontrou a linha branca atras do robo
  } else if (valores->line_br <= white_line) {
    #if DEBUG_FOUND_LN
    Serial.println("found linha atras right");
    #endif

    if (buffer_dispatch_event == DISPATCH_BACK_LEFT) {
      #if DEBUG_FOUND_LN
      Serial.println("DISPATCH SECOND BACK RIGHT");
      #endif
      buffer_dispatch_event = 0;

      return LINHA_BRANCA_ATRAS_ENCONTRADA_LAST_RIGHT;
    } else {
      #if DEBUG_FOUND_LN
      Serial.println("DISPATCH FIRST BACK RIGHT");
      #endif
      buffer_dispatch_event = DISPATCH_BACK_RIGHT;
      return PROCURANDO_ALVO;
    }

  } else if (valores->line_bl <= white_line) {
    #if DEBUG_FOUND_LN
    Serial.println("found linha atras left");
    #endif

    if (buffer_dispatch_event == DISPATCH_BACK_RIGHT) {
      #if DEBUG_FOUND_LN
      Serial.println("DISPATCH SECOND BACK RIGHT");
      #endif
      buffer_dispatch_event = 0;

      return LINHA_BRANCA_ATRAS_ENCONTRADA_LAST_LEFT;
    } else {
      #if DEBUG_FOUND_LN
      Serial.println("DISPATCH FIRST BACK LEFT");
      #endif
      buffer_dispatch_event = DISPATCH_BACK_LEFT;
      return PROCURANDO_ALVO;
    }

    // Verifica se o sensor retornou um valor alto, ou seja,
  } else if(valores->ir == IR_FOUND_OBJECT) {
    #if DEBUG_STATUS
    Serial.print("found with ir\n");
    #endif

    return ALVO_ENCONTRADO_IR;
  } else if((valores->us <= US_MAX_RANGE) && valores->us >= US_MIN_RANGE) {
    #if DEBUG_STATUS
      Serial.println("found with us\n");
    #endif

    return ALVO_ENCONTRADO_US;
    // Se tudo falhar, deve voltar a procurar o alvo
  } else {
    #if DEBUG_STATUS
    Serial.print("searching\n");
    #endif

    return PROCURANDO_ALVO;
  }
}

void Move(volatile char *estado){
  switch(*estado){
    case LINHA_BRANCA_FRENTE_ENCONTRADA_LAST_LEFT:
      *estado = RECUANDO;
      DisableMovement();
      MoveRight();
      if(StateBasedDelay(250, estado, RECUANDO) == DELAY_FAILURE){
        break;
      }
      MoveFoward();
      if(StateBasedDelay(500, estado, RECUANDO) == DELAY_FAILURE){
        break;
      }
      *estado = PROCURANDO_ALVO;

      break;

    case LINHA_BRANCA_FRENTE_ENCONTRADA_LAST_RIGHT:
      *estado = RECUANDO;
      DisableMovement();
      MoveLeft();
      if(StateBasedDelay(250, estado, RECUANDO) == DELAY_FAILURE){
        break;
      }
      DisableMovement();
      MoveFoward();
      if(StateBasedDelay(500, estado, RECUANDO) == DELAY_FAILURE){
        break;
      }
      *estado = PROCURANDO_ALVO;

      break;

    case LINHA_BRANCA_ATRAS_ENCONTRADA_LAST_LEFT:
      DisableMovement();
      MoveBackLeft();
      *estado = AVANCANDO;
      if(StateBasedDelay(500, estado, AVANCANDO) == DELAY_FAILURE){
        break;
      }
      *estado = PROCURANDO_ALVO;

      break;

    case LINHA_BRANCA_ATRAS_ENCONTRADA_LAST_RIGHT:
      DisableMovement();
      MoveBackRight();
      *estado = AVANCANDO;
      if(StateBasedDelay(500, estado, AVANCANDO) == DELAY_FAILURE){
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
      if(StateBasedDelay(700, estado, PROCURANDO_ALVO) == DELAY_FAILURE){
        break;
      }

      // Se nao achar nada, procura pra direita
      MoveLeft();
      if(StateBasedDelay(150, estado, PROCURANDO_ALVO) == DELAY_FAILURE){
        break;
      }

      // Move pra frente
      MoveFoward();
      if(StateBasedDelay(700, estado, PROCURANDO_ALVO) == DELAY_FAILURE){
        break;
      }

      // Se nao achar nada, procura pra esquerda
      MoveRight();
      if(StateBasedDelay(150, estado, PROCURANDO_ALVO) == DELAY_FAILURE){
        break;
      }

      break;

    default:
      *estado = PROCURANDO_ALVO;
      break;
  }
}
