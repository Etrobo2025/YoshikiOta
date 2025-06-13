#include "app.h" // <1>
#include <stdio.h>

#include "Tracer.h" // <2>
#include "ForceSensor.h" // <3>
#include "Clock.h"  

Tracer tracer;  // <4>
Clock clock;    // <5>


using namespace spikeapi;

void tracer_task(intptr_t exinf) { // <1>
  tracer.run(); // <2>
  ext_tsk();
}

void main_task(intptr_t unused) {
  const uint32_t duration = 100*1000;
  ForceSensor forceSensor(EPort::PORT_D);

  tracer.init();
  sta_cyc(TRACER_CYC);
  
  while (!forceSensor.isTouched()) {
      clock.sleep(duration);
  }

  stp_cyc(TRACER_CYC);
  tracer.terminate();
  ext_tsk();
}

