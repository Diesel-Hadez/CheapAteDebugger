#ifndef __INSTRUCTION_ACTION_H
#define __INSTRUCTION_ACTION_H

class BaseInstructionAction {
public:
  int m_StepCount;
  
public:
  virtual void Execute()=0;
  virtual ~BaseInstructionAction() = default;
};

#endif
