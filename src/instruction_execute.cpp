#include "cpu.hpp"
#include "utils.hpp"
#include <vector>
//R-TYPES

void CPU::add_execute(std::vector<int32_t> args) {
    registers[args[0]] = registers[args[1]] + registers[args[2]];
}

void CPU::sub_execute(std::vector<int32_t> args) {
    registers[args[0]] = registers[args[1]] - registers[args[2]];
}

void CPU::and_execute(std::vector<int32_t> args) {
    registers[args[0]] = registers[args[1]] & registers[args[2]];
}

void CPU::or_execute(std::vector<int32_t> args) {
    registers[args[0]] = registers[args[1]] | registers[args[2]];
}

void CPU::xor_execute(std::vector<int32_t> args) {
    registers[args[0]] = registers[args[1]] ^ registers[args[2]];
}

void CPU::sll_execute(std::vector<int32_t> args) {
    registers[args[0]] = registers[args[1]] << registers[args[2]];
}

void CPU::srl_execute(std::vector<int32_t> args) {
    registers[args[0]] = (uint32_t) registers[args[1]] >> registers[args[2]];
}

void CPU::sra_execute(std::vector<int32_t> args) {
    registers[args[0]] = registers[args[1]] >> registers[args[2]];
}

void CPU::slt_execute(std::vector<int32_t> args) {
    registers[args[0]] = (registers[args[1]] < registers[args[2]]) ? 1 : 0;
}

void CPU::sltu_execute(std::vector<int32_t> args) {
    registers[args[0]] = ((uint32_t) registers[args[1]] < (uint32_t) registers[args[2]]) ? 1 : 0;
}

// I-TYPES

void CPU::addi_execute(std::vector<int32_t> args) {
    registers[args[0]] = registers[args[1]] + args[2];
}

void CPU::andi_execute(std::vector<int32_t> args) {
    registers[args[0]] = registers[args[1]] & signExtend(args[2], 12);
}

void CPU::ori_execute(std::vector<int32_t> args) {
    registers[args[0]] = registers[args[1]] | signExtend(args[2], 12);
}

void CPU::xori_execute(std::vector<int32_t> args) {
    registers[args[0]] = registers[args[1]] ^ signExtend(args[2], 12);
}

void CPU::slli_execute(std::vector<int32_t> args) {
    registers[args[0]] = registers[args[1]] << args[2];
}

void CPU::srli_execute(std::vector<int32_t> args) {
    registers[args[0]] = (uint32_t) registers[args[1]] >> args[2];
}

void CPU::srai_execute(std::vector<int32_t> args) {
    registers[args[0]] = registers[args[1]] >> args[2];
}

void CPU::slti_execute(std::vector<int32_t> args) {
    registers[args[0]] = (registers[args[1]] < signExtend(args[2], 12)) ? 1 : 0;
}

void CPU::sltiu_execute(std::vector<int32_t> args) {
    registers[args[0]] = ((uint32_t) registers[args[1]] < (uint32_t) signExtend(args[2], 12)) ? 1 : 0;
}

// LOAD INSTRUCTIONS

void CPU::lb_execute(std::vector<int32_t> args) {
    registers[args[0]] = signExtend(loadByteFromMemory(signExtend(args[2], 12) + registers[args[1]]), 8);
}

void CPU::lbu_execute(std::vector<int32_t> args) {
    registers[args[0]] = (uint8_t) loadByteFromMemory(signExtend(args[2], 12) + registers[args[1]]);
}

void CPU::lh_execute(std::vector<int32_t> args) {
    registers[args[0]] = signExtend(loadHalfwordFromMemory(signExtend(args[2], 12) + registers[args[1]]), 16);
}

void CPU::lhu_execute(std::vector<int32_t> args) {
    registers[args[0]] = (uint16_t) loadHalfwordFromMemory(signExtend(args[2], 12) + registers[args[1]]);
}

void CPU::lw_execute(std::vector<int32_t> args) {
    registers[args[0]] = loadWordFromMemory(signExtend(args[2], 12) + registers[args[1]]); 
}

// STORE INSTRUCTIONS
void CPU::sb_execute(std::vector<int32_t> args) {
    writeToMemory(args[1] + signExtend(args[2], 12), args[0], 1);
}

void CPU::sh_execute(std::vector<int32_t> args) {
    writeToMemory(args[1] + signExtend(args[2], 12), args[0], 2);
}

void CPU::sw_execute(std::vector<int32_t> args) {
    writeToMemory(args[1] + signExtend(args[2], 12), args[0], 4);
}

void CPU::beq_execute(std::vector<int32_t> args) {
    if (registers[args[0]] == registers[args[1]]) {
        PC += args[2];
    }
}

// BRANCH INSTRUCTIONS
void CPU::bge_execute(std::vector<int32_t> args) {
    if (registers[args[0]] >= registers[args[1]]) {
        PC += args[2];
    }

}

void CPU::bgeu_execute(std::vector<int32_t> args) {
    if ((uint32_t) registers[args[0]] == (uint32_t) registers[args[1]]) {
        PC += args[2];
    }
}

void CPU::blt_execute(std::vector<int32_t> args) {
    if (registers[args[0]] < registers[args[1]]) {
        PC += args[2];
    }
}

void CPU::bltu_execute(std::vector<int32_t> args) {
    if ((uint32_t) registers[args[0]] < (uint32_t) registers[args[1]]) {
        PC += args[2];
    }
}

void CPU::bne_execute(std::vector<int32_t> args) {
    if (registers[args[0]] != registers[args[1]]) {
        PC += args[2];
    }
}

// JUMP INSTRUCTIONS
void CPU::jal_execute(std::vector<int32_t> args) {
    registers[args[1]] = PC + 4;
    PC += args[2];
}

void CPU::jalr_execute(std::vector<int32_t> args) {
    registers[args[0]] = PC + 4;
    PC = registers[args[1]] + args[2];
}

// U-TYPE INSTRUCTIONS
void CPU::auipc_execute(std::vector<int32_t> args) {
    registers[args[0]] = PC + (args[1] << 12);
}

void CPU::lui_execute(std::vector<int32_t> args) {
    registers[args[0]] = args[1] << 12;
}

// EXTENSIONS/PSEUDO-INSTRUCTIONS
void CPU::mul_execute(std::vector<int32_t> args) {
    registers[args[0]] = registers[args[1]] * registers[args[2]];
}
