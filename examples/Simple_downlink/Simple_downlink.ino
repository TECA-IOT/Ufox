/*
Derechos Reservados "Teca" 2020, autor Marco A. Caballero Rev.1.2

UFOX  es un kit de desarrollo Sigfox basado en el microcontrolador 
ATMEGA 32U4 y modem WSSFM10R4 la compilacion es compatible con  Arduino Leonardo
más informacion en https://github.com/TECA-IOT/Ufox

 En el proceso de  downlink Sigfox, el dispositivo inicia la comunicacion 
 con la red enviando un mensaje de 12 bytes como máximo (Similar al uplink),
 con la diferencia que el dispositivo queda a la escuha de la red.
 
 El proceso tarda aproximandamente un minuto, el tamaño de los datos recibidos 
 es de 8 bytes.

 Previamente su cuenta de backend Sigfox debe estar habilitado para el downlink, 
 puede configurar un Device type personalizado y seleccionar entre el modo
 "DIRECT" o "CALLBACK"
 
 Los mensajes tipo entero son convertidos a hexagesimal automaticamente por el 
 metodo ".SEND_RCV()" . Soporta  variables tipo uint32_t.
 
 Para el envío de mensajes personalizados puede definir una variable String o char
 array, usted deberá dar el formato hexagesimal adecuado. puede hacer uso de la 
 funcion "sprintf()" para el formateo de datos a valores hexagesimales y entregarlo al método
 ".SEND_RCV()" para el envío.
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
  
  while(!Serial);  //comentar si usará una fuente de energía externa
  
  Serial.println("-Presione botón 13-");
 
}

void loop() {

  if(digitalRead(btn)==0){
    
    digitalWrite(RXLED,LOW);
    wisol.RST();
    
    uint32_t valor =10; //valor a enviar
    
    String valor_recibido = wisol.SEND_RCV(valor); //aproximandamente esperar 1 minuto 
    
    //uint32_t valor ="10"; //valor a enviar
    // String valor_recibido = wisol.SEND_RCV(valor); 
   
    Serial.println(valor_recibido);                 
                                         
    digitalWrite(RXLED,HIGH);
    wisol.SLEEP();
    delay(3000);
    Serial.println("-Presione botón 13-");
    
   }
}
