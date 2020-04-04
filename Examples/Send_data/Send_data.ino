///////////////////////////////////////
//Derechos reservados por "Teca" 2020//
///////////////////////////////////////
//Aviso://////////////////////////////////////////////////////////////////////
//UFOX es un kit de desarrollo Sigfox basado en el microcontrolador         //
//ATMEGA 32U4. La compilacion es compatible con la tarjeta Arduino Leonardo //
//por lo que todas sus funcionalidades son validas tambien en UFOX.         //
//////////////////////////////////////////////////////////////////////////////
//Algunos comandos basicos:
//                 AT         -> Comando básico
//                 AT$I=10    -> Extraer ID de modem
//                 AT$I=11    -> Extraer PAC de modem
//                 AT$P=2     -> Deep sleep wisol
//                ---------------------
//                -> Enviar un valor hexagesimal, máximo 12 bytes                 
//                 AT$GI?
//                 AT$RC
//                 AT$SF=12AB 
//                 _______________
//                |               |         
//                |               |
//                |     WISOL     |
//                |     Modem     |
//                |  WSSFM10R4AT  |
//                |               |
//                |   |   |   |   |
//                 ---------------
//                   Rst  Rx  TX
//                    |    |   |
//(pin Arduino)       12  TX1 RX1   (Serial1)  

int RXLED = 17;    //  led azul
int rst_wisol=12; // pin 12 como reset modem wisol
int btn=13;       //boton en pin 14

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600); 
  pinMode(btn,INPUT);
  pinMode(RXLED, OUTPUT); 
  
  while (!Serial) {;}//esperar a que puerto serial este disponible|
                    //comentar en caso se requiere hacer uso con aliementacion externa
  reset_wisol();
  send_comand("AT");
  send_comand("AT$I=10");
  send_comand("AT$I=11");
  send_comand("AT$P=2");  //deep sleep modem wisol

  Serial.println("PRESIONE BOTON D13 ");
}

void loop() {
  if(digitalRead(13)==0) //press button D13
  { 
    Serial.println("---Enviando informacion Sigfox---");
    reset_wisol();
    int temp=random(0,100);          //16bits|2bytes
    long latitud=120869717;          //32bits|4bytes
    long longitud=770512918;         //32bits|4bytes
    int bateria=random(3000,3500);   //16bits|2bytes
                                     //Total 12 bytes
    char cadena_data[50]="";
    sprintf(cadena_data,"AT$SF=%04x%08lx%08lx%04x",temp,latitud,longitud,bateria); //formatear cadena a 
    send_comand("AT$GI?");
    send_comand("AT$RC");
    send_comand(String(cadena_data));

    send_comand("AT$P=2");  //deep sleep modem wisol
  
    delay(3000);
    Serial.println("PRESIONE BOTON D13   ");
  }
}


void send_comand(String dat)
{  
digitalWrite(RXLED, LOW);
char caracter;
String cadena=""; 
char dat_cad[50]="";

 dat=dat+"\r\n";
 dat.toCharArray(dat_cad, (dat.length() + 1));  
 Serial.print("env:> ");Serial.print(dat_cad);
 Serial1.write(dat_cad);
  do{
    if(Serial1.available()){
      caracter = Serial1.read();
      cadena+=caracter;
    }
  }while(caracter!=0x0A);
  Serial.print("  < rec: ");
  Serial.print(cadena);
  caracter=0x00;
  cadena="";
  delay(50);
  digitalWrite(RXLED, HIGH);
}

void reset_wisol(){
  pinMode(rst_wisol,OUTPUT); //pin reset wisol
  digitalWrite(rst_wisol,LOW); //reset modem wisol
  delay(100);
  digitalWrite(rst_wisol,HIGH); //reset modem wisol
  delay(100);
}
