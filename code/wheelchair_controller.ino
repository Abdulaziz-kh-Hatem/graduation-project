// Wheelchair Motor and Sensor Controller

int linearSpeed = 120;
int rotationSpeed = 100;
int stopDelayTime = 1500;

// Motor Driver Pins
const int ENA = 5;
const int IN1 = 8;
const int IN2 = 9;
const int ENB = 6;
const int IN3 = 10;
const int IN4 = 11;

// Sensor and Buzzer Pins
const int FRONT_TRIG = 2;
const int FRONT_ECHO = 12;
const int REAR_TRIG = 4;
const int REAR_ECHO = 7;
const int BUZZER_PIN = 3;

char command; 
char currentState = '2'; // '1'=Forward, '3'=Backward, '4'=Rotate, '2'=Stop
unsigned long lastSensorUpdate = 0; 

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(FRONT_TRIG, OUTPUT); pinMode(FRONT_ECHO, INPUT);
  pinMode(REAR_TRIG, OUTPUT);  pinMode(REAR_ECHO, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  Serial.begin(9600); 
  stopMotors(); 
}

void loop() {
  // Read Bluetooth command
  if (Serial.available() > 0) {
    command = Serial.read(); 
    
    if(command == '1' || command == '2' || command == '3' || command == '4') {
        currentState = command; 
    }
    
    switch (command) {
      case '1':
        moveForward(); 
        break;
      case '3':
        moveBackward();
        break;
      case '4':
        rotateChair();
        break;
      case '2':
        stopMotors();
        break;
    }
  }

  // Check for obstacles every 40 ms
  if (millis() - lastSensorUpdate >= 40) {
    checkObstacles();
    lastSensorUpdate = millis();
  }
}

void checkObstacles() {
  if (currentState == '1') {
    long frontDist = getDistance(FRONT_TRIG, FRONT_ECHO);
    if (frontDist > 0 && frontDist < 40) {
      stopMotors();                          
      digitalWrite(BUZZER_PIN, HIGH);        
      delay(stopDelayTime);                  
      digitalWrite(BUZZER_PIN, LOW);         
      
      currentState = '4'; 
      rotateChair();
    }
  }
  else if (currentState == '3') {
    long rearDist = getDistance(REAR_TRIG, REAR_ECHO);
    if (rearDist > 0 && rearDist < 30) {
      stopMotors();                          
      digitalWrite(BUZZER_PIN, HIGH);        
      delay(stopDelayTime);                  
      digitalWrite(BUZZER_PIN, LOW);         
      
      currentState = '2'; 
    }
  }
}

long getDistance(int trig, int echo) {
  digitalWrite(trig, LOW); delayMicroseconds(2);
  digitalWrite(trig, HIGH); delayMicroseconds(10);
  digitalWrite(trig, LOW);
  
  long duration = pulseIn(echo, HIGH, 8000); 
  
  if (duration == 0) return 999;
  return duration * 0.034 / 2;
}

void moveForward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, linearSpeed);
  analogWrite(ENB, linearSpeed);
}
 
void moveBackward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, linearSpeed);
  analogWrite(ENB, linearSpeed);
}

void rotateChair() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, rotationSpeed);
  analogWrite(ENB, rotationSpeed);
}

void stopMotors() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
