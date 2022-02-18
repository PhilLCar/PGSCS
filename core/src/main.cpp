#include <iostream>
#include <gauge.hpp>

int main(int argc, char *argv[]) {
  Gauge test = Gauge();

  test.setDescription(Gauge::ALTERNATIVE, Gauge::PMMC_RECTIFIER, Gauge::FULL_SCALE_READING, Gauge::VERTICAL, Gauge::RATED_2KV);
  test.setInput("V", 220.0, 0);
  test.setError(1.5, 1);
  test.setGauge("Hz", 40.0, 70.0, 0.0, 60.0, 2.0, 4.0, 10.0, 0);

  test.makeSVG("html/gauges/test.svg");

  return 0;
}