/*
Derechos Reservados "Teca" 2020, autor Marco A. Caballero Rev.1.2

UFOX  es un kit de desarrollo Sigfox basado en el microcontrolador 
ATMEGA 32U4 y modem WSSFM10R4 la compilacion es compatible con  Arduino Leonardo
más informacion en https://github.com/TECA-IOT/Ufox

  este ejemplo necesita un sensor DHT22 y las librerias de adafruit:
  - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
  - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor
  para mas informacion lea los ejemplos incluidos con sus respectivas librerias
  compruebe el correcto funcionamiento del DHT usando el ejemplo DHTtester de adafruit

  Para desempaquetar esta cadena de datos usted debe configuar un callback 
  personalizado en el backend de sigfox con  las variables correspondientes con las que 
  fueron declarados en este ejemplo.
*/

#include <Ufox.h>

#define btn   13
#define RXLED  17 

Ufox wisol;

#include "DHT.h"

#define DHTPIN 2     // Digital pin connected to the DHT sensor
// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);

void setup() {
 Serial.begin(115200);
 wisol.begin(9600);
 dht.begin();
 
 while (!Serial);  //comentar si usará una fuente de energía externa

 pinMode(RXLED,OUTPUT);
 pinMode(btn,INPUT);
 
Serial.println("-Presione botón 13-");
}

void loop() {

  if(digitalRead(btn)==0){
    
     wisol.RST(); 
     digitalWrite(RXLED,LOW);
     
     uint8_t  humedad = dht.readHumidity();// varia entre 0% hasta 100% un byte es suficiente
     int16_t temperatura_dht = dht.readTemperature()*10; // multiplicamos por 10 antes de convertirlo en entero con signo para no perder un decimal. 2bytes
     int16_t temperatura_w = wisol.TEMP();     //int=16bits=2bytes
     uint16_t bateria = wisol.VOLT();         //int=16bits=2bytes
                                                 //Total=7Bytes                                                  
     Serial.print(humedad); Serial.print(" ");
     Serial.print(temperatura_dht); Serial.print(" ");
     Serial.print(temperatura_w); Serial.print(" ");
     Serial.print(bateria); Serial.println(" ");
     
     char buff[30]="";
     //formatear a cadena, convertir los datos a valores hexagesimales
     sprintf(buff,"%02x%04x%04x%04x",humedad,temperatura_dht,temperatura_w,bateria);  
     //Custom payload config   hum::uint:8 tmpD::int:16 tmpW::int:16 bat::uint:16

     Serial.print("Enviando: ");
     Serial.println(buff);
     
     Serial.println(wisol.SEND(buff)); //Envio de datos Sigfox
     
     digitalWrite(RXLED,HIGH);
     wisol.SLEEP(); 
     
     delay(3000);
     Serial.println("-Presione botón 13-");
  }
}
