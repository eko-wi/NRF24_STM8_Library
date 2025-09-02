/*
   Test NRF24L01 with stm8s103f3p6 breakout board
   CE on port C4, CSN on port C3
   Use sduino core in Arduino IDE
   Expected output: the onboard LED (port B5, active low) will blink as any data is received.
*/
#include <RF24_c.h>
bool PTX = TRUE;
uint8_t rxaddr[] = "bbbbb";
uint8_t txaddr[] = "aaaaa";
uint8_t rxbuf[32];
uint8_t txbuf[32]; //not used here
uint8_t channel = 114;

void ledon() {
  GPIOB->ODR &= ~(1 << 5);
}

void ledoff() {
  GPIOB->ODR |= (1 << 5);
}

void setup() {
  GPIOB->DDR = 1 << 5;
  ledon(); //blink the onboard LED to mark start of program
  delay(100);
  ledoff();
  delay(200);
  ledon();
  delay(100);
  ledoff();
  delay(200);
  Nrf24_init(GPIOC, GPIO_PIN_4, GPIOC, GPIO_PIN_3); //CE, CSN
  Nrf24_config(&PTX);
  Nrf24_setChannel(channel);
  Nrf24_setCRC(1, 1);                     //arg 1: use CRC, arg 2: use 2 byte
  Nrf24_SetOutputRF_PWR(RF24_PA_LOW);     //options: MIN, LOW, HIGH, MAX
  Nrf24_SetSpeedDataRates(RF24_250KBPS);  //options: 1MBPS, 2MBPS, 250KBPS
  Nrf24_setRetransmitDelay(1);
  if (Nrf24_setRADDR(rxaddr) == ERROR) {
    ledon();
    delay(50);
    ledoff();
    delay(100);
  }
  if (Nrf24_setTADDR(txaddr) == ERROR) {
    ledon();
    delay(50);
    ledoff();
    delay(100);
  }
  Nrf24_powerUpRx(&PTX);
}

void loop() {
  if (Nrf24_dataReady()) {
    ledon();
    Nrf24_getData(rxbuf);
    delay(5);
    Nrf24_flushRx();
    //send back something here maybe
    ledoff();
  }
}
