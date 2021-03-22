//UFOX EN MODO DE AHORRO MAXIMO DE ENERGIA
//CON BATERIA DE 2800mAH (18650-litio) PUEDE LLEGAR A DURAR HASTA 30 DIAS.
//POR: MARCO ANTONIO CABALLERO MORENO
//V1 21/03/21
///*********************************************
//ESTE EJEMPLO MUESTRA UN METODO PARA PONER A UFOX EN UN MODO DE BAJO CONSUMO EXTREMO.
//LA COMUNICACION USB ES DESABILITADA PARA AHORRAR LO MAXIMO EN ENERGIA.
//ES POSIBLE SEGUIR CONTADO CON COMUNICACION SERIAlPARA USUARIO, EMPLEANDO UN PIN DIGITAL, PARA ESTE EJEMPLO EL 5,
//USANDO LA LIBRERIA SOFTWARE SERIAL DE ARDUINO. SE REQUIERE UN MODULO CONVERSOR USB A SERIAL
//EXTERNO COMO: FTDI,CP2102, CH340, ETC..
//
//LA LIBRERIA ARDUINO LOW POWER https://github.com/rocketscream/Low-Power, POR ROCKETSCREAM. PROPORCIONA UN METODO 
//SIMPLE PARA ACCERDER A LOS MODOS DE BAJO CONSUMO DEL ATMEGA32U4, ES POSIBLE TEMPORIZAR HASTA UN MAXIMO DE 8 
//SEGUNDOS EN MODO SUSPENSION ALMACENANDO VARIABLES EN RAM, ESTO RESULTA UTIL PARA EJECUCION CONTINUA Y 
//TRANSMISION DE DATOS TEMPORIZADOS SIN REQUERIR A ELECTRONICA ADICIONALES O MODULOS EXTERNOS.
//LA TECNICA EMPLEA UNA VARIABLE CONTADORA "val" QUE SE USA PARA DECIDIR SI ES TIEMPO DE REALIZAR LAS TAREAS O
//PERMANER ESTADO DE SUSPENCION
//EL DISPOSITIVO NO SE REINICIARA LUEGO DE SALIR DEL MODO SUSPENSION, ES DECIR TODAS LAS
//EJECUCIONES SE SEGUIRAN REALIZANDO DENTRO DE LA FUNCION LOOP


#include <LowPower.h>
#include <SoftwareSerial.h>
#include <Ufox.h>

#define RXLED  17 
#define LED  9 

SoftwareSerial mySerial(4, 5); //(RX,TX)

Ufox wisol;

int val=0; //variable contador
int addr=0; //direccion eeprom
float tmp = 83 ; //tiempo que permanecera apagado (Minutos) =  82 *8/60 = 10.9 min

void setup()
{
  //Serial.begin(9600); 
  mySerial.begin(9600); //iniciar serial de usuario pin 5-TX
  wisol.begin(9600); //iniciar radio wisol
  mySerial.println("Iniciando Dispositivo Ufox!");
  //while (!Serial) ;
  delay(100);
  
  wisol.SLEEP();
  pinMode(LED,OUTPUT);
  pinMode(RXLED,OUTPUT);
  
    for(int i=0; i<10;i++){
    digitalWrite(LED,HIGH);
    delay(30);
    digitalWrite(LED,LOW);  
    delay(30);
    }
    
  TASK(); //realizar tareas, lectura de sensores, actuadores, enviar por sigfox, recibir de sigfox,etc...
  mySerial.print("Apagar UFOX (Min): ");
  mySerial.println((tmp*8)/60);
}

void loop() 
{
 val++;
 mySerial.print(".");
    
     if(val >= tmp){
     digitalWrite(LED,LOW);
     mySerial.println("Despertar UFOX! ");
     
     TASK(); //realizar tareas, lectura de sensor, actuadores, enviar por sigfox, recibir de sigfox,etc...
 
     val=0;
     mySerial.print("Apagar UFOX (Min): ");
     mySerial.println((tmp*8)/60);
     LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); //APAGAR
       }   
 LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); //APAGAR
}

void TASK(){
    wisol.RST(); //despertar radio sigfox
      digitalWrite(RXLED,LOW); //encender led
      mySerial.println("Enviar dato Sigfox...");  
      int datos = wisol.VOLT(); //leer la bateria
      mySerial.println(wisol.SEND(datos));    //enviar dato sigfox y mostrar resultado de envio
      mySerial.print("Enviando: ");
      mySerial.println(datos);  
      digitalWrite(RXLED,HIGH);
    wisol.SLEEP();//apagar radio sigfox
}
