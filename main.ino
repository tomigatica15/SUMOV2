const int trig = 2;
const int echo = 3;
const int THRESHOLD = 500;

const int sensorPins[] = {A0, A1, A2, A3};
const int motorPins[] = {8, 9, 10, 11};

const int sensorValues[4] = {0, THRESHOLD, THRESHOLD, THRESHOLD};

void setup() {
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  for (int i = 0; i < 4; i++) {
    pinMode(sensorPins[i], INPUT);
    pinMode(motorPins[i], OUTPUT);
  }
}

void controlMotor(int motorPin1, int motorPin2, int direction, int delayTime) {
  digitalWrite(motorPin1, direction);
  digitalWrite(motorPin2, !direction);
  delay(delayTime);
}

void ultrasonic() {
  long distance;
  int duration;

  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);
  distance = duration * 0.034 / 2;

  if (distance < 20) {
    controlMotor(motorPins[0], motorPins[1], HIGH, 1); // Both motors forward
  } else {
    controlMotor(motorPins[2], motorPins[3], HIGH, 1); // Both motors backward
  }
}

void loop() {
  ultrasonic();
  int sensorData = 0;
  for (int i = 0; i < 4; i++) {
    if (analogRead(sensorPins[i]) > THRESHOLD) {
      sensorData |= (1 << i);
    }
  }

  switch (sensorData) {
    case 1: // 0001
      controlMotor(motorPins[1], motorPins[3], HIGH, 1000); // Right Back White
      break;
    case 2: // 0010
      controlMotor(motorPins[0], motorPins[2], HIGH, 1000); // Left Back White
      break;
    case 3: // 0011
      controlMotor(motorPins[1], motorPins[3], HIGH, 1000); // Right Back White
      break;
    case 4: // 0100
      controlMotor(motorPins[0], motorPins[2], HIGH, 1000); // Left Front White
      break;
    case 5: // 0101
      controlMotor(motorPins[0], motorPins[2], HIGH, 1000); // Left Front White
      break;
    case 6: // 0110
      controlMotor(motorPins[2], motorPins[3], HIGH, 1000); // Back Left & Right White
      break;
    case 7: // 0111
      controlMotor(motorPins[2], motorPins[3], HIGH, 1000); // Back Left & Right White
      break;
    case 8: // 1000
      controlMotor(motorPins[0], motorPins[2], HIGH, 1000); // Left Front White
      break;
    case 9: // 1001
      controlMotor(motorPins[0], motorPins[1], HIGH, 1); // Front Left & Back Right White
      break;
    case 10: // 1010
      controlMotor(motorPins[0], motorPins[2], HIGH, 1000); // Left Front & Back Left White
      break;
    case 11: // 1011
      controlMotor(motorPins[2], motorPins[3], HIGH, 1000); // Back Left & Right White
      break;
    case 12: // 1100
      controlMotor(motorPins[0], motorPins[1], HIGH, 1); // Front Left & Front Right White
      break;
    case 13: // 1101
      controlMotor(motorPins[2], motorPins[3], HIGH, 1000); // Back Left & Right White
      break;
    case 14: // 1110
      controlMotor(motorPins[2], motorPins[3], HIGH, 1000); // Back Left & Right White
      break;
    default: // All Black
      controlMotor(motorPins[0], motorPins[1], HIGH, 1); // Both motors forward
      break;
  }
}
