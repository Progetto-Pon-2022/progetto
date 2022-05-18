#include <Servo.h>

int dist = 25; //DISTANZA MINIMA IN MM

int pos = 0;
int posAttuale = 0;
int valPrec = 0;
int vLetto = 0;
int time = 0;
bool acceso = true;
Servo motore1;
Servo motore2;

unsigned long int tempo_pulsante = 0;
const int SONAR_TRIGGER_PIN = 6;
const int SONAR_ECHO_PIN = 7;


// Variabile che gestisce il numero associato allo stato
int stato = 0;

unsigned int measure_distance()
{
 digitalWrite(SONAR_TRIGGER_PIN, HIGH);
 
//Tenendo alto per 10 microsecondi il trigger il sensore invia un impulso sonoro
//e resta in attesa che ritorni dopo aver rimbalzato sull'ostacolo

 delayMicroseconds(10);
 digitalWrite(SONAR_TRIGGER_PIN, LOW);
 unsigned long durata_impulso = pulseIn (SONAR_ECHO_PIN, HIGH);

// pulseln(,) legge quando il pin va al livello richiesto (nel nostro caso a livello alto)
// e ci restituisce il tempo in ms di permanenza a quel livello

 delay(50);
 return( (unsigned int) (durata_impulso / 58) );
// La funzione ci restituisce la distanza in cm (µs/58=cm)
}

// SETUP
void setup()
{
  Serial.begin(9600);
  motore1.attach(9);
  motore2.attach(10);
  pinMode(SONAR_TRIGGER_PIN, OUTPUT);
  pinMode(SONAR_ECHO_PIN, INPUT);
}


// LOOP
void loop(){
  morsa();
}

void morsa(){
  unsigned int distanza = measure_distance();
   Serial.println(distanza);
  if (distanza < dist){
    posAttuale = 180;
    Serial.println("si");
    for (int i=0; i<180;i=i+5){
      
      motore1.write(i);
      delay(50);
    }
    braccio();
  }else{
    Serial.println("no");
    posAttuale = 0;
    motore1.write(posAttuale);
    delay(1000);
    motore2.write(posAttuale);
  }
  
}

void braccio(){
  for (int i=0; i<95;i=i+2){
    motore2.write(i);
    delay(100);
  }
}
