//Pin connected to ST_CP of 74HC595
int latchPin = 8;
//Pin connected to SH_CP of 74HC595
int clockPin = 12;
////Pin connected to DS of 74HC595
int dataPin = 11;
int multiplexerDelay = 10;
const int analogInPin = A0; 
int rateValue = 0;

void setup() {
	Serial.begin(9600);
//set pins to output so you can control the shift register
	pinMode(latchPin, OUTPUT);
	pinMode(clockPin, OUTPUT);
	pinMode(dataPin, OUTPUT);
}
void loop() {
// count from 0 to 255 and display the number
// on the LEDs
	rateValue = analogRead(analogInPin);
	
  // map it to the range of the analog out:
  	multiplexerDelay = map(rateValue, 0, 1023, 0, 10);
Serial.println(multiplexerDelay);
	for (int numberToDisplay = 0; numberToDisplay < 8; numberToDisplay++) {
	// take the latchPin low so
		// the LEDs don't change while you're sending in bits:
		digitalWrite(latchPin, LOW);
		// shift out the bits:
		shiftOut(dataPin, clockPin, MSBFIRST, 1 << numberToDisplay);
		//take the latch pin high so the LEDs will light up:
		digitalWrite(latchPin, HIGH);
		// pause before next value:
	delay(multiplexerDelay);
	}
}