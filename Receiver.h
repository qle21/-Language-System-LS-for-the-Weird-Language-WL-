#ifndef RECEIVER_H
#define RECEIVER_H

#include "DataType.h"
#include <map>
#include <string>
#include <vector>
#include <memory>



class Receiver {
private:
    map<string, unique_ptr<DataType>> data_memory;
    vector<string> program_memory;
    int pc;  // Program Counter

public:
    Receiver();

    void loadDataMemory(const map<string, unique_ptr<DataType>>& memory);
    void loadProgramMemory(const vector<string>& memory);
    void setProgramCounter(int counter);
    int getProgramCounter() const;
    void incrementProgramCounter();
    string getNextInstruction();
    int getProgramMemorySize() const;
    void updateDataMemory(const string& key, unique_ptr<DataType> value);
    DataType* getDataFromMemory(const string& key);
    const map<string, unique_ptr<DataType>>& getDataMemory() const;
};

#endif // RECEIVER_H
