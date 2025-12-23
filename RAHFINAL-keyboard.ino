#include <Servo.h>

// ===== SERVA =====
Servo baseServo;
Servo armServo;
Servo clawServo;

// ===== PINY SERV =====
const int BASE_PIN = 9;
const int ARM_PIN  = 10;
const int CLAW_PIN = 11;

// ===== KLÁVESNICE =====
const int keyPins[4] = {2, 3, 4, 5};

// ===== JOYSTICK =====
const int JOY_Y   = A0;
const int JOY_BTN = 6;

// ===== BASE 360 =====
const int BASE_STOP = 90;
const int BASE_LEFT = 80;
const int BASE_RIGHT = 100;

// ===== ARM 180 =====
int armAngle = 90;
const int ARM_STEP = 2;

// ===== CLAW =====
int clawAngle = 130;
const int CLAW_HOME = 130;
const int CLAW_MIN  = 160;
const int CLAW_MAX  = 170;
const int DEADZONE  = 100;

// =========================

void setup() {
  // Serva
  baseServo.attach(BASE_PIN);
  armServo.attach(ARM_PIN);
  clawServo.attach(CLAW_PIN);

  baseServo.write(BASE_STOP);
  armServo.write(armAngle);
  clawServo.write(CLAW_HOME);

  // Klávesnice
  for (int i = 0; i < 4; i++) {
    pinMode(keyPins[i], INPUT_PULLUP);
  }

  // Joystick
  pinMode(JOY_BTN, INPUT_PULLUP);
}

void loop() {
  // ====== BASE ======
  if (digitalRead(keyPins[0]) == LOW) {
    baseServo.write(BASE_LEFT);
  }
  else if (digitalRead(keyPins[1]) == LOW) {
    baseServo.write(BASE_RIGHT);
  }
  else {
    baseServo.write(BASE_STOP);
  }

  // ====== ARM ======
  if (digitalRead(keyPins[2]) == LOW) {
    armAngle += ARM_STEP;
  }
  else if (digitalRead(keyPins[3]) == LOW) {
    armAngle -= ARM_STEP;
  }

  armAngle = constrain(armAngle, 0, 180);
  armServo.write(armAngle);

  // ====== CLAW ======
  int joyY = analogRead(JOY_Y);
  bool clawBtn = (digitalRead(JOY_BTN) == LOW);

  if (clawBtn) {
    if (joyY < 512 - DEADZONE) {
      clawAngle = CLAW_MIN;
    }
    else if (joyY > 512 + DEADZONE) {
      clawAngle = CLAW_MAX;
    }
  }
  else {
    if (clawAngle < CLAW_HOME) clawAngle++;
    else if (clawAngle > CLAW_HOME) clawAngle--;
  }

  clawServo.write(clawAngle);

  delay(15);
}
