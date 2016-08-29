# presilha-robot
Team Presilha FTW

##LIBRARIES:
- **robo_mov.h**: contém as funcoes para acionar os motores e controlar o giro delas
- **robo_sensors.h**: contém as funcoes para ler os sensores e as variaveis que armazenam os valores

##NOTES:
- Utilizar apenas as funcoes prontas para programar na int main()
- Biblioteca [TimerOne.h](http://playground.arduino.cc/Code/Timer1) pode ser encontrado no Arduino Playground

##PINOS:
- Infravermelho: **4**
- Sensor de linha frente direito: **A0**
- Sensor de linha frente esquerdo: **A1**
- Sensor de linha tras direito: **A2**
- Sensor de linha tras esquerdo: **A3**

##FUNCOES:
###Movimentacao
>
- **WHEEL_Start();** -> Ativa os pinos das ponte h, e inicia as rodas paradas
- **WHEEL_DisableSpin();** -> Desativa as rodas
- **WHEEL_SpinAhead();** -> O sentido de giro das rodas é para frente
- **WHEEL_SpinBack();** -> O sentido de giro das rodas é para tras
- **WHEEL_SpinRight();** -> O sentido de giro das rodas é uma para frente e outra para tras, girando em seu proprio eixo
- **WHEEL_SpinLeft();** -> O sentido de giro das rodas é uma para tras e outra para frente, girando em seu proprio eixo

###Sensores
>
- **sensors_t** -> Struct para armazenar os valores lidos

>>
- **int line_fr** -> armazena o valor do sensor de linha da frente (F) da direita (R)
- **int line_fl** -> armazena o valor do sensor de linha da frente (F) da esquerda (L)
- **int line_br** -> armazena o valor do sensor de linha de tras (B) da direita (R)
- **int line_bl** -> armazena o valor do sensor de linha de tras (B) da esquerda(L)
- **int ir** -> armazena o valor do sensor infravermelho

>
- **SENSORS_CheckAll(&variavel);** -> Checa tudo o que deve checar e coloca na variavel
- **SENSORS_Start();** -> Inicia os pinos necessarios
- **SENSORS_CalibrateLineSensor(&min, &max);** -> Calibra os valores de minimo e maximo dos sensores de linha
