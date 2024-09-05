#include "utils.hpp"
#include "cpu.hpp"
#include <string>
#include <unordered_map>
#include <map>
#include <utility>
#include <vector>

class FailedCompilation : public std::exception {
private:
    const char *errorMsg;
public:
    FailedCompilation(const char *errorMsg) {
        this->errorMsg = errorMsg;    
    }
    const char *what() const noexcept override {
        return errorMsg;
    }
};

typedef void (CPU::*execute_fn)(std::vector<int32_t>);

std::vector<std::pair<std::string, execute_fn>> CPU::COMMANDS = std::vector<std::pair<std::string, execute_fn>>();

CPU::CPU() {
    memory = std::unordered_map<int32_t, int8_t>();

    COMMANDS.push_back({"add", &CPU::add_execute});
    COMMANDS.push_back({"sub", &CPU::sub_execute});
    COMMANDS.push_back({"and", &CPU::and_execute});
    COMMANDS.push_back({"or", &CPU::or_execute});
    COMMANDS.push_back({"xor", &CPU::xor_execute});
    COMMANDS.push_back({"sll", &CPU::sll_execute});
    COMMANDS.push_back({"srl", &CPU::srl_execute});
    COMMANDS.push_back({"sra", &CPU::sra_execute});
    COMMANDS.push_back({"slt", &CPU::slt_execute});
    COMMANDS.push_back({"sltu", &CPU::sltu_execute});
    COMMANDS.push_back({"addi", &CPU::addi_execute});  
    COMMANDS.push_back({"andi", &CPU::andi_execute});
    COMMANDS.push_back({"ori", &CPU::ori_execute});
    COMMANDS.push_back({"xori", &CPU::xori_execute});
    COMMANDS.push_back({"slli", &CPU::slli_execute});
    COMMANDS.push_back({"srli", &CPU::srli_execute});
    COMMANDS.push_back({"srai", &CPU::srai_execute});
    COMMANDS.push_back({"slti", &CPU::slti_execute});
    COMMANDS.push_back({"sltiu", &CPU::sltiu_execute});
    COMMANDS.push_back({"lb", &CPU::lb_execute});
    COMMANDS.push_back({"lbu", &CPU::lbu_execute});
    COMMANDS.push_back({"lh", &CPU::lh_execute});
    COMMANDS.push_back({"lhu", &CPU::lhu_execute});
    COMMANDS.push_back({"lw", &CPU::lw_execute});
    COMMANDS.push_back({"sb", &CPU::sb_execute});
    COMMANDS.push_back({"sh", &CPU::sh_execute});
    COMMANDS.push_back({"sw", &CPU::sw_execute});
    COMMANDS.push_back({"beq", &CPU::beq_execute});
    COMMANDS.push_back({"bge", &CPU::bge_execute});
    COMMANDS.push_back({"bgeu", &CPU::bgeu_execute});
    COMMANDS.push_back({"blt", &CPU::blt_execute});
    COMMANDS.push_back({"bltu", &CPU::bltu_execute});
    COMMANDS.push_back({"bne", &CPU::bne_execute});
    COMMANDS.push_back({"jal", &CPU::jal_execute});
    COMMANDS.push_back({"jalr", &CPU::jalr_execute});
    COMMANDS.push_back({"auipc", &CPU::auipc_execute});
    COMMANDS.push_back({"lui", &CPU::lui_execute});
    COMMANDS.push_back({"mul", &CPU::mul_execute});
}

// Convert list of string arguments to list of integer arguments
std::vector<int> CPU::argsStoi(std::vector<std::string> args) {
    static std::map<std::string, int> registerMappings = std::map<std::string, int> {
        {"zero", 0},
        {"ra", 1},
        {"sp", 2},
        {"gp", 3},
        {"tp", 4},
        {"t0", 5},
        {"t1", 6},
        {"t2", 7},
        {"s0", 8},
        {"s1", 9},
        {"a0", 10},
        {"a1", 11},
        {"a2", 12},
        {"a3", 13},
        {"a4", 14},
        {"a5", 15},
        {"a6", 16},
        {"a7", 17},
        {"s2", 18},
        {"s3", 19},
        {"s4", 20},
        {"s5", 21},
        {"s6", 22},
        {"s7", 23},
        {"s8", 24},
        {"s9", 25},
        {"s10", 26},
        {"s11", 27},
        {"t3", 28},
        {"t4", 29},
        {"t5", 30},
        {"t6", 31}
    };

    std::vector<int> intArgs = std::vector<int>();
    try {
        for (std::string arg : args) {
            if (arg[0] == 'x') {
                int registerNumber = std::stoi(arg.substr(1, arg.size() - 1));
                if (registerNumber < 0 || registerNumber > 31) {
                    throw FailedCompilation("Invalid argument to assembly instruction");
                }
                intArgs.push_back(registerNumber);
            }
            else if (registerMappings.contains(arg)) {
                intArgs.push_back(registerMappings[arg]);
            }
            else {
                intArgs.push_back(std::stoi(arg));
            }
        }
    }
    // Errors when we have an invalid string argument in the assembly
    catch (std::exception e) {
        throw FailedCompilation("Invalid argument to assembly instruction");     
    }
    return intArgs;
}



// Verify that a full command has valid form
void CPU::verifyCommand(std::string command) {
    std::vector<std::string> args = strSplit(command, ' ');

    // Blank line in code
    if (args.empty()) {
        return;
    }
    
    std::string commandName = args[0];
    verifyCommandName(commandName);
    args.erase(args.begin());

    std::vector<int> argList = argsStoi(args);
    verifyArgListLength(commandName, argList);
}

// Verify that the command has the correct number of arguments
void CPU::verifyArgListLength(std::string commandName, std::vector<int> argList) {
    static const std::vector<std::pair<std::string, int>> ARG_LENGTHS = {
        {},
        {},
        {},
        {},
        {},
        {},
        {},

    };
}

// Verify that a command name exists
void CPU::verifyCommandName(std::string commandName) {
    for (auto command : COMMANDS) {
        if (commandName == command.first) {
            return;
        }
    }
    throw FailedCompilation("Invalid RISC-V command used in code");
}

// Get the execution function for instruction with name "command"
execute_fn CPU::getExecuteFunction(std::string commandName) {
    for (int i = 0; i < NUM_COMMANDS; i++) {
         if (commandName == COMMANDS[i].first) {
             return COMMANDS[i].second;
         }
    }
}

// Executes the given command
void CPU::executeLine(std::string command) {
    verifyCommand(command);
    // Replace commas with spaces
    for (int i = 0; i < command.size(); i++) {
        if (command[i] == ',') {
            command[i] = ' '; 
        }
    }
    std::vector<std::string> args = strSplit(command, ' ');
    execute_fn execution_fn = getExecuteFunction(args[0]);
    args.erase(args.begin());
    (*this.*execution_fn)(argsStoi(args));
}

// Memory state functions
// Writes numBytes bytes from value to memory at given address
void CPU::writeToMemory(int16_t address, int32_t value, uint8_t numBytes) {
    for (int byteNum = 0; byteNum < numBytes; byteNum++) {
        writeMemoryByte(address + 4 * byteNum, (int8_t) (value >> (8 * byteNum)));
    }
}

// Loads byte from memory at given address
int8_t CPU::loadByteFromMemory(int32_t address) {
    return readMemoryByte(address);
}

// Loads halfword from memory at given address
int16_t CPU::loadHalfwordFromMemory(int32_t address) {
    return mergeBytes(readMemoryByte(address + 4), readMemoryByte(address));
}

// Loads word from memory at given addresss
int32_t CPU::loadWordFromMemory(int32_t address) {
    return mergeBytes(readMemoryByte(address + 12), readMemoryByte(address + 8), readMemoryByte(address + 4), readMemoryByte(address));
}

// Reads a byte from memory at the specified address
int8_t CPU::readMemoryByte(int32_t address) {
    auto it = memory.find(address);
    if (it != memory.end()) {
        return it->second;
    }
    return 0;
}

// Writes a memory byte to specified address
void CPU::writeMemoryByte(int32_t address, int8_t value) {
    memory[address] = value;
}
