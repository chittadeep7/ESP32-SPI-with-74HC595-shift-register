#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/spi_master.h"
#include "driver/gpio.h"

#define MISO GPIO_NUM_19
#define MOSI GPIO_NUM_23         
#define CLK  GPIO_NUM_18            
#define CS   GPIO_NUM_5
#define LATCH GPIO_NUM_27

spi_device_handle_t spi;

//spi comfiguration
void spi_init(void)
{
  spi_bus_config_t buscfg = {                                  
    .miso_io_num = MISO,
    .mosi_io_num = MOSI,
    .sclk_io_num = CLK,
    .quadwp_io_num = -1,
    .quadhd_io_num = -1,
    .max_transfer_sz = 512 * 8                                     
  };

  spi_device_interface_config_t devcfg = {
    .clock_speed_hz = 1 * 1000 * 1000,       //1MHz       
    .mode = 0,                               //spi mode 0
    .spics_io_num = CS,                           
    .queue_size = 7                                         
  };

  spi_bus_initialize(VSPI_HOST, &buscfg, SPI_DMA_CH_AUTO);

  spi_bus_add_device(VSPI_HOST, &devcfg, &spi);
}


void app_main(void)
{
  gpio_set_direction(LATCH, GPIO_MODE_OUTPUT);
  spi_init();
   gpio_set_level(LATCH, 0);                  //latch STCP low until all data is transmitted
    spi_transaction_t tx = {
      .flags = SPI_TRANS_USE_TXDATA, 
      .tx_buffer = 0b10010111,                //transmit the binary data to shift register                
      .length = 8};
      
    spi_device_polling_transmit(spi, &tx);
    gpio_set_level(LATCH, 1);                  //STCP high data is availabe at Q0- Q7
}                                              //use serial data output pin Q7S to connect to another shift register