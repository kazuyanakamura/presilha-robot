# presilha-robot
Team Presilha FTW

##LIBRARIES:

Todas as bibliotecas devem ir para o endereco padrao do Arduino, isto é, seu "~/Arduino/libraries/" do computador

- **robo_mov.h**: contém as funcoes para acionar os motores e controlar o giro delas, mas nao o movimento em si
- **robo_sensors.h**: contém as funcoes para ler os sensores e as variaveis que armazenam os valores (sensors_t)

Recomenda-se criar um link simbolico caso queria alterar as libs de movimentaçao e sensores
default desse projeto

```bash
# deve-se colocar o path completo para criar o link simbolico corretamente
ln -s ~/pathToProject/robo_mov ~/Arduino/libraries/
ln -s ~/pathToProject/robo_sensors ~/Arduino/libraries/
```

##NOTAS:
- Utilizar apenas as funcoes prontas para programar o motor e sensores na int main(). Se criar funcao nova, favor comentar para maior legibilidade
- Biblioteca [MsTimer2](http://playground.arduino.cc/uploads/Main/MsTimer2.zip) pode ser encontrado no Arduino Playground. Usaremos ela pra ler os sensores constantemente
- Se possível, usar o StateBasedDelay. Ele tem a capacidade de parar a qualquer momento se a condição não bater. Sua sintaxe é a seguinte:
> char StateBasedDelay(int delay, char VARIAVEL_QUE_GUARDA_ESTADO, char ESTADO_QUE_DEVERIA_ESTAR);

> A vantagem de usar essa função é a que se a VARIAVEL_QUE_GUARDA_ESTADO != ESTADO_QUE_DEVERIA_ESTAR, o delay para de rodar.

> Exemplo de uso: if(StateBasedDelay(1000) == DELAY_FAILURE){ // Codigo }
- Todas as funcoes das bibliotecas criadas estão neste README

##PINOS:
- Infravermelho: **4**
- Sensor de linha frente direito: **A0**
- Sensor de linha frente esquerdo: **A1**
- Sensor de linha tras direito: **A2**
- Sensor de linha tras esquerdo: **A3**

##DEFINICOES:
- IR_OBJECT_FOUND
- IR_NOTHING_FOUND
- DELAY_FAILURE
- DELAY_SUCCESS

##FUNCOES:
###Movimentacao
>
- **StartMovement();** -> Ativa os pinos das ponte h, e inicia as rodas paradas
- **DisableMovement();** -> Desativa as rodas
- **MoveFoward();** -> O sentido de giro das rodas é para frente
- **MoveBack();** -> O sentido de giro das rodas é para tras
- **MoveRight();** -> O sentido de giro das rodas é uma para frente e outra para tras, girando em seu proprio eixo
- **MoveLeft();** -> O sentido de giro das rodas é uma para tras e outra para frente, girando em seu proprio eixo

###Sensores
>
- **sensors_t** -> Struct para armazenar os valores lidos. Ela contém as seguintes variáveis

>>
- **int line_fr** -> armazena o valor do sensor de linha da frente (F) da direita (R)
- **int line_fl** -> armazena o valor do sensor de linha da frente (F) da esquerda (L)
- **int line_br** -> armazena o valor do sensor de linha de tras (B) da direita (R)
- **int line_bl** -> armazena o valor do sensor de linha de tras (B) da esquerda(L)
- **int ir** -> armazena o valor do sensor infravermelho

>
- **CheckAllSensors(&variavel);** -> Checa tudo o que deve checar e coloca no struct do tipo 'sensors_t'
- **StartSensors();** -> Inicia os pinos necessarios para os sensores
- **CalibrateLineSensor(&black, &white);** -> Calibra os valores de minimo e maximo dos sensores de linha. Importante para o robo nao confundir sujeira com branco
