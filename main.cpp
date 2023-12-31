#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <memory>

#include "IntegerNode.h"
#include "MyLinkedList.h"
#include "ADD.h"
#include "VARINT.h"
#include "VARLIST.h"
#include "COMBINE.h"
#include "CHS.h"
#include "GET.h"
#include "SET.h"
#include "COPY.h"
#include "IF.h"
#include "GOTO.h"
#include "Receiver.h"
#include <unistd.h>


using namespace std;

void print_data_memory(const map<string, unique_ptr<DataType>>& data_memory) {
    
    cout << endl;
    cout << "Printing data_memory" << endl << endl;
    
    for (const auto& pair : data_memory) {
        cout << "   " << pair.first << ": ";
        
        IntegerNode* intNode = dynamic_cast<IntegerNode*>(pair.second.get());
        if (intNode) {
            cout << intNode->value << endl;
            continue;
        }
        
        MyLinkedList* listNode = dynamic_cast<MyLinkedList*>(pair.second.get());
        if (listNode) {
            cout << listNode->to_string() << endl;
            continue;
        }
        
        cout << "Unknown data type" << endl;
    }
    cout << "-----------------------------------------------------" << endl;
    cout << endl;
}

void print_instructions(vector<string> &program_memory) {
    cout << "-----------------------------------------------------" << endl;
    cout << "Printing all instructions:" << endl << endl;
    for (const string& instruction : program_memory) {
        cout << instruction << endl;
    }
    cout << endl;
}

void print_instruction_details(const string& instruction_name, const vector<string>& args, const vector<string>& parts, Receiver& receiver) {
   
    cout << endl;
    cout << "-----------------------------------------------------" << endl;
    cout << "Executing instruction at program counter (PC): " << receiver.getProgramCounter() << endl << endl;
    cout << "Printing Instruction details:" << endl << endl;
    cout << "   Instruction name: " << instruction_name << endl;

    // Print the arguments
    cout << "   Arguments: ";
    for (const string& arg : args) {
        cout << arg << " ";
    }
    cout << endl;

    // Print all parts
    cout << "   All parts: ";
    for (const string& part : parts) {
        cout << part << " ";
    }
    cout << endl;
    cout << endl;
}

int execute_line(const string& instruction, Receiver& receiver) {
    
    istringstream iss(instruction);
    vector<string> parts;
    string part;
    
    // Splitting the instruction into parts
    while (iss >> part) {
        parts.push_back(part);
    }
    

    string instruction_name = parts[0];
    vector<string> args(parts.begin() + 1, parts.end());
    
    print_instruction_details(instruction_name, args, parts, receiver);

    cout << "EXECUTING INSTRUCTION..." << endl;
    // Execute the appropriate instruction based on instruction_name
    if (instruction_name == "ADD") {
        ADD addCommand(args);
        addCommand.execute(receiver);
    } else if (instruction_name == "VARINT") {
        VARINT varintCommand(args);
        varintCommand.execute(receiver);
    } else if (instruction_name == "VARLIST") {
        VARLIST varlistCommand(args);
        varlistCommand.execute(receiver);
    } else if (instruction_name == "CHS") {
        CHS chsCommand(args);
        chsCommand.execute(receiver);
    } else if (instruction_name == "COMBINE") {
        COMBINE combineCommand(args);
        combineCommand.execute(receiver);
    } else if (instruction_name == "GET") {
        GET getCommand(args);
        getCommand.execute(receiver);
    } else if (instruction_name == "SET") {
        SET setCommand(args);
        setCommand.execute(receiver);
    } else if (instruction_name == "COPY") {
        COPY copyCommand(args);
        copyCommand.execute(receiver);
    } else if (instruction_name == "IF") {
        IF ifCommand(args);
        ifCommand.execute(receiver);
        int jumpLine = ifCommand.getJumpLine();
        if (jumpLine != -1) {
            receiver.setProgramCounter(jumpLine);
            return jumpLine;
        }
    } else if (instruction_name == "GOTO") {
        GOTO gotoCommand(args);
        gotoCommand.execute(receiver);
        int jumpLine = gotoCommand.getJumpLine();
        receiver.setProgramCounter(jumpLine);
        return jumpLine;
    } else if (instruction_name == "HLT") {
        cout << "Halting the execution" << endl;
        receiver.setProgramCounter(receiver.getProgramMemorySize()); // Setting to end of program
        return receiver.getProgramCounter();
    }

    receiver.incrementProgramCounter();
    return receiver.getProgramCounter();
}

int main() {
    ifstream file("input.txt");
    if (!file) {
        cerr << "Unable to open file input.txt" << endl;
        return 1;
    }
    
    string line;
    Receiver receiver;
    vector<string> program_memory;

    while (getline(file, line)) {
        size_t firstNonDigit = line.find_first_not_of("0123456789.");
        if (firstNonDigit != string::npos) {
            string cleaned_line = line.substr(firstNonDigit);
            program_memory.push_back(cleaned_line);
        }
    }

    receiver.loadProgramMemory(program_memory);
    print_instructions(program_memory); // Print all instructions before starting execution

    char command;
    bool running = true;

    while (running) {
        cout << "Enter command:" << endl;
        cout << "'o' - execute line by line" << endl;
        cout << "'a' - execute all lines" << endl;
        cout << "'q' - quit: ";
        cin >> command;
        
        switch (command) {
            case 'o':
                if (receiver.getProgramCounter() < receiver.getProgramMemorySize()) {
                    string currentInstruction = receiver.getNextInstruction();
                    execute_line(currentInstruction, receiver);
                    print_data_memory(receiver.getDataMemory());
                } else {
                    cout << "No more instructions to execute." << endl;
                }
                break;
                
            case 'a':
                while (receiver.getProgramCounter() < receiver.getProgramMemorySize()) {
                    string currentInstruction = receiver.getNextInstruction();
                    if (currentInstruction == "HLT") {
                        break;
                    }
                    execute_line(currentInstruction, receiver);
                    print_data_memory(receiver.getDataMemory()); // Print data memory after each instruction execution
                }
                break;
                
            case 'q':
                cout << "Exiting program." << endl;
                running = false;
                break;
                
            default:
                cout << "Invalid command. Please enter 'o', 'a', or 'q'." << endl;
                break;
        }
    }

    return 0;
}
