#ifndef CHIP8_ACTIONS_H
#define CHIP8_ACTIONS_H
#include "../__InstructionAction.hpp"
#include "Chip8/Chip8Memory.hpp"
#include "Chip8/Chip8Registers.hpp"


namespace C8::Opcode {
  enum class ArgsType {
    CONSTANT,
    NNN,
    XKK,
    XY,
    XYN,
    X
  };

  using Literal=unsigned short;
  using Nibble=unsigned short;
  union Args {
    unsigned short NNN;
    // X Register and KK literal.
    struct {
      C8::Register x;
      Literal kk;
    } XKK;
    struct {
      C8::Register x;
      C8::Register y;
    } XY;
    
    struct {
      C8::Register x;
      C8::Register y;
      Nibble n;
    } XYN;

    C8::Register X;

  };

  constexpr inline Args DecodeArgs(unsigned short data, ArgsType type) {
    Args ret{};
    constexpr auto ToReg = [](unsigned short v) -> C8::Register {return static_cast<C8::Register>(v);};
    switch (type) {
      case ArgsType::NNN:
        ret.NNN = data & 0x0FFF;
      break;
      case ArgsType::XKK:
        ret.XKK.x = ToReg(data & 0x0F00);
        ret.XKK.kk = data & 0x00FF;
      break;
      case ArgsType::XY:
        ret.XY.x = ToReg(data & 0x0F00);
        ret.XY.y = ToReg(data & 0x00F0);
      break;
      case ArgsType::XYN:
        ret.XYN.x = ToReg(data & 0x0F00);
        ret.XYN.y = ToReg(data & 0x00F0);
        ret.XYN.n = data & 0x000F;
      break;
      case ArgsType::X:
        ret.X = ToReg(data & 0x0F00);
      break;
      default:
      break;
    };
    

    return ret;
  }
} // namespace C8::Opcode

namespace C8::Actions {

    class BaseChip8InstructionAction: public BaseInstructionAction {
    protected:
        C8::Emulator& m_Emulator;
        constexpr static int OPCODE_SIZE = 2;
        
    public:
        explicit BaseChip8InstructionAction(C8::Emulator& emulator) : 
        m_Emulator(emulator)
        {
            m_StepCount = OPCODE_SIZE;

        }

        virtual void Execute()=0; 
      virtual ~BaseChip8InstructionAction(){}
    };

    class ClearScreen: public BaseChip8InstructionAction {
            
    public:
        explicit ClearScreen(C8::Emulator& emulator) : 
        BaseChip8InstructionAction(emulator) {

        }

        void Execute() override {
          m_Emulator.ClearScreen();
        }
    };

    

    class Ret: public BaseChip8InstructionAction {
            
    public:
        explicit Ret(C8::Emulator& emulator) : 
        BaseChip8InstructionAction(emulator) {

        }

        void Execute() override {
            auto ret = m_Emulator.GetMemoryPtr()->PopStack();
            m_Emulator.GetRegistersPtr()->SetProgramCounter(ret);
        }
    };

    

    class Jump: public BaseChip8InstructionAction {
            
        C8::MemoryRegister m_Addr;

    public:
        Jump(C8::MemoryRegister addr, C8::Emulator& emulator) : 
        BaseChip8InstructionAction(emulator),
        m_Addr(addr) {

        }

        void Execute() override {
            // Prevent stepping over this instruction
            // since we're directly modifying the program counter
            m_StepCount = 0;
            m_Emulator.GetRegistersPtr()->SetProgramCounter(m_Addr);
        }
    };

    

    class Call: public BaseChip8InstructionAction {
            
        C8::MemoryRegister m_Addr;

    public:
        Call(C8::MemoryRegister addr, C8::Emulator& emulator) : 
        BaseChip8InstructionAction(emulator),
        m_Addr(addr) {

        }

        void Execute() override {
            m_Emulator.GetMemoryPtr()->PushStack(m_Emulator.GetRegistersPtr()->GetProgramCounter()+OPCODE_SIZE); 
            m_Emulator.GetRegistersPtr()->SetProgramCounter(m_Addr);
        }
    };

    

    class SkipEqualImm: public BaseChip8InstructionAction {
            
        C8::Register m_X;
        C8::MemoryValue m_Value;

    public:
        SkipEqualImm(C8::Register x, C8::MemoryValue value, C8::Emulator& emulator) : 
        BaseChip8InstructionAction(emulator),
        m_X(x),
        m_Value(value) {

        }

        void Execute() override {

        }
    };

    

    class SkipNotEqualImm: public BaseChip8InstructionAction {
            
        C8::Register m_X;
        C8::MemoryValue m_Value;

    public:
        SkipNotEqualImm(C8::Register x, C8::MemoryValue value, C8::Emulator& emulator) : 
        BaseChip8InstructionAction(emulator),
        m_X(x),
        m_Value(value) {

        }

        void Execute() override {

        }
    };

    

    class SkipEqualReg: public BaseChip8InstructionAction {
            
        C8::Register m_X;
        C8::Register m_Y;

    public:
        SkipEqualReg(C8::Register x, C8::Register y, C8::Emulator& emulator) : 
        BaseChip8InstructionAction(emulator),
        m_X(x),
        m_Y(y) {

        }

        void Execute() override {

        }
    };

    

    class LoadRegImm: public BaseChip8InstructionAction {
            
        C8::Register m_X;
        C8::MemoryValue m_Value;

    public:
        LoadRegImm(C8::Register x, C8::MemoryValue value, C8::Emulator& emulator) : 
        BaseChip8InstructionAction(emulator),
        m_X(x),
        m_Value(value) {

        }

        void Execute() override {

        }
    };

    

    class AddRegImm: public BaseChip8InstructionAction {
            
        C8::Register m_X;
        C8::MemoryValue m_Value;

    public:
        AddRegImm(C8::Register x, C8::MemoryValue value, C8::Emulator& emulator) : 
        BaseChip8InstructionAction(emulator),
        m_X(x),
        m_Value(value) {

        }

        void Execute() override {

        }
    };

    

    class Load: public BaseChip8InstructionAction {
            
        C8::Register m_X;
        C8::Register m_Y;

    public:
        Load(C8::Register x, C8::Register y, C8::Emulator& emulator) : 
        BaseChip8InstructionAction(emulator),
        m_X(x),
        m_Y(y) {

        }

        void Execute() override {

        }
    };

    

    class Or: public BaseChip8InstructionAction {
            
        C8::Register m_X;
        C8::Register m_Y;

    public:
        Or(C8::Register x, C8::Register y, C8::Emulator& emulator) : 
        BaseChip8InstructionAction(emulator),
        m_X(x),
        m_Y(y) {

        }

        void Execute() override {

        }
    };

    

    class And: public BaseChip8InstructionAction {
            
        C8::Register m_X;
        C8::Register m_Y;

    public:
        And(C8::Register x, C8::Register y, C8::Emulator& emulator) : 
        BaseChip8InstructionAction(emulator),
        m_X(x),
        m_Y(y) {

        }

        void Execute() override {

        }
    };

    

    class Xor: public BaseChip8InstructionAction {
            
        C8::Register m_X;
        C8::Register m_Y;

    public:
        Xor(C8::Register x, C8::Register y, C8::Emulator& emulator) : 
        BaseChip8InstructionAction(emulator),
        m_X(x),
        m_Y(y) {

        }

        void Execute() override {

        }
    };

    

    class Add: public BaseChip8InstructionAction {
            
        C8::Register m_X;
        C8::Register m_Y;

    public:
        Add(C8::Register x, C8::Register y, C8::Emulator& emulator) : 
        BaseChip8InstructionAction(emulator),
        m_X(x),
        m_Y(y) {

        }

        void Execute() override {

        }
    };

    

    class Subtract: public BaseChip8InstructionAction {
            
        C8::Register m_X;
        C8::Register m_Y;

    public:
        Subtract(C8::Register x, C8::Register y, C8::Emulator& emulator) : 
        BaseChip8InstructionAction(emulator),
        m_X(x),
        m_Y(y) {

        }

        void Execute() override {

        }
    };

    

    class ShiftRight: public BaseChip8InstructionAction {
            
        C8::Register m_X;
        C8::Register m_Y;

    public:
        ShiftRight(C8::Register x, C8::Register y, C8::Emulator& emulator) : 
        BaseChip8InstructionAction(emulator),
        m_X(x),
        m_Y(y) {

        }

        void Execute() override {

        }
    };

    

    class SubtractNoBorrow: public BaseChip8InstructionAction {
            
        C8::Register m_X;
        C8::Register m_Y;

    public:
        SubtractNoBorrow(C8::Register x, C8::Register y, C8::Emulator& emulator) : 
        BaseChip8InstructionAction(emulator),
        m_X(x),
        m_Y(y) {

        }

        void Execute() override {

        }
    };

    

    class ShiftLeft: public BaseChip8InstructionAction {
            
        C8::Register m_X;
        C8::Register m_Y;

    public:
        ShiftLeft(C8::Register x, C8::Register y, C8::Emulator& emulator) : 
        BaseChip8InstructionAction(emulator),
        m_X(x),
        m_Y(y) {

        }

        void Execute() override {

        }
    };

    

    class SkipNotEqualReg: public BaseChip8InstructionAction {
            
        C8::Register m_X;
        C8::Register m_Y;

    public:
        SkipNotEqualReg(C8::Register x, C8::Register y, C8::Emulator& emulator) : 
        BaseChip8InstructionAction(emulator),
        m_X(x),
        m_Y(y) {

        }

        void Execute() override {

        }
    };

    

    class LoadIndirect: public BaseChip8InstructionAction {
            
        C8::MemoryRegister m_Addr;

    public:
        LoadIndirect(C8::MemoryRegister addr, C8::Emulator& emulator) : 
        BaseChip8InstructionAction(emulator),
        m_Addr(addr) {

        }

        void Execute() override {

        }
    };

    

    class JumpIndirect: public BaseChip8InstructionAction {
            
        C8::MemoryRegister m_Addr;

    public:
        JumpIndirect(C8::MemoryRegister addr, C8::Emulator& emulator) : 
        BaseChip8InstructionAction(emulator),
        m_Addr(addr) {

        }

        void Execute() override {

        }
    };

    

    class Random: public BaseChip8InstructionAction {
            
        C8::Register m_X;
        C8::MemoryValue m_Value;

    public:
        Random(C8::Register x, C8::MemoryValue value, C8::Emulator& emulator) : 
        BaseChip8InstructionAction(emulator),
        m_X(x),
        m_Value(value) {

        }

        void Execute() override {

        }
    };

    

    class Draw: public BaseChip8InstructionAction {
            
        C8::Register m_X;
        C8::Register m_Y;
        C8::MemoryValue m_Value;

    public:
        Draw(C8::Register x, C8::Register y, C8::MemoryValue value, C8::Emulator& emulator) : 
        BaseChip8InstructionAction(emulator),
        m_X(x),
        m_Y(y),
        m_Value(value) {

        }

        void Execute() override {
          auto x = m_Emulator.GetRegister(m_X);
          auto y = m_Emulator.GetRegister(m_Y);
          auto height = m_Value;
          m_Emulator.DrawScreen(x, y, height);
        }
    };

    

    class SkipNextIfKeyPressed: public BaseChip8InstructionAction {
            
        C8::Register m_X;

    public:
        SkipNextIfKeyPressed(C8::Register x, C8::Emulator& emulator) : 
        BaseChip8InstructionAction(emulator),
        m_X(x) {

        }

        void Execute() override {

        }
    };

    

    class SkipNextIfKeyNotPressed: public BaseChip8InstructionAction {
            
        C8::Register m_X;

    public:
        SkipNextIfKeyNotPressed(C8::Register x, C8::Emulator& emulator) : 
        BaseChip8InstructionAction(emulator),
        m_X(x) {

        }

        void Execute() override {

        }
    };

    

    class LoadDelayTimer: public BaseChip8InstructionAction {
            
        C8::Register m_X;

    public:
        LoadDelayTimer(C8::Register x, C8::Emulator& emulator) : 
        BaseChip8InstructionAction(emulator),
        m_X(x) {

        }

        void Execute() override {

        }
    };

    

    class WaitAndStoreKey: public BaseChip8InstructionAction {
            
        C8::Register m_X;

    public:
        WaitAndStoreKey(C8::Register x, C8::Emulator& emulator) : 
        BaseChip8InstructionAction(emulator),
        m_X(x) {

        }

        void Execute() override {

        }
    };

    

    class SetDelayTimer: public BaseChip8InstructionAction {
            
        C8::Register m_X;

    public:
        SetDelayTimer(C8::Register x, C8::Emulator& emulator) : 
        BaseChip8InstructionAction(emulator),
        m_X(x) {

        }

        void Execute() override {

        }
    };

    

    class SetSoundTimer: public BaseChip8InstructionAction {
            
        C8::Register m_X;

    public:
        SetSoundTimer(C8::Register x, C8::Emulator& emulator) : 
        BaseChip8InstructionAction(emulator),
        m_X(x) {

        }

        void Execute() override {

        }
    };

    

    class AddIRegister: public BaseChip8InstructionAction {
            
        C8::Register m_X;

    public:
        AddIRegister(C8::Register x, C8::Emulator& emulator) : 
        BaseChip8InstructionAction(emulator),
        m_X(x) {

        }

        void Execute() override {

        }
    };

    

    class LoadIRegister: public BaseChip8InstructionAction {
            
        C8::Register m_X;

    public:
        LoadIRegister(C8::Register x, C8::Emulator& emulator) : 
        BaseChip8InstructionAction(emulator),
        m_X(x) {

        }

        void Execute() override {

        }
    };

    

    class LoadBCDReg: public BaseChip8InstructionAction {
            
        C8::Register m_X;

    public:
        LoadBCDReg(C8::Register x, C8::Emulator& emulator) : 
        BaseChip8InstructionAction(emulator),
        m_X(x) {

        }

        void Execute() override {

        }
    };

    

    class StoreRegistersToI: public BaseChip8InstructionAction {
            
        C8::Register m_X;

    public:
        StoreRegistersToI(C8::Register x, C8::Emulator& emulator) : 
        BaseChip8InstructionAction(emulator),
        m_X(x) {

        }

        void Execute() override {

        }
    };

    

    class LoadRegistersFromI: public BaseChip8InstructionAction {
            
        C8::Register m_X;

    public:
        LoadRegistersFromI(C8::Register x, C8::Emulator& emulator) : 
        BaseChip8InstructionAction(emulator),
        m_X(x) {

        }

        void Execute() override {

        }
    };


}
#endif
