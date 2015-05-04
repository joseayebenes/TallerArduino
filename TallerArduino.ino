#include <TinyGPS++.h>
#include <SoftwareSerial.h>

//VARIABLES SERIAL
String inputString = "";         
boolean stringComplete = false; 

//VARIABLES ULTRASONIDOS
static const int echoPin=10, trigPin=11;

//VARIABLES GPS
static const int RXPin = 3, TXPin = 2;
TinyGPSPlus gps;
SoftwareSerial GPSSerial(RXPin, TXPin);

void setup() {
  Serial.begin(9600);
  GPSSerial.begin(9600);
  pinMode(13,OUTPUT);
  inputString.reserve(50);
  pinMode(echoPin,INPUT);
  pinMode(trigPin,OUTPUT);
}

void loop() {
  if (stringComplete) {
    procesarComando();
    inputString = "";
    stringComplete = false;
  }
  
  if (GPSSerial.available() > 0){
    gps.encode(GPSSerial.read());
  }
}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    inputString += inChar;
    if (inChar == '\n') {
      stringComplete = true;
  }  
}
  
void procesarComando(){
  
  char comando=inputString[0];
  switch(comando){
    case 'w':
      Serial.print("comando W  ");
      
    break;
    case 's':
      Serial.println("comando S");
    break;
    case 'a':
      Serial.println("comando A");
    break;
    case 'd':
      Serial.println("comando D");
    break;
  }
  
}

void displayInfo()
{
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
  }
  else
  {
    Serial.print(F("INVALID"));
  }
  Serial.print(F("  Date/Time: "));
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  }
  else
  {
    Serial.print(F("INVALID"));
  }
  Serial.print(F(" "));
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(gps.time.centisecond());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.println();
}

void leerDistancia(){
  long tiempo;
  float distancia;
  digitalWrite(trigPin,LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  tiempo=pulseIn(echoPin, HIGH);
  
  distancia= int(0.017*tiempo);
  Serial.println("Distancia ");
  Serial.println(distancia);
  Serial.println(" cm");
}
