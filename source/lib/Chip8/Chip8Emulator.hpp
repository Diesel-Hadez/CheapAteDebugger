#ifndef CHIP8EMULATOR_H
#define CHIP8EMULATOR_H
#include <memory>

#include "../__Emulator.hpp"
#include "Chip8/Chip8Registers.hpp"

namespace C8 {
  class Registers;
  class CPU;
  class Memory;
  namespace Actions {
    class BaseChip8InstructionAction;
  }  // namespace Actions

  using RegistersPtr = std::unique_ptr<Registers>;
  using CPUPtr = std::unique_ptr<CPU>;
  using MemoryPtr = std::unique_ptr<Memory>;
  using BaseChip8InstructionActionPtr =
      std::unique_ptr<Actions::BaseChip8InstructionAction>;

  class Emulator : BaseEmulator {
  private:
    RegistersPtr m_Registers;
    CPUPtr m_CPU;
    MemoryPtr m_Memory;

    bool m_Paused;
    bool m_Running;

  public:
    auto GetRegistersPtr() const -> Registers* { return m_Registers.get(); }
    auto GetMemoryPtr() const -> Memory* { return m_Memory.get(); }

    void StepPC();
    auto GetRegister(C8::Register) -> C8::RegisterValue;

    void Run();
    void Fetch() override;
    void Decode() override;
    void Execute() override;
    void ClearScreen();
    void DrawScreen(int vx, int vy, int height);
    Emulator(RegistersPtr, CPUPtr, MemoryPtr);
    ~Emulator() override = default;
  };
}  // namespace C8
#endif
