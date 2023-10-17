#include "Chip8CPU.hpp"
#include "__CPU.hpp"
#include "Actions.hpp"

C8::CPU::CPU(Emulator& emulator): m_Emulator(emulator){
}

BaseInstructionActionPtr C8::CPU::Next() {
  BaseInstructionActionPtr ret {nullptr};

  ret = std::make_unique<C8::Actions::DispClear>(m_Emulator);

  return std::move(ret);
}
