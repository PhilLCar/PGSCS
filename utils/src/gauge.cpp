#include <gauge.hpp>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <regex>

static const char* HEADER = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n\
<svg version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" width=\"100%\" height=\"100%\" viewBox=\"0 0 400 400\">\n\
  <rect width=\"100%\" height=\"100%\" fill=\"white\"/>\n";
static const char* FOOTER = "</svg>\n";

void Gauge::setDescription(Current current, Principle principle, Error error, Mount mount, Rating rating) {
  this->current   = current;
  this->principle = principle;
  this->error     = error;
  this->mount     = mount;
  this->rating    = rating;
}

void Gauge::setInput(const char *inputUnits, double inputMax, int inputPrecision) {
  this->inputUnits     = inputUnits;
  this->inputMax       = inputMax;
  this->inputPrecision = inputPrecision;
}

void Gauge::setError(double gaugeError, int errorPrecision) {
  this->gaugeError     = gaugeError;
  this->errorPrecision = errorPrecision;
}

void Gauge::setGauge(const char *gaugeUnits, double gaugeMin, double gaugeMax, double gaugeOffset, double setValue,
                     double minorIncrement, double mediumIncrement, double majorIncrement, int gaugePrecision) {
  this->gaugeUnits      = gaugeUnits;
  this->gaugeMin        = gaugeMin;
  this->gaugeMax        = gaugeMax;
  this->gaugeOffset     = gaugeOffset;
  this->setValue        = setValue;
  this->minorIncrement  = minorIncrement;
  this->mediumIncrement = mediumIncrement;
  this->majorIncrement  = majorIncrement;
  this->gaugePrecision  = gaugePrecision;
}

void Gauge::makeSVG(const char *filename) {
  std::ofstream file(filename, std::ios_base::out);

  if (file.is_open()) {
    file << HEADER;
    file << getCurrentType();
    file << getPrinciple();
    file << getError();

    file << FOOTER;
    file.close();
  }
}

//////////////////////////////////////////////////////////////////////////////////
std::string Gauge::getSymbolSVG(const char *filename, const char *replace) {
  std::ifstream svg(filename, std::ios_base::in);
  std::string   line;
  std::string   content;

  if (svg.is_open()) {
    std::getline(svg, line);
    std::getline(svg, line);

    while (!svg.eof()) {
      std::getline(svg, line);
      content += "  " + std::regex_replace(line, std::regex("%"), replace) + "\n";
    }

    svg.close();
  }

  return content;
}

std::string Gauge::getCurrentType() {
  std::string svg = "  <svg x=\"50\" y=\"1800\" viewport=\"0 0 100 150\" transform=\"scale(0.2 0.2)\">\n";
  switch (current) {
  case ALTERNATIVE:
    svg += getSymbolSVG("utils/img/TAC.svg", NULL);
    break;
  case DIRECT:
    svg += getSymbolSVG("utils/img/TDC.svg", NULL);
    break;
  }
  return svg;
}

std::string Gauge::getPrinciple() {
  std::string svg = "  <svg x=\"160\" y=\"1800\" viewport=\"0 0 100 150\" transform=\"scale(0.2 0.2)\">\n";
  switch (principle) {
  case PMMC:
    svg += getSymbolSVG("utils/img/SMC.svg", NULL);
    break;
  case PMMC_RADIOMETER:
    svg += getSymbolSVG("utils/img/SRMC.svg", NULL);
    break;
  case PMMC_RECTIFIER:
    svg += getSymbolSVG("utils/img/SMCR.svg", NULL);
    break;
  case PMMC_RADIOMETER_RECTIFER:
    svg += getSymbolSVG("utils/img/SRMCR.svg", NULL);
    break;
  case MOVING_IRON:
    svg += getSymbolSVG("utils/img/SMI.svg", NULL);
    break;
  case VIBRATING_REED:
    svg += getSymbolSVG("utils/img/SVR.svg", NULL);
    break;
  case ELECTRODYNAMIC_IRONLESS:
    svg += getSymbolSVG("utils/img/SEDI.svg", NULL);
    break;
  case ELECTRODYNAMIC_RADIOMETER:
    svg += getSymbolSVG("utils/img/SEDR.svg", NULL);
    break;
  case FERRODYNAMIC:
    svg += getSymbolSVG("utils/img/SEDF.svg", NULL);
    break;
  case FERRODYNAMIC_RADIOMETER:
    svg += getSymbolSVG("utils/img/SFD.svg", NULL);
    break;
  case ELECTROSTATIC:
    svg += getSymbolSVG("utils/img/SED.svg", NULL);
    break;
  case INDUCTION:
    svg += getSymbolSVG("utils/img/SI.svg", NULL);
    break;
  }
  return svg;
}

std::string Gauge::getError() {
  std::ostringstream stream;
  std::string        svg = "  <svg x=\"270\" y=\"1800\" viewport=\"0 0 100 150\" transform=\"scale(0.2 0.2)\">\n";

  stream << std::fixed << std::setprecision(errorPrecision) << gaugeError;
  switch (error)
  {
  case VALUE:
    svg += getSymbolSVG("utils/img/AV.svg", stream.str().c_str());
    break;
  case SPAN:
    svg += getSymbolSVG("utils/img/AS.svg", stream.str().c_str());
    break;
  case VALUE_FISCAL:
    svg += getSymbolSVG("utils/img/AFV.svg", stream.str().c_str());
    break;
  case FULL_SCALE_READING:
    svg += getSymbolSVG("utils/img/AFSR.svg", stream.str().c_str());
    break;
  }

  return svg;
}