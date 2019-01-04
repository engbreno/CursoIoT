/*
ATIVIDADE 3D - Node-RED - Serversocket + MQQT - Enviando dados sensor análogico
CURSO IoT - Julho 2018 
Internet das Coisas com Arduino e ESP-01 
Autor: Prof. Breno M. de Oliveira
*/

#include <Arduino.h>
#include <SoftwareSerial.h> //Biblioteca para criação de portas seriais (softserial)

//Declarando os pinos dos LEDs, botões e potênciometro
#define pin_led1 8
#define pin_led2 9
#define pin_led3 10
#define pin_btn1 6
#define pin_btn2 7
#define pin_pot A0

SoftwareSerial ESP01(2, 3); //Cria uma nova interface serial através dos Pinos D2 e D3 do Arduino,
                            //onde será conectado o módulo wifi ESP-01
                            // Pino 2 é o RX do Arduino (TX do ESP)
                            // Pino 3 é o TX do Arduino (RX do ESP) - Precisa do divisor de tensão 5V -> 3.3V

// Função para envio de comandos ATs para o ESP-01
// Parametros de Entrada: Cmd - Comando , ACK - retorno
// Parametros de Saída: Verdadeiro ou Falso (true or false)
boolean EnviaComandoESP01(String cmd, String ack, unsigned long timeout, String descricao, String retorno)
{
  Serial.println(cmd);
  ESP01.println(cmd); // Envia o comando (cmd) para o ESP01
  timeout = timeout + millis();
  while (millis() < timeout)
  {
    if (ESP01.available())
    {
      String resposta = ESP01.readString();
      resposta.trim();
      if (resposta.indexOf(ack) != -1)
      {

        if (ack == "+CIFSR:STAIP,")
        {
          int i1 = resposta.indexOf("+CIFSR:STAIP,") + 13; //13 é o tamanho de "+CIFSR:STAIP,"
          int i2 = resposta.indexOf("+", i1 + 2);
          Serial.print("IP:");
          String ip = resposta.substring(i1, i2);
          ip.trim();
          Serial.println(ip);
          return true;
        }
        Serial.print(descricao);
        Serial.print(" : ");
        Serial.println(retorno);
        return true;
      }
    }
  }
  return false;
}

String cipSend = "";
String temp = "";
String StringEntrada = ""; //Armazena as Strings vindas do Wifi
String status = "";

void setup()
{
  pinMode(pin_led1, OUTPUT);
  pinMode(pin_led2, OUTPUT);
  pinMode(pin_led3, OUTPUT);
  pinMode(pin_btn1, OUTPUT);
  pinMode(pin_btn2, OUTPUT);
  Serial.begin(9600);
  ESP01.begin(9600);
  EnviaComandoESP01("AT+RST", "Ready", 5000, "ESP01 - Resetando o ESP01", "Reset OK");
  EnviaComandoESP01("AT+CWQAP", "OK", 5000, "ESP01 - Desconectando de Redes Anteriores...", "Desconectado!");
  EnviaComandoESP01("AT+CWMODE=1", "OK", 5000, "ESP01 - Setando Modo Station...", "Setado!");
  if (EnviaComandoESP01("AT+CWJAP=\"CursoIoT\",\"julho2018\"", "WIFI GOT IP", 20000, "ESP01 - Conectando na Rede CursoIoT...", "Conectado!"))
  {
    EnviaComandoESP01("AT+CIFSR", "+CIFSR:STAIP,", 5000, "ESP01 - Adquirindo numero de IP...", "IP Adquirido:");
    EnviaComandoESP01("AT+CIPMUX=1", "OK", 5000, "ESP01 - Setando TCPServer para multiplas conexoes (Max 5) ...", "TCPServer Multiplicas Conexoes OK");
    EnviaComandoESP01("AT+CIPSERVER=1,80", "OK", 5000, "ESP01 - Startando o TCPServer na porta 80...", "TCPServer Operante");
  }
  else
  {
    Serial.println("Nao foi possível conectar a rede Wifi!");
  }
}

void loop()
{

  while (ESP01.available())
  {
    StringEntrada = ESP01.readString();
    Serial.println(StringEntrada);

    StringEntrada.trim(); // Remove caracteres fantasmas

    if (StringEntrada.indexOf("LED1=ON") != -1)
    { //Se encontrar a String "LED1=ON" dentro da StringEntrada
      digitalWrite(pin_led1, HIGH);
      Serial.println("LED1 - Aceso");
    }

    if (StringEntrada.indexOf("LED2=ON") != -1)
    {
      digitalWrite(pin_led2, HIGH);
      Serial.println("LED2 - Aceso");
    }

    if (StringEntrada.indexOf("LED3=ON") != -1)
    {
      digitalWrite(pin_led3, HIGH);
      Serial.println("LED3 - Aceso");
    }

    if (StringEntrada.indexOf("LED1=OFF") != -1)
    {
      digitalWrite(pin_led1, LOW);
      Serial.println("LED1 - Apagado");
    }

    if (StringEntrada.indexOf("LED2=OFF") != -1)
    {
      digitalWrite(pin_led2, LOW);
      Serial.println("LED2 - Apagado");
    }

    if (StringEntrada.indexOf("LED3=OFF") != -1)
    {
      digitalWrite(pin_led3, LOW);
      Serial.println("LED3 - Apagado");
    }

    if (StringEntrada.indexOf("TEMP=?") != -1)
    {
      temp = String(analogRead(A0));
      cipSend = "AT+CIPSEND=";
      cipSend += 0;
      cipSend += ",";
      cipSend += temp.length();
      cipSend += "\r\n";
      EnviaComandoESP01(cipSend, "SEND OK", 2000, "ESP01 - Enviando temperatura...", "Enviada");
      delay(20);
      ESP01.print(temp);
    }

    if (StringEntrada.indexOf("BTN1=?") != -1)
    {
      if (digitalRead(pin_btn1))
      {
        status = "BTN1=ON";
      }
      else
      {
        status = "BTN1=OFF";
      }
      cipSend = "AT+CIPSEND=";
      cipSend += 0;
      cipSend += ",";
      cipSend += status.length();
      cipSend += "\r\n";
      EnviaComandoESP01(cipSend, "SEND OK", 2000, "ESP01 - Enviando estado do Botão 1...", "Enviado");
      delay(20);
      ESP01.print(status);
      //EnviaComandoESP01("AT+CIPCLOSE=0","OK",2000,"ESP01 - Fechando","Enviado");
    }

    if (StringEntrada.indexOf("BTN2=?") != -1)
    {
      if (digitalRead(pin_btn2))
      {
        status = "BTN2=ON";
      }
      else
      {
        status = "BTN2=OFF";
      }
      cipSend = "AT+CIPSEND=";
      cipSend += 0;
      cipSend += ",";
      cipSend += status.length();
      cipSend += "\r\n";
      EnviaComandoESP01(cipSend, "SEND OK", 2000, "ESP01 - Enviando estado do Botão 2...", "Enviado");
      delay(20);
      ESP01.print(status);
    }
  }
}