// Code pour l'arduino servant à la communication avec l'électrovane.

const byte pwm0pin = 11;  // Ouput digital pin number

// This is the maximum PWM value and means the PWM frequency is around 244Hz.
// Reducing this value will increase the PWM frequency and reduce the number of steps
const uint16_t MAX_PWM_VALUE = 65535U;

String shitBucket;

boolean newData = false;

unsigned int dataNumber = 0; 


//----------------------------------------------------------------------------------------------------
void setup() {
  //Setup Serial at baud rate 9600 for both serial ports
  Serial.begin(9600);
  Serial1.begin(9600);
  //Serial.println("Starting...");
  //Init PWM to 16 bits instead of 8 bits
  initPWM();
}

//----------------------------------------------------------------------------------------------------
void loop() {
  //Read serial and update
  readNUpdate();
}

//----------------------------------------------------------------------------------------------------

void readNUpdate() {   
    if (Serial.available() > 0) {
      //If serial is available, update PWM and send "I read the value: *value, next."
        Serial1.print("I read ");
        //shitBucket = Serial.readString();
        shitBucket = Serial.readStringUntil('\r');
        newData = true;
        //Update PWM output
        updateOutput();
        Serial1.print("the value: ");
        Serial1.print(shitBucket);
        Serial1.println(", next.");
    }
}

//----------------------------------------------------------------------------------------------------

void updateOutput() {
    if (newData == true) {
        dataNumber = 0;
        //Serial.println(shitBucket);
        //Cast string to integer
        dataNumber = shitBucket.toInt();
        //Serial.println(dataNumber);
        //Write PWM to the digital output.
        setPWM(0, dataNumber);
        newData = false;
    }
}


//----------------------------------------------------------------------------------------------------
// Setup timers for 16 bit PWM signal instead of regular 8 bits
void initPWM() {
    noInterrupts();
    TCCR1A = 1 << WGM11 | 1 << COM1A1 | 1 << COM1B1; // set on top, clear OC on compare match
    TCCR1B = 1 << CS10  | 1 << WGM12 | 1 << WGM13;   // clk/1, mode 14 fast PWM
    ICR1 = MAX_PWM_VALUE;
    interrupts();
    pinMode(pwm0pin, OUTPUT);
  }

//----------------------------------------------------------------------------------------------------
// Set a 16 bit PWM value for a channel
void setPWM(byte no, uint16_t pwm) {
    noInterrupts();
    switch (no) {
        case 0 :
          OCR1A = pwm;
          break;
        case 1 :
          OCR1B = pwm;
          break;
      }
    interrupts();
  }
