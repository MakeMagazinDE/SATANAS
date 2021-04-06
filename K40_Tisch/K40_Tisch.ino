#define EN        8       // Schrittmotor-Treiber einschalten
#define X_DIR     5       // Richtungs-Pin Z-Achse
#define X_STP     2       // Schritt-Pin Z-Achse
#define X_UP     10       // Pin Schalter rauf
#define X_DOWN   11       // Pin Schalter runter
#define FOCUS    12       // Pin Taster Autofocus   
#define ENDSTOPP  9       // Pin oberer Tischanschlag 
#define F_EBENE  21       // Abstand Endschalter Fokusebene (mm)
void step(boolean dir, byte dirPin, byte stepperPin, int steps)
{
  digitalWrite(dirPin, dir);
  delay(50);
  for (int i = 0; i < steps; i++) {
    digitalWrite(stepperPin, HIGH);
    delayMicroseconds(800);  
    digitalWrite(stepperPin, LOW);
    delayMicroseconds(800);  
  }
}
void reset(boolean dir, byte dirPin, byte stepperPin, byte stopPin)
{
    while(digitalRead(stopPin) == true) {
    step(false, dirPin, stepperPin, 10);  
  }
  Serial.println("Endstopp erreicht"); 
}
void setup(){
  pinMode(X_DIR, OUTPUT); pinMode(X_STP, OUTPUT);
  pinMode(EN, OUTPUT);
  digitalWrite(EN, LOW);
  pinMode(X_UP, INPUT_PULLUP);
  pinMode(X_DOWN, INPUT_PULLUP);
  pinMode(FOCUS, INPUT_PULLUP);
  pinMode(ENDSTOPP, INPUT_PULLUP);
  Serial.begin(9600);           
  Serial.println("Tisch Reset"); 
  reset(false, X_DIR, X_STP, ENDSTOPP);
  step(true, X_DIR, X_STP, F_EBENE*100);  
  Serial.println("Tisch in Leer-Fokusebene"); 
}
void loop(){
  if (digitalRead(X_DOWN) == false) {
    Serial.println("Tisch runter"); 
    step(true, X_DIR, X_STP, 10);
  }
  if (digitalRead(X_UP) == false) {
    Serial.println("Tisch rauf"); 
    step(false, X_DIR, X_STP, 10);
  } 
  if (digitalRead(FOCUS) == false) {
    Serial.println("Autofokus angefordert"); 
    reset(false, X_DIR, X_STP, ENDSTOPP);
    step(true, X_DIR, X_STP, F_EBENE*100);  
    Serial.println("Tisch im Autofokus"); 
  } 
}
