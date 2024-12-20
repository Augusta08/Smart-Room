#include <DHT.h>

#define IN1Pin 13
#define IN2Pin 12
#define ENAPin 6
#define pirPin 10
#define ledPin 11
int pirState;
#define outLight 9
#define ldrPin A0
int ldrValue;
#define DHTPIN 2       // Pin connected to DATA
#define DHTTYPE DHT11  // Define the sensor type

DHT dht(DHTPIN, DHTTYPE);

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
  someoneInside();
  outsideLight();
  hotRoom();
}

void someoneInside() {
  pirState = digitalRead(pirPin);
  if (pirState == HIGH){
    digitalWrite(ledPin, HIGH);
    Serial.println("Room light ON");
  } else {
    digitalWrite(ledPin, LOW);
  }
}

void outsideLight() {
  ldrValue = analogRead(ldrPin);
  if (ldrValue >= 512) {
    digitalWrite(outLight, HIGH);
    Serial.println("Outside light ON");
  } else {
    digitalWrite(outLight, LOW);
  }
  delay(2);
}

void hotRoom() {
  float temp = dht.readTemperature(); // Read temperature (Celsius)
  float humidity = dht.readHumidity(); // Read humidity

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
  }

  delay(1000); // Wait 2 seconds before the next reading
}