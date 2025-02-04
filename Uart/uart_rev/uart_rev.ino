//https://www.artronshop.co.th/article/122/how-to-use-serial1-serial2-on-esp32


// กำหนดโครงสร้างข้อมูล (Struct) สำหรับเก็บค่าที่ได้รับผ่าน Serial2
struct Data {
  int8_t Values_1[4];  // เก็บค่า 4 ตัว (signed 8-bit) สำหรับข้อมูลชุดที่ 1
  int8_t Values_2[4];  // เก็บค่า 4 ตัว (signed 8-bit) สำหรับข้อมูลชุดที่ 2
} Buffer;  // สร้างตัวแปร Buffer จาก struct Data

// กำหนดขา RX และ TX สำหรับ Serial2 บน ESP32
#define Rx2 16  // ขารับข้อมูล (RX2) ใช้ขา GPIO16
#define Tx2 17  // ขาส่งข้อมูล (TX2) ใช้ขา GPIO17

void setup() {
  Serial.begin(115200);  // เริ่มต้นใช้งาน Serial Monitor ที่ความเร็ว 115200 baud
  Serial2.begin(115200, SERIAL_8N1, Rx2, Tx2);  // ตั้งค่า Serial2 ที่ความเร็ว 115200 baud, 8N1 (8-bit, No parity, 1 stop bit)
}

void loop() {
  // ตรวจสอบว่ามีข้อมูลเข้ามาทาง Serial2 หรือไม่
  if (Serial2.available()) {
    // อ่านข้อมูลที่เข้ามา และเก็บในตัวแปร Buffer
    Serial2.readBytes((uint8_t *)&Buffer, sizeof(Buffer));

    // แสดงค่าข้อมูลที่ได้รับจาก Serial2 บน Serial Monitor
    Serial.print("Data : ");

    // วนลูปพิมพ์ค่าของ Values_1 (4 ตัว)
    for (uint8_t i = 0; i < 4; i++) {
      Serial.print(Buffer.Values_1[i]);  // พิมพ์ค่าทีละตัว
      Serial.print(",");  // คั่นค่าด้วย ","
    }

    Serial.print(" | ");  // คั่นระหว่าง Values_1 และ Values_2

    // วนลูปพิมพ์ค่าของ Values_2 (4 ตัว)
    for (uint8_t i = 0; i < 4; i++) {
      Serial.print(Buffer.Values_2[i]);  // พิมพ์ค่าทีละตัว
      Serial.print(",");  // คั่นค่าด้วย ","
    }

    Serial.println(" ");  // ขึ้นบรรทัดใหม่ใน Serial Monitor
    
    delay(10);  // หน่วงเวลา 10ms เพื่อให้การรับส่งข้อมูลเสถียร
  }
}
