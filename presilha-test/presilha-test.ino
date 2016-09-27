void setup() {
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(9, LOW);
  digitalWrite(8, LOW);
  delay(5000);
}

void loop() {
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
  digitalWrite(9, HIGH);
  digitalWrite(8, LOW);
    
  delay(5000);

  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(9, LOW);
  digitalWrite(8, LOW);

  delay(100);
  
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(8, HIGH);
  
  delay(5000);
}

