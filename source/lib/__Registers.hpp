#ifndef __REGISTERS_EMU_H
#define __REGISTERS_EMU_H
#include <unordered_map>
template<typename RegisterKey, typename RegisterValue>
class BaseRegisters {
protected:
  std::unordered_map<RegisterKey, RegisterValue> m_Registers;
public:

  virtual ~BaseRegisters()=default;
};

#endif
