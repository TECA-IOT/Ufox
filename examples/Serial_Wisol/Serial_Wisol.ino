/*
Derechos Reservados "Teca" 2020, autor Marco A. Caballero Rev.1.2

UFOX  es un kit de desarrollo Sigfox basado en el microcontrolador 
ATMEGA 32U4y modem WSSFM10R4  la compilacion es compatible con  Arduino Leonardo
más informacion en https://github.com/TECA-IOT/Ufox


En este ejemplo tienes que introducir comandos AT en la terminal Serial a 9600 baudios (Nueva línea)
dentro de la documentacion se adjunta una hoja de datos del modem wisol wssfm10r4at
Algunos comandos basicos:
                 AT         -> Comando básico
                 AT$I=10    -> Extraer ID de modem
                 AT$I=11    -> Extraer PAC de modem
                 Enviar un valor hexagesimal:
                 AT$GI?
                 AT$RC
                 AT$SF=12AB
                 _______________
                |               |
                |     WISOL     |
                |     Modem     |
                |  WSSFM10R4AT  |
                |               |
                |   |   |   |   |
                 ---------------
                   Rst  Rx  TX
                    |    |   |
(pin Arduino)       12  TX1 RX1   (Serial1)  
*/

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  while (!Serial) {;} //Esperar hasta que el  puerto com serial se encuentre disponible

  Serial.println("¡Bienvenido!");
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
