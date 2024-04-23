#ifndef CHIP8_CPU_H
#define CHIP8_CPU_H
#include <functional>
#include <unordered_map>

#include "../__CPU.hpp"
#include "Chip8Emulator.hpp"
namespace C8 {
  class CPU : public BaseCPU {
  private:
    // clang-tidy doesn't like this being a reference for some reason?
    // NOLINTNEXTLINE
    Emulator& m_Emulator;

  public:
    explicit CPU(Emulator& emulator);
    auto Next() -> BaseInstructionActionPtr override;
  };
}  // namespace C8

#endif
