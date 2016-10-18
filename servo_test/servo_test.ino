#include <Servo.h>

// setup servo
#define SERVORIGHT   50
#define SERVOCENTRE 100
#define SERVOLEFT   150
#define SERVOPIN     5      // GPIO 5

Servo servo;

void setup() {
    Serial.begin(115200);
    Serial.println(" SG90 Servo");
    // set the servo data pin
    servo.attach(SERVOPIN);

}

void loop() {
    Serial.println("test");
    servo.write(SERVOLEFT);
    delay(300);

    servo.write(SERVORIGHT);
    delay(600);

    servo.write(SERVOCENTRE);
    delay(300);

    delay(2000); // 2 sec
}

