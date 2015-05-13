#include <TinyGPS++.h> //Librería GPS
#include <SoftwareSerial.h> //Crear Puerto Serie
#include <OneWire.h>  //Comunicación con Sensor Temperatura
#include <DallasTemperature.h> //Para leer Temperatura

// VARIABLES SERIAL
char comando;

//VARIABLES ULTRASONIDOS
static const int echoPin=10, trigPin=11;

//VARIABLES GPS
static const int RXPin = 3, TXPin = 2;
TinyGPSPlus gps;
SoftwareSerial GPSSerial(RXPin, TXPin);

//VARIABLES TEMPERATURA
static const int Pin =12; 
OneWire ourWire(Pin); 
DallasTemperature sensors(&ourWire); 
 
 
void setup() {
  Serial.begin(9600);
  
  GPSSerial.begin(9600);
  
  pinMode(13,OUTPUT);
  
  pinMode(echoPin,INPUT);
  pinMode(trigPin,OUTPUT);
  
  sensors.begin(); 
}

void loop() {
  if(Serial.available()>0){
    comando=Serial.read();
    procesarComando();
  }
  if (GPSSerial.available() > 0){
    gps.encode(GPSSerial.read());
  }

}

  
void procesarComando(){
  switch(comando){
    case 'w':
      Serial.println("Avanzar 500 ms");
      
    break;
    case 's':
      Serial.println("Atras 500 ms");
    break;
    case 'a':
      Serial.println("Izquierda 500 ms");
    break;
    case 'd':
      Serial.println("Derecha 500 ms");
    break;
    case 'l':
      Serial.println("Leer Distancia");
      leerDistancia();
    break;
    case 'p':
      Serial.println("Leer Posicion");
      displayInfo();
    break;
    case 't':
      Serial.println("Leer Temperatura");
      leerTemperatura();
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
  long distancia;
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  tiempo=pulseIn(echoPin, HIGH);
  distancia= tiempo/58;
  Serial.println("Distancia ");
  Serial.println(distancia);
  Serial.println(" cm");
}

void leerTemperatura(){
  sensors.requestTemperatures(); 
  Serial.print(sensors.getTempCByIndex(0)); 
  Serial.println(" grados Centigrados");
}
