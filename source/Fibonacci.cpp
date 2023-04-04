#include "Fibonacci.hpp"

/*
Genereaza sirul lui Fibonacci
Complexitate:
    - timp: O(n)
    - spatiu: O(n)
*/
Fibonacci::Fibonacci()
{
    seq[1] = 1;
    seq[2] = 1;
    for(int i = 3; i <= count; i++)
        seq[i] = seq[i - 1] + seq[i - 2];
}