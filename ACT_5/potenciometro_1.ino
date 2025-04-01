const int ppot = 34; // Pin donde está conectado el potenciómetro
const int pled = 32; // Pin donde está conectado el LED
const float voltR = 3.3; // Voltaje de referencia de la ESP32
int potVa = 0; // Variable para almacenar el valor del potenciómetro
float ang = 0; // Variable para almacenar el ángulo calculado
float volt = 0; // Variable para almacenar el voltaje
float brilloPorcentaje = 0; // Variable para almacenar el porcentaje de brillo del LED

void setup() {
  Serial.begin(115200); // Inicializa la comunicación serial a 115200 baudios
  pinMode(pled, OUTPUT); // Configura el pin del LED como salida
}

void loop() {
  potVa = analogRead(ppot); // Lee el valor del potenciómetro
  volt = potVa * (voltR / 4095.0); // Calcula el voltaje
  ang = map(potVa, 0, 4095, 0, 270); // Mapea el valor del potenciómetro a un ángulo entre 0 y 270 grados
  int brillo = map(potVa, 0, 4095, 0, 255); // Mapea el valor del potenciómetro a un valor de brillo entre 0 y 255
  analogWrite(pled, brillo); // Ajusta el brillo del LED
  brilloPorcentaje = (brillo / 255.0) * 100; // Calcula el porcentaje de brillo

  Serial.print("Ángulo: ");
  Serial.print(ang);
  Serial.print(" grados, Voltaje: ");
  Serial.print(volt);
  Serial.print(" V, Brillo del LED: ");
  Serial.print(brilloPorcentaje);
  Serial.println(" %");
}