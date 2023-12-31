#ifndef COMBINE_H
#define COMBINE_H

#include "Instruction.h"
#include "Receiver.h"
#include <string>
#include <vector>

class COMBINE : public Instruction {
public:
    COMBINE(const vector<string>& args);

    void execute(Receiver& receiver) override;
};

#endif // COMBINE_H
