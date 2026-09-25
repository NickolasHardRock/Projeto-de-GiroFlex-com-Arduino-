// Giroflex policial - LEDs alternados + sirene sweep (não bloqueante)
// LEDs: pinos 3 e 4
// Buzzer passivo: pino 5

const int LED1 = 3;
const int LED2 = 4;
const int BUZZER = 5;

// giroflex
unsigned long lastLedToggle = 0;
unsigned long ledInterval = 120; // ms entre alternâncias (menor = mais rápido)
bool ledState = false;

// sirene sweep
unsigned long sirenStart = 0;
const unsigned long SIREN_PERIOD = 1800; // ms para ciclo completo sobe+desce
const int FREQ_MIN = 700;   // Hz
const int FREQ_MAX = 2200;  // Hz

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  noTone(BUZZER);
  sirenStart = millis();
  lastLedToggle = millis();
}

void loop() {
  unsigned long now = millis();

  // Giroflex: alterna LEDs
  if (now - lastLedToggle >= ledInterval) {
    lastLedToggle = now;
    ledState = !ledState;
    digitalWrite(LED1, ledState ? HIGH : LOW);
    digitalWrite(LED2, ledState ? LOW : HIGH);
  }

  // Sirene: calcula frequência com função triangular (sobe e desce)
  unsigned long t = (now - sirenStart) % SIREN_PERIOD;
  float phase = (float)t / (float)SIREN_PERIOD; // 0..1
  float tri = (phase < 0.5) ? (phase * 2.0) : ((1.0 - phase) * 2.0);
  int freq = (int)(FREQ_MIN + tri * (FREQ_MAX - FREQ_MIN));

  // Toca nota curta para permitir atualização contínua
  tone(BUZZER, freq, 30);
  // sem delay() para manter não bloqueante
}
