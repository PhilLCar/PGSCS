#ifndef VALUE_UTILS
#define VALUE_UTILS

#include <string>

class Value {
public:
  Value(std::string &value);

public:
  operator char () const;
  operator unsigned char () const;
  operator short () const;
  operator unsigned short () const;
  operator int () const;
  operator unsigned int () const;
  operator long () const;
  operator unsigned long () const;
  operator long long () const;
  operator unsigned long long () const;

  operator float () const;
  operator double () const;
  operator long double () const;

  operator std::string () const;

private:
  std::string value;
};

#endif