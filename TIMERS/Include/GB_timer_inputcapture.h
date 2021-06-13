#ifndef GB_TIMER_INPUTCAPTURE_H_
#define GB_TIMER_INPUTCAPTURE_H_

//variables which stores the timer/counter value on capturing the event
uint32_t gb_a,gb_b,gb_c,gb_bx,gb_cx;        //range 0-65535

void GB_timerinputcapture();

#include "GB_timer_inputcapture.cpp"


#endif


