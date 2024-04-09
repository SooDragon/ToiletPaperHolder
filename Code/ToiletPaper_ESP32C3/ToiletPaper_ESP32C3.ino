#include <ESP32Servo.h>

Servo cover;
Servo hanger;

#define cover_Close      0
#define cover_Open       170

#define hanger_Right      0
#define hanger_Wrong      174

#define switch_pin        9
#define cover_pin         6
#define hanger_pin        7
#define servo_min_us      500
#define servo_max_us      2500
#define servo_period_Hz   50

void setup() {
  Serial.begin();
  cover.setPeriodHertz(servo_period_Hz);
	hanger.setPeriodHertz(servo_period_Hz);
  cover.attach(cover_pin, servo_min_us, servo_max_us);
	hanger.attach(hanger_pin, servo_min_us, servo_max_us);
}

void loop() {
  if (ReadSW() == 1) {
    ChangeMode();
  }
}

bool ReadSW() {
  pinMode(switch_pin, INPUT_PULLUP);

  uint8_t _chatterCheck = 0;
  for (uint8_t _count = 0; _count < 100; _count ++) {
    _chatterCheck = _chatterCheck + !(digitalRead(switch_pin));
    delay(1);
  }

  if (_chatterCheck < 50) {
    return 0;
  }
  else {
    Serial.print("Switch Pressed"); Serial.println(_chatterCheck);
    return 1;
  }
}

void ChangeMode() {
  Serial.print("Changing Mode to: ");
  cover.write(cover_Open);
  delay(1000);
  if (45 < hanger.read()) {
    hanger.write(hanger_Right);
    Serial.println("Right");
  }
  else {
    hanger.write(hanger_Wrong);
    Serial.println("Wrong");
  }
  delay(1000);
  cover.write(cover_Close);
  Serial.println("Changing Complete");
}
