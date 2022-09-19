#define xStep 2
#define xDir 5
#define xEnd

#define yStep 3
#define yDir 6
#define yEnd

#define spnEn 13

#define enCNC 8

#define Delay 150

struct cord {
  int x,y;
};

int X = 0, Y = 0; // in mm;

int xSq[8] = {
  17,51,85, 119,153,187,221,255
};

int ySq[8] = {
  17,51,85, 119,153,187,221,255
};

void stepX(int mm) {
  X+=mm;
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

void stepY(int mm) {
  Y+=mm;
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


void goHome() {
  while(digitalRead(xEnd)) {
    digitalWrite(xStep, HIGH);
    digitalWrite(xStep, LOW);
    delayMicroseconds(Delay);    
  }
  X = 0;

  while(digitalRead(yEnd)) {
    digitalWrite(yStep, HIGH);
    digitalWrite(yStep, LOW);
    delayMicroseconds(Delay);    
  }
  Y = 0;

  return;
}

int readInt() {
  int res = 0;
  bool ok = 0;
  while(true) {
    if(Serial.available() > 0) {
      char c = Serial.peek();
      if(c >= '0' && c <= '9') {
        ok = 1;
        res = res*10 + c-'0';
        Serial.read();
      }
      else if(ok){
        break;
      }
      else {
        Serial.read();
      }
    }
  }
  return res;
}


char readChar() {
  while(true) {
    if(Serial.available() > 0) {
      return Serial.read();
    }
  }
}

void setup() {
  pinMode(yStep, OUTPUT);
  pinMode(yDir, OUTPUT);
  pinMode(yEnd, INPUT_PULLUP);
  
  pinMode(xStep,OUTPUT);
  pinMode(xDir, OUTPUT);
  pinMode(xEnd, INPUT_PULLUP)

  pinMode(EnCNC, OUTPUT);
  digitalWrite(EnCNC, LOW);
  
  Serial.begin(9600);
  digitalWrite(mgPin, LOW);

  goHome();  
}

void goTo(cord s) {
  stepX(s.x-X);
  stepY(s.y-Y);
}

void loop() {
  char oper = readChar();

  if(oper == 'M') {
    cord s; s.x = xSq[readInt()]; s.y = ySq[readInt()];
    cord e; e.x = xSq[readInt()]; e.y = ySq[readInt()];
    goTo(s)
    if(e.x < s.x) {
      stepX(-17);
    } else if(s.x < e.x) {
      stepX(17);
    }

    if(s.y < e.y) {
      goTo({s.x,e.y-17});
    } else if(e.y < s.y) {
      goTo({s.x, e.y+17});
    }

    goTo({e.x,Y});
    goTo(e);
  } else if(oper == '') {
    
  }
}
