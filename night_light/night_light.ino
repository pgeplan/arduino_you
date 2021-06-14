

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(A0, INPUT); // photocell pin
  pinMode(2, OUTPUT); // LED pin
  
}

void loop() {
  // put your main code here, to run repeatedly:
  int photoValue = analogRead(A0);
  Serial.println(photoValue);
  
  if (photoValue < 100) { // check serial monitor to tune this value
    digitalWrite(2, HIGH);
  }
  else {
    digitalWrite(2, LOW);
  }
}
