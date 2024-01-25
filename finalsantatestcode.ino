/*#include <avr/power.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <avr/pgmspace.h>

#include "notes2.h"

#define SWITCH_PIN 0
#define SPEAKER_PIN 1
#define LED_PIN 13

#define BPM 100l
#define BEAT 4
#define NOTES_LEN 28

#define HALF_BEAT (BEAT / 2)
const uint16_t notes[2 * NOTES_LEN] PROGMEM = {
  // Jingle Bells melody
  NOTE_E3, BEAT / 2,
  NOTE_E3, BEAT / 2,
  NOTE_E3, HALF_BEAT / 2,
  NOTE_E3, BEAT / 2,
  NOTE_E3, BEAT / 2,
  NOTE_E3, HALF_BEAT / 2,
  NOTE_E3, BEAT / 2,
  NOTE_G3, BEAT / 2,
  NOTE_C3, BEAT / 2,
  NOTE_D3, BEAT / 2,
  NOTE_E3, HALF_BEAT / 2,
  NOTE_F3, BEAT / 2,
  NOTE_F3, BEAT / 2,
  NOTE_F3, BEAT / 2,
  NOTE_F3, BEAT / 2,
  NOTE_F3, HALF_BEAT / 2,
  NOTE_F3, BEAT / 2,
  NOTE_E3, BEAT / 2,
  NOTE_E3, BEAT / 2,
  NOTE_E3, BEAT / 2,
  NOTE_E3, HALF_BEAT / 2,
  NOTE_D3, BEAT / 2,
  NOTE_D3, BEAT / 2,
  NOTE_E3, BEAT / 2,
  NOTE_D3, HALF_BEAT / 2,
  NOTE_G3, BEAT / 2
};

void setup() {
  pinMode(SWITCH_PIN, INPUT);
  digitalWrite(SWITCH_PIN, HIGH);

  pinMode(LED_PIN, OUTPUT);
  pinMode(SPEAKER_PIN, OUTPUT);

  ADCSRA &= ~(1 << ADEN); // Turn off ADC
  ACSR |= _BV(ACD);        // Disable the analog comparator
}

void playRest(long duration, long beatDurationMillis) {
  noTone(SPEAKER_PIN);
  delay(duration * beatDurationMillis);
}

void playNote(long freq, long duration, long beatDurationMillis) {
  tone(SPEAKER_PIN, freq);
  digitalWrite(LED_PIN, HIGH);
  delay(4 * duration * beatDurationMillis / 5);
  noTone(SPEAKER_PIN);
  digitalWrite(LED_PIN, LOW);
  delay(duration * beatDurationMillis / 5);
}

void playSong() {
  long beatDurationMillis = (60l * 1000l) / (BPM * BEAT);
  for (int i = 0; i < NOTES_LEN; i++) {
    int note = i << 1;
    long freq = pgm_read_word_near(notes + note);
    long duration = pgm_read_word_near(notes + note + 1);

    if (freq == 0) {
      playRest(duration, beatDurationMillis);
    } else {
      playNote(freq, duration, beatDurationMillis);
    }
  }
}

void loop() {
  gotoSleep();

  // Wait for the button to be released
  while (digitalRead(SWITCH_PIN) == LOW) {}

  playSong();
  delay(200);
}

void gotoSleep() {
  GIMSK |= 1 << PCIE;   // Enable Pin Change Interrupt
  PCMSK |= 1 << PCINT0; // Watch for Pin Change on Pin5 (PB0)

  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_mode();

  // Waking up from sleep mode.
  sleep_disable();

  GIMSK &= ~(1 << PCIE); // Disable the interrupt so it doesn't keep flagging
  PCMSK &= ~(1 << PCINT0);
}

// Interrupt for PIN0 falling edge
ISR(PCINT0_vect) {}
*/


#include <avr/power.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <avr/pgmspace.h>

#define SWITCH_PIN 0
#define SPEAKER_PIN 1
#define LED_PIN 3

#define BPM 150l
#define BEAT 4
#define NOTES_LEN 28

#define HALF_BEAT (BEAT / 2)
#define NOTE_E5 659
#define NOTE_G5 784
#define NOTE_F5 698
#define NOTE_D5 587
#define NOTE_C5 523
const uint16_t notes[2 * NOTES_LEN] PROGMEM = {
  // Jingle Bells melody with adjusted frequencies and durations
  NOTE_E5, BEAT,
  NOTE_E5, BEAT,
  NOTE_E5, HALF_BEAT,
  NOTE_E5, BEAT,
  NOTE_E5, BEAT,
  NOTE_E5, HALF_BEAT,
  NOTE_E5, BEAT,
  NOTE_G5, BEAT,
  NOTE_C5, BEAT,
  NOTE_D5, BEAT,
  NOTE_E5, HALF_BEAT,
  NOTE_F5, BEAT,
  NOTE_F5, BEAT,
  NOTE_F5, BEAT,
  NOTE_F5, BEAT,
  NOTE_F5, HALF_BEAT,
  NOTE_F5, BEAT,
  NOTE_E5, BEAT,
  NOTE_E5, BEAT,
  NOTE_E5, BEAT,
  NOTE_E5, HALF_BEAT,
  NOTE_D5, BEAT,
  NOTE_D5, BEAT,
  NOTE_E5, BEAT,
  NOTE_D5, HALF_BEAT,
  NOTE_G5, BEAT
};

void setup() {
  pinMode(SWITCH_PIN, INPUT);
  digitalWrite(SWITCH_PIN, HIGH);

  pinMode(LED_PIN, OUTPUT);
  pinMode(SPEAKER_PIN, OUTPUT);

  ADCSRA &= ~(1 << ADEN); // Turn off ADC
  ACSR |= _BV(ACD);        // Disable the analog comparator
}

void playRest(long duration, long beatDurationMillis) {
  noTone(SPEAKER_PIN);
  delay(duration * beatDurationMillis);
}

void playNote(long freq, long duration, long beatDurationMillis) {
  tone(SPEAKER_PIN, freq);
  digitalWrite(LED_PIN, HIGH);
  delay(4 * duration * beatDurationMillis / 5);
  noTone(SPEAKER_PIN);
  digitalWrite(LED_PIN, LOW);
  delay(duration * beatDurationMillis / 5);
}

void playSong() {
  long beatDurationMillis = (60l * 1000l) / (BPM * BEAT);
  for (int i = 0; i < NOTES_LEN; i++) {
    int note = i << 1;
    long freq = pgm_read_word_near(notes + note);
    long duration = pgm_read_word_near(notes + note + 1);

    if (freq == 0) {
      playRest(duration, beatDurationMillis);
    } else {
      playNote(freq, duration, beatDurationMillis);
    }
  }
}

void loop() {
  gotoSleep();

  // Wait for the button to be released
  while (digitalRead(SWITCH_PIN) == LOW) {}

  playSong();
  delay(200);
}

void gotoSleep() {
  GIMSK |= 1 << PCIE;   // Enable Pin Change Interrupt
  PCMSK |= 1 << PCINT0; // Watch for Pin Change on Pin5 (PB0)

  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_mode();

  // Waking up from sleep mode.
  sleep_disable();

  GIMSK &= ~(1 << PCIE); // Disable the interrupt so it doesn't keep flagging
  PCMSK &= ~(1 << PCINT0);
}

// Interrupt for PIN0 falling edge
ISR(PCINT0_vect) {}
