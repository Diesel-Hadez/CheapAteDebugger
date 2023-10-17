#ifndef CHIP8_REGISTERS_H
#define CHIP8_REGISTERS_H
#include <array>
namespace C8 {
  class Registers {
private:
  using Register=unsigned char; 
  static constexpr int NUM_REGISTERS = 0xF+1;
  std::array<Register, NUM_REGISTERS> m_Registers;

  using MemoryRegister=unsigned short;
  MemoryRegister m_AddressRegister;
public:

  };
} // namespace C8

#endif
