#include <Arduino.h>
// Espressif version of CAN
#include <driver/twai.h>

void setup() {
 Serial.begin(115200);
 twai_general_config_t genConfig = TWAI_GENERAL_CONFIG_DEFAULT(GPIO_NUM_5,GPIO_NUM_4,TWAI_MODE_NORMAL);
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
  txMessage.data_length_code = 1;
  txMessage.data[0] = 0x111; // Dummy Data
  txMessage.flags = TWAI_MSG_FLAG_EXTD;
esp_err_t result = twai_receive(&rxMessage, pdMS_TO_TICKS(100));

if (result == ESP_OK) {
    Serial.println(txMessage.data[0]);
  } else if (result == ESP_ERR_TIMEOUT) {
    Serial.println("No message received.");
  } else {
    Serial.println("Receive error!");
  }
}