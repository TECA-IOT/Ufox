/*
Derechos Reservados "Teca" 2020, autor Marco A. Caballero Rev.1.2

UFOX  es un kit de desarrollo Sigfox basado en el microcontrolador 
ATMEGA 32U4 y modem WSSFM10R4 la compilacion es compatible con  Arduino Leonardo
más informacion en https://github.com/TECA-IOT/Ufox

Extraer ID y PAC de modem wssfm10R4
Estos Valores son requeridos para la activacion del dispositivo en la red Sigfox

*/

#include <Ufox.h>

Ufox wisol;

void setup() {
  Serial.begin(115200);
  wisol.begin(9600);
  
  while(!Serial);

  delay(1000);

  Serial.print("ID: ");
  Serial.println(wisol.ID());
    
  Serial.print("PAC: ");
  Serial.println(wisol.PAC());

  
}

void loop() {
  // put your main code here, to run repeatedly:

}
