/*
Derechos Reservados "Teca" 2022, autor Marco A. Caballero Rev.1.3

UFOX  es un kit de desarrollo Sigfox basado en el microcontrolador 
ATMEGA 32U4 y modem WSSFM10R4 la compilacion es compatible con  Arduino Leonardo
más informacion en https://github.com/TECA-IOT/Ufox

  En este ejemplo se hace envio de multiples datos, puede aplicarse en ejemplos de tracking de vehiculos, 
  cadena de frio, gps, entre otros.

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

Ufox ufox;

void setup() {
  delay(3000);
 Serial.begin(115200);
 ufox.begin(9600);
 
 while (!Serial);  //es necesario comentar esta linea si usará una fuente de energía externa

 pinMode(RXLED,OUTPUT);
 pinMode(btn,INPUT);
 
Serial.println("-Presione botón 13-");
}

void loop() {

  if(digitalRead(btn)==0){
    
     ufox.RST(); 
     digitalWrite(RXLED,LOW);
     
     int32_t latitud = 120869717;       //long=32bits=4bytes
     int32_t longitud = 770512918;      //long=32bits=4bytes
     int16_t temperatura = ufox.TEMP();     //int=16bits=2bytes
     uint16_t bateria = ufox.VOLT();         //int=16bits=2bytes
                                                 //Total=12Bytes  
                                                                                                 
     Serial.print(latitud); Serial.print(" ");
     Serial.print(longitud); Serial.print(" ");
     Serial.print(temperatura); Serial.print(" ");
     Serial.print(bateria); Serial.println(" ");
     
     char buff[30]="";
     //formatear a cadena, convertir los datos a valores hexagesimales
     // MÁS INFORMACIÓN http://perlenespanol.com/tutoriales/funciones/funciones_printf_y_sprintf.html
     sprintf(buff,"%08lx%08lx%04x%04x",latitud,longitud,temperatura,bateria);  
     //Custom payload config   lat::int:32 long::int:32 temp::int:16 bat::uint:16

     Serial.print("UPLINK: ");  Serial.println(buff);   
     Serial.println(ufox.SEND(buff)); //Envio de datos Sigfox
     
     digitalWrite(RXLED,HIGH);
     ufox.SLEEP(); 
     
     delay(3000);
     Serial.println("-Presione botón 13-");
  }
}
