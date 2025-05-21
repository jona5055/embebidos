#include <ESP32Servo.h>

// Pines de las fotoresistencias (LDRs)
#define LDR_SUP_DER 34  // Superior derecho
#define LDR_SUP_IZQ 35  // Superior izquierdo
#define LDR_INF_IZQ 32  // Inferior izquierdo
#define LDR_INF_DER 33  // Inferior derecho

// Pines de los servomotores
#define SERVO_X_PIN 14  // Eje horizontal (abajo)
#define SERVO_Y_PIN 13  // Eje vertical (arriba)

// Configuración de servos
Servo servoX, servoY;
int posX = 90;  // Posición inicial horizontal (centro)
int posY = 90;  // Posición inicial vertical (centro)

// Parámetros de seguimiento
int margen = 50;   // Margen de diferencia para activar movimiento
int paso = 1;      // Incremento de movimiento del servo
int delayMs = 15;  // Retardo entre lecturas

void setup() {
  Serial.begin(115200);
  
  // Configurar pines LDR como entradas
  pinMode(LDR_SUP_DER, INPUT);
  pinMode(LDR_SUP_IZQ, INPUT);
  pinMode(LDR_INF_IZQ, INPUT);
  pinMode(LDR_INF_DER, INPUT);
  
  // Configurar servos (ESP32 requiere esta inicialización)
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  
  servoX.setPeriodHertz(50);
  servoY.setPeriodHertz(50);
  
  servoX.attach(SERVO_X_PIN, 500, 2400);
  servoY.attach(SERVO_Y_PIN, 500, 2400);
  
  servoX.write(posX);
  servoY.write(posY);
  
  delay(1000);  // Pausa inicial
}

void loop() {
  // Leer valores de los LDRs
  int supDer = analogRead(LDR_SUP_DER);
  int supIzq = analogRead(LDR_SUP_IZQ);
  int infIzq = analogRead(LDR_INF_IZQ);
  int infDer = analogRead(LDR_INF_DER);

  // Calcular diferencias para cada eje
  int difHorizontal = (supDer + infDer) - (supIzq + infIzq);  // Derecha vs Izquierda
  int difVertical = (supDer + supIzq) - (infDer + infIzq);    // Arriba vs Abajo

  // Movimiento horizontal (eje X)
  if (abs(difHorizontal) > margen) {
    posX += (difHorizontal > 0) ? paso : -paso;
    posX = constrain(posX, 0, 180);  // Limitar rango
    servoX.write(posX);
  }

  // Movimiento vertical (eje Y)
  if (abs(difVertical) > margen) {
    posY += (difVertical > 0) ? paso : -paso;
    posY = constrain(posY, 0, 180);  // Limitar rango
    servoY.write(posY);
  }

  // Opcional: Mostrar valores para depuración
  Serial.print("X: ");
  Serial.print(posX);
  Serial.print(" | Y: ");
  Serial.print(posY);
  Serial.print(" | DifH: ");
  Serial.print(difHorizontal);
  Serial.print(" | DifV: ");
  Serial.println(difVertical);

  delay(delayMs);
}