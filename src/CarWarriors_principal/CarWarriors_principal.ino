#include "F1.h"
#include "F2.h"

bool Cam = false;

void setup() {
  setup_principal();

  Serial.begin(9600);
}

void loop() {
  
  if (Cam == false) {
    func_buttons();
  } else if (Cam == true) {
    digitalWrite(LED_BUILTIN, LOW);
  }

}
