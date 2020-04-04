///////////////////////////////////////
//Derechos Reservados por "TECA" 2020//
///////////////////////////////////////

//Aviso://////////////////////////////////////////////////////////////////////
//UFOX es un kit de desarrollo Sigfox basado en el microcontrolador         //
//ATMEGA 32U4. La compilacion es compatible con la tarjeta Arduino Leonardo //
//por lo que todas sus funcionalidades son validas tambien en UFOX.         //
//////////////////////////////////////////////////////////////////////////////
// Introducir comandos AT en la terminal Seria a 9600 baudios (Nueva línea)
// dentro de la documentacion se adjunta una hoja de datos del modem wisol wssfm10r4at
//Algunos comandos basicos:
//                 AT         -> Comando básico
//                 AT$I=10    -> Extraer ID de modem
//                 AT$I=11    -> Extraer PAC de modem
//                 AT$GI?
//                 AT$RC
//                 AT$SF=12AB -> Enviar un valor hexagesimal
//                 _______________
//                |               |         
//                |               |
//                |     WISOL     |
//                |     Modem     |
//                |  WSSFM10R4AT  |
//                |               |
//                |   |   |   |   |
//                 ---------------
//                   Rst  Rx  TX
//                    |    |   |
//(pin Arduino)       12  TX1 RX1   (Serial1)  


void setup() {
  
  Serial.begin(9600);
  Serial1.begin(9600);
  while (!Serial) {;} //Esperar hasta que el  puerto serial se encuentre disponible

  Serial.println("¡Bienvenido Ufox!");
  Serial.println("escribe un comando AT");
}

void loop() {
   while (Serial.available()) {
    Serial1.write(Serial.read());
  }
  while (Serial1.available()) {
    Serial.write(Serial1.read());
  }
}
