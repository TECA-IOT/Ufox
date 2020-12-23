/*
Derechos Reservados "Teca" 2020, autor Marco A. Caballero Rev.1.2

UFOX  es un kit de desarrollo Sigfox basado en el microcontrolador 
ATMEGA 32U4 y modem WSSFM10R4 la compilacion es compatible con  Arduino Leonardo
más informacion en https://github.com/TECA-IOT/Ufox

  este ejemplo necesita un sensor de humedad de suelo capacitivo con salida analogica.
  por ejemplo este de DF-robot o una similar https://wiki.dfrobot.com/Capacitive_Soil_Moisture_Sensor_SKU_SEN0193

  Para desempaquetar esta cadena de datos usted debe configuar un callback 
  personalizado en el backend de sigfox con  las variables correspondientes con las que 
  fueron declarados en este ejemplo.
*/

#include <Ufox.h>

#define btn   13
#define RXLED  17 

Ufox wisol;

const int AirValue = 0;   //el valor que devuelve el sensor cuando esta suspendido en el aire. (no tocar con las manos)
const int WaterValue = 210;  //el valor que devuelve el sensor cuando esta sumerguido en agua. puede usar un vaso con agua del caño.


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
     
     uint16_t  humedad_adc = analogRead(A0); //2bytes
     int   h_r = map(humedad_adc, AirValue, WaterValue, 0, 100);
     uint8_t   humedad_relativa = 0;// solo varia de 0 a 100. un byte es suficiente.
     
     if( h_r<0   ) h_r=0;
     else if( h_r>100 ) h_r=100;

     humedad_relativa = h_r; //1 byte
     
     int16_t temperatura_w = wisol.TEMP();     //int=16bits=2bytes
     uint16_t bateria = wisol.VOLT();         //int=16bits=2bytes
                                                 //Total=7Bytes                                                  
     Serial.print(humedad_adc); Serial.print(" ");
     Serial.print(humedad_relativa); Serial.print(" ");
     Serial.print(temperatura_w); Serial.print(" ");
     Serial.print(bateria); Serial.println(" ");
     
     char buff[30]="";
     //formatear a cadena, convertir los datos a valores hexagesimales
     sprintf(buff,"%04x%02x%04x%04x",humedad_adc,humedad_relativa,temperatura_w,bateria);  
     //Custom payload config   humADC::uint:16 humREL::uint:8 temp::int:16 bat::uint:16

     Serial.print("Enviando: ");
     Serial.println(buff);
     
     Serial.println(wisol.SEND(buff)); //Envio de datos Sigfox
     
     digitalWrite(RXLED,HIGH);
     wisol.SLEEP(); 
     
     delay(3000);
     Serial.println("-Presione botón 13-");
  }
}
