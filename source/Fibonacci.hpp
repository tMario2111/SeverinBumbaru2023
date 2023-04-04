#pragma once

class Fibonacci
{
public:
    Fibonacci();
    static constexpr int count = 50;
    unsigned long long seq[count + 1];
};