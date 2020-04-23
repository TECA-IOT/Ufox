/*
Derechos Reservados "Teca" 2020, autor Marco A. Caballero Moreno Rev.1.2

UFOX  es un kit de desarrollo Sigfox basado en el microcontrolador 
ATMEGA 32U4 y modem WSSFM10R4 la compilacion es compatible con  Arduino Leonardo
más informacion en https://github.com/TECA-IOT/Ufox
  
  Recepcion de datos local
*/

#include <Ufox.h>

#define btn   13
#define RXLED  17

Ufox wisol;

void setup() {
  pinMode(btn,INPUT);
  pinMode(RXLED,OUTPUT);
  
  Serial.begin(115200);
  wisol.begin(9600);
  
  while(!Serial);  //comentar si usará una fuente de energía externa

}

void loop() {
  
   String rec = wisol.comand("AT$RL");    
   Serial.print("recibido: ");
   Serial.println(rec);
      
}
