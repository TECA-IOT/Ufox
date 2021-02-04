// basado en el ejemplo de ds3231_alarm.ino de la libreria RTClib
//  https://github.com/adafruit/RTClib

/* Example implementation of an alarm using DS3231

   VCC and GND of RTC should be connected to some power source
   SDA, SCL sof RTC should be connected to SDA, SCL of arduino
   SQW should be connected to CLOCK_INTERRUPT_PIN
   CLOCK_INTERRUPT_PIN needs to work with interrupts
*/

#include <RTClib.h>
#include <Ufox.h>
#include "LowPower.h"

// the pin that is connected to SQW
#define CLOCK_INTERRUPT_PIN 1 // TX0 es un pin se comunicacion serial con el wisol
#define RXLED    17

RTC_DS3231 rtc;
Ufox wisol;

void setup() {
  Serial.begin(9600);
  //while(!Serial);
  delay(3000);

  // initializing the rtc
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC!");
    Serial.flush();
    abort();
  }

  if (rtc.lostPower()) { //poner el RTC a la hora solo si le quitaron la pila
    // this will adjust to the date and time at compilation
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  //we don't need the 32K Pin, so disable it
  rtc.disable32K();
  
  // set alarm 1, 2 flag to false (so alarm 1, 2 didn't happen so far)
  // if not done, this easily leads to problems, as both register aren't reset on reboot/recompile
  rtc.clearAlarm(1);
  rtc.clearAlarm(2);

  // stop oscillating signals at SQW Pin
  // otherwise setAlarm1 will fail
  rtc.writeSqwPinMode(DS3231_OFF);

  // turn off alarm 2 (in case it isn't off already)
  // again, this isn't done at reboot, so a previously set alarm could easily go overlooked
  rtc.disableAlarm(2);
  
  // schedule an alarm 10 seconds in the future
  if (!rtc.setAlarm1(
        rtc.now() + TimeSpan(10),
        //rtc.now() + TimeSpan(0, 0, 3, 0), //dias,horas,minutos,segundos
        //DateTime(2021, 2, 4, 15, 30, 0),
        DS3231_A1_Second // this mode triggers the alarm when the seconds match. See Doxygen for other options
      )) {
    Serial.println("Error, alarm wasn't set!");
  } else {
    Serial.println("Alarm will happen in 10 seconds!");
  }

  
}

void loop() {  
  // print current time
  char date[10] = "hh:mm:ss";
  rtc.now().toString(date);
  Serial.print(date);
  
  Serial.print(" Alarm1: ");
  Serial.print(rtc.alarmFired(1));

  if (rtc.alarmFired(1)) {
    rtc.clearAlarm(1); //liberar el pin que esta siendo  conectado a tierra para que no interfiera con la comunicacion serial
    Serial.println("Alarm cleared");
    

    delay(200);    //asegurarse que las alarmas estan apagadas antes de configurar el wisol para evitar interferencias
    Tx(); //despertar el wisol y transmitir
    delay(100);
    rtc.setAlarm1(   rtc.now() + TimeSpan(90),      DS3231_A1_Second );//configurar proxima alarma
    delay(200);

    pinMode(CLOCK_INTERRUPT_PIN, INPUT);attachInterrupt(digitalPinToInterrupt(CLOCK_INTERRUPT_PIN), onAlarm, CHANGE);//preparar el pin para escuchar eventos

    digitalWrite(RXLED, HIGH);
    TXLED0; //apagar leds para ahorrar energia
    
    
    LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);//poner el micro a dormir
    
    //esta linea no se ejecutara hasta que una interrupcion despiesta el micro
    detachInterrupt(digitalPinToInterrupt(CLOCK_INTERRUPT_PIN) );//deshabilitar interrupcion para que no interfiera con la comunicacion serial
    TXLED1;
    digitalWrite(17, HIGH);
    delay(500);//parpadear leds para señalar que se detecto evento en le pin
    digitalWrite(17, LOW);
    TXLED0;
  }

  Serial.println("");
  delay(200);


}

void onAlarm() {
  Serial.println("Alarm occured!"); //el pin esta siendo conectado a tierra por el RTC
}

void Tx(){
    
  wisol.begin(9600);
  delay(100);
  
      wisol.RST();
      digitalWrite(RXLED, LOW);
      uint16_t bateria = wisol.VOLT();         //int=16bits=2bytes
      uint16_t adc  = analogRead(A0);
      Serial.print(adc); Serial.print(" ");
      Serial.print(bateria     ); Serial.println(" ");

      char buff[30] = "";
      //formatear a cadena, convertir los datos a valores hexagesimales
      sprintf(buff, "%04x%04x",adc, bateria);
      //Custom payload config  adc::uint:16 bat::uint:16

      Serial.print("Enviando: ");
      Serial.println(buff);

      Serial.println(wisol.SEND(buff)); //Envio de datos Sigfox

      digitalWrite(RXLED, HIGH);
      //wisol.SLEEP();
      delay(1000);
      wisol.RST();
      Serial1.end();
  }
