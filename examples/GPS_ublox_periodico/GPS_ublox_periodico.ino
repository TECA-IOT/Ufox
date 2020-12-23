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

  este ejemplo requiere de la libreria TinyGPS https://github.com/mikalhart/TinyGPS
  y un gps compatible. este ejemplo se probo haciendo uso de un UBLOX NEO 6M

  Estas variables en conjunto forman una cadena de 12 bytes.

  Para desempaquetar esta cadena de datos usted debe configuar un callback 
  personalizado en el backend de sigfox con  las variables correspondientes con las que 
  fueron declarados en este ejemplo.
*/

#include <Ufox.h>//para usar el modulo wisol
#define btn   13
#define RXLED  17 
Ufox wisol;

#include <SoftwareSerial.h>//para comunicacion con el gps
#include <TinyGPS.h>
TinyGPS gps;
SoftwareSerial ss(10, 11);

float flat, flon;//float=32bits=4bytes
long lastTx = -70000;

void setup() {
 Serial.begin(115200);
 wisol.begin(9600);
 ss.begin(9600);
 
 //while (!Serial);  //comentar si usará una fuente de energía externa

 pinMode(RXLED,OUTPUT);
 pinMode(btn,INPUT);
 
}

void loop() {

  delay(300);

  
  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;
    while (ss.available())
    {
      char c = ss.read();
      // Serial.write(c); // uncomment this line if you want to see the GPS data flowing
      if (gps.encode(c)) // Did a new valid sentence come in?
        newData = true;
    }

  if (newData)
  {
    //float flat, flon;//float=32bits=4bytes
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
    flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat;
    flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon;
    /*
    Serial.print("LAT=");    
    Serial.print(flat, 6);
    Serial.print(" LON=");    
    Serial.print(flon, 6);
    Serial.print(" SAT=");
    Serial.print(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
    Serial.print(" PREC=");
    Serial.print(gps.hdop() == TinyGPS::GPS_INVALID_HDOP ? 0 : gps.hdop());
    Serial.println("");//*/
  }
  
  /* 
  gps.stats(&chars, &sentences, &failed);
  Serial.print(" CHARS=");
  Serial.print(chars);
  Serial.print(" SENTENCES=");
  Serial.print(sentences);
  Serial.print(" CSUM ERR=");
  Serial.println(failed);
  if (chars == 0)    Serial.println("** No characters received from GPS: check wiring **");//*/


  if( millis()-lastTx>60000 ){

    lastTx = millis();
    
     wisol.RST(); 
     digitalWrite(RXLED,LOW);
     
     int16_t temperatura = wisol.TEMP();      //int=16bits=2bytes
     uint16_t bateria = wisol.VOLT();         //int=16bits=2bytes
                                              //float flat, flon;//float=32bits=4bytes
                                              //Total=12Bytes                                                  
     Serial.print(flat); Serial.print(" ");
     Serial.print(flon); Serial.print(" ");
     Serial.print(temperatura); Serial.print(" ");
     Serial.print(bateria); Serial.println(" ");
     
     char buff[30]="";
     //formatear a cadena, convertir los datos a valores hexagesimales
     sprintf(buff,"%08lx%08lx%04x%04x",flat,flon,temperatura,bateria);  
     //Custom payload config   lat::float:32 long::float:32 temp::int:16 bat::uint:16
     //para recebir los datos puede usar un VPS y traccar con un callback http
     //Url pattern:   http://54.232.160.145:5055/?id={device}&lat={customData#lat}&lon={customData#long}&timestamp={time}&temp={customData#temp}&bat={customData#bat}

     Serial.print("Enviando: ");
     Serial.println(buff);
     
     Serial.println(wisol.SEND(buff)); //Envio de datos Sigfox
     
     digitalWrite(RXLED,HIGH);
     wisol.SLEEP(); 
     
     delay(3000);
     
  }
  
}
