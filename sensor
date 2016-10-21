#define trigPin 4
#define echoPin 16
#define infredPin 5
int preLevel, preInfred;
void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(infredPin, INPUT);
  preLevel = 0;
  preInfred = 1;
//  pinMode(led, OUTPUT);
//  pinMode(led2, OUTPUT);
}

void loop() {
  int infredoff, level;
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2)/29.1;
//  if (distance < 4) {  // This is where the LED On/Off happens
//    digitalWrite(led,HIGH); // When the Red condition is met, the Green LED should turn off
//  digitalWrite(led2,LOW);
//}
//  else {
//    digitalWrite(led,LOW);
//    digitalWrite(led2,HIGH);
//  }
//  if (distance >= 200 || distance <= 0){
//    Serial.println("Out of range");
//  }
//  else {
//    Serial.print(distance);
//    Serial.println(" cm");
//  }

//Serial.println(distance);
//Serial.println("dis");
infredoff=digitalRead(infredPin);
level = distance / 10;
if(level > 7)
{
  level = 7;
}
//Serial.println("level");
//Serial.println(level);
//Serial.println("infredoff");
//Serial.println(infredoff);
level=level+48;
infredoff=infredoff+48;

if((level != preLevel) || (infredoff != preInfred))
{
  Serial.write('S');
  Serial.write('D');
  Serial.write(level);
  Serial.write('A');
  Serial.write(infredoff);
  //Serial.println(infredoff);
}
preLevel = level;
preInfred = infredoff;
delay(500);
}
