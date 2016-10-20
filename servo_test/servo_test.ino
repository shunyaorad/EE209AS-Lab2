#include <Servo.h>

// setup servo
#define SERVOCENTER 45  // 50 is the rest position
#define SERVORIGHT  90
#define SERVOLEFT   0
#define SERVOPIN     2      // GPIO 5

Servo servo;

void setup() {
    Serial.begin(115200);
    Serial.println(" SG90 Servo");
    // set the servo data pin
    servo.attach(SERVOPIN);

}

void loop() {
    servo.write(SERVOCENTER);
    Serial.println("center");
    delay(4000);

    servo.write(SERVORIGHT);
    Serial.println("right");
    delay(4000);
    
    servo.write(SERVOLEFT);
    Serial.println("left");
    delay(4000);
}

