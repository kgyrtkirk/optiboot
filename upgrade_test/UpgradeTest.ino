// optiboot-service upgrade test

void setup() {
	Serial.begin(115200);
	Serial.print(F(__FILE__));
	// initialize digital pin 13 as an output.
	pinMode(13, OUTPUT);
}

void loop() {
	digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
	delay(100);              // wait for a second
	digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
	delay(100);              // wait for a second
}
