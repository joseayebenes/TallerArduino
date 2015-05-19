#include <TinyGPS++.h> //Librería GPS
#include <SoftwareSerial.h> //Crear Puerto Serie

// VARIABLES SERIAL
char comando;

//VARIABLES ULTRASONIDOS
static const int echoPin=12, trigPin=11;

//VARIABLES GPS
static const int RXPin = 3, TXPin = 2;
TinyGPSPlus gps;
SoftwareSerial GPSSerial(RXPin, TXPin);

//VARIABLES MOTORES
static const int ENAPin=5, IN1Pin=7, IN2Pin=6, IN3Pin=8, IN4Pin=9, ENBPin=10;

//VARIABLES ENCODER
static const int EDPin=4, EIPin=13;
int velD=40, velI=40;


void setup() {
  //Configuramos el Serial Bluetooth
  Serial.begin(9600);
  //Configuramos el Serial del GPS
  GPSSerial.begin(9600);
  
  //Configuramos el sensor de Ultrasonidos
  pinMode(echoPin,INPUT);
  pinMode(trigPin,OUTPUT);
  
  //Configuramos los motores
  pinMode(ENAPin, OUTPUT);
  pinMode(IN1Pin, OUTPUT);
  pinMode(IN2Pin, OUTPUT);
  pinMode(IN3Pin, OUTPUT);
  pinMode(IN4Pin, OUTPUT);
  pinMode(ENBPin, OUTPUT);
  
  digitalWrite(ENAPin,LOW);
  digitalWrite(ENBPin,LOW);
  digitalWrite(IN1Pin,HIGH);
  digitalWrite(IN2Pin,LOW);
  digitalWrite(IN3Pin,HIGH);
  digitalWrite(IN4Pin,LOW);
  
  //Configuramos los Encoder
  
  pinMode(EDPin,INPUT);
  pinMode(EIPin,INPUT);
}

void loop() {
  if(Serial.available()>0){
    comando=Serial.read();
    procesarComando();
  }
  if (GPSSerial.available() > 0){
    gps.encode(GPSSerial.read());
    //Serial.write(GPSSerial.read());
  }
  /*if(comando=='w'){
    
    if(leerDistancia()<20){
      digitalWrite(ENAPin,LOW);
      digitalWrite(ENBPin,LOW);
      Serial.println("CHOQUE");
    }
  }*/
}

  
void procesarComando(){
  switch(comando){
    case 'w':
      digitalWrite(ENAPin,HIGH);
      digitalWrite(ENBPin,HIGH);
      delay(20);
      analogWrite(ENAPin,velD);
      analogWrite(ENBPin,velI);
    break;
    case 's':
      digitalWrite(ENAPin,LOW);
      digitalWrite(ENBPin,LOW);
    break;
    case 'a':
      digitalWrite(ENBPin,LOW);
      digitalWrite(ENAPin,HIGH);
      delay(7);
      analogWrite(ENAPin,velD);
      
    break;
    case 'd':
      digitalWrite(ENAPin,LOW);
      digitalWrite(ENBPin,HIGH);
      delay(7);
      analogWrite(ENBPin,velI);
    break;
    case 'l':
      Serial.println(leerDistancia());
    break;
    case 'p':
      displayInfo();
    break;   
    default:
       Serial.println("Comando Desconocido");
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

float leerDistancia(){
  float tiempo;
  float distancia;
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  tiempo=pulseIn(echoPin, HIGH, 8000);
  
  if(tiempo ==8000){
    return 555;
  }
  distancia= tiempo*0.017;
  
  return distancia;
}

