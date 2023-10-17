#include <iostream>
#include "Chip8Emulator.hpp"
#include "Chip8Memory.hpp"
#include "Chip8Registers.hpp"
#include "Chip8CPU.hpp"

void C8::Emulator::Fetch() {

}

void C8::Emulator::Decode() {

}

void C8::Emulator::Execute() {

}

void C8::Emulator::ClearScreen() {
  std::cout << "Clearing Screen" << std::endl;
}

void C8::Emulator::DrawScreen(int vx, int vy, int height) {
  std::cout << "Drawing Screen at (" << vx <<
    ", " << vy << ") with height " << height <<
    "!"  << std::endl;
}
C8::Emulator::Emulator(C8::RegistersPtr regs,
                       C8::CPUPtr cpu,
                       C8::MemoryPtr memory): 
  m_Registers(std::move(regs)),
  m_CPU(std::move(cpu)),
  m_Memory(std::move(memory))
{
  
}
