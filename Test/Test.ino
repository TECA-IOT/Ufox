/*
Derechos Reservados "Teca" 2020, autor Marco A. Caballero Rev.1.2

UFOX  es un kit de desarrollo Sigfox basado en el microcontrolador 
ATMEGA 32U4 y modem WSSFM10R4 la compilacion es compatible con  Arduino Leonardo
más informacion en https://github.com/TECA-IOT/Ufox

Se muestra los metodos de la libreria Ufox

*/

#include <Ufox.h>

Ufox wisol;
//Ufox wisol(true);    //debug serial
//Ufox wisol(true,12); //debug serial y pin resest wisol

void setup() {

Serial.begin(115200);
wisol.begin(9600);
delay(5000);
//while (!Serial);
//wisol.debug(false);
Serial.println(wisol.comand("AT"));
Serial.println(wisol.comand("AT$GI?"));
Serial.println(wisol.comand("AT$RC"));
Serial.println(wisol.ID());
Serial.println(wisol.PAC());
Serial.println(wisol.VOLT());
Serial.println(wisol.TEMP());
Serial.println(wisol.SEND(123));
Serial.println(wisol.SLEEP());
delay(10000);
wisol.RST();
Serial.println(wisol.SEND("ABF123")); 
delay(10000);
Serial.println(wisol.SEND_RCV(456));//esperar 1 minuto downlink sigfox
delay(10000);
Serial.println(wisol.SEND_RCV("ABCDF123"));// esperar 1 minuto downlink sigfox
Serial.println(wisol.comand("AT$V?"));

}

void loop() {

}
