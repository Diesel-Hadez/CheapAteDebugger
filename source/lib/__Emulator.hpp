#ifndef __EMULATOR_H
#define __EMULATOR_H

class BaseEmulator {
public:
  virtual void Fetch()=0;
  virtual void Decode()=0;
  virtual void Execute()=0;
  virtual ~BaseEmulator()=default;
};

#endif
