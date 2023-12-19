#include <iostream>

#include "Chip8Emulator.hpp"

#include "Chip8CPU.hpp"
#include "Chip8Memory.hpp"
#include "Chip8Registers.hpp"

void C8::Emulator::Run() {
  while (m_Running) {
    if (m_Paused) {
      continue;
    }
    Fetch();
    Decode();
    Execute();
  }
}

void C8::Emulator::Fetch() {}

void C8::Emulator::Decode() {
  m_LastAction = m_CPU->Next();
}

void C8::Emulator::Execute() {
  if (m_LastAction == nullptr) {
    return;
  }
  std::cout << "Executing Instruction" << std::endl;
  m_LastAction->Execute();
  StepPC();
}

void C8::Emulator::StepPC() {
  auto cur_pc = m_Registers->GetProgramCounter();
  m_Registers->SetProgramCounter(cur_pc + m_LastAction->m_StepCount);
}

auto C8::Emulator::GetRegister(C8::Register r) -> C8::RegisterValue {
  return m_Registers->GetVRegister(r);
}

// clang-tidy wants me to make this method static, not knowing
// that I plan to make future plans that would not be able
// to make it static
// NOLINTNEXTLINE
void C8::Emulator::ClearScreen() {
  std::cout << "Clearing Screen" << std::endl;
}

// clang-tidy wants me to make this method static, not knowing
// that I plan to make future plans that would not be able
// to make it static
// NOLINTNEXTLINE
void C8::Emulator::DrawScreen(int vx, int vy, int height) {
  std::cout << "Drawing Screen at (" << vx << ", " << vy << ") with height "
            << height << "!" << std::endl;
}

C8::Emulator::Emulator(C8::RegistersPtr regs,
                       C8::CPUPtr cpu,
                       C8::MemoryPtr memory)
    : m_Registers(std::move(regs))
    , m_CPU(std::move(cpu))
    , m_Memory(std::move(memory))
    , m_Paused(false)
    , m_Running(true) {
  // Load font
  constexpr std::array<MemoryValue, 80> FONT_SET = {
      0xF0, 0x90, 0x90, 0x90, 0xF0,  // 0
      0x20, 0x60, 0x20, 0x20, 0x70,  // 1
      0xF0, 0x10, 0xF0, 0x80, 0xF0,  // 2
      0xF0, 0x10, 0xF0, 0x10, 0xF0,  // 3
      0x90, 0x90, 0xF0, 0x10, 0x10,  // 4
      0xF0, 0x80, 0xF0, 0x10, 0xF0,  // 5
      0xF0, 0x80, 0xF0, 0x90, 0xF0,  // 6
      0xF0, 0x10, 0x20, 0x40, 0x40,  // 7
      0xF0, 0x90, 0xF0, 0x90, 0xF0,  // 8
      0xF0, 0x90, 0xF0, 0x10, 0xF0,  // 9
      0xF0, 0x90, 0xF0, 0x90, 0x90,  // A
      0xE0, 0x90, 0xE0, 0x90, 0xE0,  // B
      0xF0, 0x80, 0x80, 0x80, 0xF0,  // C
      0xE0, 0x90, 0x90, 0x90, 0xE0,  // D
      0xF0, 0x80, 0xF0, 0x80, 0xF0,  // E
      0xF0, 0x80, 0xF0, 0x80, 0x80  // F
  };
  MemoryAddress cur_addr = 0;
  for (auto byte : FONT_SET) {
    m_Memory->SetMemory(cur_addr++, byte);
  }

  // Load Sample ROM
  const std::array<MemoryValue, 4> rom = {
      0xF0,
      0x29,  // I = sprite_addr[V0]
      0xD0,
      0x05,  // Draw(0,0,5) (At 0,0 draw with height 5)
  };
  cur_addr = C8::Registers::CHIP8_INITIAL_ADDRESS;
  for (auto byte : rom) {
    m_Memory->SetMemory(cur_addr++, byte);
  }
}
