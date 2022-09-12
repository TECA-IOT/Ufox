# 1. Ufox devkit Sigfox RC4
![](https://github.com/TECA-IOT/Ufox/blob/master/image/Ufox%20devkit.png)
Kit de desarrollo Sigfox para región RC4: 
-Argentina, Chile, Colombia, Costa Rica El Salvador, Panamá, Guatemala, Honduras, Nicaragua, Panama, Perú, Trinidad & Tobago, Uruguay, Paraguay.
Asia pacifico: 
Australia, Hong Kong, Indonesia, Malasia, Nueva Zelanda, Singapure, Taiwán, Thailandia.

## 1.1 Visita la Wiki Ufox: Documentación y ejemplos avanzados
`<link>` : <https://github.com/TECA-IOT/Ufox/wiki>
### 1.1.1 API librería ufox.h
`<link>` : <https://github.com/TECA-IOT/Ufox/wiki/API>
### 1.1.2 Manual Técnico
`<link>` : <https://github.com/TECA-IOT/Ufox/wiki/Manual-T%C3%A9cnico>
### 1.1.3 Enviar múltiples variables en mensaje sigfox con función sprintf
`<link>` : <https://github.com/TECA-IOT/Ufox/wiki/Funci%C3%B3n-Sprintf>
### 1.1.4 Librería Fritzing
`<link>` : <https://github.com/TECA-IOT/Ufox/wiki/Libreria-de-ufox-para-Fritzing>
### 1.1.4 Guía de inicio rápido
`<link>` : <https://github.com/TECA-IOT/Ufox/wiki/Gu%C3%ADa-de-inicio-r%C3%A1pido>

### 1.1.5 SHIELD UFOX INFORMACION:
`<link>` : <https://github.com/TECA-IOT/Shield-Ufox>

## 1.2 Caracteristicas

- Microcontrolador Atmega32U4 USB y Modem Wisol WSSFM10R4 RC4 .
- Programable con Arduino IDE (compatible con pines de arduino Leonardo, ProMicro, Micro, y otras placas arduino basadas en el micro atmega32U4).
- Incluye una antena interna helicoidal  de 3 Dbi y opcionalmente un conector  UFL para antenas externas. (se recomienda previamente desoladar la antena helicoidal para su uso). 
- Alimentación desde fuente USB 5V con voltaje de operación interno de 3.3V.
- Ideal para desarrollar prototipos y aplicaciones de forma rapida y sencilla, incluye un microcotrolador Atmega32U4  compatible con arduino.
- Cuenta con un regulador de voltaje de 3.3V AMS1117  suministra  hasta 1 amperio de corriente.
- Diseño compacto, seguro y de bajo consumo
- Comunicación serial por Hardware (Serial1 Arduino) dedicado exclusivamente para comunicacion con modem Wisol.
- Reset de modulo Wisol Conectado al Pin "12" Arduino. 
- Botón de proposito general programable en el pin "13" Arduino
- Pines Digitales, Analogicos, PWM, comunicacion SPI, I2C,Interrupcion externa, Serial.
- informacion acerca de arduino leonardo: 
`<link>` : <https://store.arduino.cc/usa/leonardo>

![](https://github.com/TECA-IOT/Ufox/blob/master/image/ufox%20antena.png)

## 1.3 Caracteristicas 
### 1.3.1 Electricas 

| Descripcion (1*)| Unidad                    |
| ------------- | ------------------------------ |
| Voltaje entrada USB (Conector micro USB)|  5 Voltios    |  
| Voltaje Mínimo entrada (Pin VIN) |  3.7 Voltios    |  
| Voltaje Máximo  entrada (Pin VIN) |  9 Voltios    |  
| Corriente máxima    | 1A    |
| Voltaje de funcionamiento interno típico  |  3.3 Voltios  | 

| Descripcion (2*)| Unidad                    |
| ------------- | ------------------------------ |
| Voltaje Máximo absoluto entrada (Pin 3.3V) |  4 Voltios    |  
| Voltaje Mínimo absoluto entrada (Pin 3.3V) |  2.7 Voltios  |  

- Notas(*)
- (1*) Referente a la Entrada de voltaje por el Pin "VIN" o por el conector micro USB. Este voltaje ingresa por el regulador interno, el regulador suministrara a su salida 3.3 Voltios alimentando a toda la electrónica interna. El voltaje regulado se ve reflejado en el Pin "3.3V".
- (2*) Referente a la entrada de voltaje en el Pin "3.3V" para el  caso donde no exista entrada de voltaje por el pin "VIN". Este voltaje es suministrado sin proteccion directamente a toda la electronica interna. Esta forma de alimentar puede ser útil cuando se requiera emplear baterias. (Se recomienda agregar un diodo en serie)

### 1.3.2 Radiofrecuencia
| Descripcion | Unidad                    |
| ------------- | ------------------------------ |
| Antena helicoidal    | 3 DBi      |
| Frec. Uplink     | 920.8 MHz      |
| Frec. Downlink     | 922.3 MHz      |
| Data rate     | 600bps      |
| Potencia RF     | +22dbm   0,2045W máx   |
| Modulación     | DBPSK    |
| Técnica de transmisión     | FHSS   |
| Técnologia de transmisión     | UNB (Ultra narrow band) - Sigfox   |
| Canales de transmisión     | 54 canales (9 macro-canales x 6 micro-canales)   |


## 1.4 Descripcion de pines Ufox

![](https://github.com/TECA-IOT/Ufox/blob/master/image/PINOUT_ufox_R1_3.png)


# 2. Cargar un Sketch a Ufox
- Enchufe el cable usb con el conector micro usb de Ufox, luego conectar a su PC
- Espere a que su PC  reconosca a Ufox (el reconocimiento es instantaneos para SO Window ,7,8,10).
- Abra el Ide Arduino.
- Puede cargar un  ejemplo de inicio  como el siguiente:

## 2.1 Blink Ufox
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

- Selecciones la placa Arduino Leonardo y seleccion el puerto COM detectado en su PC.
- Y cargue el sketch.

![blink ufox](https://github.com/TECA-IOT/ufox-schematics/blob/main/blink%20ufox.gif)

## 2.2 Comuncación Serial con modem Wisol
*El modem Wisol WSSFM10R4AT puede comunicarse mediante puerto serial1 a 9600 baudios, con una sintaxis definida con comando "AT", puede consultar mas informacion de comandos en la hoja de datos (datasheet). El modem trabaja a una frecuencia de 920MHZ Uplink y 922 Dowlink. Consulte mas informacionde como activar el mdem en la platafoma de sigfox o con su operador sigfox Local : Aqui 

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

- Una vez cargado el sketch abra la terminal serial a 9600 baudios, seleccionar la opcion "Nueva línea".
- Escribir el comando "AT",presionar  enter, y a continuacion el chip wisol respondera con un "Ok"  
- Comandos de interes:
- ID:          AT$I=10
- PAC:         AT$I=11
- Voltaje:     AT$V?
- Temperatura: AT$T?

![COMANDOS AT UFOX](https://github.com/TECA-IOT/ufox-schematics/blob/main/UFOX%20COMANDOS%20AT_.gif)

## 2.3 Enviar mensaje sigfox mediante comandos AT
Enviar un mensaje a backend sigfox sera el siguiente: 255 decimal, SIGA LA SECUENCIA DE COMANDOS SIGUIENTE:
- AT$GI?
- AT$RC
- AT$SF=FF

![COMANDOS AT UFOX SEND](https://github.com/TECA-IOT/ufox-schematics/blob/main/COMANDO%20AT%20UFOX%20SEND.gif)


## 2.4 Cómo registrar dispositivos a la red Sigfox
-  Obtenga un dispositivo SIGFOX ReadyTM (hardware).
- Obtenga el par de código ID/PAC de los dispositivos (extraible en el modem del dispositivo).
- Firme un contrato de suscripción con SIGFOX.
- Obtenga el inicio de sesión de SIGFOX Cloud (Backend Sigfox).
- Registre sus objetos con ID / PAC.
 Sus dispositivos están listos para la comunicación.
 
 ### Activación por Buy Sigfox
 - Disponible sólo para paises de: Colombia, Ecuador, Uruguay, Costa Rica, El Salvador, Panamá, 
 - Ingresar a la pagina  Buy Sigfox, Activate my devkit, Seleccionar su País e introducir los codigos ID y PAC: `<link>` : <https://buy.sigfox.com/activate> 
 
 ### Activación por contrato directo:
 - Para el resto de Paises. Contactarse por nuestro correos:  <gerencia.tecaperu@gmail.com> ó   nuestra pagina web <https://teca.pe> ó redes sociales <https://www.facebook.com/TecaIoTPeru>
 
#### 2.4.1 GLOSARIO
- ID : Identificador del dispositivo de 4 bytes (Es único)
- PAC :Código de autorización de transferencia de 8 bytes (Válido una vez). PAC es el certificado de propiedad del objeto, es requerido por la plataforma SIGFOX para validar las solicitudes de registro / transferencia de equipos. Una vez utilizado, la validez del código expira y se asigna un nuevo código.
- El PAC se proporciona en la venta del dispositivo (EXTRAIBLE DEL MODULO RF)
 - Ejemplo: 006D8AF2; 10708756FE9515D5  

# 3. LIBRERÍA UFOX ARDUINO | librería Sigfox
La libreria ufox incorpora una serie de funciones y metodos que simplifican la conexion a la red de sigfox. Instale la libreria Ufox  en el IDE de arduino descargando este repositorio, existen diversos modos de instalar libreria externas, 
## 3.1 Instalación
### 3.1.1 Opción 1: 
- Descomprima este repositorio descargado en formato .ZIP y copie la carpeta dentro de :  [Unidad]:\Users\[usuario]\Documents\Arduino\libraries
### 3.1.2 Opción 2: 
- Desde el mismo IDE Arduino dirijase a Programa, Incluir  Libreria, Añadir biblioteca  .ZIP . Localice el repositorio descargado y abrir.
- Una vez instalado recargue el  Ide arduino y podra ver que la libreria y ejemplo se muestran: 
### 3.1.3 Opción 3:
- Abrir el IDE Arduino, y desde el gestor de descargas de Librerias de Arduino descargar buscar "ufox" y descargarlo.
![descargar libreria ufox](https://github.com/TECA-IOT/ufox-schematics/blob/main/descargar%20libreria%20ufox.gif)

## 3.2 Enviar un Mensaje Simple con librería Ufox.h

En este ejemplo puede enviar un mensaje numérico cada vez que el botón 13 (ubicado al lado derecho del devkit), es presionado. Tener en consideración que los mensajes Sigfox son enviados en formato de hexagesimales con un tamaño  máximo de 12 bytes de carga útil (Payload), todos los valores numéricos serán convertidos a valores hexagesimales de forma automatica por librería. Elija el ejemplo llamado "Simple_uplink". 
![](https://github.com/TECA-IOT/Ufox/blob/master/image/lib_ufox1.png)

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


###
- La información podrá vizualizarse en el backend de Sigfox. Usted previamente debe tener asociado a su cuenta el devkit Ufox con un contrato de conectividad. Se mostrara el ID de su dispositivo asociado y el nuevo codigo PAC que has sido generado tras la activación del contrato.
- El Backend de Sigfox es la plataforma para poder gestionar las conexiones de sus dispositivos. La configuración mas importante a consideracion son los Callbacks, donde podra redireccionar los mensajes por medio de HTTP o HTTPS a otros servidores, o tambien redireccionarlos a AWS IOT Core, Azure e IBM.

![Simple uplink Ufox - backend sigfox](https://github.com/TECA-IOT/ufox-schematics/blob/main/simple%20uplink%20ufox.gif)


