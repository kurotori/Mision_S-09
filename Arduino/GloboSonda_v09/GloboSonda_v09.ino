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

//Inicialización de librerías
Thermistor temp(0);
TinyGPS gps1;
SFE_BMP180 pressure;
//Pines seriales
//Pin del módulo  TX RX
// Módulo GPS
SoftwareSerial gps(8,9);
// Módulo GSM
SoftwareSerial gsm(7,6);
// Variables Generales
int turno = 0; //             Variable para contabilizar turnos
String mensaje = ""; //       Variable para guardar el mensaje final
bool newData = false;//       Variable para manejo de datos del GPS
bool SMSerror;//              Variable para manejo de datos para GSM
String SATS;

String comando="";
String sketch="GloboSonda";
String _version="0.9";
unsigned long tiempo=0;

void setup() {
  Serial.begin(9600);
  //GPS
  gps.begin(9600);
  //GSM
  //gsm.begin(9600);

}

void loop() {
  //Se toma el valor actual del tiempo de ejecución (en ms)
  tiempo=millis();
  //Se chequea la existencia de datos de comunicación serial
  if (Serial.available()) {
      comando=Serial.readString();
    //Comienza la comprobación de comandos
    if (comando.equals("STATUS\n")){
      Status();
    }
    else if (comando.equals("DATOS\n")){
      Datos();
    }
    else if(comando.equals("STATUSGPS\n")){
      StatusGPS();
    }
    else if(comando.equals("STATUSGSM\n")){
      StatusGSM();
    }
    //Si no corresponde a ningún comando establecido
    //se devuelve un error.
    else{
      Serial.println("ERROR: Comando Desconocido");  
    }
  }
  Status();
  StatusGSM();
  delay(2000);
}
//===============COMANDOS===================//
//STATUS - Devuelve información general del sistema
void Status(){
  Serial.println("===ARDUINO===");
  Serial.print("Sketch: ");
  Serial.println(sketch);
  Serial.print("Version: ");
  Serial.println(_version);
  Serial.print("Tiempo desde el arranque: ");
  Serial.println(String(tiempo)+" ms");
  Serial.println("==============");
  StatusGPS();
}

//DATOS - Devuelve los datos recopilados por los sensores
void Datos(){
  String d = "|???|???|AAAA|BBBB|CCCC|DDDD|EEEE|FFFF|GGGG|HHHH";
  Serial.println(tiempo+d);
}

//STATUSGSM - Para pruebas. Pretende devolver el estado del módulo GSM
void StatusGSM(){
  Serial.println("====GSM====");
  
  gsm.listen();
  delay(100);
  gsm.write("AT?\r");
  
  if(gsm.available()){
    //Serial.println(". . .");
    Serial.write(gsm.read());
  }
  else {
    Serial.println("GSM no responde");
  }
}

//STATUSGPS
 void StatusGPS(){
  gps.listen();
  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;
  for (unsigned long start = millis(); millis() - start < 1000;){
       while (gps.available())
        {
        char c = gps.read();
        if (gps1.encode(c)) // Did a new valid sentence come in?
          newData = true;
        }
      } 
    if (newData){
        short fsats;
        fsats=gps1.satellites();
        SATS=String(fsats)+" SATS";
        //mensaje="LA"+String(flat,6)+"|LO"+String(flon,6);
        //Serial.println(mensaje);
    }
    else{
        SATS="SATS???|";
        //mensaje="Obteniendo Señal de GPS";
        //Serial.println(mensaje);
    }
    gps1.stats(&chars, &sentences, &failed);
    if (chars == 0){
        SATS="SATS!!!|";
      //Serial.println("** No se reciben datos del GPS. Chequear cables **");
    }
    else{
      SATS=SATS+" "+chars+" "+sentences+" "+failed;
    }
    Serial.println("====GPS====");
    Serial.print("SATELITES: ");
    Serial.println(SATS);
 }

