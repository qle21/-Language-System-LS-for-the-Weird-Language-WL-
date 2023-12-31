#ifndef SET_H
#define SET_H

#include "Instruction.h"
#include <string>
#include <vector>

class SET : public Instruction {
public:
    SET(const vector<string>& args);

    void execute(Receiver& receiver) override;
};

#endif // SET_H
