// Reference technique: https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/network/esp_now.html

// Inclure les librairies
#include <BluetoothSerial.h>
#include <esp_now.h>
#include <WiFi.h>

// Stockage de l'adresse MAC du récepteur pour usage ultérieur. Remplacer les 'XX' par les valeur notées plus avant.
uint8_t MAC_recepteur[] = {0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX};

// La variable qui sera envoyée au récepteur
String maValeurEnvoyee;

// La fonction de rappel qui nous assurera de la bonne livraison du message
void quand_donnees_Envoyees(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nDernier paquet envoyé:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Succès" : "Échec");
}

// Une variable qui servira à stocker les réglages concernant le récepteur
esp_now_peer_info_t infosRecepteur;

BluetoothSerial SerialBT;
 
void setup() {
  // On initie la comm série à 115200 Bauds et le Bluetooth
  Serial.begin(115200);
  SerialBT.begin("Emetteur");
 
  // On démarre le Wifi en mode Station
  WiFi.mode(WIFI_STA);

  // Puis on initialise ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Erreur d'initialisation ESP-NOW");
    return;
  }

  // Si ESP-NOW a corectement démarré, il est temps d'enregistrer la fonction de rappel:
  esp_now_register_send_cb(quand_donnees_Envoyees);
  
  // Tout est prêt pour l'appairage avec notre récepteur:
  memcpy(infosRecepteur.peer_addr, MAC_recepteur, 6);
  
  // On définit un canal (0 utilisera automatiquement le même canal que celui utilisé par le wifi)
  infosRecepteur.channel = 0;  

  // On ne chiffre pas les échanges
  infosRecepteur.encrypt = false;
  
  // Appairage        
  if (esp_now_add_peer(&infosRecepteur) != ESP_OK){
    Serial.println("Échec de l'appairage");
    return;
  }
}
 
void loop() {
  //on crée une variable qui contiendra le message reçu par bluetooth et on lui affecte la valeur reçue
  String message;
  if(SerialBT.available()) {
    message = SerialBT.readString();
    }
  
  // On affecte la valeur reçue à la variable du message envoyé
  if(message != NULL)
  {
  maValeurEnvoyee = message;
  // On envoie le message
  esp_err_t resultat = esp_now_send(MAC_recepteur, (uint8_t *) &maValeurEnvoyee, sizeof(maValeurEnvoyee));
   
  if (resultat == ESP_OK) {
    Serial.println("Envoi OK");
  }
  else {
    Serial.println("Erreur envoi");
  }
    }
  // On effectue cette opération toutes les 3 secondes
  //delay(3000);
}
