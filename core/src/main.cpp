#include <iostream>
#include <gauge.h>

int main(int argc, char *argv[]) {
  ConfigurationFile conf("res/gauges.conf");
  Gauge frequency = Gauge(conf, "Frequency");
  Gauge rpm = Gauge(conf, "RPM");

  frequency.makeSVG("html/gauges/frequency.svg");

  rpm.makeSVG("html/gauges/rpm.svg");

  return 0;
}