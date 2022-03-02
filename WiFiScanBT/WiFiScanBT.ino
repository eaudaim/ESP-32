
#include "WiFi.h"
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

void setup()
{
    SerialBT.begin("ESP32");
    Serial.begin(115200);
    

    // Set WiFi to station mode and disconnect from an AP if it was previously connected
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);
}

void loop()
{
    // WiFi.scanNetworks will return the number of networks found

    int n = WiFi.scanNetworks();

    if (n == 0) {
        SerialBT.println("no networks found");
    } else {
        SerialBT.print(n);
        SerialBT.println(" networks found");
        for (int i = 0; i < n; ++i) {
            
            // Print SSID and RSSI for each network found on the bluetooth serial, also print a number for the type of encryption : TKIP (WPA)= 2, WEP= 5, CCMP (WPA)= 4, NONE= 7, AUTO= 8
            SerialBT.print(i + 1);
            SerialBT.print(": ");
            SerialBT.print(WiFi.SSID(i));
            SerialBT.print(" (");
            SerialBT.print(WiFi.RSSI(i));
            SerialBT.print(")");
            SerialBT.println(WiFi.encryptionType(i));                 
            delay(10);
        }
    }
    SerialBT.println("");

    // Wait a bit before scanning again
    delay(5000);
}
