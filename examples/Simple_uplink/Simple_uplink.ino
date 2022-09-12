/*
Derechos Reservados "Teca" 2020, autor Marco A. Caballero Rev.1.3

UFOX  es un devkit Sigfox basado en el microcontrolador 
ATMEGA 32U4 y modem Sigfox SFM10R4 (RC4) la compilacion es compatible con  Arduino Leonardo
más informacion en https://github.com/TECA-IOT/Ufox

 - Envío de un valor numérico random simple. -
 
 Los mensajes de tipo entero son convertidos a valores hexagesimal automaticamente por la libreria, el 
 metodo ".SEND()" soporta variables tipo uint32_t y cadenas string. Tenga en cuenta que el payload sigfox
 es como maximo de 12bytes por mensaje.
 
 Para el envío de mensajes mas extensos puede definir una variable String o char
 array, usted deberá dar el formato a hexagesimal adecuado. puede hacer uso de la funcion 
 "sprintf()" para el formateo de datos a valores hexagesimales y entregarlo omo cadena al método
 ".SEND()".
*/

#include <Ufox.h>

#define btn   13
#define RXLED  17 

Ufox ufox;

void setup() {
  pinMode(btn,INPUT);
  pinMode(RXLED,OUTPUT);
  
  Serial.begin(115200);
  ufox.begin(9600);

  while(!Serial);  //es necesario comentar esta linea si usará una fuente de energía externa

 Serial.println("-Presione botón 13-");
}

void loop() {
  
  if(digitalRead(btn)==0){

    digitalWrite(RXLED,LOW);
    ufox.RST(); //despertar o resetear modem sigfox
    
    uint32_t valor =random(0,150);
    Serial.println("valor:"); Serial.println(valor); //imprimir en consola serial el mensaje
    ufox.SEND(valor); //transmitir mensaje Sigfox

    //String valor2 ="10";
    //Serial.println(wisol.SEND(valor2));
    
    digitalWrite(RXLED,HIGH);
    ufox.SLEEP(); //mandar a deep sleep modem sigfox
    delay(3000);
    Serial.println("-Presione botón 13-");
  }
  
}
