#include <DHT.h>

#define DHTPIN D2
#define DHTTYPE DHT11

#define FLAME_PIN D5
#define LED_PIN D6
#define BUZZER_PIN D7

DHT dht(DHTPIN, DHTTYPE);

float suhuBatas = 40.0;

void setup() {
  Serial.begin(115200);

  pinMode(FLAME_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  dht.begin();
}

void loop() {

  float suhu = dht.readTemperature();
  int flame = digitalRead(FLAME_PIN);

  if (isnan(suhu)) {
    Serial.println("Gagal membaca DHT11");
    return;
  }

  Serial.print("Suhu: ");
  Serial.print(suhu);
  Serial.print(" C | Flame: ");
  Serial.println(flame);

  // HIGH = api terdeteksi
  if (suhu >= suhuBatas && flame == HIGH) {

    Serial.println("KEBAKARAN TERDETEKSI!");

    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER_PIN, 1000);

  } else {

    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER_PIN);
  }

  delay(1000);
}