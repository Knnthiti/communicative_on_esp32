#include "driver/uart.h"

struct Data {
  int8_t Values_1[4];
  int8_t Values_2[4];
} message;

long TIME = 0;

#define UART_PORT UART_NUM_1  // ใช้ UART1
#define TXD_PIN 12
#define RXD_PIN 13
#define BUF_SIZE 1024

void setup() {
  // หากต้องการ Debug ผ่าน Serial Monitor
  Serial.begin(115200);
  Serial.println("UART1 Sender Start");

  // ติดตั้ง UART driver
  uart_driver_install(UART_PORT, BUF_SIZE, 0, 0, NULL, 0);

  // ตั้งค่าขา TX, RX สำหรับ UART1
  uart_set_pin(UART_PORT, TXD_PIN, RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);

  // ตั้งค่า Baudrate
  uart_set_baudrate(UART_PORT, 115200);
}

void loop() {
  if ((millis() - TIME) > 100) {
    for (uint8_t i = 0; i < 4; i++) {
      message.Values_1[i] = 50;
      message.Values_2[i] = random(-128, 127);
    }

    // ส่งข้อมูลผ่าน UART1
    uart_write_bytes(UART_PORT, (uint8_t *)&message, sizeof(message));

    Serial.println("Send via UART1");  // debug log

    TIME = millis();
  }
}