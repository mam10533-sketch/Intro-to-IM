int switchPin = 2;
int soundPin = A0;
int led1 = 9;
int led2 = 10;

int brightness = 255; // starts at full brightness
int threshold = 70;  // sound volume that's needed

void setup() {
  pinMode(switchPin, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // slide switch on and off
  if (digitalRead(switchPin) == LOW) {
    analogWrite(led1, 0);
    analogWrite(led2, 0);
    brightness = 255; // brightness reset when turned back on 
    return;
  }

  // sound detection
  int soundValue = analogRead(soundPin);
  int change = abs(soundValue - 512);

  if (change > threshold) {
    brightness = brightness - 50; // drop brightness by 50 each sound
    Serial.println("Lowering brightness.."); // debug to make sure sound is going through and brightness lowering
    delay(200);
  }

  // keeping the brightness between 0 and 255
  if (brightness < 0) {
    brightness = 0;
  }

  analogWrite(led1, brightness);
  analogWrite(led2, brightness);
}