#include <ESP8266WiFi.h>
#include <DHT.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

/************************* Pin Definition *********************************/

// DHT11 for reading temperature and humidity value
#define DHTPIN D7
String temp;
String hum;
#define DHTTYPE DHT11     // DHT 11
DHT dht(DHTPIN, DHTTYPE);

#define NOTE_B0 31
#define NOTE_C1 33
#define NOTE_CS1 35
#define NOTE_D1 37
#define NOTE_DS1 39
#define NOTE_E1 41
#define NOTE_F1 44
#define NOTE_FS1 46
#define NOTE_G1 49
#define NOTE_GS1 52
#define NOTE_A1 55
#define NOTE_AS1 58
#define NOTE_B1 62
#define NOTE_C2 65
#define NOTE_CS2 69
#define NOTE_D2 73
#define NOTE_DS2 78
#define NOTE_E2 82
#define NOTE_F2 87
#define NOTE_FS2 93
#define NOTE_G2 98
#define NOTE_GS2 104
#define NOTE_A2 110
#define NOTE_AS2 117
#define NOTE_B2 123
#define NOTE_C3 131
#define NOTE_CS3 139
#define NOTE_D3 147
#define NOTE_DS3 156
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_FS3 185
#define NOTE_G3 196
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_CS4 277
#define NOTE_D4 294
#define NOTE_DS4 311
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_FS4 370
#define NOTE_G4 392
#define NOTE_GS4 415
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_CS5 554
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_AS5 932
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_CS6 1109
#define NOTE_D6 1175
#define NOTE_DS6 1245
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_FS6 1480
#define NOTE_G6 1568
#define NOTE_GS6 1661
#define NOTE_A6 1760
#define NOTE_AS6 1865
#define NOTE_B6 1976
#define NOTE_C7 2093
#define NOTE_CS7 2217
#define NOTE_D7 2349
#define NOTE_DS7 2489
#define NOTE_E7 2637
#define NOTE_F7 2794
#define NOTE_FS7 2960
#define NOTE_G7 3136
#define NOTE_A7 3236
// Your WiFi credentials.
// Set password to "" for open networks.
const char* ssid = "White House";
const char* password = "11223344";

ESP8266WebServer server(80);

const int redPin = D4;
const int greenPin = D3;
const int bluePin = D2;
const int buzzerPin = D6;

void handleRoot() {
  server.send(200, "text/plain", "Hello from ESP8266!");
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void setup() {
  // Debug console
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  dht.begin();

  server.on("/", handleRoot); // http://localIPAddress/

  server.on("/dht-temp", []() // http://localIPAddress/dht-temp
  {
    float t = dht.readTemperature();
    temp = String(t);
    server.send(200, "text/plain", temp);
    Serial.print("Temperature: ");
    Serial.println(t);
  });

  server.on("/dht-hum", []()  // http://localIPAddress/dht-hum
  {
    float h = dht.readHumidity();
    hum = String(h);
    server.send(200, "text/plain", hum);
    Serial.print("Humidity: ");
    Serial.println(h);

    // Set LED color and buzzer based on humidity level
    if (h >= 70) {
  // Merah
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, HIGH);
  delay(100);
   int notes[] = {262, 262, 294, 262, 349, 330, 262, 262, 294, 262, 392, 349, 262, 262, 523, 440, 349, 330, 294, 466, 466, 440, 349, 392, 349};
  int durations[] = {200, 200, 400, 400, 400, 800, 200, 200, 400, 400, 400, 800, 200, 200, 400, 400, 400, 200, 200, 200, 200, 200, 400, 200, 400};
  
  for (int i = 0; i < sizeof(notes)/sizeof(notes[0]); i++) {
    playTone(buzzerPin, notes[i], durations[i]);
    delay(durations[i]);
  }// Play a tone with frequency 1000 Hz for 2000 ms
} else if (h >= 40 && h < 70) {
  // Kuning
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, HIGH);
  
  // Play Super Mario Bros theme song
  int melody[] = {
    // Super Mario Bros theme
    NOTE_E7, NOTE_E7, 0, NOTE_E7,
    0, NOTE_C7, NOTE_E7, 0,
    NOTE_G7, 0, 0, 0,
    NOTE_G6, 0, 0, 0,

    NOTE_C7, 0, 0, NOTE_G6,
    0, 0, NOTE_E6, 0,
    0, NOTE_A6, 0, NOTE_B6,
    0, NOTE_AS6, NOTE_A6, 0,

    NOTE_G6, NOTE_E7, NOTE_G7,
    NOTE_A7, 0, NOTE_F7, NOTE_G7,
    0, NOTE_E7, 0, NOTE_C7,
    NOTE_D7, NOTE_B6, 0, 0,

    NOTE_C7, 0, 0, NOTE_G6,
    0, 0, NOTE_E6, 0,
    0, NOTE_A6, 0, NOTE_B6,
    0, NOTE_AS6, NOTE_A6, 0,

    NOTE_G6, NOTE_E7, NOTE_G7,
    NOTE_A7, 0, NOTE_F7, NOTE_G7,
    0, NOTE_E7, 0, NOTE_C7,
    NOTE_D7, NOTE_B6, 0, 0
  };

  int tempo[] = {
    // Super Mario Bros tempo
    12, 12, 12, 12,
    12, 12, 12, 12,
    12, 12, 12, 12,
    12, 12, 12, 12,

    12, 12, 12, 12,
    12, 12, 12, 12,
    12, 12, 12, 12,
    12, 12, 12, 12,

    9, 9, 9,
    12, 12, 12, 12,
    12, 12, 12, 12,
    12, 12, 12, 12,

    12, 12, 12, 12,
    12, 12, 12, 12,
    12, 12, 12, 12,
    12, 12, 12, 12,

    9, 9, 9,
    12, 12, 12, 12,
    12, 12, 12, 12,
    12, 12, 12, 12
  };

  for (int i = 0; i < sizeof(melody) / sizeof(melody[0]); i++) {
    playTone(buzzerPin, melody[i], tempo[i] * 10);
    delay(tempo[i] * 10);
  }
} else {
  // Hijau
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, LOW);
  noTone(buzzerPin); // Turn off the buzzer
}

  });

  server.on("/set-temperature", []() {
  if (server.hasArg("value")) {
    String value = server.arg("value");
    // Ubah nilai temperature sesuai dengan value yang diterima
    // Contoh: temperature = value.toFloat();
  }
  server.send(200, "text/plain", "OK");
});

server.on("/set-humidity", []() {
  if (server.hasArg("value")) {
    String value = server.arg("value");
    // Ubah nilai humidity sesuai dengan value yang diterima
    // Contoh: humidity = value.toFloat();
  }
  server.send(200, "text/plain", "OK");
});

  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  server.handleClient();
}

void playTone(int pin, int frequency, int duration) {
  tone(pin, frequency);
  delay(duration);
  noTone(pin);
}
