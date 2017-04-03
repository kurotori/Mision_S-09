#include <DS1302.h>

#include <SoftwareSerial.h>
#include <Time.h>
#include <TimeLib.h>

#include <SD.h>

unsigned long milisegundos=0;
unsigned long milisegundosA=0;
unsigned long milisegundosP=0;
//Variables para Tarjeta SD
File archivo;
String texto = "";

//Variables para LED RGB
int ledR = 7;
int ledG = 8;
int ledB = 9;

//Variables para manejo de módulo RTC
DS1302 RTC(2, 3, 5);
String tiempo = "";
String datoT = "";
int dia, mes, anio, hora, minuto;
SoftwareSerial puertoA(A2, A3);

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  RTC.halt(false);
  RTC.writeProtect(false);
  puertoA.begin(9600);
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);
  pinMode(10, OUTPUT);
  Serial.print("Inicializando tarjeta SD...");

  if (!SD.begin(4)) {
    Serial.println("ERROR: Fallo de inicialización de Tarjeta SD");
    while (1) {
      digitalWrite(ledR, HIGH);
      delay(250);
      digitalWrite(ledR, LOW);
      delay(250);
    }
    return;
  }
  else {
    digitalWrite(ledG, HIGH);
  }
  Serial.println("Tarjeta SD Lista");
}

void loop() {
 //PARA PRUEBAS 
//  milisegundos = millis();
//  if( (milisegundos-milisegundosP)>=1000 ){
//    milisegundosP=millis();
//    tiempo = RTC.getTimeStr();
//    tiempo = tiempo + " " + RTC.getDateStr();
//    Serial.println(tiempo);
//  }

  
  datoT="";
  digitalWrite(ledG, HIGH);
  puertoA.listen();
  if (puertoA.available()) {
    tiempo = puertoA.readString();
      datoT += tiempo.charAt(0);
      datoT += tiempo.charAt(1);
      dia=datoT.toInt();
      datoT = "";

      datoT += tiempo.charAt(2);
      datoT += tiempo.charAt(3);
      mes=datoT.toInt();
      datoT = "";
      
      datoT += tiempo.charAt(4);
      datoT += tiempo.charAt(5);
      datoT += tiempo.charAt(6);
      datoT += tiempo.charAt(7);
      anio=datoT.toInt();
      datoT = "";

      datoT += tiempo.charAt(8);
      datoT += tiempo.charAt(9);
      hora=datoT.toInt();
      datoT = "";

      datoT += tiempo.charAt(10);
      datoT += tiempo.charAt(11);
      minuto=datoT.toInt();
      datoT = "";
      
      RTC.setTime(hora,minuto,00);
      RTC.setDate(dia,mes,anio);
    //1234567890
    //0909
    tiempo = RTC.getTimeStr();
    puertoA.println(tiempo);

    //    while(1){
    //      digitalWrite(ledG, LOW);
    //      delay(250);
    //      digitalWrite(ledG, HIGH);
    //      delay(250);
    //    }
  }


  if (Serial.available()) {
    digitalWrite(ledG, LOW);
    digitalWrite(ledR, HIGH);
    texto = Serial.readString();
    archivo = SD.open("prueba.txt", FILE_WRITE);
    digitalWrite(ledR, LOW);
    if (archivo) {
      digitalWrite(ledB, HIGH);
      tiempo = String(RTC.getDateStr())+ " " + String(RTC.getTimeStr());
      archivo.println(tiempo+"-"+texto);
      archivo.close();
      Serial.println("---Escritura Existosa---");
      digitalWrite(ledB, LOW);
    }
    else {
      digitalWrite(ledR, HIGH);
      delay(100);
      digitalWrite(ledR, LOW);
      digitalWrite(ledB, HIGH);
      delay(100);
      digitalWrite(ledB, LOW);
      digitalWrite(ledR, HIGH);
      delay(100);
      digitalWrite(ledR, LOW);
      digitalWrite(ledB, HIGH);
      delay(100);
      digitalWrite(ledB, LOW);
      Serial.println("---ERROR: No se puede acceder al archivo---");
    }
    // Código para pruebas de lectura de contenido - No necesario en
    //    Serial.println("------------------------------");
    //    Serial.println("--- Contenidos del Archivo ---");
    //    Serial.println("------------------------------");
    //    archivo = SD.open("prueba.txt");
    //    if (archivo) {
    //      while (archivo.available()) {
    //        Serial.write(archivo.read());
    //      }
    //      archivo.close();
    //      }
    //    else {
    //      Serial.println("---ERROR: No se puede acceder al archivo---");
    //    }



  }
}

