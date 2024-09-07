#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "TFT_eSPI.h"  // Include the graphics library (TFT_eSPI)
#include <SPI.h>

#define TDELAY 500  // Delay time in milliseconds

TFT_eSPI tft = TFT_eSPI();  // Create an instance of the TFT_eSPI library

// Function prototypes
void setup();
void loop();

// Setup function
void setup() {
    // Initialize the TFT display
    tft.init();
    tft.fillScreen(0xF81F);  // Fill screen with a color (0xF81F)
}

// Loop function
void loop() {
    static uint32_t wr = 1;
    static uint32_t rd = 0xFFFFFFFF;
    // static int wr = 1;
    // static int rd = 0xFFFFFFFF;

    vTaskDelay(pdMS_TO_TICKS(TDELAY));  // Delay for TDELAY milliseconds

    // Draw a pixel and read its value
    tft.drawPixel(30, 30, wr);
    ESP_LOGI("TAG", "Pixel value written = %04X", static_cast<unsigned int>(wr));


    rd = tft.readPixel(30, 30);
    ESP_LOGI("TAG", "Pixel value read = %04X", static_cast<unsigned int>(rd));

    if (rd != wr) {
        ESP_LOGE("TFT", "ERROR: Written and read values do not match!");
    } else {
        ESP_LOGI("TFT", "PASS");
    }

    // Walking 1 test
    wr = wr << 1;
    if (wr >= 0x10000) wr = 1;
}

// Main application entry point
extern "C" void app_main() {
    setup();  // Call the setup function

    // Run the loop function indefinitely
    while (true) {
        loop();
        vTaskDelay(pdMS_TO_TICKS(1000));  // Delay for 1 second
    }
}
