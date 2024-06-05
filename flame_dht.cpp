#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

#define FLAME_PIN 3
#define LED_PIN 4
#define BUZZER_PIN 5

DHT dht(DHTPIN, DHTTYPE);

// Ambang suhu kebakaran
float suhuBatas = 30.0;

void setup() {

  Serial.begin(9600);

  pinMode(FLAME_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  dht.begin();

  Serial.println("================================");
  Serial.println(" SISTEM DETEKSI KEBAKARAN ");
  Serial.println("================================");
}

void loop() {

  float suhu = dht.readTemperature();
  float kelembaban = dht.readHumidity();

  int flame = digitalRead(FLAME_PIN);

  if (isnan(suhu) || isnan(kelembaban)) {
    Serial.println("Gagal membaca DHT11");
    delay(1000);
    return;
  }

  Serial.print("Suhu: ");
  Serial.print(suhu);
  Serial.print(" C");

  Serial.print(" | Kelembaban: ");
  Serial.print(kelembaban);
  Serial.print(" %");

  Serial.print(" | Flame: ");
  Serial.print(flame);

  if (flame == LOW) {
    Serial.print(" (API TERDETEKSI)");
  } else {
    Serial.print(" (AMAN)");
  }

  Serial.println();

  // Kondisi kebakaran
  if (suhu > suhuBatas && flame == LOW) {

    Serial.println(">>> KEBAKARAN TERDETEKSI <<<");

    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER_PIN, 1000);

  } else {

    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER_PIN);
  }

  delay(1000);
}


#include <DHT.h>

#define DHTPIN D2
#define DHTTYPE DHT11

#define FLAME_PIN D5
#define LED_PIN D6
#define BUZZER_PIN D7

DHT dht(DHTPIN, DHTTYPE);

const float suhuBatas = 30.0;

void setup() {
  Serial.begin(115200);

  pinMode(FLAME_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  dht.begin();
}

void loop() {

  float suhu = dht.readTemperature();
  float kelembaban = dht.readHumidity();

  int flame = digitalRead(FLAME_PIN);

  if (isnan(suhu) || isnan(kelembaban)) {
    Serial.println("Gagal membaca DHT11");
    delay(1000);
    return;
  }

  Serial.print("Suhu: ");
  Serial.print(suhu);
  Serial.print(" C");

  Serial.print(" | Kelembaban: ");
  Serial.print(kelembaban);
  Serial.print("%");

  Serial.print(" | Flame: ");
  Serial.print(flame);

  if (suhu > suhuBatas && flame == LOW) {

    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);

    Serial.println(" | KEBAKARAN");

  } else {

    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);

    Serial.println(" | AMAN");
  }

  delay(1000);
}