
// costanti motore destra
#define direzioneDx 12 // pin di direzione
#define pwmDx 3 // pin PWM
#define ENpinDx 9 // enable pin 

// costanti motore sinistra
#define direzioneSx 13 // pin di direzione
#define pwmSx 11 // pin PWM
#define ENpinSx 8 // enable pin 

// pin per la lettura di un pulsante
#define button 5
#define led 4

void movement(int velMotSx, bool direzDx, int velMotDx, bool direzSx){
  // motore di destra
  analogWrite(pwmDx, velMotSx);  
  digitalWrite(direzioneDx, direzDx);
  digitalWrite(ENpinDx, HIGH);

  //motore di sinistra
  analogWrite(pwmSx, velMotDx); 
  digitalWrite(direzioneSx, direzSx);   
  digitalWrite(ENpinSx, HIGH);
}

int motInput;
int sp;
byte velMotori = 200; 
int input; 
bool stateMotor = false; 

void setup() {
  // set dei pin digitali come output
  pinMode(pwmDx, OUTPUT);
  pinMode(pwmSx, OUTPUT);
  pinMode(ENpinDx, OUTPUT);
  pinMode(ENpinSx, OUTPUT);
  pinMode(direzioneDx, OUTPUT);
  pinMode(direzioneSx, OUTPUT);

  // pin bottone
  pinMode(button, INPUT);
  
  // disabilito gli enable pin
  digitalWrite(ENpinDx, LOW);
  digitalWrite(ENpinSx, LOW);

  input = -1;
  
  Serial.begin(4800); //monitor seriale per la comunicazione
}


/*
IDEA PER IL MOVIMENTO:
con il mio programma ottengo un valore che va da 0 a 50,
ed è tanto più piccolo quanto l'obiettivo è "centrale".
pensavo di andare a sottrarre questo valore alla velocità 
del cingolo dalla parte in cui si vuole girare.
più il valore è grande, tanto più l'oggetto sarà
laterale e tanto più il robot girerà
*/

void loop() {
  // disabilito gli enable pin
  digitalWrite(ENpinDx, LOW);
  digitalWrite(ENpinSx, LOW);

  if (digitalRead(button) )
  {
    stateMotor = !stateMotor;
    delay(2000);
  }
  if (stateMotor == true)
  {
    // fermo il motore
      Serial.println("off");
      digitalWrite(ENpinSx, LOW);
      digitalWrite(ENpinDx, LOW);
      analogWrite(pwmSx, 0);
      analogWrite(pwmDx, 0);
  }
  else
  {
    // lo faccio muovere
    Serial.println("on");
    if (Serial.available()) 
    {
      input = Serial.readString().toInt();
      motInput = abs(input - 50);
  
      sp = velMotori - motInput;
      if (input > 0)
      {
        if (input > 50)
        {
          //devo andare a destra
          movement(sp*4, false, velMotori, true);
        }
        else
        {
          // devo andare a sinistra
          movement(velMotori, false, sp*4, true);
        }
      }
    }
    
  }
}
