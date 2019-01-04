/*
ATIVIDADE 1 - Trabalhando com entradas e saídas digitais
CURSO IoT - Julho 2018 
Internet das Coisas com Arduino e ESP-01 
Autor: Prof. Breno M. de Oliveira
*/

#include <Arduino.h>

//Declarando os pinos dos LEDs
#define pin_led1 8
#define pin_led2 9
#define pin_led3 10

//Declarando os pinos dos Botoes
#define pin_btn1 6
#define pin_btn2 7


void setup() {
    // O código dentro do SETUP só executa um vez.

pinMode(pin_led1, OUTPUT);
pinMode(pin_led2, OUTPUT);
pinMode(pin_led3, OUTPUT);

pinMode(pin_btn1, INPUT);
pinMode(pin_btn2, INPUT);

}

void loop() {
    // O código dentro do LOPP executa infinitamente.
    if (digitalRead(pin_btn1) == 1) 
        {
        digitalWrite(pin_led1, HIGH);        
        }
    else
        {
        digitalWrite(pin_led1, LOW);
        }


    if (digitalRead(pin_btn2) == 1) 
        {
        digitalWrite(pin_led2, HIGH); 
        digitalWrite(pin_led3, HIGH); 
        }
    else 
        {
        digitalWrite(pin_led2, LOW);
        digitalWrite(pin_led3, LOW);        
        }

    delay(10);

}