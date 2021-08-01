#include <Arduino.h>

// Mapeamento de hardware
#define RED 6
#define GREEN 3
// #define BLUE 5
#define BUTTON 3

// Define nome para as cores utilizadas
#define red 0xff0000
#define yellow 0xffff00
#define green 0x00ff00

// Colocar as cores num vetor para iterar
long int signalSequence[3] = {red, yellow, green};
unsigned long timePressed[3] = {1000, 100, 1000};
unsigned long timeNotPressed[3] = {2000, 200, 2000};
unsigned long indexSequence = 0;

// Acumula a cor a ser utilizada
long int signal = red;

void state(long int color, unsigned long *tempoptr);

// Variáveis para contar tempo
unsigned long tempo0 = 0, tempo1 = 0, delayTime = 0;
unsigned long *ptr = &tempo0;

void setup() {
  // Associa o botão com o pino de entrada
  pinMode(BUTTON, INPUT_PULLUP);
  // Coloca as portas de pwm como saída
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  // pinMode(BLUE, OUTPUT);
}

void loop() {
  // Faz uma leitura do tempo
  tempo1 = millis();
  if (tempo1 > tempo0 + delayTime) {
    // Alterna o valor a ser iterado
    indexSequence = (++indexSequence > 2) ? 0 : indexSequence;
    if (digitalRead(BUTTON)) {
      delayTime = timePressed[indexSequence];
      signal = signalSequence[indexSequence];
    } else {
      delayTime = timeNotPressed[indexSequence];
      signal = signalSequence[indexSequence];
    }
    state(signal, ptr);
  }
  // Pass
}

void state(long int color, unsigned long *tempoptr) {
  analogWrite(RED, (color & 0xff0000) >> 16);
  analogWrite(GREEN, (color & 0x00ff00) >> 8);
  // analogWrite(BLUE, (color &0x0000ff));

  // Começa a contar o tempo.
  *tempoptr = millis();
}
