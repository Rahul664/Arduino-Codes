const int IN1 = 2;
const int IN2 = 3;
const int EN1 = 9;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(EN1, OUTPUT);
  
  // Change IN1, IN2 to set the direction of the coil
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
}

void loop() {
  digitalWrite(EN1, HIGH); // Turn ON inductor
  delay(20);                // 20 ms ON
  digitalWrite(EN1, LOW);  // Turn OFF inductor
  delay(20);                // 20 ms OFF
}