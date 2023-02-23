#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
// Structure example to send data
// Must match the receiver structure
typedef struct struct_message
{
  int a;
} struct_message;
// Create a struct_message called myData
struct_message myDataRec;
// callback function that will be executed when data is received
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
{
  memcpy(&myDataRec, incomingData, sizeof(myDataRec));
  Serial.println(myDataRec.a);
}
void setup()
{
  // Init Serial Monitor
  Serial.begin(9600);
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  // Init ESP-NOW
  if (esp_now_init() != ESP_OK)
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  // Once ESPNow is successfully Init, we will register for recv CB to get recv packer info
  esp_now_register_recv_cb(OnDataRecv);
}
void loop()
{
}
