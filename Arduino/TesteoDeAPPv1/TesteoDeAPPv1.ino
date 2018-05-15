int orden="";


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  comando();
  if(orden==1){
    Serial.println("ARDUINO NANO - SCRIPT DE PRUEBA V0.2");
    orden=0;
  }
  if(orden==2){
    tiradatos();
  }
  else{
    
  }
}

// Ordenes
//1- estatus
//2- acción

void tiradatos(){
  Serial.println("LA11.1111|LO-22.2222|AL333|HU44|TH55|PA66|TB77|AB88|T199|");
  delay(1000);
  Serial.println("LA!!!|LO-22.2222|AL333|HU44|TH55|PA66|TB77|AB88|T1100|FIN");
  delay(1000);
  Serial.println("LA???|LO-22.2222|AL333|HU44|TH55|PA66|TB77|AB88|T199|FIN");
  delay(1000);
  Serial.println("LA11.1111|LO!!!|AL333|HU44|TH55|PA66|TB77|AB88|T130|FIN");
  delay(1000);
  Serial.println("LA11.1111|LO???|AL333|HU44|TH55|PA66|TB77|AB88|T145|FIN");
  delay(1000);
  Serial.println("LA11.1111|LO-22.2222|AL!!!|HU44|TH55|PA66|TB77|AB88|T1-120|FIN");
  delay(1000);
  Serial.println("LA11.1111|LO-22.2222|AL???|HU44|TH55|PA66|TB77|AB88|T1-48|FIN");
  delay(1000);
  Serial.println("LA11.1111|LO-22.2222|AL333|HU???|TH55|PA66|TB77|AB88|T180|FIN");
  delay(1000);
  Serial.println("LA11.1111|LO-22.2222|AL333|HU!!!|TH55|PA66|TB77|AB88|T199|FIN");
  delay(1000);
  Serial.println("LA11.1111|LO-22.2222|AL333|HU44|TH!!!|PA66|TB77|AB88|T199|FIN");
  delay(1000);
  Serial.println("LA11.1111|LO-22.2222|AL333|HU44|TH???|PA66|TB77|AB88|T199|FIN");
  delay(1000);
  //PRESION
  Serial.println("LA11.1111|LO-22.2222|AL333|HU44|TH55|PA???|TB77|AB88|T199|FIN");
  delay(1000);
  Serial.println("LA11.1111|LO-22.2222|AL434|HU44|TH55|PA!!!|TB77|AB88|T199|FIN");
  delay(1000);
  //TEMP BAROMETRO
  Serial.println("LA11.1111|LO-22.2222|AL345|HU44|TH55|PA66|TB???|AB88|T199|FIN");
  delay(1000);
  Serial.println("LA11.1111|LO-22.2222|AL444|HU44|TH55|PA66|TB!!!|AB88|T199|FIN");
  delay(1000);
  Serial.println("LA11.1111|LO-22.2222|AL555|HU44|TH55|PA66|TB77|AB???|T199|FIN");
  delay(1000);
  Serial.println("LA11.1111|LO-22.2222|AL00|HU44|TH55|PA66|TB77|AB!!!|T199|FIN");
  delay(1000);
  //TERMOMETRO 1
  Serial.println("LA11.1111|LO-22.2222|AL-30|HU44|TH55|PA66|TB77|AB88|T1???|FIN");
  delay(1000);
  Serial.println("LA11.1111|LO-22.2222|AL333|HU44|TH55|PA66|TB77|AB88|T1!!!|FIN");
  delay(1000);
  //chequear comandos desde serial
  comando();
}

void comando() {
 while (Serial.available() > 0) {
   char incomingCharacter = Serial.read();
   switch (incomingCharacter) {
     case 's':
      orden=1;
      break;
 
     case 'r':
     orden=2;
      break;
      
     default:
     orden=orden;
     break;
    }
 }
}


