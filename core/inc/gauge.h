#ifndef GAUGE_CORE
#define GAUGE_CORE

#include <string>

#include <conf.h>

class Gauge {
public:
  enum Current {
    DIRECT = 0,
    ALTERNATIVE
  };

  enum Principle {
    PMMC = 0,
    PMMC_RECTIFIER,
    PMMC_RADIOMETER,
    PMMC_RADIOMETER_RECTIFER,
    MOVING_IRON,
    VIBRATING_REED,
    ELECTRODYNAMIC_IRONLESS,
    ELECTRODYNAMIC_RADIOMETER,
    FERRODYNAMIC,
    FERRODYNAMIC_RADIOMETER,
    ELECTROSTATIC,
    INDUCTION
  };

  enum Error {
    VALUE = 0,
    SPAN,
    VALUE_FISCAL,
    FULL_SCALE_READING
  };

  enum Mount {
    VERTICAL = 0,
    HORIZONTAL,
    ANGLED
  };

  enum Rating {
    EXEMPT = 0,
    RATED_500V,
    RATED_2KV,
    RATED_5KV
  };

public:
  Gauge(ConfigurationFile& file, const std::string &gauge);
  Gauge(ConfigurationFile& file, const char *gauge);

public:
  void makeSVG(const char *filename);

private:
  std::string getSymbolSVG(const char *filename, const char *replace);
  std::string getCurrentType();
  std::string getPrinciple();
  std::string getError();
  std::string getMount();
  std::string getRating();
  std::string getInputValue();
  std::string getGaugeMarkings();
  std::string getUnits();

private:
  Current     current;
  Principle   principle;
  Error       error;
  Mount       mount;
  Rating      rating;
  const char *inputUnits;
  const char *gaugeUnits;
  double      inputMax;
  double      gaugeError;
  double      gaugeMin;
  double      gaugeMax;
  double      gaugeOffset;
  double      minorIncrement;
  double      mediumIncrement;
  double      majorIncrement;
  double      setValue;
  double      minZone;
  double      maxZone;
  int         angle;
  int         inputPrecision;
  int         errorPrecision;
  int         gaugePrecision;
};

#endif