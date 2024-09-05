#ifndef CPU_HPP_INCLUDED
#define CPU_HPP_INCLUDED

#include <iostream>
#include <string>
#include <unordered_map>
class CPU {
private:
    typedef void (CPU::*execute_fn)(std::vector<int32_t>);
    const static int NUM_COMMANDS = 38; 
    static std::vector<std::pair<std::string, execute_fn>> COMMANDS;
       
    std::unordered_map<int32_t, int8_t> memory;
    int32_t registers[32];
    uint32_t PC;

    void writeToMemory(int16_t, int32_t, uint8_t);
    int8_t loadByteFromMemory(int32_t);
    int16_t loadHalfwordFromMemory(int32_t);
    int32_t loadWordFromMemory(int32_t);
    int8_t readMemoryByte(int32_t);
    void writeMemoryByte(int32_t, int8_t);

    void add_execute(std::vector<int32_t>);
    void sub_execute(std::vector<int32_t>);
    void and_execute(std::vector<int32_t>);
    void or_execute(std::vector<int32_t>);
    void xor_execute(std::vector<int32_t>);
    void sll_execute(std::vector<int32_t>);
    void srl_execute(std::vector<int32_t>);
    void sra_execute(std::vector<int32_t>);
    void slt_execute(std::vector<int32_t>);
    void sltu_execute(std::vector<int32_t>);
    void addi_execute(std::vector<int32_t>);
    void andi_execute(std::vector<int32_t>);
    void ori_execute(std::vector<int32_t>);
    void xori_execute(std::vector<int32_t>);
    void slli_execute(std::vector<int32_t>);
    void srli_execute(std::vector<int32_t>);
    void srai_execute(std::vector<int32_t>);
    void slti_execute(std::vector<int32_t>);
    void sltiu_execute(std::vector<int32_t>);
    void lb_execute(std::vector<int32_t>);
    void lbu_execute(std::vector<int32_t>);
    void lh_execute(std::vector<int32_t>);
    void lhu_execute(std::vector<int32_t>);
    void lw_execute(std::vector<int32_t>);
    void sb_execute(std::vector<int32_t>);
    void sh_execute(std::vector<int32_t>);
    void sw_execute(std::vector<int32_t>);
    void beq_execute(std::vector<int32_t>);
    void bge_execute(std::vector<int32_t>);
    void bgeu_execute(std::vector<int32_t>);
    void blt_execute(std::vector<int32_t>);
    void bltu_execute(std::vector<int32_t>);
    void bne_execute(std::vector<int32_t>);
    void jal_execute(std::vector<int32_t>);
    void jalr_execute(std::vector<int32_t>);
    void auipc_execute(std::vector<int32_t>);
    void lui_execute(std::vector<int32_t>);
    void mul_execute(std::vector<int32_t>);

    std::vector<int> argsStoi(std::vector<std::string>);

public:
    CPU();
    void verifyCommand(std::string);
    void verifyArgListLength(std::string, std::vector<int>);
    void verifyCommandName(std::string);
    execute_fn getExecuteFunction(std::string);
    void executeLine(std::string);
};

#endif
