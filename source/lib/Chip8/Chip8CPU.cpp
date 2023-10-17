#include "Chip8CPU.hpp"
#include "Chip8/Chip8Memory.hpp"
#include "__CPU.hpp"
#include "Actions.hpp"

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
  const auto x = change_type(masked(0x0F00), Opcode::ArgsType::X);


  if (constant(0x00E0)){
    ret = std::make_unique<C8::Actions::DispClear>(m_Emulator);
  }
  else if (constant(0x00EE)){}
  else if (nnn(0x1000)){}
  else if (nnn(0x2000)){}
  else if (xnn(0x3000)){}
  else if (xnn(0x4000)){}
  else if (xy(0x5000)){}
  else if (xnn(0x6000)){}
  else if (xnn(0x7000)){}
  else if (xy(0x8000)){}
  else if (xy(0x8001)){}
  else if (xy(0x8002)){}
  else if (xy(0x8003)){}
  else if (xy(0x8004)){}
  else if (xy(0x8005)){}
  else if (xy(0x8005)){}
  else if (xy(0x8006)){}
  else if (xy(0x8007)){}
  else if (xy(0x800E)){}
  else if (xy(0x9000)){}
  else if (nnn(0xA000)){}
  else if (nnn(0xB000)){}
  else if (xnn(0xC000)){}
  else if (xyn(0xD000)){}
  else if (x(0xE09E)){}
  else if (x(0xE0A1)){}
  else if (x(0xF007)){}
  else if (x(0xF00A)){}
  else if (x(0xF015)){}
  else if (x(0xF018)){}
  else if (x(0xF01E)){}
  else if (x(0xF029)){}
  else if (x(0xF033)){}
  else if (x(0xF055)){}
  else if (x(0xF065)){}
  else {
    // Unknown Opcode
  }
  return std::move(ret);
}
