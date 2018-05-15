#include <SoftwareSerial.h>
#include <SD.h>

unsigned long milisegundos=0;
unsigned long milisegundosA=0;
unsigned long milisegundosP=0;
//Variables para Tarjeta SD
File archivo;
String texto = "";



void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  //Inicialización de la tarjeta SD
  //Se intenta conectar al lector y realizar un chequeo de 
  //lectura-escritura
  Serial.print("Inicializando tarjeta SD...");
  if (!SD.begin(4)) {
    Serial.println("ERROR: Fallo de inicialización de Tarjeta SD");
    return;
  }
  else {
    Serial.println("Tarjeta SD Inicializada");
  }
  Serial.println("Tarjeta SD Lista");
}

void loop() {
    //Se chequea la existencia de datos en el puerto serial
    if (Serial.available()) {
      //Si existen datos, se los guarda en una variable
    texto = Serial.readString();
    // Se inicializa el archivo destino en la tarjeta SD
    archivo = SD.open("prueba.txt", FILE_WRITE);
    //Si la inicialización del archivo es exitosa, se escribe el dato
    // en el archivo y se lo cierra.
    if (archivo) {
      archivo.println(texto);
      archivo.close();
      Serial.println("---Escritura Existosa---");
    }
    else {
      //En caso de error de escritura en el archivo
      Serial.println("---ERROR: No se puede acceder al archivo---");
    }
  }
}

