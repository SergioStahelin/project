//Programa : Teste basico encoder Arduino
//Autor : Arduino e Cia

//Carrega a biblioteca do encoder
#include "RotaryEncoder.h"

//Pinos de ligacao do encoder
RotaryEncoder encoder(A3, A2);

//Variavel para o botao do encoder
int botao1 = 0;
int newPos = 0;

//Valvula
int valvula = 0;

void setup()
{
  Serial.begin(9600);
  Serial.println("Gire o encoder....");
  pinMode(A5, INPUT);
  pinMode(A5, INPUT_PULLUP);
  pinMode(A4, OUTPUT);
  
}

void loop()
{
  //Verifica se o botao do encoder foi pressionado
  botao1 = digitalRead(A5);
  if (botao1 != 1)
  {
    Serial.println("Botao pressionado");
    if (valvula == 0){
      digitalWrite(A4, HIGH);
      valvula = 1;
    }else{
      digitalWrite(A4, LOW);
      valvula = 0;
    }
    while (digitalRead(A5) == 0)
      delay(100);
  }

  //Le as informacoes do encoder
  static int pos = 0;
  encoder.tick();
  int newPos = encoder.getPosition();
  //Se a posicao foi alterada, mostra o valor
  //no Serial Monitor
  if (pos != newPos) {
    Serial.print(newPos);
    Serial.println();
    pos = newPos;
  }
}
