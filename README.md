# AI-on-LCD
Hey all, Good to see you again, This is professor OAK-- ahem sorry my bad..  This is an easy no bs demo straightly to the point.. I connect ESP32 TO LCD THAT'S IT SIMPLE NO BS
In this project, I demonstrate how a 16×2 LCD display can be connected with an ESP32 microcontroller and enhanced using Gemini Vertex AI to fetch intelligent, real-time content from the internet. I want to show you how the AI can be used with embedded system like the ESP32. This tutorial covers everything from API generation to hardware wiring and code optimization.

1. The AI Integration (Gemini 1.5 Flash)
The journey begins with the creation of a secure API key using Google Gemini Vertex AI. This key acts as the bridge between the ESP32 and the AI service. Once generated, it is integrated directly into the ESP32 firmware using the official x-goog-api-key request header. This ensures a stable and authenticated connection when communicating with the Gemini endpoint, bypassing common security rejections.

2. Hardware Configuration

For the hardware setup, we use a 30-pin ESP32 board connected to a 16×2 LCD display (HD44780). We follow a specific pin mapping to ensure zero interference during the boot process:

RS & Enable: Connected to GPIO 13 and GPIO 12.
Data Lines (D4–D7): Mapped to GPIOs 14, 27, 26, and 25.
Power (VDD/A): Wired to VIN (5V) for maximum contrast.
Contrast (V0): Controlled by a 10k Ohm potentiometer.

3. Software Logic & Customization

There's something you need to take care of here, connecting your esp32 to the Arduino IDE is kinda hard if you don't know stuff and are beginning your journey, trust me debugging this takes more time than the entire connections or the coding part.

MUST READ IF ESP32 IS NOT SET UP BY DEFAULT

You need the esp32 board manager for the same..

1. Open the Arduino IDE.
2. Go to File > choose Preferences.
3. In the "Additional Board Manager URLs" field, paste the following URL: https://espressif.github.io/arduino-esp32/package_esp32_index.json.
If you have other URLs in the field, separate them with a comma.
4. Click OK to save the changes. 

If your internet is slow for some reason Arduino IDE has in-built threshold time after which the download of ESP-32 fails, the file for the board manager of ESP 32 is pretty big for your information
TO fix this you need to locate the yaml file and change the download timeout for the same


Once powered on, the ESP32 connects to local Wi-Fi and initiates a request to the Gemini Vertex AI endpoint. The response is a short fact about Earth—is processed via the ArduinoJson library and displayed in a smooth scrolling format.

4. How to Modify the code:

Change Content: Edit the payload string to request motivational quotes, weather, or jokes.

Adjust Frequency: Change the fetchInterval (e.g., 120000 for 2 minutes) to conserve your Free Tier quota. 

Scrolling Speed: Adjust the delay() value in the main loop to fit your reading preference.

5.  Troubleshooting & FAQ

The code which I obtained was after many iterations of errors like HTTP 404,429 AND what not???, but this version absolutely works unless stuff happens.... 

HTTP 404 Error: Ensure you are using the v1beta endpoint in your URL for the Flash model.

HTTP 429 Error: You have exceeded your rate limit. Increase the delay between requests to at least 60 seconds.

Blank Screen: Adjust the contrast potentiometer on Pin 3 until characters appear.

📦 Parts List

ESP32-WROOM-32 (30-Pin Version)

PS: You can also use the 38 pin version but the code changes for it, you can modify my code to the required pins and try it.. I didn't have access to the 38 pin version by the way though..

16x2 LCD Display (Blue/Green Backlight) anything works mate..

10k Ohm Potentiometer (small or big pot, they work the same) 

Breadboard & Jumper Wires (get these mate)
