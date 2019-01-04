/*
ATIVIDADE 2B - Controlando o Arduino via Controle Remoto IR
CURSO IoT - Julho 2018 
Internet das Coisas com Arduino e ESP-01 
Autor: Prof. Breno M. de Oliveira
*/

#include <Arduino.h>
#include <IRremote.h>

#define PinoReceptorIR 7  //Define o pino do sensor IR no Arduino

IRrecv ReceptorIR(PinoReceptorIR); //Criando o objeto da biblioteca IRRemote
decode_results SinalIRDecodificado;    // Criando o objeto da biblioteca IRRemote para o códigos decodificados do Sensor IR

void setup() {
    
    pinMode(13, OUTPUT); // Define o pino 13 como sáida
    Serial.begin(9600);    //Inicializa a serial em 9600 de BaudRate
    ReceptorIR.enableIRIn();   // Ativa o receptor IR 

}

void loop() {

 if (ReceptorIR.decode(&SinalIRDecodificado)) //Se o RececptorIR receber o código de algum botão do controle remote: Salva no objeto SinalIRDecodificado 

  {  
    digitalWrite(13,HIGH); // Acende o Led do Arduino
    Serial.print("CódigoIR: ");        
    Serial.print(SinalIRDecodificado.value, HEX); //Imprime o valor em hexadecimal 
    Serial.print(",  bits: ");          
    Serial.println(SinalIRDecodificado.bits); //Imprime o valor em binário 
    ReceptorIR.resume();    // Receive the next value 
  }  
  delay(600); //delay 600ms
  digitalWrite(13,LOW);
    
}

/*
MAPA DE TECLAS - CONTROLE REMOTO - HEXADECIMAL
CH-   FFA25D
CH    FF629D
CH+   FFE21D
PREV  FF22DD
NEXT  FF02FD
PLAY  FFC23D
VOL-  FFE01F
VOL+  FFA857
EQ    FF906F
0     FF6897
100+  FF9867
200+  FFB04F
1     FF30CF
2     FF18E7
3     FF7A85
4     FF10EF
5     FF38C7
6     FF5AA5
7     FF42BD
8     FF4AB5
9     FF52AD
*/
