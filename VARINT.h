#ifndef VARINT_H
#define VARINT_H

#include "Instruction.h"
#include <string>
#include <vector>

class VARINT : public Instruction {
public:
    VARINT(const vector<string>& args);

    void execute(Receiver& receiver) override;  
};

#endif // VARINT_H
