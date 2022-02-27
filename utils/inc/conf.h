#ifndef CONF_UTILS
#define CONF_UTILS

#include <string>
#include <map>

#include <confgroup.h>

class ConfigurationFile {

public:
  ConfigurationFile(const char *filename);
  ConfigurationFile(const std::string &filename);

public:
  ConfigurationGroup &operator [](const char *groupname);
  ConfigurationGroup &operator [](const std::string &groupname);

private:
  std::string trim(std::string &ref);

private:
  std::map<std::string, ConfigurationGroup> groups;
};

#endif