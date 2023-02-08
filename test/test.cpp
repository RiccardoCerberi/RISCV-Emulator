#include <cstdint>
#include<iostream>
#include<cstdio>
#include<array>

class Log {
public:
    enum Level {
        error = 0, warning, info
    };
    void setLevel(Level);
    void error(char c);
};



int main() {
    Log l;

    l.setLevel(Level::error);
}