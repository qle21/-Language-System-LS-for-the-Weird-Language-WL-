#ifndef CHS_H
#define CHS_H

#include "Instruction.h"
#include "Receiver.h"
#include <string>
#include <vector>

class CHS : public Instruction {
public:
    CHS(const vector<string>& args);

    void execute(Receiver& receiver) override; 
};

#endif // CHS_H
