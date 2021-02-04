// video tutorial disponible en https://github.com/TECA-IOT
#include <Ufox.h>

#define btn      13
#define RXLED    17
#define alarma    1
#define inactivo  0
#define pinEvento 2

byte Evento = inactivo;

long ts = 0 ;
long TimeOutTrigger = 15*60*1000L;
long TimeOutRutina = 4*60*60*1000L;
Ufox wisol;

void onAlarm() {
 Evento = alarma;
}


void setup() {
  Serial.begin(115200);
  wisol.begin(9600);

  while (!Serial);  //comentar si usará una fuente de energía externa

  pinMode(RXLED, OUTPUT);
  pinMode(pinEvento, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pinEvento), onAlarm, CHANGE);
  delay(1000);
  Evento = inactivo;
  ts = - TimeOutTrigger;
  Serial.println("Boot");
}

void loop() {

  if (Evento) {
    if ( (millis() - ts) < ( TimeOutTrigger )) {
      Evento = inactivo;
      //pirEstado = inactivo;//limpiar variables
      Serial.print("<");
    }
    else {
      ts = millis();
      Serial.println("Evento!");
      Tx();


      Evento = inactivo;
    }
  }
  
  delay(500);
}

void Tx(){
  
      wisol.RST();
      digitalWrite(RXLED, LOW);
      uint16_t bateria = wisol.VOLT();         //int=16bits=2bytes
      //Total=7Bytes
      byte Estado = digitalRead(pinEvento);
      Serial.print(Evento); Serial.print(" ");
      Serial.print(Estado   ); Serial.print(" ");
      Serial.print(bateria     ); Serial.println(" ");

      char buff[30] = "";
      //formatear a cadena, convertir los datos a valores hexagesimales
      sprintf(buff, "%02x%02x%04x", Evento, Estado, bateria);
      //Custom payload config  evento::uint:8 estado::uint:8 bat::uint:16

      Serial.print("Enviando: ");
      Serial.println(buff);

      Serial.println(wisol.SEND(buff)); //Envio de datos Sigfox

      digitalWrite(RXLED, HIGH);
      wisol.SLEEP();
  }
