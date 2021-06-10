// Indoor Wind Chimes
// Matthew E. Dugal
// 2021-06-09

const int DevicePinLed = 13;
const int DevicePinSensor = 3;
const int DevicePinFan = 5;

// Current physical device has 2 magnets
// One physical rotation of the anemometer causes 4 state changes
// 4 state changes in 1 second = 60 RPM
unsigned long StateChangeMultiplier = 15;

// The threshold at which the output (led and fan) will turn on
// Any activity on input should be translated to output
// This seems to work quite well with the weather here
unsigned long RpmThreshold = 15;

unsigned long StateChangeCount = 0;
unsigned long CalculatedRpm = 0;

unsigned long StartTime = 0;
unsigned long CurrentTime = 0;
unsigned long MicrosPassed = 0;

bool CurrentState = false;
bool PreviousState = false;

void setup()
{
  pinMode(DevicePinLed, OUTPUT);
  pinMode(DevicePinSensor, INPUT);
  pinMode(DevicePinFan, OUTPUT);

  Serial.begin(9600);

  // Set fan and led to ON for 5 seconds at startup
  digitalWrite(DevicePinLed, HIGH);
  digitalWrite(DevicePinFan, HIGH);
  delay(5000);
  digitalWrite(DevicePinLed, LOW);
  digitalWrite(DevicePinFan, LOW);
}

void loop()
{
  StartTime = micros();
  CurrentTime = micros();
  MicrosPassed = 0;

  StateChangeCount = 0;
  CurrentState = digitalRead(DevicePinSensor);
  PreviousState = CurrentState;

  // Loop for 1 second, checking for state changes along the way
  // Using this method, the lowest recordable value is 15 RPM
  // This is plenty enough resolution for the purpose of this device
  while (MicrosPassed < 1000000)
  {
    CurrentState = digitalRead(DevicePinSensor);

    if (CurrentState != PreviousState)
    {
      StateChangeCount ++;
    }

    PreviousState = CurrentState;

    CurrentTime = micros();

    // Every 70 minutes, micros() will overflow back to zero
    // This rollover will cause issues with this inner loop
    // At worst, this method cause loop to run for 2 seconds instead of 1
    if (CurrentTime < StartTime)
    {
      StartTime = 0;
    }

    MicrosPassed = CurrentTime - StartTime;
  }

  CalculatedRpm = StateChangeCount  * StateChangeMultiplier;

  Serial.print(CalculatedRpm);
  Serial.println(" RPM");

  if (CalculatedRpm > RpmThreshold)
  {
    digitalWrite(DevicePinLed, HIGH);
    digitalWrite(DevicePinFan, HIGH);
  }
  else
  {
    digitalWrite(DevicePinLed, LOW);
    digitalWrite(DevicePinFan, LOW);
  }

  delay(10);
}
