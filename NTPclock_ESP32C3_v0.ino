#include <WiFi.h>
#include <time.h>
#include <TFT_eSPI.h>

// Definim pinii exact cum a mers în programul tău de test
#define TFT_MOSI 7
#define TFT_SCLK 6
#define TFT_CS   10
#define TFT_DC   3
#define TFT_RST  4
#define TFT_BL   5

TFT_eSPI tft = TFT_eSPI();

// --- CONFIGURARE WIFI ---
const char* ssid     = "bbk2";       
const char* password = "internet2";       

// --- CONFIGURARE NTP ---
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 7200;         // GMT+2 
const int   daylightOffset_sec = 3600;    // Ora de vară (schimbă în 0 iarna)

void setup() {
  Serial.begin(115200);

  // --- Inițializare Display (EXACT cum a mers la tine) ---
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);
  tft.init();
  tft.setRotation(2); 
  tft.fillScreen(TFT_BLACK);

  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextDatum(MC_DATUM); 
  tft.drawString("Conectare WiFi...", 120, 120, 4);

  // --- Conectare WiFi ---
  Serial.print("Conectare la WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Conectat!");

  // --- Setare NTP ---
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Eroare NTP");
    tft.fillScreen(TFT_RED);
    tft.drawString("Eroare Internet", 120, 120, 4);
    while(1);
  }

  // --- Pregătire ecran final ---
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_CYAN, TFT_BLACK);
  tft.drawString("CEAS NTP", 120, 40, 4);
  tft.drawLine(20, 65, 220, 65, TFT_CYAN);
}

void loop() {
  struct tm timeinfo;

  if (getLocalTime(&timeinfo)) {
    
    // Formatam ora
    char timeString[9];
    strftime(timeString, sizeof(timeString), "%H:%M:%S", &timeinfo);

    // Stergem zona orei si afisam (Font 6)
    tft.fillRect(0, 90, 240, 50, TFT_BLACK);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextDatum(MC_DATUM);
    tft.drawString(timeString, 120, 110, 6); // Folosim fontul 6

    // Formatam data
    char dateString[12];
    strftime(dateString, sizeof(dateString), "%d.%m.%Y", &timeinfo);

    // Stergem zona datei si afisam
    tft.fillRect(0, 160, 240, 30, TFT_BLACK);
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.drawString(dateString, 120, 170, 4);
  }

  delay(1000);
}
