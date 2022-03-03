
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
    } 
    else {
        SerialBT.print(n);
        SerialBT.println(" networks found");

        for (int i = 0; i < n; ++i) {

            // Print SSID, RSSI an encryption for each network found on the bluetooth serial
            SerialBT.print(i + 1);
            SerialBT.print(": ");
            SerialBT.print(WiFi.SSID(i));
            SerialBT.print(" (");
            SerialBT.print(WiFi.RSSI(i));
            SerialBT.print(")");
            SerialBT.println(WiFi.encryptionType(i));                 
            delay(10);

                if(WiFi.encryptionType(i) == 0) 
                {
                    SerialBT.println("OPEN");
                }

                else if(WiFi.encryptionType(i) == 1)
                {
                    SerialBT.println("WEP");
                }

                else if(WiFi.encryptionType(i) == 2)
                {
                    SerialBT.println("WPA_PSK");
                }

                else if(WiFi.encryptionType(i) == 3)
                {
                    SerialBT.println("WPA2_PSK");
                }

                else if(WiFi.encryptionType(i) == 4)
                {
                    SerialBT.println("WPA_WPA2_PSK");
                }

                else if(WiFi.encryptionType(i) == 5)
                {
                    SerialBT.println("WPA2_ENTREPRISE");
                }

                else
                {
                    SerialBT.println("Wifi is unknown encrypted");
                }
                    
                }
        }
    
    SerialBT.println("");

    // Wait a bit before scanning again
    delay(5000);
}
