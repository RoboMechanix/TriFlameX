#define ledPin 2

void blink_led(unsigned int times, unsigned int duration) {
    for (unsigned int i = 0; i < times; i++) {
        digitalWrite(ledPin, HIGH);
        delay(duration);
        digitalWrite(ledPin, LOW);
        delay(200);
    }
}

void setup_led() {
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW); 
}