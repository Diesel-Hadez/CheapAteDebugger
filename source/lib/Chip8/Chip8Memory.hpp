#ifndef CHIP8_MEMORY_H
#define CHIP8_MEMORY_H
#include <array>
namespace C8 {
  using MemoryAddress=std::size_t;
  using Byte=unsigned char;
  using MemoryValue=Byte;
  class Memory {
    public:
      static constexpr int MEMORY_SIZE = 4096;
    private:
      std::array<MemoryValue, MEMORY_SIZE> m_Memory;
    public:
      void SetMemory(MemoryAddress addr, MemoryValue val) {
        if (addr >= MEMORY_SIZE) return;
        m_Memory.at(addr) = val;
      }
      MemoryValue GetMemory(MemoryAddress addr) {
        return m_Memory.at(addr);
      }

  };
} // namespace C8

#endif
