// Your pins will probably be different .
// Remember that analog pins (A0 , A1 , ...) can also act as digital
const byte ANODE_PINS [8] = {9,2,3,5,7,8,4,6};
const byte CATHODE_PINS [8] = {11,10,A1,A0,A3,A5,A4,A2};

void setup() {
  // put your setup code here, to run once:
  for(byte i = 0; i < 8; i++) {
    pinMode(ANODE_PINS[i], OUTPUT);
    pinMode(CATHODE_PINS[i], OUTPUT);
    digitalWrite(ANODE_PINS[i], HIGH);
    digitalWrite(CATHODE_PINS[i], HIGH); 
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for ( byte aNum = 0; aNum < 8; aNum ++) {
    // TODO : Turn "on" the anode (+) wire ( high or low ?)
    // You can get the pin name with ANODE_PINS [ pNum ] , and pass
    // that to digitalWrite .
    digitalWrite(ANODE_PINS[aNum], LOW);
    
    
    for ( byte cNum = 0; cNum < 8; cNum ++) {
    // TODO : Turn "on" the cathode ( -) wire ( high or low ?)
    // Again , you can get the pin with CATHODE_PINS [ nNum ]
    // TODO : Wait a little while
    // TODO : Turn " off " the cathode ( -) wire
         digitalWrite(CATHODE_PINS[cNum], LOW);
         delay(500);
         digitalWrite(CATHODE_PINS[cNum], HIGH);

    }
    digitalWrite(ANODE_PINS[aNum], HIGH);
    // TODO : Turn "off " the anode (+) wire
  }
}
