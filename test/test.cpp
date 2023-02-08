#include <cstdint>
#include<iostream>
#include<cstdio>
#include<array>

class Log {
public:
    enum class level {
        error = 0, warning, info
    };
    void setLevel(level lev_err) {
        m_err = lev_err;
    }
    void error(char c);
private:
    level m_err;
};

enum class data_size : size_t
{
    byte = sizeof(uint8_t),
    half_word = sizeof(uint16_t),
    word = sizeof(uint8_t),
    double_word = sizeof(uint8_t)
};

int main() {
    data_size value = data_size::half_word;
    data_size value_ = data_size::half_word;
}