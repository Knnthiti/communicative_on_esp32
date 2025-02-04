// สร้างโครงสร้างข้อมูล (struct) สำหรับเก็บค่าข้อมูลที่ต้องการส่งผ่าน Serial
struct Data {
  int8_t Values_1[4];  // Array 4 ตัว เก็บค่าคงที่ 100
  int8_t Values_2[4];  // Array 4 ตัว เก็บค่าตัวเลขสุ่มระหว่าง -128 ถึง 127
} message;  // สร้างตัวแปร message จาก struct Data

long TIME = 0;  // ตัวแปรเก็บเวลาสำหรับควบคุมการส่งข้อมูล

void setup() {
  // เริ่มต้นใช้งาน Serial (UART) ที่ความเร็ว 115200 baud
  // พร้อมตั้งค่าขา RX และ TX ของ ESP32
  Serial.begin(115200, SERIAL_8N1, SOC_RX0, SOC_TX0);
}

void loop() {
  // เช็คว่าผ่านไปอย่างน้อย 10 มิลลิวินาทีแล้วหรือยัง
  if ((millis() - TIME) > 10) {
    // กำหนดค่าให้กับ message.Values_1 และ message.Values_2
    for (uint8_t i = 0; i < 4; i++) {
      message.Values_1[i] = 100;  // กำหนดให้ทุกค่าของ Values_1 เป็น 100
      message.Values_2[i] = random(-128, 127);  // กำหนดให้ Values_2 เป็นค่าที่สุ่มระหว่าง -128 ถึง 127
    }

    // ส่งข้อมูลโครงสร้าง message ผ่าน Serial เป็น byte array
    Serial.write((uint8_t *)&message, sizeof(message));

    // อัปเดตค่าเวลา TIME เป็นค่าปัจจุบัน
    TIME = millis();
  }
}
