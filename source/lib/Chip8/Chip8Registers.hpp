#ifndef CHIP8_REGISTERS_H
#define CHIP8_REGISTERS_H
#include <array>
#include "../__Registers.hpp"
namespace C8 {
  using RegisterValue=unsigned short;
  using MemoryRegister=unsigned short;
  enum class Register {
    V0=0,
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
  MemoryRegister m_AddressRegister;
  RegisterValue m_ProgramCounter;
public:
  static constexpr int NUM_V_REGS = 17;
  static constexpr int CHIP8_INITIAL_ADDRESS= 0x200;
  void SetProgramCounter(RegisterValue val){m_ProgramCounter = val;}
  RegisterValue GetProgramCounter() const {return m_ProgramCounter;}
  void SetVRegister(Register r, RegisterValue v) {m_Registers.at(r) = v;}
  RegisterValue GetVRegister(Register r) const { return m_Registers.at(r);}
  MemoryRegister GetAddressRegister() const {return m_AddressRegister;}
  void SetAddressRegister(MemoryRegister value) {m_AddressRegister = value;}
  Registers(): m_AddressRegister(0), m_ProgramCounter(CHIP8_INITIAL_ADDRESS){
    for (int i = 0; i <= NUM_V_REGS; i++) {
      m_Registers.insert({static_cast<Register>(i), 0});
    }
  }

  };
} // namespace C8

#endif
