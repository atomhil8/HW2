#include <iostream>
#include <bitset>
#include <cmath>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {

    if (argc != 3) {
        cout << "Error: Program must have exactly 2 arguments" << endl;
        return 1;
    }

    float loopBound = stof(argv[1]);
    float increment = stof(argv[2]);

    union {
        float f;
        unsigned int i;
    } uLoopBound, uIncrement;

    uLoopBound.f = loopBound;
    uIncrement.f = increment;

    // Print IEEE representation
    cout << "Loop bound:  " << bitset<32>(uLoopBound.i) << endl;
    cout << "Loop counter: " << bitset<32>(uIncrement.i) << endl << endl;

    // Extract exponent bits
    int expA = (uLoopBound.i >> 23) & 0xFF;
    int expB = (uIncrement.i >> 23) & 0xFF;

    int diff = expA - expB;

    if (diff < 23) {
        cout << "There is no overflow!" << endl;
    }
    else {
        cout << "Warning: Possible overflow!" << endl;

        int thresholdExp = expB + 24;

        unsigned int thresholdBits = thresholdExp << 23;

        union {
            float f;
            unsigned int i;
        } overflow;

        overflow.i = thresholdBits;

        cout << "Overflow threshold:" << endl;
        cout << overflow.f << endl;
        cout << bitset<32>(overflow.i) << endl;
    }

    return 0;
}