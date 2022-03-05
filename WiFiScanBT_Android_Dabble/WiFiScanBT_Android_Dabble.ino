
#include <WiFi.h>
#include <DabbleESP32.h>
#include <BluetoothSerial.h>






#define CUSTOM_SETTINGS
#define INCLUDE_NOTIFICATION_MODULE
#define NOTIFICATION_SETTINGS

BluetoothSerial SerialBT;

void setup() {

    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
//  delay(100);

  SerialBT.begin();                            //start bluetooth serial port
  Dabble.begin("MyEsp32");                     //set bluetooth name of the device
  Dabble.waitForAppConnection();               //waiting for App to connect
 // Notification.clear();                      //clear previous notifictions
  Notification.setTitle("Vulnerable Network Finder");      // title of phone's push notification
}

void loop() {

    int n = WiFi.scanNetworks();
    int i;
    if (WiFi.encryptionType(i) == 1){
        Notification.notifyPhone(WiFi.SSID(i));
        SerialBT.print(": ");
        SerialBT.print(WiFi.SSID(i));
        SerialBT.print(" (");
        SerialBT.print(WiFi.RSSI(i));
        SerialBT.print(")");
    } 
    else  {
        Notification.notifyPhone(String("Nothing found"));
    }
}
