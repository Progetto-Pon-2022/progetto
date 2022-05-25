#include <Servo.h>

int dist = 25;

bool oggetto = true;

Servo motore1;
Servo motore2;
Servo motore3;

unsigned long int tempo_pulsante = 0;
const int SONAR_TRIGGER_PIN = 8;
const int SONAR_ECHO_PIN = 9;

unsigned int measure_distance()
{
 digitalWrite(SONAR_TRIGGER_PIN, HIGH);

 delayMicroseconds(10);
 digitalWrite(SONAR_TRIGGER_PIN, LOW);
 unsigned long durata_impulso = pulseIn (SONAR_ECHO_PIN, HIGH);

 delay(50);
 return( (unsigned int) (durata_impulso / 58) );
}

void setup()
{
  Serial.begin(9600);
  
  motore1.attach(5);
  motore2.attach(3);
  motore3.attach(11);
  
  pinMode(SONAR_TRIGGER_PIN, OUTPUT);
  pinMode(SONAR_ECHO_PIN, INPUT);
}


void loop(){
  unsigned int distanza = measure_distance();
  Serial.print("distanza: ");
  Serial.println(distanza);
   
  if (distanza < dist){ // se ho un oggetto vicino
    Serial.println("Oggetto Trovato");
    
    Serial.print("Chiudo pinza - ");
    motore1.write(50);
    delay(2000);
    
    Serial.println(" Alzo Braccio");
    braccio_su();
    delay(2000);
    
    Serial.print("Apro pinza - ");
    motore1.write(180);
    delay(2000);
    
    Serial.println(" Abbasso Braccio");
    braccio_giu();
    delay(2000);
    
  }else{ // se non ho un oggetto vicino
    Serial.println("Nessun oggetto");
    
    Serial.print("Pinza aperta - ");
    motore1.write(180);
    delay(2000);
  
    Serial.println(" Braccio giu");
    motore2.write(0);
    motore3.write(95);
    delay(2000);
  }
  Serial.println("");
}

void braccio_su(){
  for (int i = 0; i < 95; i = i + 2){
    motore2.write(i);
    motore3.write(95-i);
    delay(100);
  }
}

void braccio_giu() {
  for (int i = 0; i < 95; i = i + 2){
    motore3.write(i);
    motore2.write(95-i);
    delay(100);
  }
}
