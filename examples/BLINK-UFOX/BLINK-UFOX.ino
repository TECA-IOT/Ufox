/*
Derechos Reservados "Teca" 2020, autor Marco A. Caballero Rev.1.2


UFOX  es un kit de desarrollo Sigfox basado en el microcontrolador 
ATMEGA 32U4 y modem WSSFM10R4, la compilacion es compatible con Arduino Leonardo
más informacion en https://github.com/TECA-IOT/Ufox

  Nota: el TXLED (ROJO) no tuvo tanta suerte, tendremos que usar valores predefinidos
  macros: TXLED1 = "ON", TXLED0 = "OFF"
 (También podríamos usar las mismas macros para el LED RX: RXLED1, y RXLED0.)
*/

int RXLED = 17;  // El RXLED (AZUL) tiene un pin Arduino definido con numero 17

void setup()
{
  pinMode(RXLED, OUTPUT);  //LED RX como salida
}

void loop()
{
  digitalWrite(RXLED, LOW);   // encender RXLED 
  TXLED0;                   //  apagar TXLED
  delay(500);                 // Esperar un segundo
  digitalWrite(RXLED, HIGH);    // apagar el RXLED
  TXLED1;                     //TXLED macro, encender TXLED 
  delay(500);                 // Esperar un segundo
}
