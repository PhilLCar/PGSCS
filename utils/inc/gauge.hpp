#ifndef GAUGE_UTILS
#define GAUGE_UTILS

#include <string>

class Gauge {
public:
  enum Current {
    DIRECT,
    ALTERNATIVE
  };

  enum Principle {
    PMMC,
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
    VALUE,
    SPAN,
    VALUE_FISCAL,
    FULL_SCALE_READING
  };

  enum Mount {
    VERTICAL,
    HORIZONTAL,
    ANGLED
  };

  enum Rating {
    EXEMPT,
    RATED_500V,
    RATED_2KV,
    RATED_5KV
  };

public:
  void setDescription(Current current, Principle principle, Error error, Mount mount, Rating rating);
  void setInput(const char *inputUnits, double inputMax, int inputPrecision);
  void setError(double gaugeError, int errorPrecision);
  void setGauge(const char *gaugeUnits, double gaugeMin, double gaugeMax, double gaugeOffset, double setValue,
                double minorIncrement, double mediumIncrement, double majorIncrement, int gaugePrecision);
  
  void makeSVG(const char *filename);

private:
  std::string getSymbolSVG(const char *filename, const char *replace);
  std::string getCurrentType();
  std::string getPrinciple();
  std::string getError();

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
  int         inputPrecision;
  int         errorPrecision;
  int         gaugePrecision;
};

#endif