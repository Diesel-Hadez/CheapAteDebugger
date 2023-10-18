#ifndef CHIP8EMULATOR_H
#define CHIP8EMULATOR_H
#include <memory>
#include "../__Emulator.hpp"
#include "Chip8/Chip8Registers.hpp"
#include "__CPU.hpp"

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

    BaseInstructionActionPtr m_LastAction;

    bool m_Paused;
    bool m_Running;

  public:
    Registers* GetRegistersPtr() const {return m_Registers.get();}
    Memory* GetMemoryPtr() const {return m_Memory.get();}

    void StepPC();
    C8::RegisterValue GetRegister(C8::Register);
  public:
    void Run();
    void Fetch() override;
    void Decode() override;
    void Execute() override;
    void ClearScreen();
    void DrawScreen(int vx, int vy, int height);
    Emulator(RegistersPtr, CPUPtr, MemoryPtr);
    ~Emulator();
  };
} // namespace C8
#endif
