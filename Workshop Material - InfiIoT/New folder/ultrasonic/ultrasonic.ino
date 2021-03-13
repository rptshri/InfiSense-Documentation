const int trig = 9;
const int eco = 10;
void setup() {
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(eco, INPUT);
}

void loop(){
  long distance, duration;
  digitalWrite(trig, LOW);
  delayMicroseconds(2);//clears trig pin
  int i=10;
  while(i-->0) {
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);  
  }
  duration = pulseIn(eco, HIGH);
  Serial.print("duration()");
  Serial.println(duration);
  distance = duration*0.017;
  Serial.print("distance(cms): ");
  Serial.println(distance);
  delay(1000);
}

