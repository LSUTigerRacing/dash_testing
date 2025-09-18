
#include <WiFi.h>
#include <WiFiAP.h>

// Set these to your desired credentials.
const char *ssid = "Free Wifi";
const char *password = "RacingTiger";

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(512000);

  // You can remove the password parameter if you want the AP to be open.
  // a valid password must have more than 7 characters
  if (!WiFi.softAP(ssid, password)) {
    log_e("Soft AP creation failed.");
    while (1);
  }
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  Serial.println("Server started");
}

void loop() {
  
}
