/*
ATIVIDADE 3BA - ServerSocket para acionamento de Leds/Relés remotamente. 
CURSO IoT - Julho 2018 
Internet das Coisas com Arduino e ESP-01 
Autor: Prof. Breno M. de Oliveira
*/

#include <Arduino.h> 
#include <SoftwareSerial.h> //Biblioteca para criação de portas seriais (softserial)

//Declarando os pinos dos LEDs
#define pin_led1 8
#define pin_led2 9
#define pin_led3 10
int pinos_leds[] = {pin_led1, pin_led2, pin_led3};

//Cria uma nova interface serial através dos Pinos D2 e D3 do Arduino,
//onde será conectado o módulo wifi ESP-01 
// Pino 2 é o RX do Arduino (TX do ESP) 
// Pino 3 é o TX do Arduino (RX do ESP) - Precisa do divisor de tensão 5V -> 3.3V
SoftwareSerial ESP01(2, 3); 

boolean EnviaComandoESP01(String cmd, String ack, unsigned long timeout, String descricao, String retorno){
  Serial.println(cmd);
  ESP01.println(cmd); // Envia o comando (cmd) para o ESP01 
  timeout = timeout + millis();
 while(millis() < timeout){
  if (ESP01.available()){
    String resposta = ESP01.readString();
    resposta.trim();
    if (resposta.indexOf(ack) != -1){

       if (ack == "+CIFSR:STAIP,") {
         int i1 = resposta.indexOf("+CIFSR:STAIP,") + 13; //13 é o tamanho de "+CIFSR:STAIP,"
         int i2 =  resposta.indexOf("+", i1+2);
         Serial.print("IP:");
         String ip = resposta.substring(i1,i2);
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
 
void setup()
{
 pinMode(pinos_leds[0],OUTPUT);
 pinMode(pinos_leds[1],OUTPUT);
 pinMode(pinos_leds[2],OUTPUT);
 Serial.begin(9600);
 ESP01.begin(9600);
 
EnviaComandoESP01("AT+RST", "Ready",5000,"ESP01 - Resetando o ESP01", "Reset OK");
EnviaComandoESP01("AT+CWQAP","OK", 5000,"ESP01 - Desconectando de Redes Anteriores...", "Desconectado!");
EnviaComandoESP01("AT+CWMODE=1","OK",5000,"ESP01 - Setando Modo Station...","Setado!"); 
EnviaComandoESP01("AT+CWJAP=\"CursoIoT\",\"julho2018\"","WIFI GOT IP",20000,"ESP01 - Conectando na Rede CursoIoT...","Conectado!");
EnviaComandoESP01("AT+CIFSR", "+CIFSR:STAIP,",5000,"ESP01 - Adquirindo numero de IP...","IP Adquirido:"); 
EnviaComandoESP01("AT+CIPMUX=1","OK",5000,"ESP01 - Setando TCPServer para multiplas conexoes (Max 5) ...","TCPServer Multiplicas Conexoes OK");
EnviaComandoESP01("AT+CIPSERVER=1,80","OK",5000,"ESP01 - Startando o TCPServer na porta 80...","TCPServer Operante");
}
 
void loop(){

 String StringEntrada="";  //Armazena as Strings vindas do Wifi
 boolean StringPronta = false; // Flag de controle das strings vindas do Wifi
 
 while (ESP01.available()){
   StringEntrada=ESP01.readString();
   StringEntrada.trim(); // Remove caracteres fantasmas (single space (ASCII 32), tab (ASCII 9), vertical tab (ASCII 11), form feed (ASCII 12), carriage return (ASCII 13), or newline (ASCII 10))
   StringPronta = true;
  }
 
  if (StringPronta){  
  
  if (StringEntrada.indexOf("LED1=ON") != -1) { //Se encontrar a String "LED1=ON" dentro da StringEntrada
    digitalWrite(pinos_leds[0],HIGH);
    Serial.println("LED1 - Aceso" );
   }

   if (StringEntrada.indexOf("LED2=ON") != -1) { 
    digitalWrite(pinos_leds[1],HIGH);
    Serial.println("LED2 - Aceso" );
   }
 
  if (StringEntrada.indexOf("LED3=ON") != -1) {
    digitalWrite(pinos_leds[2],HIGH);
    Serial.println("LED3 - Aceso" );
   }

  if (StringEntrada.indexOf("LED1=OFF") != -1) {
    digitalWrite(pinos_leds[0],LOW);
    Serial.println("LED1 - Apagado" );
   }

  if (StringEntrada.indexOf("LED2=OFF") != -1) {
    digitalWrite(pinos_leds[1],LOW);
    Serial.println("LED2 - Apagado" );
   }

  if (StringEntrada.indexOf("LED3=OFF") != -1) {
    digitalWrite(pinos_leds[2],LOW);
    Serial.println("LED3 - Apagado" );
   }

  }

 } 