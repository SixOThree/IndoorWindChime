# IndoorWindChime
This is the Arduino code for the hobby project Indoor Wind Chime.

This project consists of an indoor wind chime device controlled by an Adafruit Metro Mini connected to an outdoor anemometer measuring the wind speed using a hall effect sensor with magnets.

The method of RPM calculation is as follows:
Two magnets on the anemometer cause a hall efect monitor to change state four times per rotation
The number of state changes during a second is captured
The RPM value is extrapolated from the number of state changes during this one second
If the RPM value passes a threshold, the indoor wind chime fan is enabled
After a brief delay, this loop is repeated
If the RPM value again meets the threshold the fan will continue to stay on
After roughly 5 seconds of fan operation, the chimes will begin to ring
There is no rolling average or use of interupts to achieve a higher precision
The indoor wind chime device is not capable of performing brief bursts of activity
So this method fits the device quite perfectly
The result is pleasing and captures the outdoor weather well
