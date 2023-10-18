#include "Chip8CPU.hpp"
#include "Chip8/Chip8Memory.hpp"
#include "__CPU.hpp"
#include "Actions.hpp"
#include <iostream>

C8::CPU::CPU(Emulator& emulator): m_Emulator(emulator){
}

BaseInstructionActionPtr C8::CPU::Next() {
  BaseInstructionActionPtr ret {nullptr};
  auto * regs = m_Emulator.GetRegistersPtr();
  auto * mem = m_Emulator.GetMemoryPtr();

  const auto pc = regs->GetProgramCounter();
  const auto first_byte = mem->GetMemory(pc);
  const auto second_byte= mem->GetMemory(pc+1);

  const auto opcode = (first_byte << 8) | second_byte;
  C8::Opcode::ArgsType type{Opcode::ArgsType::CONSTANT};
  C8::Opcode::Args args;

  const auto masked =  [opcode](unsigned short mask) { 
      return [opcode, mask](unsigned short compare) -> bool {
        return (opcode & mask) == compare;
      }; 
  };


  const auto change_type = [&type,&args, opcode](auto func, Opcode::ArgsType a) {
    return [&type, func, &args, a, opcode](unsigned short compare) {
      auto ret = func(compare);
      if (ret) {
        type = a;
        args = Opcode::DecodeArgs(opcode, type);
      }
      return ret;
    };
  };

  const auto constant = masked(0xFFFF);
  const auto nnn = change_type(masked(0xF000), Opcode::ArgsType::NNN);
  const auto xnn= change_type(masked(0xF000), Opcode::ArgsType::XKK);
  const auto xyn= change_type(masked(0xF000), Opcode::ArgsType::XYN);
  const auto xy= change_type(masked(0xF00F), Opcode::ArgsType::XY);
  const auto x = change_type(masked(0xF0FF), Opcode::ArgsType::X);

  #define CONST_CALL(action) ret = std::make_unique<action>(m_Emulator);
  #define NNN_CALL(action) ret = std::make_unique<action>(args.NNN, m_Emulator);
  #define XNN_CALL(action) ret = std::make_unique<action>(args.XKK.x, args.XKK.kk, m_Emulator);
  #define XYN_CALL(action) ret = std::make_unique<action>(args.XYN.x, args.XYN.y, args.XYN.n, m_Emulator);
  #define XY_CALL(action) ret = std::make_unique<action>(args.XY.x, args.XY.y, m_Emulator);
  #define X_CALL(action) ret = std::make_unique<action>(args.X, m_Emulator);

  if (constant(0x00E0))
  {
    CONST_CALL(Actions::ClearScreen)
  }
  else if (constant(0x00EE))
  {
    CONST_CALL(Actions::Ret)
  }
  else if (nnn(0x1000))
  {
    NNN_CALL(Actions::Jump)
  }
  else if (nnn(0x2000))
  {
    NNN_CALL(Actions::Call)
  }
  else if (xnn(0x3000))
  {
    XNN_CALL(Actions::SkipEqualImm)
  }
  else if (xnn(0x4000))
  {
    XNN_CALL(Actions::SkipNotEqualImm)
  }
  else if (xy(0x5000))
  {
    XY_CALL(Actions::SkipEqualReg)
  }
  else if (xnn(0x6000))
  {
    XNN_CALL(Actions::LoadRegImm)
  }
  else if (xnn(0x7000))
  {
    XNN_CALL(Actions::AddRegImm)
  }
  else if (xy(0x8000))
  {
    XY_CALL(Actions::Load)
  }
  else if (xy(0x8001))
  {
    XY_CALL(Actions::Or)
  }
  else if (xy(0x8002))
  {
    XY_CALL(Actions::And)
  }
  else if (xy(0x8003))
  {
    XY_CALL(Actions::Xor)
  }
  else if (xy(0x8004))
  {
    XY_CALL(Actions::Add)
  }
  else if (xy(0x8005))
  {
    XY_CALL(Actions::Subtract)
  }
  else if (xy(0x8006))
  {
    XY_CALL(Actions::ShiftRight)
  }
  else if (xy(0x8007))
  {
    XY_CALL(Actions::SubtractNoBorrow)
  }
  else if (xy(0x800E))
  {
    XY_CALL(Actions::ShiftLeft)
  }
  else if (xy(0x9000))
  {
    XY_CALL(Actions::SkipNotEqualReg)
  }
  else if (nnn(0xA000))
  {
    NNN_CALL(Actions::LoadIndirect)
  }
  else if (nnn(0xB000))
  {
    NNN_CALL(Actions::JumpIndirect)
  }
  else if (xnn(0xC000))
  {
    XNN_CALL(Actions::Random)
  }
  else if (xyn(0xD000))
  {
    std::cout << "It's Drawing time" << std::endl;
    XYN_CALL(Actions::Draw)
  }
  else if (x(0xE09E))
  {
    X_CALL(Actions::SkipNextIfKeyPressed)
  }
  else if (x(0xE0A1))
  {
    X_CALL(Actions::SkipNextIfKeyNotPressed)
  }
  else if (x(0xF007))
  {
    X_CALL(Actions::LoadDelayTimer)
  }
  else if (x(0xF00A))
  {
    X_CALL(Actions::WaitAndStoreKey)
  }
  else if (x(0xF015))
  {
    X_CALL(Actions::SetDelayTimer)
  }
  else if (x(0xF018))
  {
    X_CALL(Actions::SetSoundTimer)
  }
  else if (x(0xF01E))
  {
    X_CALL(Actions::AddIRegister)
  }
  else if (x(0xF029))
  {
    std::cout << "LoadIRegister" << std::endl;
    X_CALL(Actions::LoadIRegister)
  }
  else if (x(0xF033))
  {
    X_CALL(Actions::LoadBCDReg)
  }
  else if (x(0xF055))
  {
    X_CALL(Actions::StoreRegistersToI)
  }
  else if (x(0xF065))
  {
    X_CALL(Actions::LoadRegistersFromI)
  }
  else {
    // Unknown Opcode
  }
  return std::move(ret);
}
