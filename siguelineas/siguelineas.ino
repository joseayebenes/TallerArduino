//Declaracion de variables


int IN1=6;
int IN2=7;
int IN3=8;
int IN4=9;
int ENA=5;
int ENB=10;


//Conexiones sensor de luz
int S0=2;
int S1=3;
int S2=4;
int S3=11;
int taosOutPin =12;
int LED=13;



void setup() {
  // put your setup code here, to run once:
  TCS3200setup(); // Inicializamos los pines 
  pinMode(IN1,OUTPUT);
  pinMode(IN2, OUTPUT);
  //Seguimos con los que queden...
  
  Serial.begin(9600); //Habilita el puerto serie a 9600 baudios
}

void loop() {
  

  //FUNCIONES QUE SON ÚTILES
   /*
   Serial.println("hola"); //Escribe por consola(En el PC) "Hola"
   
   por ejemplo
     float  sensor = mideLuz(taosOutPin);
     Serial.println(sensor);
     
     Mides la luminosidad si es negro (hay que saber que valor devuelve sobre negro) el coche va en buen camino,
     si es blanco (hay que saber que valor es) hay que girar el coche hasta que encuentre el negro otra vez
     
   */
}


void TCS3200setup()
{
  //Inicializar los pines
  pinMode(LED, OUTPUT);
  
  //Seleccion del color
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  
  //Seleccion de la salida
  pinMode(taosOutPin, INPUT);
  
  //Seleccionar la escala
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  
  
  }
  
  
  float mideLuz(int taosOutPin)
  {
    taosMode(1);
    
    //Delay encendido de sensor
    int sensorDelay = 100;
    
    //Seleccion del color
    digitalWrite(S3,LOW);
    digitalWrite(S2,HIGH);
    
    //Definicion de variable a devolver
    float readPulse;
    
    //Encender LED
    digitalWrite(LED, HIGH);
    
    //Esperar
    delay(sensorDelay);
    
    //Medir el nivel de blanco
    readPulse = pulseIn(taosOutPin, LOW, 80000);
    
    if(readPulse < 0.1)
    {
      readPulse = 80000;
    }
    
    //Apagar sensor
    taosMode(0);
    
    //Devolver el valor
    return readPulse;
  }
  
  
  
  void taosMode(int mode)
  {
    if(mode == 0)
    {
      digitalWrite(LED, LOW);
      digitalWrite(S0, LOW);
      digitalWrite(S1, LOW);
      
      }
    else if(mode == 1)
    {
      digitalWrite(S0, HIGH);
      digitalWrite(S1, HIGH);
      }   
    
    
    }
