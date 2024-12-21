static inline std::string performByteStuffing(std::string msg, char flag, char esc) {
    std::ostringstream output;
    output << flag;

    for (auto c : msg) {
        if (c == flag || c == esc) {
            output << esc;
        }
        output << c;
    }

    output << flag;
    return output.str();
}

static inline std::string reverseByteStuffing(std::string msg, char esc) {
    msg = msg.substr(1, msg.size() - 2);
    std::ostringstream output;
    bool dont_skip = false;
    for (auto c : msg) {
        if (c == esc && dont_skip == false) {
            dont_skip = true;
            continue;
        }
        dont_skip = false;
        output << c;
    }
    return output.str();
}

// Converts a char to its binary bit stream representation
static inline std::string to_bit_stream(char c) {
    std::string bitStream;
    for (int i = 7; i >= 0; --i) {
        bitStream += ((c >> i) & 1) ? '1' : '0';
    }
    return bitStream;
}

// Converts a binary bit stream back to a char
static inline char char_from_bit_stream(const std::string& bitStream) {
    if (bitStream.size() != 8) {
        throw std::invalid_argument("Bit stream must be exactly 8 bits long.");
    }

    char c = 0;
    for (size_t i = 0; i < 8; ++i) {
        if (bitStream[i] == '1') {
            c |= (1 << (7 - i));
        } else if (bitStream[i] != '0') {
            throw std::invalid_argument("Bit stream must contain only '0' or '1'.");
        }
    }
    return c;
}

static inline std::string to_bit_stream(std::string msg) {
    std::string output = "";
    for (auto c : msg) {
        output += to_bit_stream(c);
    }

    return output;
}

static inline std::string from_bit_stream(std::string msg) {
    std::string output = "";
    int len = msg.size();
    if (len % 8 != 0) {
        throw std::invalid_argument("Bit stream must be exactly 8 * K bits long.");
    }

    len = len / 8;
    for (int i = 0;i < len;i++) {
        output += char_from_bit_stream(msg.substr(i * 8, 8));
    }

    return output;
}
