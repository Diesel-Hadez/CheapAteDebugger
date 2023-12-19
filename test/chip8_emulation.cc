#include <type_traits>

#include <Chip8/Chip8CPU.hpp>
#include <Chip8/Chip8Emulator.hpp>
#include <Chip8/Chip8Memory.hpp>
#include <Chip8/Chip8Registers.hpp>
#include <Emulators.hpp>
#include <gtest/gtest.h>

using OpcodeType = int16_t;
using RegisterIndex = int16_t;
namespace Assemble {
  // Note: Not all instructions are here.
  // e.g: No way for testing drawing, so those instructions are omitted.
  // Same with key input-related instructions.
  auto Return() -> OpcodeType {
    return 0x00EE;
  }
  auto JumpTo(C8::MemoryAddress addr) -> OpcodeType {
    return 0x1000 | (0x0FFF & addr);
  }
  auto CallSub(C8::MemoryAddress addr) -> OpcodeType {
    return 0x2000 | (0x0FFF & addr);
  }
  auto SkipEqual(RegisterIndex x, C8::MemoryValue kk) -> OpcodeType {
    return 0x3000 | (x << 8) | kk;
  }
  auto SkipNotEqual(RegisterIndex x, C8::MemoryValue kk) -> OpcodeType {
    return 0x4000 | (x << 8) | kk;
  }
  auto SkipEqualReg(RegisterIndex x, RegisterIndex y) -> OpcodeType {
    return 0x5000 | (x << 8) | (y << 4);
  }
  auto LoadImm(RegisterIndex x, C8::MemoryValue val) -> OpcodeType {
    return 0x6000 | (x << 12) | val;
  }
  auto AddImm(RegisterIndex x, C8::MemoryValue val) -> OpcodeType {
    return 0x7000 | (x << 12) | val;
  }
  auto LoadReg(RegisterIndex x, RegisterIndex y) -> OpcodeType {
    return 0x8000 | (x << 12) | (y << 8);
  }
  auto OrReg(RegisterIndex x, RegisterIndex y) -> OpcodeType {
    return 0x8001 | (x << 12) | (y << 8);
  }
  auto AndReg(RegisterIndex x, RegisterIndex y) -> OpcodeType {
    return 0x8002 | (x << 12) | (y << 8);
  }
  auto XorReg(RegisterIndex x, RegisterIndex y) -> OpcodeType {
    return 0x8003 | (x << 12) | (y << 8);
  }
  auto AddReg(RegisterIndex x, RegisterIndex y) -> OpcodeType {
    return 0x8004 | (x << 12) | (y << 8);
  }
  auto SubReg(RegisterIndex x, RegisterIndex y) -> OpcodeType {
    return 0x8005 | (x << 12) | (y << 8);
  }
  auto ShiftRight(RegisterIndex x, RegisterIndex y) -> OpcodeType {
    return 0x8006 | (x << 12) | (y << 8);
  }
  auto SubNReg(RegisterIndex x, RegisterIndex y) -> OpcodeType {
    return 0x8007 | (x << 12) | (y << 8);
  }
  auto ShiftLeft(RegisterIndex x, RegisterIndex y) -> OpcodeType {
    return 0x800E | (x << 12) | (y << 8);
  }
  auto SkipNotEqual(RegisterIndex x, RegisterIndex y) -> OpcodeType {
    return 0x9000 | (x << 12) | (y << 8);
  }

  auto LoadI(C8::MemoryAddress addr) -> OpcodeType {
    return 0xA000 | addr;
  }

  auto JumpIndirect(C8::MemoryAddress addr) -> OpcodeType {
    return 0xB000 | addr;
  }
  auto Rand(RegisterIndex x, C8::MemoryValue kk) -> OpcodeType {
    return 0xC000 | (x << 12) | kk;
  }

  auto LoadDelayTimer(RegisterIndex x) -> OpcodeType {
    return 0xF007 | (x << 12);
  }

  auto SetDelayTimer(RegisterIndex x) -> OpcodeType {
    return 0xF015 | (x << 12);
  }

  auto AddI(RegisterIndex x) -> OpcodeType {
    return 0xF01E | (x << 12);
  }
  auto LoadSprite(RegisterIndex x) -> OpcodeType {
    return 0xF029 | (x << 12);
  }
  auto StoreBCD(RegisterIndex x) -> OpcodeType {
    return 0xF033 | (x << 12);
  }
  auto StoreRegistersToI(RegisterIndex x) -> OpcodeType {
    return 0xF055 | (x << 12);
  }
  auto LoadRegistersFromI(RegisterIndex x) -> OpcodeType {
    return 0xF065 | (x << 12);
  }
}  // namespace Assemble

class Chip8InstEmu : public testing::Test {
protected:
  C8::Emulator emulator; // NOLINT

  Chip8InstEmu()
      : emulator(std::make_unique<C8::Registers>(),
                 std::make_unique<C8::CPU>(emulator),
                 std::make_unique<C8::Memory>()) {}

  void InjectInst(C8::MemoryAddress addr, OpcodeType opcode) {
    auto *memory = emulator.GetMemoryPtr();
    memory->SetMemory(addr, (opcode & 0xFF00) >> 8);
    memory->SetMemory(addr + 1, opcode & 0xFF);
  }

  void Step(int n = 1) {
    for (int i = 0; i < n; i++) {
      emulator.Fetch();
      emulator.Decode();
      emulator.Execute();
    }
  }
};
TEST_F(Chip8InstEmu, Jump) {
  constexpr C8::MemoryAddress JUMPED_ADDR = 0x123;
  InjectInst(C8::Registers::CHIP8_INITIAL_ADDRESS,
             Assemble::JumpTo(JUMPED_ADDR));
  Step();
  EXPECT_EQ(emulator.GetRegistersPtr()->GetProgramCounter(), JUMPED_ADDR);
}
TEST_F(Chip8InstEmu, RetFromSubroutine) {
  constexpr C8::MemoryAddress JUMPED_ADDR = 0x123;
  InjectInst(C8::Registers::CHIP8_INITIAL_ADDRESS,
             Assemble::CallSub(JUMPED_ADDR));
  InjectInst(JUMPED_ADDR, Assemble::Return());
  Step(2);
  EXPECT_EQ(emulator.GetRegistersPtr()->GetProgramCounter(),
            C8::Registers::CHIP8_INITIAL_ADDRESS);
}
TEST_F(Chip8InstEmu, CallSub) {
  constexpr C8::MemoryAddress JUMPED_ADDR = 0x123;
  InjectInst(C8::Registers::CHIP8_INITIAL_ADDRESS,
             Assemble::CallSub(JUMPED_ADDR));
  Step();
  EXPECT_EQ(emulator.GetRegistersPtr()->GetProgramCounter(), JUMPED_ADDR);
}
