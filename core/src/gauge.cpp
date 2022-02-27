#include <gauge.h>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <regex>
#include <cmath>

static const char* HEADER = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n\
<svg version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" width=\"100%\" height=\"100%\" viewBox=\"0 0 400 400\">\n\
  <defs>\n\
    <style type=\"text/css\">\n\
      @font-face {\n\
        font-family: Plat Nomor;\n\
        src: url('../fonts/PlatNomor.woff');\n\
      }\n\
    </style>\n\
  </defs>\n\
  <rect width=\"100%\" height=\"100%\" fill=\"white\"/>\n";
static const char* FOOTER = "</svg>\n";

Gauge::Gauge(ConfigurationFile &file, const std::string &gauge) 
  : Gauge(file, gauge.c_str())
{
}

Gauge::Gauge(ConfigurationFile &file, const char *gauge) {
  ConfigurationGroup cg = file[gauge];

  current   = (Current)(int)cg["Current"];
  principle = (Principle)(int)cg["Principle"];
  error     = (Error)(int)cg["Error"];
  mount     = (Mount)(int)cg["Mount"];
  rating    = (Rating)(int)cg["Rating"];

  inputUnits = (std::string)cg["Input-Units"];
  gaugeUnits = (std::string)cg["Units"];

  inputMax        = cg["Input-Maximum"];
  gaugeError      = cg["Error-Range"];
  gaugeMin        = cg["Minimum"];
  gaugeMax        = cg["Maximum"];
  gaugeOffset     = cg["Offset"];
  minorIncrement  = cg["Minor"];
  mediumIncrement = cg["Medium"];
  majorIncrement  = cg["Major"];
  setValue        = cg["SetPoint"];
  minZone         = cg["Zone-Minimum"];
  maxZone         = cg["Zone-Maximum"];
  
  angle          = cg["Angle"];
  inputPrecision = cg["Input-Precision"];
  errorPrecision = cg["Error-Precision"];
  gaugePrecision = cg["Precision"];
}

void Gauge::makeSVG(const char *filename) {
  std::ofstream file(filename, std::ios_base::out);

  if (file.is_open()) {
    file << HEADER;
    file << getCurrentType();
    file << getPrinciple();
    file << getError();
    file << getMount();
    file << getRating();

    file << getInputValue();

    file << getGaugeMarkings();

    file << getUnits();

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
      content += "  " + std::regex_replace(line, std::regex(">\%<"), replace) + "\n";
    }

    svg.close();
  }

  return content;
}

std::string Gauge::getCurrentType() {
  std::string svg = "  <svg x=\"50\" y=\"1800\" viewport=\"0 0 100 150\" transform=\"scale(0.2 0.2)\">\n";

  switch (current) {
  case ALTERNATIVE:
    svg += getSymbolSVG("res/img/TAC.svg", NULL);
    break;
  case DIRECT:
    svg += getSymbolSVG("res/img/TDC.svg", NULL);
    break;
  }
  return svg;
}

std::string Gauge::getPrinciple() {
  std::string svg = "  <svg x=\"160\" y=\"1800\" viewport=\"0 0 100 150\" transform=\"scale(0.2 0.2)\">\n";

  switch (principle) {
  case PMMC:
    svg += getSymbolSVG("res/img/SMC.svg", NULL);
    break;
  case PMMC_RADIOMETER:
    svg += getSymbolSVG("res/img/SRMC.svg", NULL);
    break;
  case PMMC_RECTIFIER:
    svg += getSymbolSVG("res/img/SMCR.svg", NULL);
    break;
  case PMMC_RADIOMETER_RECTIFER:
    svg += getSymbolSVG("res/img/SRMCR.svg", NULL);
    break;
  case MOVING_IRON:
    svg += getSymbolSVG("res/img/SMI.svg", NULL);
    break;
  case VIBRATING_REED:
    svg += getSymbolSVG("res/img/SVR.svg", NULL);
    break;
  case ELECTRODYNAMIC_IRONLESS:
    svg += getSymbolSVG("res/img/SEDI.svg", NULL);
    break;
  case ELECTRODYNAMIC_RADIOMETER:
    svg += getSymbolSVG("res/img/SEDR.svg", NULL);
    break;
  case FERRODYNAMIC:
    svg += getSymbolSVG("res/img/SEDF.svg", NULL);
    break;
  case FERRODYNAMIC_RADIOMETER:
    svg += getSymbolSVG("res/img/SFD.svg", NULL);
    break;
  case ELECTROSTATIC:
    svg += getSymbolSVG("res/img/SED.svg", NULL);
    break;
  case INDUCTION:
    svg += getSymbolSVG("res/img/SI.svg", NULL);
    break;
  }
  return svg;
}

std::string Gauge::getError() {
  std::ostringstream stream;
  std::string        svg = "  <svg x=\"270\" y=\"1800\" viewport=\"0 0 100 150\" transform=\"scale(0.2 0.2)\">\n";

  stream << std::fixed << std::setprecision(errorPrecision) << ">" << gaugeError << "<";

  switch (error)
  {
  case VALUE:
    svg += getSymbolSVG("res/img/AV.svg", stream.str().c_str());
    break;
  case SPAN:
    svg += getSymbolSVG("res/img/AS.svg", stream.str().c_str());
    break;
  case VALUE_FISCAL:
    svg += getSymbolSVG("res/img/AFV.svg", stream.str().c_str());
    break;
  case FULL_SCALE_READING:
    svg += getSymbolSVG("res/img/AFSR.svg", stream.str().c_str());
    break;
  }

  return svg;
}

std::string Gauge::getMount() {
  std::string svg = "  <svg x=\"380\" y=\"1800\" viewport=\"0 0 100 150\" transform=\"scale(0.2 0.2)\">\n";

  switch (mount) {
  case VERTICAL:
    svg += getSymbolSVG("res/img/MV.svg", NULL);
    break;
  case HORIZONTAL:
    svg += getSymbolSVG("res/img/MH.svg", NULL);
    break;
  case ANGLED:
    std::string val = ">" + std::to_string(angle) + "°<";
    svg += getSymbolSVG("res/img/MA.svg", angle ? val.c_str() : "");
    break;
  }
  return svg;
}

std::string Gauge::getRating() {
  std::string svg = "  <svg x=\"490\" y=\"1800\" viewport=\"0 0 100 150\" transform=\"scale(0.2 0.2)\">\n";

  switch (rating) {
  case EXEMPT:
    svg += getSymbolSVG("res/img/RE.svg", NULL);
    break;
  case RATED_500V:
    svg += getSymbolSVG("res/img/R0.svg", NULL);
    break;
  case RATED_2KV:
    svg += getSymbolSVG("res/img/R2.svg", NULL);
    break;
  case RATED_5KV:
    svg += getSymbolSVG("res/img/R5.svg", NULL);
    break;
  }
  return svg;
}

std::string Gauge::getInputValue() {
  std::ostringstream stream;
  std::string        svg = "  <text x=\"150\" y=\"385\" font-family=\"Arial\" font-size=\"20\">";

  stream << std::fixed << std::setprecision(inputPrecision) << inputMax << inputUnits << "</text>\n";
  svg += stream.str();
  return svg;
}

std::string Gauge::getGaugeMarkings() {
  const double EPSILON = 0.0000001;
  const double ARROW_W = 0.02;
  const double ARROW_R   = 340;
  const double OUTSIDE_R = 320;
  const double INSIDE_R1 = 300;
  const double INSIDE_R2 = 290;
  const double INSIDE_R3 = 280;
  const double INSIDE_R4 = 250;
  const double CX = 330;
  const double CY = 330;
  std::ostringstream stream;
  double smallestDivision = majorIncrement * mediumIncrement * minorIncrement;
  double startPoint       = gaugeMin + gaugeOffset;
  int gaugeSpan = (gaugeMax - gaugeMin) / smallestDivision;

  while (startPoint - smallestDivision > gaugeMin) startPoint -= smallestDivision;

  stream << std::fixed << std::setprecision(6);

  if (minZone > 0.0) {
    double t = M_PI_2 * maxZone / (gaugeMax - gaugeMin);
    double s = -sin(t);
    double c = -cos(t);
    double x0 = CX - OUTSIDE_R;
    double y0 = CY;
    double x1 = CX + c * OUTSIDE_R;
    double y1 = CY + s * OUTSIDE_R;
    double x2 = CX + c * INSIDE_R1;
    double y2 = CX + s * INSIDE_R1;
    double x3 = CX - INSIDE_R1;
    double y3 = CY;

    stream << "<path d=\"M " << x0 << " " << y0 << " A " << OUTSIDE_R << " " << OUTSIDE_R << " ";
    stream << "0 0 0 " << x1 << " " << y1 << " L " << x2 << " " << y2 << " A " << INSIDE_R1 << " " << INSIDE_R1 << " ";
    stream << "0 0 1 " << x3 << " " << y3 << " Z\" fill=\"red\"/>\n";
  }
  if (maxZone > 0.0) {
    double t = M_PI_2 - M_PI_2 * maxZone / (gaugeMax - gaugeMin);
    double s = -sin(t);
    double c = -cos(t);
    double x0 = CX;
    double y0 = CY - OUTSIDE_R;
    double x1 = CX + c * OUTSIDE_R;
    double y1 = CY + s * OUTSIDE_R;
    double x2 = CX + c * INSIDE_R1;
    double y2 = CX + s * INSIDE_R1;
    double x3 = CX;
    double y3 = CY - INSIDE_R1;

    stream << "<path d=\"M " << x0 << " " << y0 << " A " << OUTSIDE_R << " " << OUTSIDE_R << " ";
    stream << "0 0 0 " << x1 << " " << y1 << " L " << x2 << " " << y2 << " A " << INSIDE_R1 << " " << INSIDE_R1 << " ";
    stream << "0 0 1 " << x3 << " " << y3 << " Z\" fill=\"red\"/>\n";
  }

  for (int i = 0; i <= gaugeSpan; i++) {
    double mod = (gaugeOffset - (gaugeMin + smallestDivision * (double)i)) / majorIncrement;
    double t = M_PI_2 * (double)i / (double)gaugeSpan;
    double s = -sin(t);
    double c = -cos(t);
    double x1 = CX + c * OUTSIDE_R;
    double y1 = CY + s * OUTSIDE_R;

    if (std::abs(mod - std::round(mod)) < EPSILON) {
      double x2 = CX + c * INSIDE_R1;
      double y2 = CY + s * INSIDE_R1;
      double x3 = CX + c * INSIDE_R3;
      double y3 = CY + s * INSIDE_R3;
      double x4 = CX + c * INSIDE_R4;
      double y4 = CY + s * INSIDE_R4;

      stream << "<line x1=\"" << x1 << "\" y1=\"" << y1 << "\" x2=\"" << x2 << "\" y2=\"" << y2 <<"\" ";
      stream << "stroke=\"black\" stroke-width=\"1pt\"/>\n";

      stream << "<line x1=\"" << x2 << "\" y1=\"" << y2 << "\" x2=\"" << x3 << "\" y2=\"" << y3 <<"\" ";
      stream << "stroke=\"black\" stroke-width=\"3pt\"/>\n";

      stream << "<text x=\"" << x4 << "\" y=\"" << y4 + 10 << "\" ";
      stream << "font-family=\"Plat Nomor\" font-size=\"30\" text-anchor=\"middle\" alignement-baseline=\"central\">";
      stream << std::setprecision(gaugePrecision);
      stream << gaugeMin + (double)i * smallestDivision << "</text>\n";
      stream << std::setprecision(6);
    }
    else if (std::abs((mod / mediumIncrement) - std::round(mod / mediumIncrement)) < EPSILON) {
      double x2 = CX + c * INSIDE_R2;
      double y2 = CY + s * INSIDE_R2;

      stream << "<line x1=\"" << x1 << "\" y1=\"" << y1 << "\" x2=\"" << x2 << "\" y2=\"" << y2 <<"\" ";
      stream << "stroke=\"black\" stroke-width=\"1pt\"/>\n";
    }
    else {
      double x2 = CX + c * INSIDE_R1;
      double y2 = CY + s * INSIDE_R1;

      stream << "<line x1=\"" << x1 << "\" y1=\"" << y1 << "\" x2=\"" << x2 << "\" y2=\"" << y2 <<"\" ";
      stream << "stroke=\"black\" stroke-width=\"1pt\"/>\n";
    }
  }

  stream << "<circle cx=\"" << CX << "\" cy=\"" << CY << "\" r=\"30\" fill=\"grey\"/>\n";

  { // Set Value
    double t = M_PI_2 * (setValue - gaugeMin) / (gaugeMax - gaugeMin);
    double s1 = -sin(t);
    double c1 = -cos(t);
    double s2 = -sin(t - ARROW_W);
    double c2 = -cos(t - ARROW_W);
    double s3 = -sin(t + ARROW_W);
    double c3 = -cos(t + ARROW_W);
    double x1 = CX + c1 * OUTSIDE_R;
    double y1 = CY + s1 * OUTSIDE_R;
    double x2 = CX + c2 * ARROW_R;
    double y2 = CY + s2 * ARROW_R;
    double x3 = CX + c3 * ARROW_R;
    double y3 = CY + s3 * ARROW_R;

    stream << "<path d=\"M" << x1 << " " << y1 << " L " << x2 << " " << y2 << " L " << x3 << " " << y3 << " Z\"";
    stream << " fill=\"#FF4000\"/>\n";
  }

  return stream.str();
}

std::string Gauge::getUnits() {
  std::ostringstream stream;

  stream << "<text font-family=\"Plat Nomor\" font-weight=\"bold\" font-size=\"50\" x=\"20\" y=\"70\">";
  stream << gaugeUnits << "</text>\n";

  return stream.str();
}