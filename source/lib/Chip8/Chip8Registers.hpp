#ifndef CHIP8_REGISTERS_H
#define CHIP8_REGISTERS_H
#include <array>
#include <cstdint>

#include "../__Registers.hpp"
namespace C8 {
  using RegisterValue = uint16_t;
  using MemoryRegister = uint16_t;
  enum class Register {
    V0 = 0,
    V1,
    V2,
    V3,
    V4,
    V5,
    V6,
    V7,
    V9,
    VA,
    VB,
    VC,
    VD,
    VE,
    VF,
  };
  class Registers : public BaseRegisters<Register, RegisterValue> {
  private:
    // clang-tidy wants me to brace initialise it
    // directly here for some reason instead of in
    // the constructor
    // NOLINTNEXTLINE
    MemoryRegister m_AddressRegister;
    RegisterValue m_ProgramCounter;

  public:
    static constexpr int NUM_V_REGS = 17;
    static constexpr int CHIP8_INITIAL_ADDRESS = 0x200;
    void SetProgramCounter(RegisterValue val) { m_ProgramCounter = val; }
    auto GetProgramCounter() const -> RegisterValue { return m_ProgramCounter; }
    void SetVRegister(Register r, RegisterValue v) { m_Registers.at(r) = v; }
    auto GetVRegister(Register r) const -> RegisterValue { return m_Registers.at(r); }
    auto GetAddressRegister() const -> MemoryRegister { return m_AddressRegister; }
    void SetAddressRegister(MemoryRegister value) { m_AddressRegister = value; }
    Registers()
        : m_AddressRegister(0)
        , m_ProgramCounter(CHIP8_INITIAL_ADDRESS) {
      for (int i = 0; i <= NUM_V_REGS; i++) {
        m_Registers.insert({static_cast<Register>(i), 0});
      }
    }
  };
}  // namespace C8

#endif
