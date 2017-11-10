/* LED cube test code
 *
 * Reads (x,y,z) co-ordinates from the Serial Monitor and toggles the state of
 * the LED at that co-ordinate. The co-ordinates are specified as "x y z", e.g.
 * "1 2 2", followed by a newline. Invalid co-ordinates are rejected.
 *
 * You need to fill in all the places marked TODO.
 *
 * == Setting up the Serial Monitor ==
 * The Serial Monitor must be configured (bottom-right corner of the screen) as:
 *   - Newline (for the line ending)
 *   - Baud rate 115200
 *
 * ENGR 40M
 * July 2017
 */

// Arrays of pin numbers. Fill these in with the pins to which you connected
// your anode (+) wires and cathode (-) wires. Hint: if you order these
// intelligently, it will make your mapping getLEDState() function a lot
// simpler!
const byte ANODE_PINS[8] = {9,2,3,5,7,8,4,6};
const byte CATHODE_PINS[8] = {11,10,A1,A0,A3,A5,A4,A2};
const byte BIG_MAP[8][8][3] = {
  {{0,0,0},{1,0,0},{2,0,0},{3,0,0},{0,0,1},{1,0,1},{2,0,1},{3,0,1} },
  {{0,1,0},{1,1,0},{2,1,0},{3,1,0},{0,1,1},{1,1,1},{2,1,1},{3,1,1} },
  {{0,2,0},{1,2,0},{2,2,0},{3,2,0},{0,2,1},{1,2,1},{2,2,1},{3,2,1} },
  {{0,3,0},{1,3,0},{2,3,0},{3,3,0},{0,3,1},{1,3,1},{2,3,1},{3,3,1} },
  {{0,0,3},{1,0,3},{2,0,3},{3,0,3},{0,0,2},{1,0,2},{2,0,2},{3,0,2} },
  {{0,1,3},{1,1,3},{2,1,3},{3,1,3},{0,1,2},{1,1,2},{2,1,2},{3,1,2} },
  {{0,2,3},{1,2,3},{2,2,3},{3,2,3},{0,2,2},{1,2,2},{2,2,2},{3,2,2} },
  {{0,3,3},{1,3,3},{2,3,3},{3,3,3},{0,3,2},{1,3,2},{2,3,2},{3,3,2} }
};

void setup()
{
  // Make all of the anode (+) wire and cathode (-) wire pins outputs
  for (byte i = 0; i < 8; i++) {
    pinMode(ANODE_PINS[i], OUTPUT);
    pinMode(CATHODE_PINS[i], OUTPUT);
    digitalWrite(ANODE_PINS[i], HIGH);
    digitalWrite(CATHODE_PINS[i], HIGH); 
  }
  // TODO: turn "off" all the LEDs (hint: you'll need a for loop)^^

  // Initialize serial communication
  // (to be read by Serial Monitor on your computer)
  Serial.begin(115200);
  Serial.setTimeout(100);
}

/* Function: getLEDState
 * ---------------------
 * Returns the state of the LED in a 4x4x4 pattern array, each dimension
 * representing an axis of the LED cube, that corresponds to the given anode (+)
 * wire and cathode (-) wire number.
 *
 * This function is called by display(), in order to find whether an LED for a
 * particular anode (+) wire and cathode (-) wire should be switched on.
 */
inline byte getLEDState(byte pattern[4][4][4], byte aNum, byte cNum)
{
  // TODO: fill this in to return the value in the pattern array corresponding
  // to the anode (+) wire and cathode (-) wire number (aNum and cNum) provided.
  int anodeIndex = aNum;
  int cathodeIndex = cNum;

  int xVal = BIG_MAP[aNum][cNum][0];
  int yVal = BIG_MAP[aNum][cNum][1];
  int zVal = BIG_MAP[aNum][cNum][2];
  return pattern[xVal][yVal][zVal];
}

/* Function: display
 * -----------------
 * Runs through one multiplexing cycle of the LEDs, controlling which LEDs are
 * on.
 *
 * During this function, LEDs that should be on will be turned on momentarily,
 * one row at a time. When this function returns, all the LEDs will be off
 * again, so it needs to be called continuously for LEDs to be on.
 */
void display(byte pattern[4][4][4])
{
  for (byte aNum = 0; aNum < 8; aNum++) { // iterate through anode (+) wires

    // Set up all the cathode (-) wires first
    for (byte cNum = 0; cNum < 8; cNum++) { // iterate through cathode (-) wires
      byte value = getLEDState(pattern, aNum, cNum); // look up the value

      // TODO: Activate the cathode (-) wire if `value` is > 0, otherwise deactivate it
      // Hint: Use digitalWrite() on CATHODE_PINS[cNum] (the cNum-th cathode (-) wire pin)
      if(value>0){
        digitalWrite(CATHODE_PINS[cNum],LOW);
      }else{
        digitalWrite(CATHODE_PINS[cNum],HIGH);
      }
    }

    // TODO: Activate the anode (+) wire (without condition)
    // Hint: Use digitalWrite() on ANODE_PINS[aNum] (the aNum-th anode (+) wire pin)
    digitalWrite(ANODE_PINS[aNum],LOW);

    // TODO: Wait a short time
    // Hint: delayMicroseconds() might be useful
    delayMicroseconds(100);

    // TODO: We're now done with this row, so deactivate the anode (+) wire
    digitalWrite(ANODE_PINS[aNum],HIGH);


  }
}

void loop()
{
  static byte ledPattern[4][4][4]; // 1 for on, 0 for off

  byte x = 0;
  byte y = 0;
  byte z = 0;
  static char message[60];

  if (Serial.available()) {
    // Parse the values from the serial string
    x = Serial.parseInt();
    y = Serial.parseInt();
    z = Serial.parseInt();

    // Check for input validity
    if (Serial.read() != '\n') {
      Serial.println("invalid input - check that line ending is set to \"Newline\"; input must be three numbers");
      return;
    }
    if (x < 0 || x > 3 || y < 0 || y > 3 || z < 0 || z > 3) {
      sprintf(message, "x = %d, y = %d, z = %d -- indices out of bounds", x, y, z);
      Serial.println(message);
      return;
    }

    // Print to Serial Monitor to give feedback about input
    sprintf(message, "x = %d, y = %d, z = %d", x, y, z);
    Serial.println(message);

    // Toggle the LED state
    ledPattern[x][y][z] = !ledPattern[x][y][z];
  }

  // This function gets called every loop
  display(ledPattern);
}

