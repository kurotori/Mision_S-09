 /*
  Lector de Sensores de la Mision S-09
  Versión: 0.9 (22 oct 2016)

  Sketch para obtener la lectura de los sensores de la sonda
  y enviarlos a la aplicación mediante la placa IOIO OTG por
  puerto serial. La versión 0.9 cambia el algoritmo base por
  uno basado en comandos para permitir tareas de diagnóstico
  remoto.

  Sensores utilizados:
  - Termistor NTC 10k
  - Barómetro BMP180/GY-68
  - Módulo GPS GY-NEO6MV2
  - Módulo GSM SIM800L
  (A ser agregado)
  - Sensor de gases MQ-135
  - Medidor de velocidad de viento

  Enero, 2017
  Por Club AeroEspacial de la Escuela Técnica de Melo

  http://globosondamelo.blogspot.com.uy

*/
#include <TinyGPS.h>
#include <SPI.h>
#include <SoftwareSerial.h>
#include <SFE_BMP180.h>
#include <Wire.h>
#include <Thermistor.h>



void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
