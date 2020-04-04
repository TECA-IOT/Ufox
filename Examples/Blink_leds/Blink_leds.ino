//////////////////////////////////////////////////////////////////////////////
//Derechos Reservados TECA 2020                                             //
//Aviso://////////////////////////////////////////////////////////////////////
// UFOX  es un kit de desarrollo sigfox basado en el microcontrolador       //
//ATMEGA 32U4. La compilacion es compatible con la tarjeta Arduino Leonardo //
//todas sus funcionalidades son validas tambien en UFOX.                    //
//////////////////////////////////////////////////////////////////////////////

int RXLED = 17;  // El RXLED (AZUL) tiene un pin Arduino definido con numero 17

// Nota: el TXLED (ROJO) no tuvo tanta suerte, tendremos que usar valores predefinidos
// macros: TXLED1 = "ON", TXLED0 = "OFF" 
// (También podríamos usar las mismas macros para el LED RX: RXLED1, y RXLED0.)

void setup()
{
  pinMode(RXLED, OUTPUT);  //LED RX como salida
}

void loop()
{
  digitalWrite(RXLED, LOW);   // encender RXLED 
  TXLED0;                   //  apagar TXLED
  delay(1000);                 // Esperar un segundo
  digitalWrite(RXLED, HIGH);    // apagar el RXLED
  TXLED1;                     //TXLED macro, encender TXLED 
  delay(1000);                 // Esperar un segundo
}
