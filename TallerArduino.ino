
//LIBRERIAS SENSOR TEMPERATURA  (Opcional, preguntar como se añaden librerias)
#include <OneWire.h>  //Comunicación con Sensor Temperatura
#include <DallasTemperature.h> //Para leer Temperatura

//VARIABLES TEMPERATURA
static const int Pin =12; 
OneWire ourWire(Pin); 
DallasTemperature sensors(&ourWire); 

// VARIABLES SERIAL
char comando;

//VARIABLES ULTRASONIDOS
static const int echoPin=10, trigPin=11;

void setup() {
  Serial.begin(9600);
  
  pinMode(echoPin,INPUT);
  pinMode(trigPin,OUTPUT);
  
  sensors.begin(); //Inicializa el sensor temperatura
}

void loop() {
  if(Serial.available()>0){
    comando=Serial.read();
    procesarComando();
  }
}

  
void procesarComando(){
  switch(comando){
    case 'w':
      Serial.println("Avanzar");
    break;
    case 's':
      Serial.println("Atras");
    break;
    case 'a':
      Serial.println("Izquierda");
    break;
    case 'd':
      Serial.println("Derecha");
    break;
    case 'l':
      Serial.println("Leer Distancia");
      leerDistancia();
    break;
    case 't':
      Serial.println("Leer Temperatura");
      leerTemperatura();
    break;
  }
  
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
  distancia= tiempo*0.0001657;
  Serial.println("Distancia ");
  Serial.println(distancia);
  Serial.println(" cm");
}

void leerTemperatura(){
  sensors.requestTemperatures(); 
  Serial.print(sensors.getTempCByIndex(0)); 
  Serial.println(" grados Centigrados");
}
