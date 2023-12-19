#ifndef CHIP8_MEMORY_H
#define CHIP8_MEMORY_H
#include <array>
#include <stack>
namespace C8 {
  using MemoryAddress = std::size_t;
  using Byte = unsigned char;
  using MemoryValue = Byte;
  class Memory {
  public:
    static constexpr int MEMORY_SIZE = 4096;

  private:
    std::array<MemoryValue, MEMORY_SIZE> m_Memory {};
    std::stack<MemoryAddress> m_Stack;

  public:
    void PushStack(MemoryAddress addr) { m_Stack.push(addr); }
    auto PopStack() -> MemoryAddress {
      auto ret = m_Stack.top();
      m_Stack.pop();
      return ret;
    }
    void SetMemory(MemoryAddress addr, MemoryValue val) {
      if (addr >= MEMORY_SIZE) {
        return;
      }
      m_Memory.at(addr) = val;
    }
    auto GetMemory(MemoryAddress addr) -> MemoryValue {
      return m_Memory.at(addr);
    }
  };
}  // namespace C8

#endif
