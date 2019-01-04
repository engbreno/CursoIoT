/*
ATIVIDADE 1B - Trabalhando com entradas e saídas digitais (Formas mais elegantes)
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

int pinos_leds[] = {pin_led1, pin_led2, pin_led3} ;
int pinos_buttons[] = {pin_btn1, pin_btn2} ;

void setup() {  // O código dentro do SETUP só executa um vez.

Serial.begin(9600);


// Configurando os pinos de saída através do bloco de repetição FOR
for (int i=0; i <= 2; i++){
    pinMode(pinos_leds[i],OUTPUT);
    Serial.println( (String)"Pino: " + pinos_leds[i] + (String)" configurado como saída" );
    delay(1000);
}

// Configurando os pinos de entrada através do bloco de repetição FOR
for (int i=0; i <= 1; i++){
    pinMode(pinos_buttons[i],INPUT);
    Serial.println( (String)"Pino: " + pinos_buttons[i] + (String)" configurado como entrada" );
    delay(1000);
}

}
void loop() { // O código dentro do LOPP executa infinitamente.
    
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