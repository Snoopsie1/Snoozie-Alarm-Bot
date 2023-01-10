#include <Arduino.h>
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#define pwmMotorA D1
#define pwmMotorB D2
#define dirMotorA D3
#define dirMotorB D4
#define playFeature D5
// - - - - - - - - - - - - - - - - - - - - Props - - - - - - - - - - - - - - - - - - - -
int motorSpeed = 750;
int targetHour = 21;
int targetMin = 55;
const char *ssid     = ". . . . .";
const char *password = ". . . . .";

const long utcOffsetInSeconds = 3600;

WiFiUDP ntpUDP; //User Datagram Protocol
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds); // Network Time Protocol
// - - - - - - - - - - - - - - - - - - - - SET UP - - - - - - - - - - - - - - - - - - - -
void setup()
{
  Serial.begin(9600);
  // Init Wifi
  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }
  // Init Time
  timeClient.begin();
  // Init LED
  pinMode(LED_BUILTIN, OUTPUT);
  // Init Motors
  pinMode(pwmMotorA, OUTPUT);
  pinMode(pwmMotorB, OUTPUT);
  pinMode(dirMotorA, OUTPUT);
  pinMode(dirMotorB, OUTPUT);
  Serial.println("Motor SHield 12E Initialized");
  // Init PlaySound
  pinMode(playFeature, OUTPUT);
  Serial.println("ISD1820 Playback Module Initialized");
}
// - - - - - - - - - - - - - - - - - - - - Methods - - - - - - - - - - - - - - - - - - - -
void motorForward()
{
  // Activates A (Left Wheel)
  digitalWrite(pwmMotorA, motorSpeed);
  digitalWrite(dirMotorA, LOW);
  // Activates B (Right Wheel)
  digitalWrite(pwmMotorB, motorSpeed);
  digitalWrite(dirMotorB, LOW);
  // Noise OFF
  digitalWrite(playFeature, LOW);
}

void motorReverse()
{
  // Reverses A (Left Wheel)
  digitalWrite(dirMotorA, HIGH);
  // Reverses B (Right Wheel)
  digitalWrite(dirMotorB, HIGH);
  // Noise On
  digitalWrite(playFeature, HIGH);
}

void turnRight()
{
  // Stops A (Left Wheel)
  digitalWrite(pwmMotorA, 0);
  // Activates B (Right Wheel)
  digitalWrite(pwmMotorB, motorSpeed);
  digitalWrite(dirMotorB, LOW);
}

void turnLeft()
{
  // Activates A (Left Wheel)
  digitalWrite(pwmMotorA, motorSpeed);
  digitalWrite(dirMotorA, LOW);
  // Stops B (Right Wheel)
  digitalWrite(pwmMotorB, 0);
}
void motorStop()
{
  digitalWrite(pwmMotorA, 0);
  digitalWrite(pwmMotorB, 0);
}
// - - - - - - - - - - - - - - - - - - - - Loop - - - - - - - - - - - - - - - - - - - -
void loop()
{
  timeClient.update();
  if (timeClient.getHours() == targetHour && timeClient.getMinutes() == targetMin)
  {
    motorForward();
    delay(1000);
    motorReverse();
    delay(1000);
  }
  else
  {
    motorStop();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    Serial.print(timeClient.getHours());
    Serial.print(":");
    Serial.print(timeClient.getMinutes());
    Serial.println("");
  }
}
