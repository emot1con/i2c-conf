const int trigPin = 9;
const int echoPin = 10;

const int mq135Pin = A0;

const int ledPin = 7;
const int buzzerPin = 8;

const float tinggiTempatSampah = 30.0;
const int batasGas = 700;

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  long durasi = pulseIn(echoPin, HIGH, 30000);

  float jarak = durasi * 0.0343 / 2.0;

  float volumeSampah =
    ((tinggiTempatSampah - jarak) / tinggiTempatSampah) * 100.0;

  if (volumeSampah < 0) volumeSampah = 0;
  if (volumeSampah > 100) volumeSampah = 100;

  int nilaiGas = analogRead(mq135Pin);

  Serial.println("--------------------------------");
  Serial.print("Jarak Sampah : ");
  Serial.print(jarak);
  Serial.println(" cm");

  Serial.print("Volume Sampah : ");
  Serial.print(volumeSampah);
  Serial.println(" %");

  Serial.print("Nilai Gas MQ-135 : ");
  Serial.println(nilaiGas);

  if (volumeSampah >= 80 || nilaiGas >= batasGas) {

    digitalWrite(ledPin, HIGH);
    tone(buzzerPin, 1000);

    Serial.println("STATUS : PERINGATAN");

  } else {

    digitalWrite(ledPin, LOW);
    noTone(buzzerPin);

    Serial.println("STATUS : NORMAL");
  }

  delay(1000);
}