#include <DHT.h>


#define DHTPIN 2       
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

#define SOIL_PIN A4   

#define LED_PIN 5      
#define BUZZER_PIN 6  

#define TEMP_THRESHOLD 30.0       
#define SOIL_THRESHOLD 400       

void sendSensorData() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  int soilValue = analogRead(SOIL_PIN); 

  if (isnan(h) || isnan(t)) {
    Serial.println("Gagal membaca dari sensor DHT22!");
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C\t");
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Soil Moisture: ");
  Serial.println(soilValue);

  if (t > TEMP_THRESHOLD) { 
    digitalWrite(LED_PIN, HIGH);
    Serial.println("Status LED: ON (Suhu > " + String(TEMP_THRESHOLD) + " *C)");
  } else {
    digitalWrite(LED_PIN, LOW);
    Serial.println("Status LED: OFF");
  }

  if (soilValue < SOIL_THRESHOLD) { 
    digitalWrite(BUZZER_PIN, HIGH);
    Serial.println("Status Buzzer: ON (Soil Moisture > " + String(SOIL_THRESHOLD) + ")");
  } else {
    digitalWrite(BUZZER_PIN, LOW);
    Serial.println("Status Buzzer: OFF");
  }
  Serial.println("---------------------------------------------");
}

void setup() {
  Serial.begin(9600);
  delay(1000); 
  
  Serial.println("=== SISTEM MEMULAI ===");
  Serial.print("DHT22 Pin: "); Serial.println(DHTPIN);
  Serial.print("Soil Sensor Pin: "); Serial.println(SOIL_PIN);
  Serial.print("LED Pin: "); Serial.println(LED_PIN);
  Serial.print("Buzzer Pin: "); Serial.println(BUZZER_PIN);
  Serial.println("=====================");

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  dht.begin();
}

void loop() {
  sendSensorData();
  delay(2000);
}
