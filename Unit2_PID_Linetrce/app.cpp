#include "app.h"
#include <stdio.h>

#include "Tracer.h"
#include "ForceSensor.h"
#include "Clock.h"  

Tracer tracer;
Clock clock;


using namespace spikeapi;

void tracer_task(intptr_t exinf) {
  tracer.run();
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

