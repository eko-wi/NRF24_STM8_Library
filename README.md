NRF24L01 + STM8 Compatible C Library (Linux, Windows)
=====================================
Want to use NRF24L01 with those STM8S103F3P6 breakout boards in Arduino IDE? But the compiler, SDCC, doesn't support RF24 library because it is in C++... So here is a C-only library for achieving mostly the same functions. Currently only tested with mentioned MCU and breakout board. Can communicate with RF24 libraries in other environments like AVR based Arduino and ESP8266.  
This was ported from the mirf library in [NRF24_STM8_Library by Nicogutz](https://github.com/nicogutz/NRF24_STM8_Library), which is a port in itself. This only works with the STM8 sduino core in Arduino IDE.

Documentation
=============
Documentation at https://nicogutz.github.io/NRF24_STM8_Library

Usage
=====
Download the whole repo, extract, then put in 'libraries' folder in Arduino storage directory.  
In the code:  
Have a global bool variable (PTX in the function parameters) to store the status for communication among functions, due to lack of an OOP container.

Available functions
===================
`void Nrf24_init(GPIO_TypeDef *CEPORT, GPIO_Pin_TypeDef CENUMBER, GPIO_TypeDef *CSNPORT, GPIO_Pin_TypeDef CSNNUMBER);`  
Initial setup. For the port, use GPIOB, GPIOC, or GPIOD. For the pin, use GPIO_PIN_x.

`void Nrf24_config(bool *PTX);`  
Set several config registers.

`ErrorStatus Nrf24_setRADDR(uint8_t *adr);`  
`ErrorStatus Nrf24_setTADDR(uint8_t *adr);`  
Set receiving and transmitting addresses. The parameters should be uint8_t arrays with length 5.

`void Nrf24_addRADDR(uint8_t pipe, uint8_t adr);`  
Set more receiving addresses. The address must only differ by one byte (in the first / last position? - not tested yet).

`bool Nrf24_dataReady();`  
Check if there is data ready to be read.

`uint8_t Nrf24_getDataPipe();`  
Get which pipe number receives data.

`bool Nrf24_isSend(int timeout, bool *PTX);`  
Return true if data is sent successfully.

`bool Nrf24_isSending(bool *PTX);`  
Return true if data is still being transmitted.

`void Nrf24_send(uint8_t *value, bool *PTX);`  
Send some data.

`bool Nrf24_rxFifoEmpty();`  
`bool Nrf24_txFifoEmpty();`  
(I did not tried those yet)

`void Nrf24_getData(uint8_t *data);`  
Receive data and put in in the specified buffer.

`uint8_t Nrf24_getStatus();`  
Read the status register.

`void Nrf24_setChannel(uint8_t ch);`  
Set radio channel from 0 to 125.

`void Nrf24_setCRC(bool useCRC, bool use2byte);`  
Set whether to use CRC, and whether to use 1 byte or 2 bytes.

`void Nrf24_configRegister(uint8_t reg, uint8_t value);`  
Write single register.

`void Nrf24_readRegister(uint8_t reg, uint8_t *value, uint8_t len);`  
`void Nrf24_writeRegister(uint8_t reg, uint8_t *value, uint8_t len);`  
Read or write consecutive registers starting from an address.

`void Nrf24_powerUpRx(bool *PTX);`  
Get ready for receiving.

`void Nrf24_powerUpTx(bool *PTX);`  
Get ready for transmitting.

`void Nrf24_powerDown();`  
Power down, to save energy.

`void Nrf24_SetOutputRF_PWR(uint8_t val);`  
Set radio power output level. Use `RF24_PA_MIN`, `RF24_PA_LOW`, `RF24_PA_HIGH`, or `RF24_PA_MAX`.

`void Nrf24_SetSpeedDataRates(uint8_t val);`  
Set bit rate. Must be same among transmitter and receivers. Use `RF24_250KBPS`, `RF24_1MBPS`, or `RF24_2MBPS`.

`void Nrf24_setRetransmitDelay(uint8_t val);`  
Set retransmit delay, for use when transmission failure.

`void Nrf24_ceHi();`  
`void Nrf24_ceLow();`  
Used internally for communicating with the NRF.

`void Nrf24_flushRx();`  
Clear receive buffer in the NRF.

