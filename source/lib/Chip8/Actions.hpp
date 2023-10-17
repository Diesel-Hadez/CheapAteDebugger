#ifndef CHIP8_ACTIONS_H
#define CHIP8_ACTIONS_H
#include "../__InstructionAction.hpp"
#include "Chip8/Chip8Registers.hpp"
#include "Chip8Emulator.hpp"

namespace C8::Opcode {
  enum class ArgsType {
    CONSTANT,
    NNN,
    XKK,
    XY,
    XYN,
    X
  };

  using Literal=unsigned short;
  using Nibble=unsigned short;
  union Args {
    unsigned short NNN;
    // X Register and KK literal.
    struct {
      C8::Register x;
      Literal kk;
    } XKK;
    struct {
      C8::Register x;
      C8::Register y;
    } XY;
    
    struct {
      C8::Register x;
      C8::Register y;
      Nibble n;
    } XYN;

    C8::Register X;

  };

  constexpr inline Args DecodeArgs(unsigned short data, ArgsType type) {
    Args ret{};
    constexpr auto ToReg = [](unsigned short v) -> C8::Register {return static_cast<C8::Register>(v);};
    switch (type) {
      case ArgsType::NNN:
        ret.NNN = data & 0x0FFF;
      break;
      case ArgsType::XKK:
        ret.XKK.x = ToReg(data & 0x0F00);
        ret.XKK.kk = data & 0x00FF;
      break;
      case ArgsType::XY:
        ret.XY.x = ToReg(data & 0x0F00);
        ret.XY.y = ToReg(data & 0x00F0);
      break;
      case ArgsType::XYN:
        ret.XYN.x = ToReg(data & 0x0F00);
        ret.XYN.y = ToReg(data & 0x00F0);
        ret.XYN.n = data & 0x000F;
      break;
      case ArgsType::X:
        ret.X = ToReg(data & 0x0F00);
      break;
      default:
      break;
    };
    

    return ret;
  }
} // namespace C8::Opcode

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
#endif
