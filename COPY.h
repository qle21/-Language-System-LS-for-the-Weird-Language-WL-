#ifndef COPY_H
#define COPY_H

#include "Instruction.h"
#include "Receiver.h"
#include <string>
#include <vector>

class COPY : public Instruction {
public:
    COPY(const vector<string>& args);

    void execute(Receiver& receiver) override;
};

#endif // COPY_H
