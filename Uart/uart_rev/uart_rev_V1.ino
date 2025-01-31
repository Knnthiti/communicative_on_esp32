//https://www.artronshop.co.th/article/122/how-to-use-serial1-serial2-on-esp32

struct Data {
  int8_t Values_1[4];
  int8_t Values_2[4];
}Buffer;

#define Rx2 16
#define Tx2 17

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, Rx2, Tx2);
}

void loop() {
  if (Serial2.available()) {
    Serial2.readBytes((uint8_t *)&Buffer, sizeof(Buffer));

    Serial.print("Data : ");
    for(uint8_t i = 0; i < 4;i++){
      Serial.print(Buffer.Values_1[i]);
      Serial.print(",");
    }
    
    Serial.print(" | ");

    for(uint8_t i = 0; i < 4;i++){
      Serial.print(Buffer.Values_2[i]);
      Serial.print(",");
    }
    Serial.println(" ");
    
    delay(10);
  }
}