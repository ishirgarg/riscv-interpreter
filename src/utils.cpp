#ifndef UTILS_INCLUDED_H
#define UTILS_INCLUDED_H

#include <inttypes.h>
#include <string>
#include <vector>

int16_t mergeBytes(uint8_t byte1, uint8_t byte0) {
    return ((int16_t) byte1 << 8) | byte0;
}

int32_t mergeBytes(uint8_t byte3, uint8_t byte2, uint8_t byte1, uint8_t byte0) {
    return ((uint32_t) byte3 << 24) | ((uint32_t) byte2 << 16) | ((uint32_t) byte1 << 8) | (uint32_t) byte0;
}

// Sign extend value using the rightmost numBits bits
int32_t signExtend(int32_t value, uint8_t numBits) {
    return (value && (1 << (numBits - 1))) ? ((value << (32 - numBits)) >> (32 - numBits)) : (((uint32_t) value << (32 - numBits)) >> (32 - numBits));
}

// Splits str into words delimited by character del; returns a vector words without del
std::vector<std::string> strSplit(std::string str, char del) {
    std::vector<std::string> args = std::vector<std::string>();
    int startIndex = 0;
    int strLength = 0;

    for (int i = 0; i < str.size() && startIndex + strLength <= str.size(); i++) {
        if (str[i] == del) {
            if (strLength > 0) {
                args.push_back(str.substr(startIndex, strLength));
            }
            strLength = 0;
            startIndex = i + 1;
        }
        else {
            strLength++;
        }
    }

    if (strLength > 0) {
        args.push_back(str.substr(startIndex, strLength));
    }

    return args;
} 
#endif

