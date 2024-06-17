#include <ezButton.h>  // The library to use for SW pin

#define CLK_PIN 2 // The Arduino Nano pin D2 connect to the pin CLK of the rotary encoder
#define DT_PIN  3 // The Arduino Nano pin D3 connect to the pin DT of the rotary encoder
#define SW_PIN  4 // The Arduino Nano pin D4 connect to the pin SW of the rotary encoder

#define DIRECTION_CW 0   // clockwise direction
#define DIRECTION_CCW 1  // anticlockwise direction

volatile int counter = 0;
volatile int direction = DIRECTION_CW;
volatile unsigned long last_time;  // for debouncing
int prev_counter;

ezButton button(SW_PIN);

void INTERRUPT_handler() {
  if ((millis() - last_time) < 50)  // debounce time is 10ms
    return;

  if (digitalRead(DT_PIN) == HIGH) {
    // The encoder is rotating in anticlockwise direction => decrease the counter
    counter--;
    direction = DIRECTION_CCW;
  } else {
    // The encoder is rotating in clockwise direction => increase the counter
    counter++;
    direction = DIRECTION_CW;
  }

  last_time = millis();
}

void setup() {
  Serial.begin(9600);

  // Configure encoder pins as inputs
  pinMode(CLK_PIN, INPUT);
  pinMode(DT_PIN, INPUT);
  button.setDebounceTime(50);  // set debounce time to 50 milliseconds

  // use interrupt for CLK pin is enough
  // call INTERRUPT_handler() when CLK pin changes from LOW to HIGH
  attachInterrupt(digitalPinToInterrupt(CLK_PIN), INTERRUPT_handler, RISING);
}

void loop() {
  button.loop();  // MUST call the loop() function first

  if (prev_counter != counter) {
    Serial.print("Twisted direction: ");
    if (direction == DIRECTION_CW)
      Serial.print("CLOCKWISE");
    else
      Serial.print("ANTICLOCKWISE");

    Serial.print(" - counter: ");
    Serial.println(counter);

    prev_counter = counter;
  }

  if (button.isPressed()) {
    Serial.println("The button is pressed");
  }

  // TO DO: your other work here
}