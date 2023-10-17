#ifndef CHIP8_MEMORY_H
#define CHIP8_MEMORY_H
#include <array>
namespace C8 {
  class Memory {
    private:
      using  Byte=unsigned char;
      static constexpr int MEMORY_SIZE = 4096;
      std::array<Byte, MEMORY_SIZE> m_Memory;
    public:

  };
} // namespace C8

#endif
