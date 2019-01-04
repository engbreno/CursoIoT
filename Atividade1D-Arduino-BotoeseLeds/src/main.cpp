/*
ATIVIDADE 1D - Trabalhando com entradas e saídas digitais (Usando Classes/Bibliotecas/Libraries)
CURSO IoT - Julho 2018 
Internet das Coisas com Arduino e ESP-01 
Autor: Prof. Breno M. de Oliveira
*/

#include <Arduino.h>
#include <Led.h> // Indica os arquivos da classe LED (bibliotecas)

Led Led1(8); // Instancia o objeto Led1 da Classe Led
Led Led2(9); // Instancia o objeto Led2 da Classe Led
Led Led3(10); // Instancia o objeto Led3 da Classe Led

void setup() {
    Serial.begin(9600);
    Led1.descricao = "Led número 1"; // Define a propriedade descricao do LED1 (String)
    Led1.cor = "Vermelho" ; // Define a propriedade cor do LED1 (String)
    Led2.descricao = "Led número 2"; // Define a propriedade descricao do LED1 (String)  
    Led2.cor = "Azul" ; // Define a propriedade cor do LED1 (String)
    Led3.descricao = "Led número 3"; // Define a propriedade descricao do LED3 (String)  
    Led3.cor = "Verde" ; // Define a propriedade cor do LED3 (String)
}

void loop() {
// Imprime na serial a propriedade descricao do LED1,número do pino e sua cor
Serial.println(String(Led1.descricao) + " : " + String(Led1.pino) + " : " + String(Led1.cor)); 
// Imprime na serial a propriedade descricao do LED2,número do pino e sua cor
Serial.println(String(Led2.descricao) + " : " + String(Led1.pino) + " : " + String(Led2.cor));
// Imprime na serial a propriedade descricao do LED3,número do pino e sua cor
Serial.println(String(Led3.descricao) + " : " + String(Led3.pino) + " : " + String(Led3.cor));

Led1.ligar(); // Liga o Led1
delay(2000); // Aguarda
Led1.desligar(); // Desliga o Led1
delay(2000); // Aguarda

Led2.piscar(100); // Pisca o LED2
Led3.piscar(1000); //Piscar o LED3

}