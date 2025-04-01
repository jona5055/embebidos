const int segmentPins1[7] = {2, 4, 5, 12, 13, 14, 15}; // Display 1 (Segundos)
const int transistorPins1[2] = {16, 17}; // Display 1 (Segundos)

const int segmentPins2[7] = {18, 19, 21, 22, 23, 25, 26}; // Display 2 (Minutos)
const int transistorPins2[2] = {27, 32}; // Display 2 (Minutos)

const uint8_t segmentMap[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

unsigned int seconds = 0; // Segundos a mostrar
unsigned int minutes = 0; // Minutos a mostrar
unsigned long lastUpdateTime = 0; // Última vez que se actualizó el tiempo
const int updateInterval = 50; // Intervalo de actualización en milisegundos (1 segundo)

void setup() {
  for (int i = 0; i < 7; i++) {
    pinMode(segmentPins1[i], OUTPUT);
    digitalWrite(segmentPins1[i], LOW);
  }
  for (int i = 0; i < 2; i++) {
    pinMode(transistorPins1[i], OUTPUT);
    digitalWrite(transistorPins1[i], LOW);
  }

  for (int i = 0; i < 7; i++) {
    pinMode(segmentPins2[i], OUTPUT);
    digitalWrite(segmentPins2[i], LOW);
  }
  for (int i = 0; i < 2; i++) {
    pinMode(transistorPins2[i], OUTPUT);
    digitalWrite(transistorPins2[i], LOW);
  }
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - lastUpdateTime >= updateInterval) {
    lastUpdateTime = currentTime;
    seconds++;
    if (seconds > 59) { // Reiniciar a 0 cuando llegue a 59 segundos
      seconds = 0;
      minutes++;
      if (minutes > 59) { // Reiniciar a 0 cuando llegue a 59 minutos
        minutes = 0;
      }
    }
  }

  // Mostrar segundos
  for (int i = 0; i < 2; i++) {
    int digit = (seconds / (int)pow(10, i)) % 10;
    uint8_t segments = segmentMap[digit];
    for (int j = 0; j < 7; j++) {
      digitalWrite(segmentPins1[j], (segments >> j) & 0x01);
    }
    digitalWrite(transistorPins1[i], HIGH);
    delay(5);
    digitalWrite(transistorPins1[i], LOW);
  }

  // Mostrar minutos
  for (int i = 0; i < 2; i++) {
    int digit = (minutes / (int)pow(10, i)) % 10;
    uint8_t segments = segmentMap[digit];
    for (int j = 0; j < 7; j++) {
      digitalWrite(segmentPins2[j], (segments >> j) & 0x01);
    }
    digitalWrite(transistorPins2[i], HIGH);
    delay(5);
    digitalWrite(transistorPins2[i], LOW);
  }
}