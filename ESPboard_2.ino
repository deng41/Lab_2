#define trigPin 4
#define echoPin 16
#define infredPin 5
int preLevel, preInfred;
void setup() {              //initialize
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(infredPin, INPUT);
  preLevel = 0;
  preInfred = 1;
}

void loop() {
  int infredoff, level;
  long duration, distance;
  digitalWrite(trigPin, LOW); //set trigger signal for distance sensor  
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);

  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW); //check echo signal to get the duration in microsecond
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2)/29.1; //convert duration to distance in cm



infredoff=digitalRead(infredPin); //check infrared signal
level = distance / 10; //map the distance to different levels
if(level > 7)
{
  level = 7;
}

level=level+48; //convert integer to ASCII
infredoff=infredoff+48;

//Send signal to UART only if the sensor signals change
if((level != preLevel) || (infredoff != preInfred))
{
  Serial.write('S'); //preamble for the signal
  Serial.write('D');
  Serial.write(level);
  Serial.write('A');
  Serial.write(infredoff);
}
preLevel = level;
preInfred = infredoff;
delay(500);
}
