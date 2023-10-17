#ifndef __MEMORY_H
#define __MEMORY_H

template<typename Addr, typename Byte>
class BaseMemory {
public:
  virtual Byte GetMemory(Addr) = 0;
  virtual void SetMemory(Addr, Byte) = 0;
  virtual ~BaseMemory() = default;
};

#endif
