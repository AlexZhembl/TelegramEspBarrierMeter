#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define WIFI_SSID ""
#define WIFI_PASSWORD ""

String tgUrl = "https://api.telegram.org/<bot_token>/sendmessage?chat_id=<chat_id>&text=";
String tgMessage = "You%20got%20new%20bill%20%23"; // You got new bill #

void setupWIFI(int ledPin) {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(LED_PIN, HIGH);
    delay(1000);
    Serial.println("Connecting...");
    digitalWrite(LED_PIN, LOW);
    delay(1000);
  }
}

void trackToTelegram(int billNumber) {
  if (WiFi.status() == WL_CONNECTED) {      //Check WiFi connection status
    std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
    client->setInsecure();
    HTTPClient http;                        //Declare an object of class HTTPClient
    http.begin(*client, tgUrl + tgMessage + billNumber);                      //Specify request destination
    int httpCode = http.GET();           //Send the request
    if (httpCode > 0) {                     //Check the returning code
      String payload = http.getString();    //Get the request response payload
      Serial.println(payload);              //Print the response payload
    } else {
        Serial.printf("[HTTPS] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();                             //Close connection
  }
}
