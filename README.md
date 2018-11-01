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

# Build / Install

This follows the standard autotools build process. 

## Prerequisites

The following packages are prerequisites for building/using this project

    automake
    libncurses5-dev
    pigpio
    build-essential

Once you have those packages installed (they should each be available from
the standard debian base), the utility can be build by running

    ./configure
    make

Personally I don't like putting my own written/built applications under /usr, 
or even /usr/local, so I generally prefer to put them in a bin subdirectory
of my home directory, which I export to the PATH on login.

    if [[ ! -e ~/bin ]]; then
      mkdir ~/bin
    fi
    cp src/servo_controller ~/bin/
    echo 'export PATH="${PATH}:~/bin"' >>~/.bashrc

This way, I don't clobber anyone elses environment
