// นำเข้าไลบรารี Wire.h เพื่อใช้งาน I2C
#include "Wire.h"

// กำหนดที่อยู่ของอุปกรณ์ I2C (Slave Address)
#define I2C_DEV_ADDR 9

// กำหนดโครงสร้างข้อมูล (Struct) สำหรับเก็บค่าที่ได้รับจาก Master
struct Data {
  int8_t Values_1[4];  // เก็บค่า 4 ตัว (signed 8-bit) สำหรับข้อมูลชุดที่ 1
  int8_t Values_2[4];  // เก็บค่า 4 ตัว (signed 8-bit) สำหรับข้อมูลชุดที่ 2
} Buffer;  // สร้างตัวแปร Buffer จาก struct Data

// ฟังก์ชันที่ทำงานเมื่อ Master ขอข้อมูล (Request)
void onRequest() {
  Wire.write("Yes my master");  // ส่งข้อความกลับไปยัง Master
}

// ฟังก์ชันที่ทำงานเมื่อ Master ส่งข้อมูลมาให้ (Receive)
void onReceive(int len) {
  while (Wire.available()) {  // ตรวจสอบว่ามีข้อมูลเข้ามาหรือไม่
    Wire.readBytes((uint8_t *)&Buffer, sizeof(Buffer));  // อ่านข้อมูลจาก Master และเก็บใน Buffer

    // แสดงข้อมูลที่ได้รับจาก Master บน Serial Monitor
    Serial.print("Data : ");
    for (uint8_t i = 0; i < 4; i++) {  // วนลูปพิมพ์ค่าจาก Values_1
      Serial.print(Buffer.Values_1[i]);
      Serial.print(",");
    }

    Serial.print(" | ");  // คั่นข้อมูล Values_1 และ Values_2

    for (uint8_t i = 0; i < 4; i++) {  // วนลูปพิมพ์ค่าจาก Values_2
      Serial.print(Buffer.Values_2[i]);
      Serial.print(",");
    }
    Serial.println(" ");  // ขึ้นบรรทัดใหม่ใน Serial Monitor

    delay(10);  // หน่วงเวลา 10ms เพื่อป้องกันการอ่านข้อมูลเร็วเกินไป
  }
}

// ฟังก์ชัน setup() ใช้สำหรับตั้งค่าการทำงานเบื้องต้น
void setup() {
  Serial.begin(115200);  // เริ่มต้นใช้งาน Serial ที่ความเร็ว 115200 baud
  Serial.setDebugOutput(true);  // เปิดใช้งานโหมด Debug สำหรับการตรวจสอบข้อผิดพลาด

  Wire.onReceive(onReceive);  // กำหนดให้ฟังก์ชัน onReceive() ทำงานเมื่อมีข้อมูลจาก Master
  Wire.onRequest(onRequest);  // กำหนดให้ฟังก์ชัน onRequest() ทำงานเมื่อ Master ขอข้อมูล

  Wire.begin((uint8_t)I2C_DEV_ADDR);  // เริ่มต้นใช้งาน I2C ในโหมด Slave ที่ Address 9
}

// ฟังก์ชัน loop() ไม่มีการทำงานเพิ่มเติม เนื่องจาก I2C ใช้ Interrupt-Driven
void loop() {
}
