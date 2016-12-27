  /*
  Lector de Sensores de la Mision S-09
  Versión: 0.8 (22 oct 2016)

  Sketch para obtener la lectura de los sensores de la sonda
  y enviarlos a la aplicación mediante la placa IOIO OTG por
  puerto serial

  Sensores utilizados:
  - Termistor NTC 10k
  - Barómetro BMP180/GY-68
  - Módulo GPS GY-NEO6MV2
  - Módulo GSM SIM800L
  (A ser agregado)
  - Sensor de gases MQ-135

  Octubre, 2016
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
//                TX RX
// Módulo GPS
SoftwareSerial gps(8,9);
// Módulo GSM
SoftwareSerial gsm(7,6);
// Variables Generales
int turno = 0; //             Variable para contabilizar turnos
String mensaje = ""; //       Variable para guardar el mensaje final
bool newData = false;//       Variable para manejo de datos del GPS
bool SMSerror;//              Variable para manejo de datos para GSM

//  Variables para medición de intervalos
unsigned long tiempoPas=0;
unsigned long tiempoHum=0;
unsigned long lapsoHum=3000;
unsigned long lapso=15000;

// Variables para el barómetro
char status;
double PresionBase;
double BPresion = 0;
double BAltitud; //BAltura = 0;
double BTemperatura = 0;
//VAriables para el sensor de humedad
float Htemperatura, humedad;
//Variables para el mensaje
String LA, LO, AL; //Datos del GPS
//String HU, TH; //Datos del sensor de humedad
String PA, TB, AB; //Datos del barómetro
String T1; //Datos del termistor

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  //GPS
  gps.begin(9600);
  //GSM
  gsm.begin(9600);
  //Barómetro
  Serial.println("Iniciando");
  IniciarBaro();
  
  turno=1;
  
}

void loop() {
  unsigned long tiempo=millis();
  //TURNOS: 
  //1- GPS
  //2- Termistor
  //3- Barómetro         
  //4- Humedad
  //5- GSM 
  //6- Componer Mensaje
  if(turno==1){
    //TURNO LIBRE
    turno=2;
  }
  else if(turno==2){
    
    int temperatura = temp.getTemp();
    T1="T1"+String(temperatura)+"|";
    turno=3;
  }
  else if(turno==3){
    
    LeerBaro();
    turno=4;
  }
  else if(turno==4){

    gps.listen();
    bool newData = false;
    unsigned long chars;
    unsigned short sentences, failed;
    //Read GPS
    for (unsigned long start = millis(); millis() - start < 1000;){
       while (gps.available())
        {
        char c = gps.read();
        if (gps1.encode(c)) // Did a new valid sentence come in?
          newData = true;
        }
      } 
    if (newData){
        
        float flat, flon, falt;
        unsigned long age;
        gps1.f_get_position(&flat, &flon, &age);
        falt=gps1.f_altitude();
        LA="LA"+String(flat,6)+"|";
        LO="LO"+String(flon,6)+"|";
        AL="AL"+String(falt,6)+"|";
        //mensaje="LA"+String(flat,6)+"|LO"+String(flon,6);
        //Serial.println(mensaje);
    }
    else{
        LA="LA???|";
        LO="LO???|";
        AL="AL???|";
        //mensaje="Obteniendo Señal de GPS";
        //Serial.println(mensaje);
    }
    gps1.stats(&chars, &sentences, &failed);
    if (chars == 0){
        LA="LA!!!|";
        LO="LO!!!|";
        AL="AL!!!|";
      //Serial.println("** No se reciben datos del GPS. Chequear cables **");
    }
    
    turno=5;
  }
  else if(turno==5){
    mensaje=LA+LO+AL+PA+TB+AB+T1;
    Serial.println(mensaje);
    turno=6;
  }
  else if(turno == 6){
    gsm.listen();
    if(tiempo - tiempoPas > lapso){
      tiempoPas=tiempo;
      EnviarSMS(mensaje);
    }
    turno=1;
  }
}


//Funciones del Módulo GSM

void EnviarSMS(String messg){
    //Serial.println("Sending Text...");
    gsm.print("AT+CMGF=1\r"); // Cambiar el módulo a modo SMS
    delay(100);
    gsm.print("AT+CMGS=\"+59895954482\"\r");  
    delay(200);
    gsm.print(messg);//Contenido del mensaje
    gsm.print("\r"); 
    delay(500);
    gsm.print((char)26);//La comunicación serial requiere un Ctrl+Z para enviar la orden, que en ASCII es el caracter 26
    delay(100);
    gsm.println();
    //Serial.println("Text Sent.");
    delay(500);
  }

//Funciones del Barómetro --> Revisar para adaptar

void IniciarBaro(){//SensorStart() {
  //Secuencia de inicio del sensor
  if (pressure.begin())
   PA="PAIniOK|";
   //Serial.println("BMP180 init success");
  else
  {
    PA="PA!!!|";
    //Serial.println("BMP180 init fail (disconnected?)\n\n");
    while (1);
  }
  //Se inicia la lectura de temperatura
  status = pressure.startTemperature();
  if (status != 0)  {
    delay(status);
    //Se lee una temperatura inicial
    status = pressure.getTemperature(BTemperatura);
    TB="TB"+String(BTemperatura,6)+"|";
    if (status != 0)    {
      //Se inicia la lectura de presiones
      status = pressure.startPressure(3);
      if (status != 0)      {
        delay(status);
        //Se lee la presión inicial incidente sobre el sensor en la primera ejecución
        status = pressure.getPressure(PresionBase, BTemperatura);
      }
    }
  }
}

void LeerBaro(){//ReadSensor() {
  //En este método se hacen las lecturas de presión y temperatura y se calcula la altura
  //Se inicia la lectura de temperatura
  status = pressure.startTemperature();
  if (status != 0)
  {
    delay(status);
    //Se realiza la lectura de temperatura
    status = pressure.getTemperature(BTemperatura);
    TB="TB"+String(BTemperatura,6)+"|";
    if (status != 0)
    {
      //Se inicia la lectura de presión
      status = pressure.startPressure(3);
      if (status != 0)
      {
        delay(status);
        //Se lleva a cabo la lectura de presión,
        //considerando la temperatura que afecta el desempeño del sensor
        status = pressure.getPressure(BPresion, BTemperatura);
        PA="PA"+String(BPresion,6)+"|";
        if (status != 0)
        {
          //Se hace el cálculo de la altura en base a la presión leída en el Setup
          BAltitud = pressure.altitude(BPresion, PresionBase);
          AB="AB"+String(BAltitud,6)+"|";
        }
        else PA="PA???|";//Serial.println("error en la lectura de presion\n");
      }
      else PA="PA?!?|";//Serial.println("error iniciando la lectura de presion\n");
    }
    else TB="TB???|";//Serial.println("error en la lectura de temperatura\n");
  }
  else TB="TB?!?|";//Serial.println("error iniciando la lectura de temperatura\n");

}
