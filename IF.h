#ifndef IF_H
#define IF_H

#include "Instruction.h"
#include <string>
#include <vector>

class IF : public Instruction {
private:
    int jumpLine;

public:
    IF(const vector<string>& args);

    void execute(Receiver& receiver) override;  // Ensure this matches the new signature
    int getJumpLine() const;
};

#endif // IF_H
