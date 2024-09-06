// #include "Arduino.h"
// #include <TFT_eSPI.h>

// extern "C" void app_main()
// {
//     initArduino();
//     pinMode(4, OUTPUT);
//     digitalWrite(4, HIGH);
//     // Do your own thing
// }

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "TFT_eSPI.h"  // Include the graphics library (TFT_eSPI)

static const char *TAG = "Main";

// Create an instance of the TFT_eSPI class
TFT_eSPI tft = TFT_eSPI();

extern "C" void app_main(void) {  // Ensure C linkage for app_main
    ESP_LOGI(TAG, "Initializing display...");

    // Initialize the display
    tft.init();
    tft.setRotation(1);  // Set display rotation (0-3)
    tft.fillScreen(TFT_BLACK);  // Clear the screen with a black background

    // Set text properties
    tft.setTextColor(TFT_WHITE, TFT_BLACK);  // Set text color to white and background to black
    tft.setTextSize(2);  // Set the size of the text

    ESP_LOGI(TAG, "Displaying 'Hello, World!'...");

    // Print "Hello, World!" at the center of the screen
    if (!tft.fontLoaded) {
        ESP_LOGE(TAG, "Font not loaded!");
        return;
    }

    tft.drawString("Hello, World!", 60, 120, 4);  // Text, X position, Y position, Font size

    // Keep the task alive; otherwise, the program will exit
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(1000));  // Delay for 1000 ms
    }
}