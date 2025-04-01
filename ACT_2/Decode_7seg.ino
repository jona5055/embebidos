#define PBTN_PIN 15
const int segments[] = {23, 22, 21, 19, 18, 5, 4};
int count = 0; bool pbtn = false, anpbtn = false;
void setup() {
  Serial.begin(115200);
  pinMode(PBTN_PIN, INPUT_PULLUP);
  for (int seg : segments) pinMode(seg, OUTPUT);
}
void displayNumber(int num) {
  const uint8_t segmentMap[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
  for (int i = 0; i < 7; i++) digitalWrite(segments[i], (segmentMap[num] >> i) & 0x01);
}
void loop() {
  if ((pbtn = digitalRead(PBTN_PIN)) == LOW && anpbtn == HIGH) displayNumber(count = (count + 1) % 10), Serial.println(count);
  anpbtn = pbtn;
}