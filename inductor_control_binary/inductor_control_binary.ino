#define EN 9  // Enable pin for L293D
#define IN1 2 // Input pin 1
#define IN2 3 // Input pin 2

// binary sequence input
int sequence[] = {1, 1, 1, 1, 1, 1, 1, 1, 1,0, 0, 0, 0, 0, 0, 0, 1, 1}; 
int sequenceLength = sizeof(sequence) / sizeof(sequence[0]);

void setup() {
    pinMode(EN, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    digitalWrite(EN, HIGH); 
}

void loop() {
    for (int i = 0; i < sequenceLength; i++) {
        if (sequence[i] == 1) {
            // Turn ON coil
            digitalWrite(IN1, HIGH);
            digitalWrite(IN2, LOW);
        } else {
            // Turn OFF coil
            digitalWrite(IN1, LOW);
            digitalWrite(IN2, LOW);
        }
        delay(20); // interval
    }
}
