// basado en el ejemplo de softrtc.ino de la libreria RTClib
//  https://github.com/adafruit/RTClib
// Date and time functions using just software, based on millis() & timer

#include "RTClib.h"
#include <Ufox.h>

RTC_Millis rtc;
DateTime future;
#define RXLED    17

Ufox wisol;

void setup () {
  Serial.begin(57600);
  while (!Serial); // wait for serial port to connect. Needed for native USB

  // following line sets the RTC to the date & time this sketch was compiled
  rtc.begin(DateTime(F(__DATE__), F(__TIME__)));
  // This line sets the RTC with an explicit date & time, for example to set
  // January 21, 2014 at 3am you would call:
  // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  DateTime now = rtc.now();
  //future = (now + TimeSpan(0, 0, 3, 0));
  future = DateTime(2021, 2, 1, 16, 34, 0);
  Serial.println("boot");
  wisol.begin(9600);
  wisol.SLEEP();
  pinMode(RXLED, OUTPUT);
}

void loop () {
  DateTime now = rtc.now();

  if ( now.unixtime() > future.unixtime() ) {

    future = (future + TimeSpan(0, 0, 3, 0));


    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();

    Serial.print(" seconds since 1970: ");
    Serial.println(now.unixtime());

    // calculate a date which is 7 days and 30 seconds into the future

    Serial.print(" now + timespan ");
    Serial.print(future.year(), DEC);
    Serial.print('/');
    Serial.print(future.month(), DEC);
    Serial.print('/');
    Serial.print(future.day(), DEC);
    Serial.print(' ');
    Serial.print(future.hour(), DEC);
    Serial.print(':');
    Serial.print(future.minute(), DEC);
    Serial.print(':');
    Serial.print(future.second(), DEC);
    Serial.println();
    Serial.println();

    wisol.RST();
    digitalWrite(RXLED, LOW);
    uint16_t adc = analogRead(A0);
    uint16_t bateria = wisol.VOLT();
    Serial.print(  adc  ); Serial.print(" ");
    Serial.print(bateria     ); Serial.println(" ");
    char buff[30] = "";
    //formatear a cadena, convertir los datos a valores hexagesimales
    sprintf(buff, "%04x%04x", adc , bateria);
    //Custom payload config  adc::uint:16 bat::uint:16

    Serial.print("Enviando: ");
    Serial.println(buff);
    Serial.println(wisol.SEND(buff)); //Envio de datos Sigfox
    digitalWrite(RXLED, HIGH);
    wisol.SLEEP();
    TXLED0;                   //  apagar TXLED

  }
  //else {    Serial.println("*");  }
  delay(3000);
}
