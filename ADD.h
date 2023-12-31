#ifndef ADD_H
#define ADD_H

#include "Instruction.h"
#include "Receiver.h"
#include <string>
#include <vector>

class ADD : public Instruction {
public:
    ADD(const vector<string>& args);

    void execute(Receiver& receiver) override;  
};

#endif // ADD_H
