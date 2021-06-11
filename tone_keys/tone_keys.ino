#define NUMBUTTONS 4

int notes[] = {262, 294, 330, 349};
int buttonPins[] = {2, 3, 4, 5, 6};

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
  bool buttonPressed = false;
  for (int i=0; i < NUMBUTTONS; i++) {
      int buttonPin = buttonPins[i];
    if (digitalRead(buttonPin) == HIGH) {
      tone(6, notes[i]);
      buttonPressed = true;
    }
    
  }
  if (buttonPressed == false) {
    noTone(6);
  }
}
