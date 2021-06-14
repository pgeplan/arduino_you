#define NUMBUTTONS 4

int notes[] = {262, 294, 330, 349};

void setup() {
  // put your setup code here, to run once:
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(2) == HIGH) {
    tone(6, notes[0]);
  }
  else if (digitalRead(3) == HIGH) {
    tone(6, notes[1]);
  }
  else if (digitalRead(4) == HIGH) {
    tone(6, notes[2]);
  }
  else if (digitalRead(5) == HIGH) {
    tone(6, notes[3]);
  }
  else {
    noTone(6);
  }
}
