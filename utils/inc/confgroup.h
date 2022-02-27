#ifndef CONFGROUP_UTILS
#define CONFGROUP_UTILS

#include <string>
#include <map>

#include <value.h>

class ConfigurationGroup {
friend class ConfigurationFile;

public:
  Value operator [](const std::string &parameter);
  Value operator [](const char *parameter);

private:
  void add(std::string &key, std::string &value);

private:
  std::map<std::string, std::string> parameters;
};

#endif