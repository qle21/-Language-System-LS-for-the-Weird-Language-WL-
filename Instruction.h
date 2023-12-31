#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <vector>
#include <string>
#include "Receiver.h"  // Include Receiver

class Instruction {
protected:
    vector<string> args;

public:
    // Constructor
    Instruction(const vector<string>& args) : args(args) {}

    // Pure virtual function 'execute' with Receiver
    virtual void execute(Receiver& receiver) = 0;

    // Virtual destructor
    virtual ~Instruction() {};
};

#endif // INSTRUCTION_H
