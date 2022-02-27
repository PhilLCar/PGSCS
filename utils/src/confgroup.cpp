#include <confgroup.h>

Value ConfigurationGroup::operator [](const std::string &parameter) {
  return Value(parameters[parameter]);
}

Value ConfigurationGroup::operator [](const char *parameter) {
  return Value(parameters[std::string(parameter)]);
}