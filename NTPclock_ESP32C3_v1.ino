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
    
    // Separam formatarile: una pentru Ora:Minut, alta pentru Secunde
    char timeHM[6]; 
    char timeS[3];  

    strftime(timeHM, sizeof(timeHM), "%H:%M", &timeinfo);
    strftime(timeS, sizeof(timeS), "%S", &timeinfo);

    // Stergem o zona mai mare pe verticala pentru a acoperi atat fontul mare cat si cel mic
    tft.fillRect(0, 75, 240, 80, TFT_BLACK);

    // Afisam Ora si Minutele MARI (Font 7 - cel mai mare din biblioteca standard)
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextDatum(MC_DATUM); // Middle Center
    tft.drawString(timeHM, 120, 105, 7); 

    // Afisam Secundele MICI (Font 2)
    // Le-am pus sub ora mare, centrate. 
    // Daca vrei sa le pui in coltul dreapta-sus, schimba din MC_DATUM in TR_DATUM si coordonata X din 120 in 230
    tft.setTextColor(TFT_YELLOW, TFT_BLACK); // Culoare galbena pentru a fi discreta (poti pune TFT_WHITE sau TFT_GREY)
    tft.setTextDatum(MC_DATUM); 
    tft.drawString(timeS, 120, 140, 2); 

    // Formatam data
    char dateString[12];
    strftime(dateString, sizeof(dateString), "%d.%m.%Y", &timeinfo);

    // Stergem zona datei si afisam
    tft.fillRect(0, 165, 240, 30, TFT_BLACK);
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.setTextDatum(MC_DATUM);
    tft.drawString(dateString, 120, 175, 4);
  }

  delay(1000);
}
