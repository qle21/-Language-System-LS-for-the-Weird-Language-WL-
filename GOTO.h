#ifndef GOTO_H
#define GOTO_H

#include "Instruction.h"
#include <string>
#include <vector>

class GOTO : public Instruction {
private:
    int jumpLine;

public:
    GOTO(const vector<string>& args);

    void execute(Receiver& receiver) override; 
    int getJumpLine() const;
};

#endif // GOTO_H
