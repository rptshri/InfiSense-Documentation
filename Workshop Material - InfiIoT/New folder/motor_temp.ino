const int dp = 8;
const int temp = A0;
float tempc, hold;
void setup() {
  pinMode(dp, OUTPUT);
  pinMode(temp, INPUT);
  Serial.begin(9600);
}
void loop() {
  hold = analogRead(temp);
  hold = hold/9.31;
  tempc = hold;
  tempLed(tempc);
  Serial.print(tempc);
  Serial.println();
  analogReference(INTERNAL);
}

void tempLed(float temp) {
  if(temp <32){
    digitalWrite(dp, HIGH); 
  }
  else if(temp>32) {
        digitalWrite(dp, HIGH); 
        delay(50);
        digitalWrite(dp, LOW);
        delay(50);
  }  
}
