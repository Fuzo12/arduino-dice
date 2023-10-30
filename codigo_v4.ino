/*
Sistemas Embebidos TP1 Parte 1-Matriz de LEDs
Trabalho realizado por:
  Cláudio Coelho a22106474
  Lucas Martins a22103318
Trabalho realizado com base em:
  https://projecthub.arduino.cc/SAnwandter1/programming-8x8-led-matrix-a3b852
  https://github.com/jackdonofrio/diceroll
  https://www.youtube.com/watch?v=xQZ_rrt7hF4
*/
#define ROW_1 9
#define ROW_2 8
#define ROW_3 7
#define ROW_4 6
#define ROW_5 5
#define ROW_6 4
#define ROW_7 3
#define ROW_8 2

#define COL_1 A3
#define COL_2 A2
#define COL_3 A1
#define COL_4 A0
#define COL_5 13
#define COL_6 12
#define COL_7 11
#define COL_8 10

const byte rows[] = {
    ROW_1, ROW_2, ROW_3, ROW_4, ROW_5, ROW_6, ROW_7, ROW_8
};
const byte col[] = {
  COL_1,COL_2, COL_3, COL_4, COL_5, COL_6, COL_7, COL_8
};

byte all[] = {B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111};
byte none[] = {B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B0000000};

byte oneSide[] = {B00000000,B00000000,B00000000,B00011000,B00011000,B00000000,B00000000,B00000000};
byte twoSide[] = {B00000000,B00000110,B00000110,B00000000,B00000000,B01100000,B01100000,B00000000};
byte threeSide[] = {B00000011,B00000011,B00000000,B00011000,B00011000,B00000000,B11000000,B11000000};
byte fourSide[] = {B11000011,B11000011,B00000000,B00000000,B00000000,B00000000,B11000011,B11000011};
byte fiveSide[] = {B11000011,B11000011,B00000000,B00011000,B00011000,B00000000,B11000011,B11000011};
byte sixSide[] = {B01100110,B01100110,B00000000,B01100110,B01100110,B00000000,B01100110,B01100110};

byte smileySprite[] = {B00000000,B01100110,B01100110,B00000000,B00000000,B01111110,B00111100,B00000000};
byte cSprite[] = {B01111111,B11111111,B11000000,B11000000,B11000000,B11000000,B11111111,B01111111};
byte lSprite[] = {B11000000,B11000000,B11000000,B11000000,B11000000,B11000000,B11111111,B11111111};
byte mSprite[] = {B11000011,B11100111,B11111111,B11011011,B11011011,B11011011,B11011011,B11011011};
byte questionSprite[] = {B01111110,B11111111,B11000011,B11000111,B00011110,B00011000,B00000000,B00011000};

void setup() 
{
  //Coloca os pinos utilizados a realizar outputs.
  for (byte i = 2; i <= 13; i++){pinMode(i, OUTPUT);}
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  //Permite que os números gerados pela função random() sejam aleatórios desde que o pino anlógico 5 se mantenha desconectado.
  randomSeed(analogRead(5));
}

void loop() {
delay(10);
byte* rollResult= roll();
//Mostra a sequência das faces do dado por ordem crescente antes da sequência na matriz de LEDs.
drawScreen(oneSide,50);
drawScreen(twoSide,50);
drawScreen(threeSide,50);
drawScreen(fourSide,50);
drawScreen(fiveSide,50);
drawScreen(sixSide,50);
drawScreen(none,25);
//Mostra um ponto de interrogação que pisca 3 vezes antes de revelar o resultado do lançamento do dado na matriz de LEDs.
drawScreen(questionSprite,25);
drawScreen(none,25);
drawScreen(questionSprite,25);
drawScreen(none,25);
drawScreen(questionSprite,25);
drawScreen(none,50);
//Mostra o resultado do lançamento do dado a piscar 5 vezes na matriz de LEDs.
drawScreen(rollResult,30);
drawScreen(none,25);
drawScreen(rollResult,30);
drawScreen(none,25);
drawScreen(rollResult,30);
drawScreen(none,25);
drawScreen(rollResult,30);
drawScreen(none,25);
drawScreen(rollResult,30);
drawScreen(none,50);
//Mostra o smiley na matriz de LEDs.
drawScreen(smileySprite,50);
drawScreen(none,50);
//Mostra as iniciais dos elementos do grupo (Claúdio Coelho e Lucas Martins) na matriz de LEDs.
drawScreen(cSprite,50);
drawScreen(none,50);
drawScreen(cSprite,50);
drawScreen(none,50);
drawScreen(lSprite,50);
drawScreen(none,50);
drawScreen(mSprite,50);
drawScreen(none,50);
}

//Ativa as colunas necessárias.
void initiateColumns(byte b){
  for(int i=0;i<8;i++){digitalWrite(col[i],(~b>>i) & 0x01);}
}

//Mostra um padão na matriz, durante o número de loops presente no campo 'duration'.
void drawScreen(byte buffer2[],int duration){
  for(byte counter=0;counter<duration;counter++){
    for(byte i=0;i<8;i++){
      initiateColumns(buffer2[i]); //Ativa as colunas necessárias.
      digitalWrite(rows[i],HIGH); //Ativa a linha de indice i.
      //initiateColumns(buffer2[i]);
      delay(2);
      digitalWrite(rows[i],LOW); //Desativa a linha de indice i.
    }
  }
}

//Cria um número aletório entre 1 e 6 que define que padrão irá ser retornado.
byte* roll(){
  switch(random(1,7)){
    case 1:
      return oneSide;
      break;
    case 2:
      return twoSide;
      break;
    case 3:
      return threeSide;
      break;
    case 4:
      return fourSide;
      break;
    case 5:
      return fiveSide;
      break;
    case 6:
      return sixSide;
      break;
  }
}