#ifndef __EMULATOR_EMU_H
#define __EMULATOR_EMU_H

#include "__CPU.hpp"
class BaseEmulator {
protected:
    BaseInstructionActionPtr m_LastAction;
public:
  virtual void Fetch()=0;
  virtual void Decode()=0;
  virtual void Execute()=0;
  virtual ~BaseEmulator()=default;
};

#endif
