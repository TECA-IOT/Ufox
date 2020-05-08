# Ufox devkit Sigfox 
![](https://github.com/TECA-IOT/Ufox/blob/master/image/Ufox.jpg )
Kit de desarrollo Sigfox para region RC4 ( Latinoamerica: Argentina, Chile, Colombia, Costa Rica, El Salvador, Guatemala, Honduras, Nicaragua, Panama, Perú, Trinidad & Tobago, Uruguay.
Asia pacifico: Australia, Hong Kong, Indonesia, Malasia, Nueva Zelanda, Singapure, Taiwán, Thailandia.


## Caracteristicas

- Microcontrolador Atmega32U4 USB y Modem Wisol WSSFM10R4 RC4 .
- Programable con Arduino IDE (compatible con pines de arduino Leonardo, ProMicro, Micro, y otras placas arduino basadas en el micro atmega32U4).
- Incluye una antena interna helicoidal  de 2.5 Dbi y opcionalmente un conector  UFL para antenas externas. (se recomienda previamente desoladar la antena helicoidal para su uso). 
- Alimentacion desde fuente USB 5V con voltaje de operacion interno de 3.3V.
- Ideal para desarrollar prototipos y aplicaciones de forma rapida y sencilla, incluye un microcotrolador Atmega32U4  compatible con arduino.
- Cuenta con un regulador de voltaje de 3.3V AMS1117  suministra  hasta 1 amperio de corriente.
- Diseño compacto, seguro y de bajo consumo
- Comunicacion serial por Hardware (Serial1 Arduino) dedicado exclusivamente para comunicacion con modem Wisol.
- Reset de modulo Wisol Conectado al Pin "12" Arduino. 
- Boton de proposito general programable en el pin "13" Arduino
- Pines Digitales, Analogicos, PWM, comunicacion SPI, I2C,Interrupcion externa, Serial.
- informacion acerca de arduino leonardo: 
`<link>` : <https://store.arduino.cc/usa/leonardo>


## Caracteristicas Electricas

| Descripcion | Unidad                    |
| ------------- | ------------------------------ |
| Voltaje Minimo  Vin |  3.7 Voltios    |  
| Voltaje Maximo  Vin |  9 Voltios    |  
| Voltaje  alimentacion VCC |  3.3 Voltios    | 
| Corriente maxima   | 1A     |
| Antena helicoidal    | 2.5 DBi      |
| Frec. Uplink     | 920.8 MHz      |
| Frec. Downlink     | 922.3 MHz      |


## Descripcion de pines Ufox

![](https://github.com/TECA-IOT/Ufox/blob/master/image/PINOUT_ufox_R1_3.png)


# Cargar un Sketch a Ufox
- Enchufe el cable micro usb con  el conector micro usb de Ufox, luego enchufar el cable microusb usb a su PC
- Espere a que su PC  reconosca a Ufox (el reconocimiento es instantaneos para SO Window ,7,8,10).
- Abra el Ide Arduino.
- Puede cargar un  ejemplo de inicio  como el siguiente:

### Blink Ufox
Ufox dispone de 2 led de señalizacion Serial Tx y RX, el usuario puede hacer uso de estos led, en este ejemplo se muestra como hacer uso de ellos.

```javascript

int RXLED = 17;  // El RXLED (AZUL) tiene un pin Arduino definido con numero 17

void setup()
{
  pinMode(RXLED, OUTPUT);  //LED RX como salida
}

void loop()
{
  digitalWrite(RXLED, LOW);   // encender RXLED 
  TXLED0;                   //  apagar TXLED
  delay(500);                 // Esperar un segundo
  digitalWrite(RXLED, HIGH);    // apagar el RXLED
  TXLED1;                     //TXLED macro, encender TXLED 
  delay(500);                 // Esperar un segundo
}
```

#### Comuncacion Serial con modem Wisol
*El modem Wisol WSSFM10R4AT puede comunicarse mediante comunicacion seral a 9600 baudios, con una sintaxis definida con comando "AT", puede consultar mas informacion de comandos en la hoja de datos (datasheet). El modem trabaja a una frecuencia de 920MHZ Uplink y 922 Dowlink. Consulte mas informacionde como activar el mdem en la platafoma de sigfox o con su operador sigfox Local : Aqui 

```javascript
void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
   while (Serial.available()) {
    Serial1.write(Serial.read());
  }
  while (Serial1.available()) {
    Serial.write(Serial1.read());
  }
  
}
```


- Selecciones la placa Arduino Leonardo y seleccion el puerto COM detectado en su PC.
- Y cargue el sketch.

![](https://github.com/markoAntonio1692/32U4-DEVKIT-SIGFOX/blob/master/image/arduino.jpg)


- Una vez cargado el sketch abra la terminal serial a 9600 baudios, seleccionar la opcion "Nueva línea".
- Escribir el comando "AT",presionar  enter, y a continuacion el chip wisol respondera con un "Ok"  
- Comandos de interes:
- ID:          AT$I=10
- PAC:         AT$I=11
- Voltaje:     AT$V?
- Temperatura: AT$T?

![](https://github.com/markoAntonio1692/32U4-DEVKIT-SIGFOX/blob/master/image/AT.JPG)


#### ENVIAR UN MENSAJE con comandos
Enviar un mensaje a backend sigfox sera el siguiente: 255 decimal, SIGA LA SECUENCIA DE COMANDOS SIGUIENTE:
- AT$GI?
- AT$RC
- AT$SF=FF

## LIBRERÍA UFOX ARDUINO
La libreria ufox incorpora una serie de funciones y metodos que simplifican la conexion a la red de sigfox. Instale la libreria Ufox  en el IDE de arduino descargando este repositorio, existen diversos modos de instalar libreria externas, 
- Opcion 1: descomprima este repositorio .ZIP y copie la carpeta dentro de :  [Unidad]:\Users\[usuario]\Documents\Arduino\libraries
- Opcion 2: desde el mismo IDE Arduino dirijase a "Programa, Incluir  Libreria, Añadir biblioteca  .ZIP" localice el repositorio descargado y abrir.

- Una vez instalado recargue el  Ide arduino y podra ver que la libreria y ejemplo se muestran: 

![](https://github.com/TECA-IOT/Ufox/blob/master/image/lib_ufox1.png)



### Enviar un Mensaje Simple
En este ejemplo puede enviar un Mensaje numerico cada vez que el boton 13 sea presionado, tenga en cuenta que los mensajes sigfox son hexagesimales de maximo 12 bytes, todos los valores numericos seran convertidos a valores hexagesimales

```javascript
#include <Ufox.h>

#define btn   13
#define RXLED  17 

Ufox wisol;

void setup() {
  pinMode(btn,INPUT);
  pinMode(RXLED,OUTPUT);
  
  Serial.begin(115200);
  wisol.begin(9600);

  while(!Serial);  //comentar si usará una fuente de energía externa

 Serial.println("-Presione botón 13-");
}

void loop() {
  
  if(digitalRead(btn)==0){

    digitalWrite(RXLED,LOW);
    wisol.RST();
    
    uint32_t valor =random(0,15);
    Serial.println(wisol.SEND(valor));

    //String valor2 ="10";
    //Serial.println(wisol.SEND(valor2));
    
    digitalWrite(RXLED,HIGH);
    wisol.SLEEP();
    delay(3000);
    Serial.println("-Presione botón 13-");
  }
  
}
```
###
- La informacion podra vizualizarse en el backend de sigfox. Usted previamente debe tener asociado a su cuenta el devkit ufox con su respectivo PAC  y ID.

![](https://github.com/TECA-IOT/Ufox/blob/master/image/wewe.png)
