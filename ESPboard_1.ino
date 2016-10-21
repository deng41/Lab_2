#include <ESP8266WiFi.h>
#include <Servo.h>
#include"controller.h"
int rmspeed = 50;// for speaker delay/speed not used in this lab, used with our own arduino mega just for fun
int nam = 0;// name of song, again, not used in this lab.
int startflag = 0;// start/stop flag for servo 1
int motor1direction = 0;//rotational direction for servo 1
int delaytimerforservo = 10;// base delay time for servo 1 and 2. this variable is controlled online
char recievedchar = '0';// recieved uart character
int receivednumber = 0;// recieved uart number
int servo2switch = 0;// start/stop flag for servo 2
Servo myservo;  // create servo object to control a servo
Servo servo2; // create servo object to control servo 2
int motor1position = 60;    // variable to store the servo motor1positionition
int motor2position = 60;// servo 2 position
int motor2direction = 0;// servo 2 rotational direction
String sensormessage = "0"; // string message from uart from esp board 2
char level = '0';// used in convert int to char
char remotecontrollermessage = '0';// used in convert char to int
const short int BUILTIN_LED1 = 2; //GPIO2 
const short int BUILTIN_LED2 = 16;//GPIO16

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
servo2.attach(5);



}

void loop() { 
  
WiFiClient client = server.available();



  if (!client){ 
    //Serial.print(1);
    

    if(Serial.available()) // recieve uart 
    {

      sensormessage = Serial.readString(); // read string from uart
      level = sensormessage.charAt(2); // data from distance sensor
      remotecontrollermessage = sensormessage.charAt(4); // data from RF controller

      receivednumber = level - '0'; // convert to int
      servo2switch = remotecontrollermessage - '0'; // convert to int


      
      Serial.println(receivednumber);
      Serial.println(servo2switch);
     }
    
    if(startflag == 1)
    {
      
      myservo.write(motor1position);  // set servo 1 to initial position            
      delay(delaytimerforservo+2*receivednumber); // set servo 1 speed
      if(motor1direction == 1) // servo going up
      {
        motor1position++; // increment for servo 1 position
        if(motor1position==160) // reach upper bound
        {
          motor1direction = 0;
          motor1position= motor1position-3;
        }
      }
      if(motor1direction ==0) // change servo 1 direction
      {
        motor1position--;
        if(motor1position==20) // reach lower bound
        {
          motor1direction = 1;
          motor1position= motor1position+3;
        }
      }
    }
    //servo2switch = 0;
    if(servo2switch == 1) // turn on servo 2
    {
      
      servo2.write(motor2position);  // initial servo2  position            
      delay(delaytimerforservo);
      if(motor2direction == 1) // servo rotation direction going up
      {
        motor2position++;
        if(motor2position==160) // reach upper bound 
        {
          motor2direction = 0;
          motor2position= motor2position-3;
        }
      }
      if(motor2direction ==0) // change direction to go down
      {
        motor2position--;
        if(motor2position==20) // reach lower bound direction 
        {
          motor2direction = 1;
          motor2position= motor2position+3;
        }
      }
    }
    
return; 
} 
  
// this full section is just for fun (a speaker with arduino mega) not include in this lab.  
Serial.write('S');
Serial.write(rmspeed);
//
Serial.write('A');
Serial.write(startflag);

Serial.write('N');
Serial.write(nam);

//Serial.write(',');
Serial.write('T');

//Looking under the hood 
//Serial.println("Somebody has connected :)");

String request = client.readStringUntil('\r');
//Looking under the hood 

if (request.indexOf("/OFF") != -1){ 
digitalWrite(LED_PIN, HIGH);
}
else if (request.indexOf("/ON") != -1){ 
digitalWrite(LED_PIN, LOW); 
}
  //reduce delay, increase speed
else if (request.indexOf("/UP") != -1){ 
rmspeed = rmspeed - 10;
delaytimerforservo = delaytimerforservo - 2;
}
  // increase delay, reduce speed
else if (request.indexOf("/DO") != -1){ 
rmspeed = rmspeed + 10;
delaytimerforservo = delaytimerforservo + 2;
}
  // stop servo
else if (request.indexOf("/SS") != -1){ 
startflag = 0;
}
  // start servo
else if (request.indexOf("/PL") != -1){ 
startflag = 1;
}
  // name of song
else if (request.indexOf("/BD") != -1){ 
nam = 1;
}
  // name of song
else if (request.indexOf("/SW") != -1){ 
nam = 2;
}

//Serve the HTML document to the browser.


// Prepare the HTML document to respond and add buttons:
String s = "HTTP/1.1 200 OK\r\n";
String ss = "hi\n";
  //This is for web interface design
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

