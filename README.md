## A simple implementaion of SPI protocol of ESP32 using a shift register 74HC595, the serial data output pin Q7S can be used to connect with another shift register.
The 74HC595 is an high speed CMOS device. An eight bit shift register accpets data from the serial input (DS) on each positive transition of the shift register clock (SHCP). When asserted low the reset function ( ) sets all shift register values to zero and is indepent of all clocks.

```
├── CMakeLists.txt
├── main
│   ├── CMakeLists.txt
│   └── main.c
└── README.md                  
```
