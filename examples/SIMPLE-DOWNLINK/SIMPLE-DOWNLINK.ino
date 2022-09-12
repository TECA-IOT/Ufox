/*
Derechos Reservados "Teca" 2022, autor Marco A. Caballero Rev.1.3

UFOX  es un devkit Sigfox basado en el microcontrolador 
ATMEGA 32U4 y modem Sigfox SFM10R4 (RC4) la compilacion es compatible con  Arduino Leonardo
más informacion en https://github.com/TECA-IOT/Ufox

 En el proceso de downlink Sigfox, el dispositivo inicia la comunicacion 
 transmitiendo un frame de 12 bytes como máximo la red (Similar al uplink),
 con la diferencia que el dispositivo queda a la espera de mensajes de la red para recepcion.
 
 El proceso tarda aproximandamente un minuto, el tamaño de los datos recibidos 
con un tamaño maximo de 8 bytes.

 Previamente su cuenta de backend Sigfox debe estar habilitado con el respectivo token de suscripcion
 del deispositivo.
 
 Para el envío de mensajes  y recepcion de downlink personalizados puede definir una variable String o char
 array, usted deberá dar el formato hexagesimal adecuado. puede hacer uso de la 
 funcion "sprintf()" para el formateo de datos a valores hexagesimales y entregarlo al método
 ".SEND_RCV()" para el envío. La funcion al termino del downlink retornara una cadena de en formato string 
 conteniendo los valores en hexadecimal.
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
  
  while(!Serial);  //comentar si usará una fuente de energía externa
  
  Serial.println("-Presione botón 13-");
 
}

void loop() {

  if(digitalRead(btn)==0){
    
    digitalWrite(RXLED,LOW);
    ufox.RST();
    
    uint32_t valor =random(0,150); //valor a enviar
    Serial.println("UPLINK: "); Serial.println(valor);
    
    String valor_recibido = ufox.SEND_RCV(valor); //aproximandamente esperar 1 minuto 
    
    //uint32_t valor ="10"; //valor a enviar
    // String valor_recibido = ufox.SEND_RCV(valor); 
   
    Serial.println("DOWNLINK: "); Serial.println(valor_recibido);                    
                                         
    digitalWrite(RXLED,HIGH);
    ufox.SLEEP();
    delay(3000);
    Serial.println("-Presione botón 13-");
    
   }
}
