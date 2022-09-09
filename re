#define YStep 3
#define YDir 6
#define XStep 2
#define XDir 5
#define EnCNC 8
#define mgPin 13

#define Delay 150
#define XDelay 150

void stepY(int mm) {
  int steps = mm*(200*16)/2/20;
   if (steps < 0) {
      steps = -steps;
      digitalWrite (YDir, HIGH);
      digitalWrite (XDir, HIGH);
   }
   else {
      digitalWrite (YDir, LOW);
      digitalWrite (XDir, LOW);
   }
   while (steps--) {
      digitalWrite (YStep, HIGH);
      digitalWrite (XStep, HIGH);
      digitalWrite (YStep, LOW);
      digitalWrite (XStep, LOW);
      delayMicroseconds(Delay);
   }
   
}

void stepX(int mm) {
  int steps = mm*(200*16)/2/20;
   if (steps < 0) {
      steps = -steps;
      digitalWrite (YDir, LOW);
      digitalWrite (XDir, HIGH);
   }
   else {
      digitalWrite (YDir, HIGH);
      digitalWrite (XDir, LOW);
   }
   while (steps--) {
      digitalWrite (YStep, HIGH);
      digitalWrite (XStep, HIGH);
      digitalWrite (YStep, LOW);
      digitalWrite (XStep, LOW);
      delayMicroseconds(Delay);
   }
   
}

void setup() {
   pinMode(YStep,OUTPUT);
   pinMode(YDir,OUTPUT);
   pinMode(13,OUTPUT);
   pinMode(4,INPUT_PULLUP);
   
   pinMode(XStep,OUTPUT);
   pinMode(XDir,OUTPUT);

   pinMode(EnCNC, OUTPUT);
   digitalWrite(EnCNC, LOW);
   Serial.begin(9600);
  digitalWrite(mgPin, LOW);
}
int Z = 0;
void loop() {
  delay(2000);
  Serial.println(digitalRead(4));
  if(digitalRead(4)) return;
  if(Z == 0) {
    digitalWrite(mgPin, HIGH);
    stepY(70);
    digitalWrite(mgPin, LOW);
    Z++;
  }
  else if(Z == 1) {
    stepX(35);
    stepY(35);
    digitalWrite(mgPin, HIGH);
    stepY(17);
    stepX(105);
    stepY(-17);
    digitalWrite(mgPin, LOW);
    stepY(-35);
    stepX(-140);
    digitalWrite(mgPin, HIGH);
    stepY(17);
    stepX(35);
    stepY(18);
    digitalWrite(mgPin, LOW);
  }
}
