# `servo_controller`

This project provides/creates the program `servo_controller`, which
allows for the basic motion control of a (standard)-ish servo motor.

It is a simple nCurses UI, which represents the position of the 
servo hat as a cursor in the center of a "bar", in the middle of the
screen. The arrow keys (left and right) move the servo hat in
either direction.

# startup

On initialization, the position of the servo-hat is always set to
50% (1500). This *should* be a safe value, but no guarantee is made
by me (the author) for the safety of your servo. 

I assume no responsibility, and the code provided in this project
is provided as-is, with no warrantee or guarantee to its fitness
for any particular purpose
