## InfraRed-Tacho

### Idea behind the project
This project originated from a physics project of building a bycicle-tacho that counts individual spokes with IR, instead of rotations via magnet.

### How it works
An infrared-lever can detect if an object is in front of it. The code counts every object (in this case spokes) and calculates the time between them. To minimize errors, every objects starts a 5ms timer in which others are ignored. This is done to avoid accidentally detecting the same spoke twice or more when using poor quality sensors. Every 6 spokes, the saved times get averaged and printed to an LCD, along with the total amount of spokes that passed since the last reset. Both the debounce-time, as well as the amount of spokes that get averaged can be changed via a variable at the top of the program.
