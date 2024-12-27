#include <DHT.h>

#define IN1Pin 13
#define IN2Pin 12
#define ENAPin 6
#define pirPin 10
#define ledPin 11
#define outLight 9
#define ldrPin A0
#define DHTPIN 2       // Pin connected to DATA
#define DHTTYPE DHT11  // Define the sensor type
int pirState;
int ldrValue;

DHT dht(DHTPIN, DHTTYPE);

unsigned long pirEventInterval = 1000;  // Interval in-between checking the pir sensor
unsigned long ldrAndTempInterval = 3000;  // Interval in-between checking the ldr and temp sensor

unsigned long pirPreviousTime = 0;
unsigned long ldrAndTempPreviousTime = 0;

void setup() {
  pinMode(IN1Pin, OUTPUT);
  pinMode(IN2Pin, OUTPUT);
  pinMode(ENAPin, OUTPUT);
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(outLight, OUTPUT);
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - pirPreviousTime >= pirEventInterval) {
    someoneInside();
    pirPreviousTime = currentTime;
  }

  if (currentTime - ldrAndTempPreviousTime >= ldrAndTempInterval) {
    outsideLight();
    hotRoom();
    ldrAndTempPreviousTime = currentTime;
  }
}

void someoneInside() {
  pirState = digitalRead(pirPin);
  if (pirState == HIGH) {
    digitalWrite(ledPin, HIGH);
    Serial.println("Room light ON");
  } else {
    digitalWrite(ledPin, LOW);
    Serial.println("Room light OFF");
  }
}

void outsideLight() {
  ldrValue = analogRead(ldrPin);
  if (ldrValue >= 512) {
    digitalWrite(outLight, HIGH);
    Serial.println("Outside light ON");
  } else {
    digitalWrite(outLight, LOW);
    Serial.println("Outside light OFF");
  }

  void hotRoom() {
    float temp = dht.readTemperature();   // Read temperature (Celsius)
    float humidity = dht.readHumidity();  // Read humidity

    // Check for errors
    if (isnan(temp) || isnan(humidity)) {
      Serial.println("Failed to read from DHT11!");
      return;
    }

    if (temp >= 35) {
      digitalWrite(IN1Pin, HIGH);
      digitalWrite(IN2Pin, LOW);
      analogWrite(ENAPin, 255);
      Serial.println("Fan ON");
    } else {
      digitalWrite(IN1Pin, LOW);
      digitalWrite(IN2Pin, LOW);
      Serial.println("Fan OFF");
    }
  }