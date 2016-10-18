#include <Servo.h> 

int cupA_pos = 40;
int cupB_pos = 60;
int rest_pos = 0; 
int servo1_pin = 2;
int servo2_pin = 0;
int rest_time = 200;
 
Servo myservo1;  // create servo object to control a servo 
Servo myservo2;  // create servo object to control a servo 
void setup() 
{ 
  myservo1.attach(servo1_pin);  // attaches the servo on GPIO5 to the servo object 
  myservo1.write(rest_pos);  // 60 is the rest position
  myservo2.attach(servo2_pin);
  myservo2.write(rest_pos);
} 

/* Pause t second */
void pause(int t) {
  delay(t * 1000);
}

/* hit the cup */
void hit(Servo servo, int t, int pos) {
  servo.write(pos);  // the cup position
  delay(t);
  servo.write(rest_pos);  // Go back to rest position
  delay(t);
}

void loop() 
{ 
   hit(myservo1, rest_time, cupA_pos);
   pause(4);
   hit(myservo2, rest_time, cupB_pos);
   pause(1);
} 
