/*
ATIVIDADE 3A - Comunicação Transparente entre Arduino e ESP01 
CURSO IoT - Julho 2018 
Internet das Coisas com Arduino e ESP-01 
Autor: Prof. Breno M. de Oliveira
*/

#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial ESP01(2, 3); //Cria uma nova interface serial através dos Pinos D2 e D3 do Arduino,
                            //onde será conectado o módulo wifi ESP-01
                            // Pino 2 é o RX do Arduino (TX do ESP)
                            // Pino 3 é o TX do Arduino (RX do ESP) - Precisa do divisor de tensão 5V -> 3.3V

void setup()
{
    Serial.begin(9600); // Inicia a comunicação entre o PC e o Arduino
    ESP01.begin(9600); // Inicia a comunicação entre Arduino e o ESP-01

    Serial.println("Comunicação PC-Arduino-ESP01");
    Serial.println("Lembre-se de setar 'Ambos, NL e CR' no serial monitor.");
    Serial.println("Ready");
}

void loop()
{
    // Escuta a comunição serial do ESP-01 e escreve na serial do Arduino
    if (ESP01.available())
    {
        Serial.write(ESP01.read());
    }

    // Escuta a comunição serial do Arduino e escreve na serial do ESP-01
    if (Serial.available())
    {
        ESP01.write(Serial.read());
    }
}