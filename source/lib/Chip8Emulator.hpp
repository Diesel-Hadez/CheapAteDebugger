#ifndef CHIP8EMULATOR_H
#define CHIP8EMULATOR_H
#include <memory>
#include <__Emulator.hpp>

namespace C8{
  class Registers;
  class CPU;
  class Memory;

  using RegistersPtr=std::unique_ptr<Registers>;
  using CPUPtr=std::unique_ptr<CPU>;
  using MemoryPtr=std::unique_ptr<Memory>;

  class Emulator: BaseEmulator {
  private:
    RegistersPtr m_Registers;
    CPUPtr m_CPU;
    MemoryPtr m_Memory;
  public:
    void Fetch() override;
    void Decode() override;
    void Execute() override;
    Emulator(RegistersPtr, CPUPtr, MemoryPtr);
  };
} // namespace C8
#endif
