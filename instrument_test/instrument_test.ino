/* Author: Shun Yao: shunyaorad@gmail.com */

#include <ESP8266WiFi.h>
#include <Servo.h>

// create servo object to control a servo
Servo myservo1;
Servo myservo2;

/* Push button */
const int buttonPin = 12; //Physical pin is 6
int buttonState = 0;

/* Servo parameters */
#define cupA_pos 90    // Position of cup A
#define cupB_pos 0    // Position of cup B
#define rest_pos 45     // Rest position not hit the cup
int servo1_pin = 2;   // Physical Pin is 4
int servo2_pin = 0;   // Physical Pin is 3
int rest_time = 200;  // miliseconds to wait for servo to move
WiFiServer server(80); //Initialize the server on Port 80

/* Potetiometer parameters */
int potDiff = 0;
int potPrev = 0;
int potVal = 0;

void setup() {
  pinMode(buttonPin, INPUT);
  // Potentiometer pin */
  pinMode(A0, INPUT);
  /* Wifi setup */
  //Our ESP8266-12E is an AccessPoint
  WiFi.mode(WIFI_AP);
  // Provide the (SSID, password);
  WiFi.softAP("JAMBOX", "12345678");
  // Start the HTTP Server
  server.begin();

  //Looking under the hood
  //Start communication between the ESP8266-12E and the monitor window
  Serial.begin(115200);
  // Obtain the IP of the Server
  IPAddress HTTPS_ServerIP= WiFi.softAPIP();
  // Print the IP to the monitor window
  Serial.print("Server IP is: ");
  Serial.println(HTTPS_ServerIP);

  /* Servo initialization */
  // attaches the servo
  myservo1.attach(servo1_pin);
  myservo2.attach(servo2_pin);
  // initiate servo position at rest
  myservo1.write(rest_pos);
  myservo2.write(rest_pos);
}

void hit(Servo servo, int t, int pos) {
  // the cup position
  servo.write(pos);
  // wait for servo to move
  delay(t);
  // Go back to rest position
  servo.write(rest_pos);
  // wait for servo to move
  delay(t);
}

/* Servo is controlled rotating potentioeter */

void readPot(Servo servo) {
  servo.write(rest_pos);
    // Loop so that it doesn't terminate itself
    while (true) {
      buttonState = digitalRead(buttonPin);
      int val = analogRead(A0);
      val = map(val, 0, 1023, cupB_pos, cupA_pos);
      servo.write(val);
      delay(15);
      if (buttonState == 1) {
        break;
      }
  }
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  //Looking under the hood
  Serial.println("Somebody has connected :)");

  //Read what the browser has sent into a String class and print the request to the monitor
  String request = client.readStringUntil('\r');

  //Looking under the hood
  Serial.println(request);

  // Prepare the HTML document to respond:
  String s = "HTTP/1.1 200 OK\r\n";
  s += "Content-Type: text/html\r\n\r\n";
  s += "<!DOCTYPE HTML>\r\n<html>\r\n";
  s += "<a href=\"Servo1_Cup_A\">Servo1_Cup_A</a>";
  s += "<br><br><br>";
  s += "<a href=\"Servo1_Cup_B\">Servo1_Cup_B</a>";
  s += "<br><br><br>";
  s += "<a href=\"Servo2_Cup_A\">Servo2_Cup_A</a>";
  s += "<br><br><br>";
  s += "<a href=\"Servo2_Cup_B\">Servo2_Cup_B</a>";
  s += "<br><br><br>";
  s += "</html>\n";
  s += "<a href=\"Potentiometer_Control1\">Potentiometer_Control1</a>";
  s += "</html>\n";
  s += "<br><br><br>";
  s += "</html>\n";
  s += "<a href=\"Potentiometer_Control2\">Potentiometer_Control2</a>";
  s += "</html>\n";

  //Serve the HTML document to the browser.
  client.flush(); //clear previous info in the stream
  client.print(s); // Send the response to the client
  delay(1);
  Serial.println("Client disonnected"); //Looking under the hood

  // Handle the Request
  if (request.indexOf("/Servo1_Cup_A") != -1){
  hit(myservo1, rest_time, cupA_pos);}

  else if (request.indexOf("/Servo1_Cup_B") != -1){
  hit(myservo1, rest_time, cupB_pos);}

  else if (request.indexOf("/Servo2_Cup_A") != -1){
  hit(myservo2, rest_time, cupA_pos);}

  else if (request.indexOf("/Servo2_Cup_B") != -1){
  hit(myservo2, rest_time, cupB_pos);}

  else if (request.indexOf("/Potentiometer_Control1") != -1){
  readPot(myservo1);}

  else if (request.indexOf("/Potentiometer_Control2") != -1){
  readPot(myservo2);}
}

