#include "Chip8/Chip8Emulator.hpp"
#include <Emulators.hpp>
#include <Chip8/Chip8Registers.hpp>
#include <Chip8/Chip8CPU.hpp>
#include <Chip8/Chip8Memory.hpp>

auto main() -> int
{
  C8::Emulator emulator(std::make_unique<C8::Registers>(), 
                        std::make_unique<C8::CPU>(emulator), 
                        std::make_unique<C8::Memory>());
  emulator.Run();
  return 0;
}
