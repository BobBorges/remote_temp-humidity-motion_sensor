#include "DHT.h"
#define DHTPIN PB7     
#define DHTTYPE DHT11   

int pirState = LOW;
int val = 0;

unsigned long epochStart;
unsigned long currentTime;
int dht_timeout = 5000;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  pinMode(PB15, OUTPUT);
  pinMode(PC13, OUTPUT);
  pinMode(PB5, INPUT);
  Serial.begin(9600);
  epochStart = millis();
  dht.begin();
}

void loop() {
  currentTime = millis();
  if (currentTime - epochStart >= dht_timeout) {
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    float f = dht.readTemperature(true);
    if (isnan(h) || isnan(t) || isnan(f)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }
    Serial.print("HUMI ");
    Serial.print(h);
    Serial.print("\n");
    Serial.print("TMPC ");
    Serial.print(t);
    Serial.print("\n");
    Serial.print("TMPF ");
    Serial.print(f);
    Serial.print("\n");
    epochStart = currentTime;
  }

  val = digitalRead(PB5);
  if (val == HIGH) {
    digitalWrite(PB15, HIGH);
    digitalWrite(PC13, LOW);
    if (pirState == LOW) {
      // we have just turned on
      Serial.println("MOTN 1");
      pirState = HIGH;
    }
  } else {
    digitalWrite(PB15, LOW); // turn LED OFF
    digitalWrite(PC13, HIGH);
    if (pirState == HIGH){
      Serial.println("MOTN 0");
      pirState = LOW;
    }
  }
}
