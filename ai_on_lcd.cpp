/*I have explained what the code does line by line, do change the code you are most welcome, enjoy with the build*/

#include <WiFi.h>          // Includes the necessary library to handle WiFi connections on the ESP32.
#include <HTTPClient.h>    // Includes the library used for making HTTP requests to external services (like Google Gemini).
#include <ArduinoJson.h>   // Includes the library required to parse the JSON response received from the API.
#include <LiquidCrystal.h> // Includes the standard library for interfacing with the LCD screen.

// YOUR VERIFIED PINS: RS=22, E=23, D4=5, D5=18, D6=19, D7=21
// Initializes the LiquidCrystal library with the specific GPIO pin numbers connected to the LCD.
LiquidCrystal lcd(22, 23, 5, 18, 19, 21);

const char* ssid     = "Your_SSID_name";      // Your WiFi network SSID (name).
const char* password = "Your_SSID_password";  // Your WiFi network password.
String apiKey        = "Your_API";            // Your Google Gemini API key.
String factText      = "Asking Gemini... ";   // Initial text displayed while waiting for the first fact.

void setup() {
  delay(1000); // CRITICAL: Gives LCD time to power up and stabilize before sending commands.
  lcd.begin(16, 2); // Initializes the LCD screen (16 columns, 2 rows).
  lcd.clear();      // Clears the initial blocky characters from the screen.
  lcd.print("WiFi Booting..."); // Prints status message to the LCD.
  
  // Initiates the connection process to the specified WiFi network.
  WiFi.begin(ssid, password); 
  // Loops and prints a "." every 500ms until a connection is successfully established.
  while (WiFi.status() != WL_CONNECTED) { 
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print(".");
  }
  fetchFact(); // Calls the function to fetch the first AI-generated fact once connected.
}

void fetchFact() {
  HTTPClient http; // Creates an instance of the HTTP client.
  // Constructs the full URL for the Gemini API endpoint using the user's API key.
  String url = "https://generativelanguage.googleapis.com/v1beta/models/gemini-1.5-flash:generateContent?key=" + apiKey;
  http.begin(url); // Specifies the destination URL for the request.
  http.addHeader("Content-Type", "application/json"); // Sets the header indicating the data being sent is in JSON format.
  // The JSON payload containing the prompt for the AI model.
  String payload = "{\"contents\": [{\"parts\":[{\"text\": \"Short science fact, max 60 chars.\"}]}]}";
  int httpCode = http.POST(payload); // Sends the POST request and stores the response code.
  
  if (httpCode > 0) { // Checks if the HTTP request was successful (code > 0).
    DynamicJsonDocument doc(2048); // Creates a buffer to hold the incoming JSON data.
    deserializeJson(doc, http.getString()); // Parses the response string into the JSON document.
    String res = doc["candidates"][0]["content"]["parts"][0]["text"]; // Extracts the actual text response from the complex JSON structure.
    res.replace("\n", ""); // Removes any newline characters from the fact text for cleaner LCD display.
    factText = "GEMINI: " + res + "    "; // Stores the new fact with a label and trailing spaces for the scrolling effect.
  }
  http.end(); // Closes the HTTP connection.
}

void loop() {
  lcd.setCursor(0, 0); lcd.print("AI LIVE FEED:   "); // Prints a static header on the top line.
  // This outer loop iterates through the entire length of the 'factText' string.
  for (int i = 0; i < factText.length(); i++) { 
    lcd.setCursor(0, 1); // Moves the cursor to the start of the second line for the scrolling text.
    String frame = ""; 
    // This inner loop builds a 16-character 'frame' of text to display at the current position.
    for (int j = 0; j < 16; j++) { 
      // Uses the modulo operator (%) to wrap the text around when it reaches the end of the string, creating a seamless scroll.
      frame += factText[(i + j) % factText.length()]; 
    }
    lcd.print(frame); // Prints the current 16-character segment (the "frame").
    delay(350); // Pauses briefly to control scroll speed.
    if (i == factText.length() - 1) fetchFact(); // If the end of the current fact is reached, fetch a new one.
  }
}
