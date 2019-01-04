/*
ATIVIDADE 2A - Trabalhando com entradas analógicas e protocolo serial
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

//Declarando o pino do Potenciometro (Sensor)
#define pin_sensor1 A0

int pinos_leds[] = {pin_led1, pin_led2, pin_led3};
int pinos_buttons[] = {pin_btn1, pin_btn2};

//Variáveis para tratamento do protocolo
int indice[4] = {0, 0, 0, 0};
String cmd;
String parametro;
int char_pos = 0;
String LinhaDados = "";

void setup()
{ // O código dentro do SETUP só executa um vez.

    Serial.begin(115200); // Configura a interface serial
    // Configurando os pinos de saída através do bloco de repetição FOR
    for (int i = 0; i <= 2; i++)
    {
        pinMode(pinos_leds[i], OUTPUT);
        Serial.println((String) "Pino: " + pinos_leds[i] + (String) " configurado como saída");
        delay(50);
    }
    // Configurando os pinos de entrada através do bloco de repetição FOR
    for (int i = 0; i <= 1; i++)
    {
        pinMode(pinos_buttons[i], INPUT);
        Serial.println((String) "Pino: " + pinos_buttons[i] + (String) " configurado como entrada");
        delay(50);
    }
}

void LerBtn(int btn)
{
    switch (btn)
    {
    case 1:
        if (digitalRead(pinos_buttons[0]) == 1)
        {
            Serial.println(String("Botao 1 - Pressionado"));
        }
        else
        {
            Serial.println(String("Botao 1 - Nao pressionado"));
        }

        break;
    case 2:
        if (digitalRead(pinos_buttons[1]) == 1)
        {
            Serial.println(String("Botao 2 - Pressionado"));
        }
        else
        {
            Serial.println(String("Botao 2 - Nao pressionado"));
        }
        break;
    default:
        break;
    }
}

float tempCelsius(int val_digital)
{
    Serial.println(analogRead(pin_sensor1));
    float tensao = val_digital * (5.0 / 1023.0);
    Serial.println(tensao);
    float temperatura = (200.0 / 5.0) * tensao - 100.0;
    return temperatura;
}

void LerTemp()
{
    Serial.println(String("Temperatura: ") + tempCelsius(analogRead(pin_sensor1)) + String("C"));
}

void LigarLED(int led)
{
    switch (led)
    {
    case 1:
        digitalWrite(pinos_leds[0],HIGH);
        break;
    case 2:
        digitalWrite(pinos_leds[1],HIGH);
        break;
    case 3:
        digitalWrite(pinos_leds[2],HIGH);
        break;
    default:
        break;
    }
}

void DesligarLED(int led)
{
    switch (led)
    {
    case 1:
        digitalWrite(pinos_leds[0],LOW);
        break;
    case 2:
        digitalWrite(pinos_leds[1],LOW);
        break;
    case 3:
        digitalWrite(pinos_leds[2],LOW);
        break;
    default:
        break;
    }
}

void loop()
{
    
    if (Serial.available())
    {
            
        LinhaDados = Serial.readStringUntil('*');
        //LinhaDados.remove(LinhaDados.length() - 1, 1); //Remove o último caractere da string (*);

        if ((LinhaDados.charAt(0) == '(') && ((LinhaDados.charAt(LinhaDados.length() - 1)) == ')')) //String do protocolo recebido
        {
            //Serial.println((String("Mensagem Recebida:")) + LinhaDados);
            indice[0] = LinhaDados.indexOf(',');                        // Encontra a posição da virgula (,)
            cmd = LinhaDados.substring(1, indice[0]);                   //Copia a substring da posicao 1 até antes da virgula
            indice[1] = LinhaDados.indexOf(')', indice[0] + 1);         // Encontra a posição do caracter F
            parametro = LinhaDados.substring(indice[0] + 1, indice[1]); //Copia substring da posicao da próxima da virgula até o F
            //Serial.println(String("Comando: ") + cmd);
            //Serial.println(String("Parametro: ") + parametro);

            if (cmd == "LERBTN") //Verificação dos comandos
            {
                LerBtn(parametro.toInt());
            }

            if (cmd == "LERTEMP")
            {
                LerTemp();
            }

            if (cmd == "LEDON")
            {
                LigarLED(parametro.toInt());
               
            }

            if (cmd == "LEDOFF")
            {
                DesligarLED(parametro.toInt());
            }
        }
        else
        {
            Serial.println("ERRO");
        }
    }
}
