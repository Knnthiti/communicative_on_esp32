struct Data {
  int8_t Values_1[4];
  int8_t Values_2[4];
}message;

long TIME = 0;

void setup() {
  Serial.begin(115200, SERIAL_8N1, SOC_RX0, SOC_TX0);
}

void loop() {
  if ((millis() - TIME) > 10) {
    for (uint8_t i = 0; i < 4; i++) {
      message.Values_1[i] = 100;
      message.Values_2[i] = random(-128, 127);
    }

    Serial.write((uint8_t *)&message, sizeof(message));

    TIME = millis();
  }
}
