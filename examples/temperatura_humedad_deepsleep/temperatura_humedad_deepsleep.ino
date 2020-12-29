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

  tambien es necesaria la libreria lowpower:
  -  rocketscream / Low-Power  Library: https://github.com/rocketscream/Low-Power
  lea los ejemplos incluidos en la libreria.

  Para desempaquetar esta cadena de datos usted debe configuar un callback 
  personalizado en el backend de sigfox con  las variables correspondientes con las que 
  fueron declarados en este ejemplo.
*/


#include <Ufox.h>
#include "LowPower.h"
const int wakeUpPin = 2;
//se necesita un pin con interrupcion. en el ufox, los pines 0,1,2,3 tiene interrupcion. el pin 0 y 1 esta ocupados en el serial1, conectaddo al modulo wisol
#define RXLED  17 

Ufox wisol;

#include "DHT.h"

#define DHTPIN 2     // Digital pin connected to the DHT sensor
// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);

void wakeUp()
{
    // una funcion vacia, solo para "despertar" el cpu.
}

void setup() {
 Serial.begin(115200);
 wisol.begin(9600);
 dht.begin();

 pinMode(RXLED,OUTPUT);
 pinMode(wakeUpPin, INPUT_PULLUP);   
 attachInterrupt(digitalPinToInterrupt(wakeUpPin), wakeUp, LOW);
 
 //while (!Serial);  //comentar si usará una fuente de energía externa

Serial.println("-Presione botón 2-");
}

void loop() {
  
     LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF); //el Serial dejara de funcionar despues del primer deep sleep
     //el modulo entrara en modo de "sueño porfundo" (ahorro de energia). el cpu permanece pausado hasta recibir una interrupcion por algun pin o un timer.
     wisol.RST(); 
     digitalWrite(RXLED,LOW);
     
     uint8_t  humedad = dht.readHumidity();// varia entre 0% hasta 100% un byte es suficiente
     int16_t temperatura_dht = dht.readTemperature()*10; // multiplicamos por 10 antes de convertirlo en entero con signo para no perder un decimal. 2bytes
     uint16_t temperatura_w = wisol.TEMP();     //int=16bits=2bytes
     uint16_t bateria = wisol.VOLT();         //int=16bits=2bytes
                                                 //Total=7Bytes                                                  
     Serial.print(humedad); Serial.print(" ");
     Serial.print(temperatura_dht); Serial.print(" ");
     Serial.print(temperatura_w); Serial.print(" ");
     Serial.print(bateria); Serial.println(" ");
     
     char buff[30]="";
     //formatear a cadena, convertir los datos a valores hexagesimales
     sprintf(buff,"%02x%04x%04x%04x",humedad,temperatura_dht,temperatura_w,bateria);  

     Serial.print("Enviando: ");
     Serial.println(buff);
     
     Serial.println(wisol.SEND(buff)); //Envio de datos Sigfox
     
     digitalWrite(RXLED,HIGH);
     wisol.SLEEP(); 
     
     delay(3000);
     Serial.println("-Presione botón 2-");
     
     //LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF); //el Serial dejara de funcionar despues del primer deep sleep
     
}
