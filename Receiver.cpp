#include "Receiver.h"

Receiver::Receiver() : pc(0) {}

void Receiver::loadDataMemory(const map<string, unique_ptr<DataType>>& memory) {
    for (const auto& pair : memory) {
        data_memory[pair.first] = pair.second->deep_copy();
    }
}

void Receiver::loadProgramMemory(const vector<string>& memory) {
    program_memory = memory;
}

void Receiver::setProgramCounter(int counter) {
    pc = counter;
}

int Receiver::getProgramCounter() const {
    return pc;
}

void Receiver::incrementProgramCounter() {
    pc++;
}

string Receiver::getNextInstruction() {
    if (pc < program_memory.size()) {
        return program_memory[pc]; // Do not increment pc here!
    }
    return ""; // Return empty string if no more instructions
}

int Receiver::getProgramMemorySize() const {
    return program_memory.size();
}

void Receiver::updateDataMemory(const string& key, unique_ptr<DataType> value) {
    data_memory[key] = move(value);
}

DataType* Receiver::getDataFromMemory(const string& key) {
    auto it = data_memory.find(key);
    if (it != data_memory.end()) {
        return it->second.get();
    }
    return nullptr; // Return nullptr if key not found
}

// Implementation of the new method
const map<string, unique_ptr<DataType>>& Receiver::getDataMemory() const {
    return data_memory;
}
