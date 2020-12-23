/*
Derechos Reservados "Teca" 2020, autor Marco A. Caballero Rev.1.2
*/
#include "Ufox.h"
#include "Arduino.h"

//uint8_t pin_rst_wisol=12; // pin 12 como reset wisol

//#define baud_ws 9600

//String ATS = "AT$";
//String ENV = "env:> ";
//String RCV = "<rec: "; 

//char cadena_cad[40]= " ";
//uint8_t i = 0;
//char caracter = 0x00;

Ufox::Ufox() {
  dbg = false;
}

Ufox::Ufox(bool _dbg) {
  dbg = _dbg;
}

Ufox::Ufox(bool _dbg,uint8_t _rst_ws) {
  dbg = _dbg;
  pin_rst_wisol=_rst_ws;
}

void Ufox::debug(bool _dbg) {
  dbg = _dbg;
}

void Ufox::begin(uint16_t _baudio) {
  baudio = _baudio;
  pinMode(pin_rst_wisol, OUTPUT);
  Serial1.begin(baud_ws );
  digitalWrite(pin_rst_wisol, LOW);
  delay(100);
  digitalWrite(pin_rst_wisol, HIGH);
  delay(100);
  if (dbg) {
    Serial.begin(baudio);
    // while (!Serial);
  }
}

String Ufox::command(String _cmd) {
  cmd = _cmd;
  if (dbg) {
     Serial.begin(baudio);
     //while (!Serial);
  }

  if (dbg){ Serial.print(ENV);Serial.println(cmd);}

 //Serial.println(cmd);
  long lastMsg = millis();
  caracter = 0x00;
  i = 0;
 for(int a=0;a<=40;a++){cadena_cad[a]= 0x00;}
  Serial1.println(cmd);
  do{
       long now = millis();
       if(now - lastMsg > 70000){
           break;
       }
      if(Serial1.available()){
         caracter = Serial1.read();
         cadena_cad[i] = caracter;
        i++;
      }
   } while (caracter != 0x0A);
  delay(10);
  lastMsg = millis();
  do{
     long now = millis();
     if(now - lastMsg > 70000){
          break;
       }
     if(Serial1.available()){
        caracter = Serial1.read();
        cadena_cad[i] = caracter;
        i++;
    }
   }while (caracter != 0x0A);
  cadena_cad[i] = 0x00;
  cadena_cad[i- 1] = 0x00;

  if (dbg) {Serial.print(RCV);Serial.println(cadena_cad); }
  caracter = 0x00;
  //Serial.println( strlen(cadena_cad));
  return cadena_cad;
}

String Ufox::command2(String _cmd) {
  cmd = _cmd;
  if (dbg) {
    Serial.begin(baudio);
   // while (!Serial);
  }
  if(dbg){ Serial.print(ENV);Serial.println(cmd);}

  caracter = 0x00;

  i = 0;
  uint32_t t = 0;
  for(int a=0;a<=40;a++){cadena_cad[a]= 0x00;}
  Serial1.println(cmd);
  //Serial.println(cmd);
  long lastMsg = millis();
  while (true)
  {
    long now = millis();

    if(Serial1.available()) {
       caracter = Serial1.read();
       if(caracter == 0x0D)caracter = ' ';
       if(caracter == 0x0A)caracter = ' ';
       cadena_cad[i] = caracter;
       //Serial.print(caracter);
       i++;
    }
    if (now - lastMsg > 70000) {
      //Serial.println("salio");
      break;
    }
    if(i==32){
      if(cadena_cad[0]=='O') break;
    }
    if(i==37) break;

  }
  //Serial.println(t);
  //Serial.println(i);
  if (i == 32) {
    cadena_cad[0] = ' ';
    cadena_cad[1] = ' ';
    cadena_cad[2] = ' ';
    char cadena_cad2[35];
    int c = 0;
    for ( c = 0; c <= i - 7; c++) {
      cadena_cad2[c] = cadena_cad[c + 7];
    }
    for ( c = 0; c < sizeof(cadena_cad); c++) {
      cadena_cad[c] = 0x00;
    }

 int k=0,j=0;
 while (cadena_cad2[k]!='\0') 
 {
  if(cadena_cad2[k]!=' ')
  {
   cadena_cad[j]=cadena_cad2[k];
   j++;
  }
  k++;
 }
    //Serial.println(cadena_cad2);
   // Serial.println(cadena_cad);
  }
    //delay(100);
    if (dbg) {Serial.print(RCV);Serial.println(cadena_cad);} 
    caracter = 0x00;
    return String(cadena_cad);
  }

  String Ufox::ID() {
    return Ufox::command(ATS + "I=10");
  }

  String Ufox::PAC() {
    return Ufox::command(ATS + "I=11");
  }

  uint16_t  Ufox::TEMP() {
    return String(Ufox::command(ATS + "T?")).toInt();
  }

  uint16_t  Ufox::VOLT() {

    return  String(Ufox::command(ATS + "V?")).toInt();
  }

  void Ufox::RST() {
    digitalWrite(pin_rst_wisol, LOW);
    delay(100);
    digitalWrite(pin_rst_wisol, HIGH);
    delay(100);
  }

  String Ufox::SLEEP() {
    return Ufox::command(ATS + "P=2");
  }

  String Ufox::SEND(uint32_t _dataint) {
    dataint = _dataint;
    Ufox::command(ATS + "GI?");
    Ufox::command(ATS + "RC");
    char cadena_cad[15] = "";
    sprintf(cadena_cad, "SF=%08lx", dataint);
    return Ufox::command(ATS + cadena_cad);
  }
  
 String Ufox::SEND(String _datastr) {
    datastr = _datastr;
    if (datastr.length() > 24) return ("error");
    if (datastr.length() % 2 != 0)datastr = "0" + datastr;
    Ufox::command(ATS + "GI?");
    Ufox::command(ATS + "RC");
    return Ufox::command(ATS + "SF=" + datastr);
  }
  
  String Ufox::SEND_RCV(uint32_t _dataint_rcv) {
    dataint_rcv = _dataint_rcv;
    Ufox::command(ATS + "GI?");
    Ufox::command(ATS + "RC");
    char cadena_cad[20] = "";
    sprintf(cadena_cad, "SF=%08lx,1", dataint_rcv);
    return Ufox::command2(ATS + cadena_cad);
  }

   String Ufox::SEND_RCV(String _datastr_rcv) {
    datastr_rcv = _datastr_rcv;
    if (datastr_rcv.length() > 24) return ("error");
    if (datastr_rcv.length() % 2 != 0)datastr_rcv = "0" + datastr_rcv;
    Ufox::command(ATS + "GI?");
    Ufox::command(ATS + "RC");
    char cadena_cad[20] = "";
    return Ufox::command2(ATS + "SF=" + datastr_rcv+",1");
  }
