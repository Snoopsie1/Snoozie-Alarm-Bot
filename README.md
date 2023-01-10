# Snoozie-Alarm-Bot
Snoozie the Alarm-Clock Bot is a 2 wheel drive robot built with a round 
chasis, 4 batteries, a playback module and an NodeMCU(ESP8266) on a 
NodeMCU Lua Wifi Motor Shield Board.

The code here is Snoozies final script.
It's does the following:
- Initializes Network Connectivity to the specifically assigned SSID and 
PASSWORD
- Initializes the Network Time Protocol Client with a User Datagram 
Protocol.
- Initializes Motors
- Initializes Playback
- Has a loop that checks for specified hour and minute. If the specified 
hour and minute has been returned from the timeClient's methods, then the 
robot will start to drive around the room, slam it's support wheel and 
make an annoying sound, until turned off.

Why did I make this project?
I am really bad at getting out of bed.
