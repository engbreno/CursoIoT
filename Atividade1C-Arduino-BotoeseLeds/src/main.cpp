/*
ATIVIDADE 1C - Trabalhando com entradas e saídas digitais (Formas mais elegantes)
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

//Função/procedimento para detecar se um botão está pressionado e assim acender um determinado Led
//Parametros de Entrada: PIN_BTN (Pino do Botao), PIN_LED(Pino do LED)
//Saída: Nenhuma
void DetectaBotao(int pin_btn, int pin_led) {
if (digitalRead(pin_btn) == 1) {
    digitalWrite(pin_led, HIGH); 
    }
else {
    digitalWrite(pin_led, LOW);    
    }

delay(15);
}


//Função/procedimento para somar 2 valores
//Parametros de Entrada: val1, val2
//Saída: float
float PrintSum(double val1, double val2) {
float result = val1 + val2;
return result;
}


void loop() { // O código dentro do LOPP executa infinitamente.
    
DetectaBotao(pin_btn1, pin_led1);
DetectaBotao(pin_btn2, pin_led2);
Serial.println(PrintSum(10,20));

}



