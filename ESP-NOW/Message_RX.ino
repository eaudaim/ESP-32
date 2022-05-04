// Inclure les librairies
#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//Definition des constantes
#define SCREEN_WIDTH 128 // Largeur de l'écran OLED (128 pixels)
#define SCREEN_HEIGHT 64 // hauteur de l'écran OLED (64 pixels)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// La variable qui sera reçue par le récepteur
String maValeurRecue;

// La fonction de rappel qui nous assurera de la bonne livraison du message
void quand_donnees_Recues(const uint8_t * mac, const uint8_t *data_reception, int taille) {
  memcpy(&maValeurRecue, data_reception, sizeof(maValeurRecue));
  Serial.print("Bytes received: ");
  Serial.println(taille);
  Serial.print("valeur reçue: ");
  Serial.println(maValeurRecue);
  Serial.println();

  // Partie affichage OLED
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

    //delay(2000);
    
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(3, 10);
  display.println(maValeurRecue);
  display.display(); 
}

 
void setup() {
  // On initie la comm série à 115200 Bauds
  Serial.begin(115200);

  // On démarre le Wifi en mode Station
  WiFi.mode(WIFI_STA);

  // Puis on initialise ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Erreur d'initialisation ESP-NOW");
    return;
  }

  // Si ESP-NOW a correctement démarré, il est temps d'enregistrer la fonction de rappel:
  esp_now_register_recv_cb(quand_donnees_Recues);

  
}
 
void loop() {
  
}
