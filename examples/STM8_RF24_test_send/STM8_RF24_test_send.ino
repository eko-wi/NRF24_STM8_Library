/*
   Test NRF24L01 with the stm8s103f3p6 breakout board
   CE on port D1, CSN on port C3
   Use sduino core in Arduino IDE
*/
#include <RF24_c.h>
bool PTX = TRUE;
uint8_t rxaddr[] = "aaaaa";
uint8_t txaddr[] = "bbbbb";
uint8_t rxbuf[32];
uint8_t txbuf[32];
uint8_t channel = 114;

long t = 0, tlasttransmit = 0;
int count = 0;

void ledon() {
  GPIOB->ODR &= ~(1 << 5);
}

void ledoff() {
  GPIOB->ODR |= (1 << 5);
}

void itoa(char* buf, int x) {
  static char tbuf[8];
  uint8_t i = 0;
  do {
    tbuf[i] = (x % 10) + '0';
    x /= 10;
    i++;
  } while (x > 0);
  while (i > 0) {
    i--;
    *buf = tbuf[i];
    buf++;
  }
}

void setup() {
  GPIOB->DDR = 1 << 5;
  ledon(); //blink the onboard LEDs to mark start of program
  delay(100);
  ledoff();
  delay(200);
  ledon();
  delay(100);
  ledoff();
  delay(200);
  Nrf24_init(GPIOD, GPIO_PIN_1, GPIOC, GPIO_PIN_3); //CE, CSN
  Nrf24_config(&PTX);
  Nrf24_setChannel(channel);
  Nrf24_setCRC(1,1);                               //arg 1: use CRC, arg 2: use 2 byte
  Nrf24_SetOutputRF_PWR(RF24_PA_MAX);              //options: MIN, LOW, HIGH, MAX
  Nrf24_SetSpeedDataRates(RF24_250KBPS);           //options: 1MBPS, 2MBPS, 250KBPS
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
  ledoff();
  delay(1000);
}

void loop() {
  t = millis();

  if (Nrf24_dataReady()) {
    Nrf24_getData(rxbuf);
    //do nothing with this, for now
  }

  if (t - tlasttransmit > 1000) {
    tlasttransmit = t;
    ledon();
    itoa(txbuf, ++count);
    //Nrf24_powerUpTx(&PTX); // no need for this, since _powerUpTx is called inside _send
    Nrf24_send(txbuf, &PTX);
    while (Nrf24_isSending(&PTX)) {
      delay(1);
    }
    Nrf24_powerUpRx(&PTX);
    delay(10);
    ledoff();
  }
}
