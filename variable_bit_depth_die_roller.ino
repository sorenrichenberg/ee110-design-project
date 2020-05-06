int roll;
int bitDepth = 8; 

void setup() {
  // pins 3 4 5 are RGB output
  // pins 6 7 8 9 10 11 12 13 are binary output
  for (int pin = 3; pin < 14; ++pin) {
    pinMode(pin, OUTPUT);
  }
  
  // pins A0 A1 increment/decrement bitDepth
  // pin A2 initiates a roll
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  
  // represent current bitDepth
  // bitdepth must be truncated to the 0-7 range
  setBits(3, 5, bitDepth - 1);
}


void loop() {
  if (analogRead(A2)) { // roll button is pressed
    // debounce
    delay(500);
    
    // generate roll output between 0 and (2 ^ bitDepth)
    roll = random( twoToThe(bitDepth) );
    
    // set binary output
    setBits(6, 13, roll);
    
  } else if (analogRead(A0)) { // increment button is pressed
    // debounce
    delay(500);
    
    // increment
    incBitDepth();
    
    // set RGB pins
    setBits(3, 5, bitDepth - 1);
   
  } else if (analogRead(A1)) { // decrement button is pressed
    // debounce? 
    delay(500);
    
    // decrement
    decBitDepth();
   
    // set RGB pins
    setBits(3, 5, bitDepth - 1);
  }
  
}

int twoToThe(int exponent) {
  // left-shift 1 to get powers of 2
  return 1 << exponent;
}

void incBitDepth() {
  // I don't like either of these increment/decrement functions,
  // but I want to remove this control structure from loop() 
  // while keeping the calculation simple.
  if (bitDepth >= 8) { // overflow at 8
    bitDepth = 1;
  } else {
    bitDepth++;
  }
  
}

void decBitDepth() {
  
  if (bitDepth <= 1) { // overflow at 1
    bitDepth = 8;
  } else {
    bitDepth--;
  }
  
}

void setBits(int startPin, int endPin, int value) {
  
  // initialize all outputs
  for (int currentPin = startPin; currentPin <= endPin; ++currentPin) {
    digitalWrite(currentPin, LOW);
  }
  
  // calculate the most significant bit
  int mostSignificantBit = twoToThe(endPin - startPin);
  
  // turn on set bits
  for (int currentPin = startPin; currentPin <= endPin; ++currentPin) {
    
    if (value & mostSignificantBit) {
      digitalWrite(currentPin, HIGH);
    }
    
    mostSignificantBit >>= 1;
  }
  
}

  
