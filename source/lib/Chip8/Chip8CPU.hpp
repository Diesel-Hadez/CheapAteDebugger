#ifndef CHIP8_CPU_H
#define CHIP8_CPU_H
#include "../__CPU.hpp"
#include "Chip8Emulator.hpp"
namespace C8 {
  class CPU: public BaseCPU {
    private:
    Emulator& m_Emulator;
    public:
      CPU(Emulator& emulator);
      BaseInstructionActionPtr Next() override;

  };
} // namespace C8

#endif
