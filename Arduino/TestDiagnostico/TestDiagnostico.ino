/* Simple Serial ECHO script : Written by ScottC 03/07/2012 */

/* Use a variable called byteRead to temporarily store
   the data coming from the computer */
String comando="";
String sketch="TestDiagnostico";
String _version="0.1";
unsigned long tiempo=0;

void setup() {
  // Turn the Serial Protocol ON
  Serial.begin(9600);
}

void loop() {
  tiempo=millis();
  /*  check if data has been sent from the computer: */
  if (Serial.available()) {
    /* read the most recent byte */
    comando = Serial.readString();
    if (comando.equals("STATUS\n")){
      Serial.println("===ARDUINO===");
      Serial.print("Sketch: ");
      Serial.println(sketch);
      Serial.print("Version: ");
      Serial.println(_version);
      Serial.print("Tiempo desde el arranque: ");
      Serial.println(String(tiempo));
      Serial.println("==============");
    }
    else{
      Serial.println("Comando Desconocido");  
    }
    
  }
}
