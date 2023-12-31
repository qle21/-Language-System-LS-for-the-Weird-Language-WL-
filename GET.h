#ifndef GET_H
#define GET_H

#include "Instruction.h"
#include "Receiver.h"
#include <string>
#include <vector>

class GET : public Instruction {
public:
    GET(const vector<string>& args);

    void execute(Receiver& receiver) override;
};

#endif // GET_H
