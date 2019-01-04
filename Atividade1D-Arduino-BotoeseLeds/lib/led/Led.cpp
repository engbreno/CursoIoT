#include <Arduino.h>
#include "Led.h" // Precisamos incluir o arquivo header no contexto.

//Implementação do Construtor da classe.
Led::Led(int pin){ 
    pino = pin;
    pinMode(pin,OUTPUT);    
};

//Implementação da função ligar.
void Led::ligar(){
     digitalWrite(pino,HIGH);
};
//Implementação da função desligar.
void Led::desligar(){
     digitalWrite(pino,LOW);
};
//Implementação da função piscar.
void Led::piscar(int tempo){
     digitalWrite(pino,HIGH);
     delay(tempo);
     digitalWrite(pino,LOW);
     delay(tempo);
};