#include "driver/uart.h"

struct Data {
  int8_t Values_1[4];
  int8_t Values_2[4];
} message;

#define Rx2 16
#define Tx2 17
#define UART_NUM UART_NUM_2
#define BUF_SIZE 1024

void setup() {
  Serial.begin(115200);

  // ติดตั้ง UART2
  uart_driver_install(UART_NUM, BUF_SIZE, 0, 0, NULL, 0);

  // กำหนดขา TX RX
  uart_set_pin(UART_NUM, Tx2, Rx2, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);

  // ตั้งค่า Baudrate
  uart_set_baudrate(UART_NUM, 115200);
}

void loop() {
  // อ่านข้อมูลขนาดเท่ากับโครงสร้าง message
  int len = uart_read_bytes(UART_NUM, (uint8_t *)&message, sizeof(message), 1000 / portTICK_PERIOD_MS);

  if (len == sizeof(message)) {
    Serial.print("Data : ");
    for (uint8_t i = 0; i < 4; i++) {
      Serial.print(message.Values_1[i]);
      Serial.print(",");
    }

    Serial.print(" | ");

    for (uint8_t i = 0; i < 4; i++) {
      Serial.print(message.Values_2[i]);
      Serial.print(",");
    }

    Serial.println(" ");
  }

  delay(10);
}