#include "GOTO.h"
#include "Receiver.h"
#include <stdexcept>

GOTO::GOTO(const vector<string>& args) : Instruction(args), jumpLine(-1) {}

void GOTO::execute(Receiver& receiver) {
    if (args.size() != 1) {
        throw invalid_argument("GOTO requires exactly one argument");
    }

    // The argument is the line number to jump to
    jumpLine = stoi(args[0]);
}

int GOTO::getJumpLine() const {
    return jumpLine;
}
