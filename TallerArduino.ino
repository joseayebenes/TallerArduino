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
static const int EDPin=1, EIPin=0; //ESTOS PINES SON ANALÓGICOS

//Variables Control Velocidad
int velD=40, velI=40; //Velocidad Actual para el analogWrite(ENAPin,velD) y analogWrite(ENBPin,velI)
int valI,valD;  //variables donde leer el valor de los pines analógicos
int statI=LOW,statD=LOW; //estado actual de los encoder
int stat2I, stat2D; //Estado anterior de los encoder
int contarI=0, contarD=0; //Cuentador el número de agujero
int sens=75; //Umbral entre 1 y 0
int last=0;


bool avanzando=false; //Cuando este avanzando adelante tiene que estar a true


void setup() {
  //Configuramos el Serial CableUSB/Bluetooth
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
  //Inhabilitamos los motores
  digitalWrite(ENAPin,LOW);
  digitalWrite(ENBPin,LOW);
  // Configuramos los motores para avanzar adelante
  digitalWrite(IN1Pin,HIGH); 
  digitalWrite(IN2Pin,LOW);
  digitalWrite(IN3Pin,HIGH);
  digitalWrite(IN4Pin,LOW);
  
  
  //CONFIGURAR NOMBRE BLUETOOTH <=> PIN de emparejamiento => 1234
   Serial.print("AT+NAME"); 
   Serial.print("Bluetooth5"); //Este es el nombre cambiar 5 por el número de vuestro kit
   delay(1000);
  
}

void loop() {
  
  if(Serial.available()>0){ //Si hay datos en el puerto Serie
    comando=Serial.read(); //Leemos el dato
    procesarComando(); //Procesamos el dato
  }
  if (GPSSerial.available() > 0){ //Si hay datos en el Software Serie del GPS
  gps.encode(GPSSerial.read());
  }
  if(avanzando){  // Si "avanzando" es igual a true
    controlarAvance(); //controlamos el avance para que vaya recto
  }
}

  
void procesarComando(){
  switch(comando){
    case 'w':
      // AVANZAR
      // Ponemos los motores en marcha y ponemos a true la variable "avanzando"
    break;
    case 's':
      // PARAR
      // Paramos los motores y ponemos la variable "avanzando" a false
    break;
    case 'a':
      // GIRAR IZQUIERDA 
      // Activamos el motor necesario y ponemos la variable "avanzando" a false      
    break;
    case 'd':
      // GIRAR DERECHA
      // Activamos el motor necesario y ponemos la variable "avanzando" a false 
    break;
    case 'l':
      // LEER y MOSTRAR DISTANCIA
      // Llamamos a la función leerDistancia() y lo mostramos por Serie
      break;
    case 'p':
      // LEER y MOSTRAR POSICION GPS
      // Llamamos a la función displayInfoGPS();
      break;   
    default:
       Serial.println("Comando Desconocido");
  }
  
}

void displayInfoGPS()
{
  // LLAMAR A FUNCIONES DE LA LIBRERIA Y MOSTRAR POR PANTALLA
  // LATITUD, LONGITUD, ALTITUD, HORA, FECHA, VELOCIDAD
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
  float distancia=0;
  
  //CALCULAR DISTANCIA
  
  return distancia;
}


void controlarAvance(){ //Función encargada para que vaya recto
//Puedes preguntar por si te interesa como funciona y modificarla
  
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
     
    if(millis()-last>=30){
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

