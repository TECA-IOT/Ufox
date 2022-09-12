/*
Derechos Reservados "Teca" 2020, autor Marco A. Caballero Moreno Rev.1.2

UFOX  es un kit de desarrollo Sigfox basado en el microcontrolador 
ATMEGA 32U4 y modem WSSFM10R4 la compilacion es compatible con  Arduino Leonardo
más informacion en https://github.com/TECA-IOT/Ufox
  
  Envio de datos local
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
  
  //while(!Serial);  //comentar si usará una fuente de energía externa

  delay(5000);
  Serial.println("-Presione botón 13-");
}

void loop() {
  
   if(digitalRead(btn)==0){
    
      digitalWrite(RXLED,LOW);
      wisol.RST();
      
      String id=wisol.ID();
      
      Serial.println(wisol.command("AT$SL="+id));
      
      digitalWrite(RXLED,HIGH);
      wisol.SLEEP();
      delay(3000);
      
      Serial.println("-Presione botón 13-");
   }
}
