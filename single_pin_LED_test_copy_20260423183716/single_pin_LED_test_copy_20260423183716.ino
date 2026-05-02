    void setup() {
      pinMode(11, OUTPUT); // MOSI

    }

    void loop() {
      digitalWrite(11, HIGH); // Set MOSI high
      delay(1000); // Wait 1 second

      digitalWrite(11, LOW); // Set MOSI low
      delay(1000); // Wait 1 second
    }

