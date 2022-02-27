#include <value.h>

Value::Value(std::string &value) {
  this->value = value;
}

Value::operator char () const {
  return (char)stol(value);
}

Value::operator unsigned char () const {
  return (unsigned char)stol(value);
}

Value::operator short () const {
  return (short)stol(value);
}

Value::operator unsigned short () const {
  return (unsigned short)stol(value);
}

Value::operator int () const {
  return stoi(value);
}

Value::operator unsigned int () const {
  return (unsigned int)stol(value);
}

Value::operator long () const {
  return stol(value);
}

Value::operator unsigned long () const {
  return stoul(value);
}

Value::operator long long () const {
  return stoll(value);
}

Value::operator unsigned long long () const {
  return stoull(value);
}

Value::operator float () const {
  return stof(value);
}

Value::operator double () const {
  return stod(value);
}

Value::operator long double () const {
  return stold(value);
}

Value::operator std::string () const {
  return value;
}