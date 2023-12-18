#include <cassert>
#include <iostream>
#include <ostream>
#include "Chip8/Chip8Emulator.hpp"
#include <Emulators.hpp>
#include <Chip8/Chip8Registers.hpp>
#include <Chip8/Chip8CPU.hpp>
#include <Chip8/Chip8Memory.hpp>

namespace Assemble  {
  auto CreateInjector(C8::Memory* memory) {
    using OpcodeType=short;
    return [memory](C8::MemoryAddress addr, OpcodeType opcode){
      memory->SetMemory(
        addr,
        (opcode & 0xFF00) >> 8
      );
      memory->SetMemory(
        addr+1,
        opcode & 0xFF
      );
    };
  }
  auto JumpTo(C8::MemoryAddress addr) -> short {
   return 0x1000 | (0x0FFF & addr); 
  }
}

auto main() -> int
{


  C8::Emulator emulator(std::make_unique<C8::Registers>(), 
                        std::make_unique<C8::CPU>(emulator), 
                        std::make_unique<C8::Memory>());

  auto InstInjector = Assemble::CreateInjector(emulator.GetMemoryPtr());

  InstInjector(
    C8::Registers::CHIP8_INITIAL_ADDRESS, 
    Assemble::JumpTo(0x123)
  );
  std::cout << std::hex << (int)emulator.GetMemoryPtr()->GetMemory(0x200) << std::endl;
  std::cout << std::hex << (int)emulator.GetMemoryPtr()->GetMemory(0x201) << std::endl;
  std::cout << std::hex << (int)emulator.GetMemoryPtr()->GetMemory(0x202) << std::endl;
  std::cout << std::hex << (int)emulator.GetMemoryPtr()->GetMemory(0x203) << std::endl;
  emulator.Fetch();
  emulator.Decode();
  emulator.Execute();

  std::cout << std::hex << emulator.GetRegistersPtr()->GetProgramCounter() << std::endl;
  assert(emulator.GetRegistersPtr()->GetProgramCounter() == 0x123);

  return 0;
}
