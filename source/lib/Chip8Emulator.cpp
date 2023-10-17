#include "Chip8Emulator.hpp"
#include "Memory.hpp"
#include "Registers.hpp"
#include "CPU.hpp"

void C8::Emulator::Fetch() {

}

void C8::Emulator::Decode() {

}

void C8::Emulator::Execute() {

}
C8::Emulator::Emulator(C8::RegistersPtr regs,
                       C8::CPUPtr cpu,
                       C8::MemoryPtr memory): 
  m_Registers(std::move(regs)),
  m_CPU(std::move(cpu)),
  m_Memory(std::move(memory))
{
  
}
