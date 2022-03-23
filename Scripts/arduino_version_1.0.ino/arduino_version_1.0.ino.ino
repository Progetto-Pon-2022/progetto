// costanti motore A
#define direzioneA 12 // pin di direzione
#define pwmA 3 // pin PWM
#define ENpinA 9 // enable pin 

// costanti motore B
#define direzioneB 13 // pin di direzione
#define pwmB 11 // pin PWM
#define ENpinB 8 // enable pin 

// variabili
byte velMotori = 200; // velocità del movimento

int cmd; // variabile usata per il comando da eseguire

void setup() {
  // set dei pin digitali come output
  pinMode(pwmA, OUTPUT);
  pinMode(pwmB, OUTPUT);
  pinMode(ENpinA, OUTPUT);
  pinMode(ENpinB, OUTPUT);
  pinMode(direzioneA, OUTPUT);
  pinMode(direzioneB, OUTPUT);

  // disabilito gli enable pin
  digitalWrite(ENpinA, LOW);
  digitalWrite(ENpinB, LOW);
  
  Serial.begin(9600); //monitor seriale per la comunicazione
}

// function
void forward() {
  // valori motore A
  analogWrite(pwmA, velMotori);  
  digitalWrite(direzioneA, LOW);
  digitalWrite(ENpinA, HIGH);

  // valori motore B
  analogWrite(pwmB, velMotori); 
  digitalWrite(direzioneB, HIGH);   
  digitalWrite(ENpinB, HIGH);
}

void backward() {
  // valori motore A
  analogWrite(pwmA, velMotori);  
  digitalWrite(direzioneA, HIGH);
  digitalWrite(ENpinA, HIGH);

  // valori motore B
  analogWrite(pwmB, velMotori); 
  digitalWrite(direzioneB, LOW);   
  digitalWrite(ENpinB, HIGH);
}

void left() {
  // valori motore A
  analogWrite(pwmA, velMotori);  
  digitalWrite(direzioneA, LOW);
  digitalWrite(ENpinA, HIGH);

  // valori motore B
  analogWrite(pwmB, velMotori); 
  digitalWrite(direzioneB, LOW);   
  digitalWrite(ENpinB, HIGH);
}

void right() {
  // valori motore A
  analogWrite(pwmA, velMotori);  
  digitalWrite(direzioneA, HIGH);
  digitalWrite(ENpinA, HIGH);

  // valori motore B
  analogWrite(pwmB, velMotori); 
  digitalWrite(direzioneB, HIGH);   
  digitalWrite(ENpinB, HIGH);
}

void stops() {
  // valori motore A
  analogWrite(pwmA, LOW);  
  digitalWrite(direzioneA, LOW);
  digitalWrite(ENpinA, HIGH);

  // valori motore B
  analogWrite(pwmB, LOW); 
  digitalWrite(direzioneB, LOW);   
  digitalWrite(ENpinB, HIGH);
}

void loop() {
  // disabilito gli enable pin
  digitalWrite(ENpinA, LOW);
  digitalWrite(ENpinB, LOW);
  
  // se abbiamo una comunicazione seriale
  if (Serial.available()) {
    cmd = Serial.read();
    Serial.println(cmd); // rimano a python il comando inserito 
    
    // controllo il tipo di comando letto
    if (cmd == 'w') {
      forward(); // avanti
    } else if (cmd == 's') {
      backward(); // indietro
    } else if (cmd == 'd') {
      right(); // destra
    } else if (cmd == 'a') {
      left(); // sinistra
    } else if (cmd == 'r') {
      stops(); // stop
    }
  } 

}
