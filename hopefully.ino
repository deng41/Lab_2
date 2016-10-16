#include <ESP8266WiFi.h>
#include <Servo.h>
#include"controller.h"
int rmspeed = 50;
int stst = 0;
int nam = 0;
int mup = 0;
int timn = 10;
Servo myservo;  // create servo object to control a servo
int pos = 60;    // variable to store the servo position

const short int BUILTIN_LED1 = 2; //GPIO2
const short int BUILTIN_LED2 = 16;//GPIO16
const short int HAHA = 2; //GPIO2
const short int LED_PIN = 16;//GPIO16
WiFiServer server(80); //Initialize the server on Port 80

void setup() {

WiFi.mode(WIFI_AP); //Our ESP8266-12E is an AccessPoint 
WiFi.softAP("Hello_IoT2", "123456789"); // Provide the (SSID, password); . 
server.begin(); // Start the HTTP Server

pinMode(LED_PIN, OUTPUT); //GPIO16 is an OUTPUT pin;
digitalWrite(LED_PIN, LOW); //Initial state is ON



Serial.begin(9600); //Start communication between the ESP8266-12E and the monitor window
IPAddress HTTPS_ServerIP= WiFi.softAPIP(); // Obtain the IP of the Server 
//Serial.print("Server IP is: "); // Print the IP to the monitor window 
//Serial.println(HTTPS_ServerIP);


pinMode(LED_PIN, OUTPUT); //GPIO16 is an OUTPUT pin;
digitalWrite(LED_PIN, LOW); //Initial state is ON

//At the bottom of loop() function add the following lines of code:

// Handle the Request
myservo.attach(16);



}

void loop() { 
  
WiFiClient client = server.available();

  if (!client){ 
    Serial.print(stst);
    if(stst == 1)
    {
      
      myservo.write(pos);              
      delay(timn);
      if(mup ==1)
      {
        pos++;
        if(pos==160)
        {
          mup = 0;
          pos= pos-3;
        }
      }
      if(mup ==0)
      {
        pos--;
        if(pos==20)
        {
          mup = 1;
          pos= pos+3;
        }
      }
    }
    
return; 
} 
Serial.write('S');
Serial.write(rmspeed);
//Serial.write(',');
Serial.write('A');
Serial.write(stst);
Serial.write('N');
Serial.write(nam);

//Serial.write(',');
//Serial.write('T');

//Looking under the hood 
//Serial.println("Somebody has connected :)");

String request = client.readStringUntil('\r');
//Looking under the hood 
//Serial.println(request);
if (request.indexOf("/OFF") != -1){ 
digitalWrite(LED_PIN, HIGH);
}
else if (request.indexOf("/ON") != -1){ 
digitalWrite(LED_PIN, LOW); 
}
else if (request.indexOf("/UP") != -1){ 
rmspeed = rmspeed - 10;
timn = timn - 2;
}
else if (request.indexOf("/DO") != -1){ 
rmspeed = rmspeed + 10;
timn = timn + 2;
}
else if (request.indexOf("/SS") != -1){ 
stst = 0;
}
else if (request.indexOf("/PL") != -1){ 
stst = 1;
}
else if (request.indexOf("/BD") != -1){ 
nam = 1;
}
else if (request.indexOf("/SW") != -1){ 
nam = 2;
}

//Serve the HTML document to the browser.


// Prepare the HTML document to respond and add buttons:
String s = "HTTP/1.1 200 OK\r\n";
String ss = "hi\n";
s += "Content-Type: text/html\r\n\r\n";
s += "<!DOCTYPE HTML>\r\n<html>\r\n";
s += "<br><input type=\"button\" name=\"b1\" value=\"LED On\"";
s += " onclick=\"location.href='/ON'\">";
s += "<br><br><br>";
s += "<br><input type=\"button\" name=\"b1\" value=\"Speed up\"";
s += " onclick=\"location.href='/UP'\">";
s += "<br><br><br>";
s += "<br><input type=\"button\" name=\"b1\" value=\"Speed down\"";
s += " onclick=\"location.href='/DO'\">";
s += "<br><br><br>";
s += "<br><input type=\"button\" name=\"b1\" value=\"LED Off\"";
s += " onclick=\"location.href='/OFF'\">";
s += "<br><br><br>";
s += "<br><input type=\"button\" name=\"b1\" value=\"STOP\"";
s += " onclick=\"location.href='/SS'\">";
s += "<br><br><br>";
s += "<br><input type=\"button\" name=\"b1\" value=\"PLAY\"";
s += " onclick=\"location.href='/PL'\">";
s += "<br><br><br>";
s += "<br><input type=\"button\" name=\"b1\" value=\"Birthday\"";
s += " onclick=\"location.href='/BD'\">";
s += "<br><br><br>";
s += "<br><input type=\"button\" name=\"b1\" value=\"Small World\"";
s += " onclick=\"location.href='/SW'\">";
s += "</html>\n";
client.flush(); //clear previous info in the stream
client.print(s); // Send the response to the client
delay(1);
//Serial.println("Client disonnected"); //Looking under the 
//Serial.print('2');

  
  }
