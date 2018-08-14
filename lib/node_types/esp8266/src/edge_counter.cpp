// edge_counter.cc

// Important to include Functional Interrupt as else it does not allow to 
// define a class-based (object specific) interrupt
#include <FunctionalInterrupt.h>
#include "edge_counter.h"


void Edge_Counter::count(void) {
    if(counter < ULNOIOT_MAX_TRIGGER)
        counter++;
    else counter = 0;
    triggered = true;
}

void Edge_Counter::reinit() {
    if(_pull_up) {
        pinMode(_pin, INPUT_PULLUP);
    } else {
        pinMode(_pin, INPUT);
    }
    measure();
}

Edge_Counter::Edge_Counter(const char* name, int pin, bool rising, bool falling) :
    Device(name) {
    _pin = pin;
    _rising = rising;
    _falling = falling;
    add_subdevice(new Subdevice(""));
    reinit();
        int mode;
    if(_falling) {
        if(_rising) mode = CHANGE;
        else mode = FALLING;
    } else { // not falling
        if(_rising) mode = RISING;
        else mode = 0;
    }
    attachInterrupt(digitalPinToInterrupt(_pin), [&] () { count(); }, mode); 
}


bool Edge_Counter::measure() {
    bool measured = false;
    noInterrupts();
    if(triggered) {
        measured = true;
        triggered = false;
        measured_value().from(counter);
    }
    interrupts();
    return measured;
}
