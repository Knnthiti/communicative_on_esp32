// รวมไลบรารี Wire เพื่อใช้โปรโตคอล I2C
#include <Wire.h>

// กำหนดที่อยู่ของ Slave
#define SLAVE_ADDR 9

// กำหนดขนาดของข้อความตอบกลับที่ต้องการอ่านจาก Slave
#define ANSWERSIZE 13

// กำหนดโครงสร้างข้อมูล (Struct) สำหรับเก็บค่าที่ต้องการส่งไปยัง Slave
struct Data {
  int8_t Values_1[4];  // เก็บค่า 4 ตัวในรูปแบบ signed 8-bit (int8_t)
  int8_t Values_2[4];  // เก็บค่า 4 ตัวในรูปแบบ signed 8-bit (int8_t)
} message;  // สร้างตัวแปร message จาก struct Data

void setup() {
  Wire.begin();        // เริ่มต้นใช้งาน I2C เป็น Master
  Serial.begin(115200);  // เริ่มต้นใช้งาน Serial ที่ความเร็ว 115200 baud
  Serial.println("I2C Master Demonstration"); // แสดงข้อความบน Serial Monitor
}

void loop() {
  delay(10);  // หน่วงเวลา 10ms เพื่อลดการส่งข้อมูลถี่เกินไป

  // ตั้งค่าข้อมูลสำหรับส่งไปยัง Slave
  for (uint8_t i = 0; i < 4; i++) {
    message.Values_1[i] = 100;              // ค่าใน Values_1 ถูกตั้งให้เป็น 100 ตลอด
    message.Values_2[i] = random(-128, 127); // ค่าใน Values_2 เป็นค่าแบบสุ่มในช่วง -128 ถึง 127
  }

  // เริ่มต้นส่งข้อมูลไปยัง Slave
  Wire.beginTransmission(SLAVE_ADDR);                  // เริ่มต้นการสื่อสารกับอุปกรณ์ที่อยู่ 9
  Wire.write((byte *)&message, sizeof(message));       // ส่งข้อมูลทั้งหมดใน struct message
  Wire.endTransmission();                              // จบการส่งข้อมูล

  // ขอรับข้อมูลตอบกลับจาก Slave
  Wire.requestFrom(SLAVE_ADDR, ANSWERSIZE);  // ขอรับข้อมูลจาก Slave เป็นจำนวน ANSWERSIZE ไบต์

  // อ่านข้อมูลจาก Slave และนำมาเก็บเป็น String
  String response = "";  // ตัวแปรสำหรับเก็บข้อความที่ได้รับ
  while (Wire.available() > 0) {  // ตรวจสอบว่ามีข้อมูลให้อ่านหรือไม่
    char b = Wire.read();  // อ่านข้อมูลทีละตัวอักษร
    response += b;         // นำตัวอักษรที่อ่านได้มาต่อกันเป็น String
  }

  // แสดงข้อความที่ได้รับจาก Slave บน Serial Monitor
  Serial.println(response);
}

