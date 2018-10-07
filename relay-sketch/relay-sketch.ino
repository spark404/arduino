
#define PUSH_BUTTON_PIN 8
#define RELAY_1_PIN 2
#define RELAY_2_PIN 3
#define RELAY_3_PIN 4
#define RELAY_4_PIN 5
#define RELAY_5_PIN 6
#define RELAY_6_PIN 7

#define SHOW_DELAY 100

int relayPins[] = { RELAY_1_PIN, RELAY_2_PIN, RELAY_3_PIN, RELAY_4_PIN, RELAY_5_PIN, RELAY_6_PIN };

int state = 0;
int previousButtonState = 0;

void setup() {
  pinMode(PUSH_BUTTON_PIN, INPUT_PULLUP);

  for (int i = 0; i < 6; i++) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins, LOW);
    delay(SHOW_DELAY);
  }

  for (int i = 0; i < 6; i++) {
    digitalWrite(relayPins[i], HIGH);
    delay(SHOW_DELAY);
  }
  
  previousButtonState = digitalRead(PUSH_BUTTON_PIN);
}

void loop() {
    int buttonState = digitalRead(PUSH_BUTTON_PIN);
    if (previousButtonState != buttonState) {
      // Edge detected
      previousButtonState = buttonState;

      if (!buttonState) {
        state += 1;
        if (state > 6) {
          state = 0;
        }
        updateRelay();
      }
    }

  delay(50);
}

void updateRelay() {
  int relay = 0x3F >> state;

  for (int i = 0; i < 6; i++) {
    digitalWrite(relayPins[i], relay & (1 << 6 - (i +1) ));
  }
}
