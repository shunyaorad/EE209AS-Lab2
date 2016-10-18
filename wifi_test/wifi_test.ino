#include <ESP8266WiFi.h>
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
int SERVO_PIN = 5;
int SERVO_RIGHT = 150;
int SERVO_LEFT = 50;
int SERVO_CENTER = 100;


WiFiServer server(80); //Initialize the server on Port 80
void setup() {

  WiFi.mode(WIFI_AP); //Our ESP8266-12E is an AccessPoint 
  WiFi.softAP("Hello_IoT", "12345678"); // Provide the (SSID, password); . 
  server.begin(); // Start the HTTP Server
  
  //Looking under the hood
  Serial.begin(115200); //Start communication between the ESP8266-12E and the monitor window
  IPAddress HTTPS_ServerIP= WiFi.softAPIP(); // Obtain the IP of the Server 
  Serial.print("Server IP is: "); // Print the IP to the monitor window 
  Serial.println(HTTPS_ServerIP);
  myservo.attach(SERVO_PIN);
  
 
}

void moveServo(int k) {
  int i = 0;
  while(i<10){
  myservo.write(SERVO_LEFT);
  delay(k*300);
  myservo.write(SERVO_RIGHT);
  delay(k*300);
  i += 1;
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

    // Prepare the HTML document to respond and add buttons:
    String s = "HTTP/1.1 200 OK\r\n";
    s += "Content-Type: text/html\r\n\r\n";
    s += "<!DOCTYPE HTML>\r\n<html>\r\n";


    s += "<a href=\"Cup_A\">Cup_A</a>";
    s += "<br><br><br>";


    s += "<a href=\"Cup_B\">Cup_B</a>";
    s += "</html>\n";

    //Serve the HTML document to the browser.
    client.flush(); //clear previous info in the stream
    client.print(s); // Send the response to the client
    delay(1);
    Serial.println("Client disonnected"); //Looking under the hood

    // Handle the Request
    if (request.indexOf("/Cup_A") != -1){ 
    moveServo(1);}
    else if (request.indexOf("/Cup_B") != -1){ 
    moveServo(2);} 
}

