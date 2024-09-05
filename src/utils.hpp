#ifndef INSTRUCTION_EXECUTE_INDLUDED_HPP
#define INSTRUCTION_EXECUTE_INDLUDED_HPP

#include <string>

int16_t mergeBytes(uint8_t, uint8_t);
int32_t mergeBytes(uint8_t, uint8_t, uint8_t, uint8_t);
int32_t signExtend(int32_t, uint8_t);
std::vector<std::string> strSplit(std::string, char);

#endif
