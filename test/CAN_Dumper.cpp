#include <Arduino.h>
// Espressif version of CAN
#include "driver/twai.h"
#include "hal/twai_types.h"
#include "hal/twai_ll.h"
#include "hal/twai_hal.h"

void setup() {
 Serial.begin(115200);
 twai_general_config_t genConfig = TWAI_GENERAL_CONFIG_DEFAULT(GPIO_NUM_5,GPIO_NUM_4,TWAI_MODE_NO_ACK);
 twai_timing_config_t timingConfig = TWAI_TIMING_CONFIG_500KBITS();
 twai_filter_config_t filterConfig = TWAI_FILTER_CONFIG_ACCEPT_ALL(); //single filter 

 if(twai_driver_install(&genConfig,&timingConfig,&filterConfig) == ESP_OK){
  Serial.println("TWAI driver installed");
 }
 if(twai_start() == ESP_OK){
  Serial.println("TWAI Driver started");
 }
 
}

void loop() {
  twai_message_t rxMessage;
  twai_message_t txMessage;
  txMessage.identifier = 0x256; //Dummy CAN ID
  txMessage.data_length_code = 8;
  txMessage.data[0] = 0x11; // Dummy Data
  txMessage.data[1] =  0x22;
  txMessage.data[2] =  0x21;
  txMessage.data[3] =  0x23;
  txMessage.data[4] =  0x22;
  txMessage.data[5] =  0x24;
  txMessage.data[6] =  0x27;
  txMessage.data[7] =  0x20;
  txMessage.flags = TWAI_MSG_FLAG_EXTD;
  esp_err_t result = twai_transmit(&rxMessage, pdMS_TO_TICKS(100));
  if(result == ESP_OK){
    printf("Message queued for transmission");
  }
  else{
    printf("Error while adding message to queue");
  }
  
}