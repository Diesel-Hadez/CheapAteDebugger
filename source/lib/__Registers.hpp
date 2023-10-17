#ifndef __REGISTERS_H
#define __REGISTERS_H
#include <unordered_map>
template<typename RegisterKey, typename RegisterValue>
class Registers {
protected:
  std::unordered_map<RegisterKey, RegisterValue> m_Registers;
public:

  virtual ~Registers()=default;
};

#endif
