#include <Arduino.h>

//DECLARAÇÃO DA CLASSE LED
class Led {
    public: //TUDO QUE ESTIVER NO PUBLIC É VISTO 
        Led(int pin); // CONSTRUCTOR DA CLASSE LED
        int pino; // Propriedade Pino do LED
        String cor; // Propriedade Cor do LED
        String descricao; //Propriedade Descrição do LED
        void ligar(); //Função para ligar o led
        void desligar(); //Função para desliga o led
        void piscar(int tempo); //Função para piscar o led com intervalo definido (tempo (ms))
};
