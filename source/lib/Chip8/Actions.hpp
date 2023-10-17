#include "../__InstructionAction.hpp"
#include "Chip8Emulator.hpp"

namespace C8::Actions {
  class DispClear: public BaseInstructionAction {
  private:
    C8::Emulator& m_Emulator;
  public:
    explicit DispClear(C8::Emulator& emulator) :
    m_Emulator(emulator)
    {
    
    }
    void Execute() override {
      m_Emulator.ClearScreen();
    }
  };

  class LoadRegister: public BaseInstructionAction {
  private:
    C8::Emulator& m_Emulator;
  public:
    explicit LoadRegister(C8::Emulator& emulator) :
    m_Emulator(emulator)
    {
    
    }
    void Execute() override {
    }

  };
}
