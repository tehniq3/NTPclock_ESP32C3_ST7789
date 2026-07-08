// Configurare pentru ESP32-C3 Mini + ST7789 240x240
#define ST7789_DRIVER
#define TFT_WIDTH  240
#define TFT_HEIGHT 240

// Pinii SPI hardware pentru ESP32-C3
#define TFT_MOSI 7
#define TFT_SCLK 6
#define TFT_CS   10
#define TFT_DC   3
#define TFT_RST  4
#define TFT_BL   5

// Ordinea culorilor (daca culorile sunt inversate, schimba in TFT_BGR)
//#define TFT_RGB_ORDER TFT_RGB  
#define TFT_RGB_ORDER TFT_BGR

// Frecventa SPI (ruleaza stabil la 40MHz pentru C3)
#define SPI_FREQUENCY       40000000
#define SPI_READ_FREQUENCY  20000000
#define SPI_TOUCH_FREQUENCY  2500000

//#define TFT_X_OFFSET  0
//#define TFT_Y_OFFSET  80


// Optional: Daca vrei sa folosesti fonturi custom, decomenteaza:
 #define LOAD_GLCD
 #define LOAD_FONT2
 #define LOAD_FONT4
 #define LOAD_FONT6
 #define LOAD_FONT7
 #define LOAD_FONT8
