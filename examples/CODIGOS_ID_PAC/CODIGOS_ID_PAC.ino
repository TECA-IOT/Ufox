/*
Derechos Reservados "Teca" 2020, autor Marco A. Caballero Rev.1.3

UFOX  es un kit de desarrollo Sigfox basado en el microcontrolador 
ATMEGA 32U4 y modem SFM10R4 la compilacion es compatible con  Arduino Leonardo
más informacion en https://github.com/TECA-IOT/Ufox

Extraer los codigos "ID y PAC" del modem Sigfox SFM10R4
Estos codigos son requeridos para la activacion del dispositivo en la red Sigfox

*/

#include <Ufox.h>

Ufox ufox;

void setup() {
  Serial.begin(115200);
  ufox.begin(9600);
  
  while(!Serial); //es necesario comentar esta linea si usará una fuente de energía externa

  delay(1000);

  Serial.print("ID: ");
  Serial.println(ufox.ID());
    
  Serial.print("PAC: ");
  Serial.println(ufox.PAC());

  
}

void loop() {
  // put your main code here, to run repeatedly:

}
