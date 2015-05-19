#include <TinyGPS++.h> //Librería GPS
#include <SoftwareSerial.h> //Crear Puerto Serie

// VARIABLES SERIAL
char comando;
bool avanzando=false;

//VARIABLES ULTRASONIDOS
static const int echoPin=12, trigPin=11;

//VARIABLES GPS
static const int RXPin = 3, TXPin = 2;
TinyGPSPlus gps;
SoftwareSerial GPSSerial(RXPin, TXPin);

//VARIABLES MOTORES
static const int ENAPin=5, IN1Pin=7, IN2Pin=6, IN3Pin=8, IN4Pin=9, ENBPin=10;

//VARIABLES ENCODER
static const int EDPin=1, EIPin=0;
//Variables Control Velocidad
int velD=40, velI=40;
int valI;
int valD;
long lastI=0;
long lastD=0;
int statI=LOW;
int statD=LOW;
int stat2I;
int stat2D;
int contarI=0;
int contarD=0;
int sens=75;
int last=0;

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
  //INICIALIZAMOS LOS MOTORES
  digitalWrite(ENAPin,LOW);
  digitalWrite(ENBPin,LOW);
  digitalWrite(IN1Pin,HIGH);
  digitalWrite(IN2Pin,LOW);
  digitalWrite(IN3Pin,HIGH);
  digitalWrite(IN4Pin,LOW);
  
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
  if(avanzando){ 
    controlarAvance();
  }
}

  
void procesarComando(){
  switch(comando){
    case 'w':
      // AVANZAR
    break;
    case 's':
      // PARAR
    break;
    case 'a':
      // GIRAR IZQUIERDA      
    break;
    case 'd':
      // GIRAR DERECHA
    break;
    case 'l':
      // LEER y MOSTRAR DISTANCIA
      break;
    case 'p':
      // LEER y MOSTRAR POSICION GPS
      break;   
    default:
       Serial.println("Comando Desconocido");
  }
  
}

void displayInfo()
{
  // LLAMAR A FUNCIONES DE LA LIBRERIA Y MOSTRAR POR PANTALLA
  // LATITUD, LONGITUD, ALTITUD, HORA, FECHA, VELOCIDAD
}
float leerDistancia(){
  float distancia=0;
  
  //CALCULAR DISTANCIA
  
  return distancia;
}


void controlarAvance(){
  
  valI=analogRead(EIPin);
  if(valI<sens)
    statI=LOW;
   else
    statI=HIGH;

   if(stat2I!=statI){  
     contarI++;
     stat2I=statI;
   }
   
   valD=analogRead(EDPin);
  if(valD<sens)
    statD=LOW;
   else
    statD=HIGH;

   if(stat2D!=statD){  
     contarD++;
     stat2D=statD;
   }
     
    if(millis()-last>=20){
      if(contarD>contarI){
        if(velD>0){velD--;}
      }else{
        if(contarD<contarI){
           if(velD<100){velD++;}
        }
      }
      analogWrite(ENAPin,velD);
      contarI=0;
      contarD=0;
      last=millis();
   }
   
  
}

