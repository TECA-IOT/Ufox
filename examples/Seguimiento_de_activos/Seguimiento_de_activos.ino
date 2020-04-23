/*
Derechos Reservados "Teca" 2020, autor Marco A. Caballero Rev.1.2

UFOX  es un kit de desarrollo Sigfox basado en el microcontrolador 
ATMEGA 32U4 y modem WSSFM10R4 la compilacion es compatible con  Arduino Leonardo
más informacion en https://github.com/TECA-IOT/Ufox

  En este ejemplo se hace el seguimiento de un activo, como en el caso de un 
  carro frigorífico, de alimentos, o incluso traking vehicular, etc. 
  enviando su posición relativa.

  La variable a monitorear es la temperatura, además se envía el voltaje de la 
  bateria en mV del dispositivo.

  Las variables latitud y longitud en formato decimal, las puede reemplazar por
  la lectura de un Gps real.

  Estas variables en conjunto forman una cadena de 12 bytes, al presionar el
   boton 13 los datos son enviados al backend de Sigfox

  Para desempaquetar esta cadena de datos usted debe configuar un callback 
  personalizado en el backend de sigfox con  las variables correspondientes con las que 
  fueron declarados en este ejemplo.
*/

#include <Ufox.h>

#define btn   13
#define RXLED  17 

Ufox wisol;

void setup() {
 Serial.begin(115200);
 wisol.begin(9600);
 
 while (!Serial);  //comentar si usará una fuente de energía externa

 pinMode(RXLED,OUTPUT);
 pinMode(btn,INPUT);
 
Serial.println("-Presione botón 13-");
}

void loop() {

  if(digitalRead(btn)==0){
    
     wisol.RST(); 
     digitalWrite(RXLED,LOW);
     
     uint32_t latitud = 120869717;       //long=32bits=4bytes
     uint32_t longitud = 770512918;      //long=32bits=4bytes
     uint16_t temperatura = wisol.TEMP();     //int=16bits=2bytes
     uint16_t bateria = wisol.VOLT();         //int=16bits=2bytes
                                                 //Total=12Bytes                                                  
     Serial.print(latitud); Serial.print(" ");
     Serial.print(longitud); Serial.print(" ");
     Serial.print(temperatura); Serial.print(" ");
     Serial.print(bateria); Serial.println(" ");
     
     char buff[30]="";
     //formatear a cadena, convertir los datos a valores hexagesimales
     sprintf(buff,"%08lx%08lx%04x%04x",latitud,longitud,temperatura,bateria);  

     Serial.print("Enviando: ");
     Serial.println(buff);
     
     Serial.println(wisol.SEND(buff)); //Envio de datos Sigfox
     
     digitalWrite(RXLED,HIGH);
     wisol.SLEEP(); 
     
     delay(3000);
     Serial.println("-Presione botón 13-");
  }
}