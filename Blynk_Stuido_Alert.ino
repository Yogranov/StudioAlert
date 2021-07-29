
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "0000000000000000000000000000000";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "SSID";
char pass[] = "PASSWORD";

const int sensorA = 14;
const int sensorB = 4;

int buttonStateA = 0;
int buttonStateB = 0;
int Status = 0;

BLYNK_WRITE(V8)
{
  if (param.asInt())
    Status = 1;
  else
    Status = 0;
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(sensorA, INPUT);
  pinMode(sensorB, INPUT);

  Blynk.begin(auth, ssid, pass);
  Blynk.virtualWrite(V8, 0);
  Blynk.syncVirtual(V8);
}

void loop()
{
  Blynk.run();
  buttonStateA = digitalRead(sensorA);
  buttonStateB = digitalRead(sensorB);
  if (Status && (buttonStateA == 1 || buttonStateB == 1))
  {
    Blynk.notify("Studio Alert!!");
    buttonStateA = 0;
    buttonStateB = 0;
    delay(5000);
  }
}
