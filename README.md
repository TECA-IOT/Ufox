# Ufox devkit Sigfox V1.0
Kit de desarrollo Sigfox para region RC4 ( Latinoamerica: Argentina, Chile, Colombia, Costa Rica, El Salvador, Guatemala, Honduras, Nicaragua, Panama, Perú, Trinidad & Tobago, Uruguay.
Asia pacifico: Australia, Hong Kong, Indonesia, Malasia, Nueva Zelanda, Singapure, Taiwán, Thailandia.

## Ufox imagen

![](https://github.com/TECA-IOT/Ufox/blob/master/image/Ufox.png )


## Caracteristicas

- Placa de desarrollo basado en el el microcontrolador Atmega32U4 USB y Modem Wisol RC4 para aplicaciones Sigfox.
- Programable con Arduino IDE (compatible con pines de arduino Leonardo, ProMicro, Micro, y otras placas arduino basadas en el micro atmega32U4).
- Incluye una antena interna helicoidal  de 2.5 Dbi y opcionalmente un conector  UFL para antenas externas. (previamente desoladar la antena helicoidal para su uso). 
- Puede alimentarse directamente de una fuente USB, circuito interno trabaja a 3.3V.
- Ideal para desarrollar prototipos y aplicaciones de forma rapida ya que incluye un microcotrolador compatible con arduino.
- Cuenta con un regulador de voltaje de 3.3V AMS1117 que suministra  hasta 1 amperio de corriente.
- Diseño compacto, seguro y de bajo consumo
- Comunicacion serial por Hardware (Serial1 Arduino) exclusivo para comunicacion con modem Wisol.
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


## Descripcion de pines Ufox

![](https://github.com/markoAntonio1692/32U4-DEVKIT-SIGFOX/blob/master/image/PINOUT.png)


# Cargar un Sketch a Ufox
- Enchufe el cable micro usb con  el conector micro usb de Ufox, luego enchufar el cable microusb usb a su PC
- Espere a que su PC  reconosca a Ufox (el reconocimiento es instantaneos para SO Window ,7,8,10).
- Abra el Ide Arduino.
- Puede cargar un  ejemplo de inicio  como el siguiente:


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


#### ENVIAR UN MENSAJE
Enviar un mensaje a backend sigfox sera el siguiente: 255 decimal, SIGA LA SECUENCIA DE COMANDOS SIGUIENTE:
- AT$GI?
- AT$RC
- AT$SF=FF
