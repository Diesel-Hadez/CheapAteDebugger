#ifndef __CPU_EMU_H
#define __CPU_EMU_H
#include <memory>
#include <type_traits>
#include "__InstructionAction.hpp"

class BaseInstructionAction;
using BaseInstructionActionPtr=std::unique_ptr<BaseInstructionAction>;
class BaseCPU {
public:
  virtual BaseInstructionActionPtr Next() = 0;
  virtual ~BaseCPU() = default;
};
#endif
