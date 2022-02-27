#include <conf.h>

#include <fstream>

ConfigurationFile::ConfigurationFile(const char *filename) {
  std::ifstream confFile(filename, std::ios_base::in);
  std::string   line;
  std::string   last = "";

  groups.emplace(last, ConfigurationGroup());

  while (!confFile.eof()) {
    std::getline(confFile, line);
    line = trim(line);
    if (line[0] == '#' || line == "") continue;
    if (line[0] == '[') {
      last = "";
      for (int i = 1; line[i] != ']' && line[i] != 0; i++) {
        last += line[i];
      }

      groups.emplace(last, ConfigurationGroup());
    } else {
      std::string key = "";
      std::string val = "";
      int i;

      for (i = 0; line[i] != '=' && line[i]; i++) {
        key += line[i];
      }
      for (++i; line[i]; i++) {
        val += line[i];
      }
      key = trim(key);
      val = trim(val);

      groups[last].add(key, val);
    }
  }
}

ConfigurationFile::ConfigurationFile(const std::string &filename)
  : ConfigurationFile(filename.c_str())
{
}

std::string ConfigurationFile::trim(std::string &ref) {
  std::string newString = "";
  std::string tmpString = "";
  bool space = true;

  for (int i = 0; i < ref.length(); i++) {
    bool whitespace = ref[i] == ' ' || ref[i] == '\t';
    if (!space || !whitespace) {
      space = false;
      if (whitespace) {
        tmpString += ref[i];
      } else {
        newString += tmpString + ref[i];
        tmpString = "";
      }
    }
  }
  return newString;
}

ConfigurationGroup &ConfigurationFile::operator [](const char *groupname) {
  return groups[std::string(groupname)];
}

ConfigurationGroup &ConfigurationFile::operator [](const std::string &groupname) {
  return groups[groupname];
}