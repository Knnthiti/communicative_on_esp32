#include "driver/uart.h"

typedef struct __attribute__((packed)) {
  uint8_t Header[2];

  union {
    uint8_t moveBtnByte;
    struct {
      uint8_t move1 : 1;
      uint8_t move2 : 1;
      uint8_t move3 : 1;
      uint8_t move4 : 1;
      uint8_t res1 : 2;
      uint8_t set1 : 1;
      uint8_t set2 : 1;
    } moveBtnBit;
  };

  union {
    uint8_t attackBtnByte;
    struct {
      uint8_t attack1 : 1;
      uint8_t attack2 : 1;
      uint8_t attack3 : 1;
      uint8_t attack4 : 1;
      uint8_t res1 : 4;
    } attackBtnBit;
  };

  int8_t stickValue[4];  //joyL_X,joyL_Y ,joyR_X,joyR_Y

} ControllerData;

ControllerData data;


long TIME = 0;

#define UART_PORT UART_NUM_2  // ใช้ UART1
#define TXD_PIN 5
#define RXD_PIN 15
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
    data.moveBtnBit.move1 = 1;
    data.moveBtnBit.move3 = 1;

    data.stickValue[0] = random(-128,127);
    data.stickValue[2] = random(-128,127);

    // ส่งข้อมูลผ่าน UART1
    uart_write_bytes(UART_PORT, (uint8_t *)&data, sizeof(data));

    Serial.println("Send via UART1");  // debug log

    TIME = millis();
  }
}