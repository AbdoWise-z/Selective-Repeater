// Function to perform XOR between two binary strings
std::string xorStrings(const std::string& a, const std::string& b) {
    std::string result;
    for (size_t i = 0; i < b.size(); ++i) {
        result += (a[i] == b[i]) ? '0' : '1';
    }
    return result;
}

// Function to compute CRC
static inline std::string calculateCRC(std::string bits, std::string generator) {
    int generatorSize = generator.size();

    // Append zeros equal to the size of the generator - 1 to the input bits
    bits += std::string(generatorSize - 1, '0');

    std::string remainder = bits.substr(0, generatorSize);

    for (size_t i = generatorSize; i <= bits.size(); ++i) {
        // Perform XOR if the leftmost bit is '1'
        if (remainder[0] == '1') {
            remainder = xorStrings(remainder, generator);
        }

        // Shift left and append the next bit from bits if available
        if (i < bits.size()) {
            remainder = remainder.substr(1) + bits[i];
        } else {
            remainder = remainder.substr(1);
        }
    }

    return remainder;
}

// Function to evaluate CRC
static inline bool evaluateCRC(const std::string& transmitted, const std::string& generator) {
    std::string remainder = calculateCRC(transmitted, generator);
    return remainder.find('1') == std::string::npos; // Valid if remainder is all zeros
}
