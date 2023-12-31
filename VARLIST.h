#ifndef VARLIST_H
#define VARLIST_H

#include "Instruction.h"
#include <string>
#include <vector>

class VARLIST : public Instruction {
public:
    VARLIST(const vector<string>& args);

    void execute(Receiver& receiver) override; 
};

#endif // VARLIST_H
