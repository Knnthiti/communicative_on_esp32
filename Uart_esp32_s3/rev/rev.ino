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

#define Rx2 5
#define Tx2 15
#define UART_NUM UART_NUM_2
#define BUF_SIZE 256

void setup() {
  Serial.begin(115200);

  // ติดตั้ง UART2
  uart_driver_install(UART_NUM, BUF_SIZE, BUF_SIZE, 0, NULL, 0);

  // กำหนดขา TX RX
  uart_set_pin(UART_NUM, Tx2, Rx2, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);

  // ตั้งค่า Baudrate
  uart_set_baudrate(UART_NUM, 115200);
}

void loop() {
  // อ่านข้อมูลขนาดเท่ากับโครงสร้าง message
  int len = uart_read_bytes(UART_NUM, (uint8_t *)&data, sizeof(data), 1000 / portTICK_PERIOD_MS);

  if (len == sizeof(data)) {
    Serial.print("LX: ");
    Serial.print(data.stickValue[0]);
    Serial.print(" | LY: ");
    Serial.print(data.stickValue[1]);
    Serial.print(" | RX: ");
    Serial.print(data.stickValue[2]);
    Serial.print(" | RY: ");
    Serial.print(data.stickValue[3]);
    Serial.print(" ||| ");
    Serial.print(data.moveBtnBit.move1);
    Serial.print(" | ");
    Serial.print(data.moveBtnBit.move2);
    Serial.print(" | ");
    Serial.print(data.moveBtnBit.move3);
    Serial.print(" | ");
    Serial.print(data.moveBtnBit.move4);
    Serial.print(" | ");
    Serial.print(data.moveBtnBit.set1);
    Serial.print(" | ");
    Serial.println(data.moveBtnBit.set2);
  }

  // delay(10);
}