#include <bits/stdc++.h>

using namespace std;

enum ICode {
    MOV,   ADD,   SUB,   JP,   JPZ,   LOAD,   STR,   HLT };
char* names[8] = {
   "MOV", "ADD", "SUB", "JP", "JPZ", "LOAD", "STR", "HLT"};

unsigned char get_icode(unsigned char instr) {
    return instr >> 5;
}
unsigned char get_valA(unsigned char instr) {
    return instr & ((1 << 5) - 1);
}
void print_instr(unsigned char instr) {
    const unsigned char icode = get_icode(instr);
    const unsigned char valA  = get_valA(instr);
    if (icode == HLT) {
        assert(valA == 0);
    }
    if (icode != HLT) {
        cout << names[icode] << " " << (unsigned int)valA << endl;
    } else {
        cout << names[icode] << endl;
    }
}

// Simulated lines & memory
unsigned char instr_store[32];
unsigned char data_memory[32];
unsigned char icode, valA;
bool mem_read, mem_write;
bool func;
unsigned char valM;
unsigned char aluA, aluB;
unsigned char valE;
unsigned char accum;
unsigned char PC;

// Bytes representing code to run - these can be
// passed to the program in various ways
const unsigned char code[] = {0, 192, 21, 193, 161, 147, 194, 162, 143, 65, 194, 160, 33, 192, 103, 161, 65, 193, 100, 160, 224};

int main() {
    cout << "The following code will be run: " << endl;
    for (int i = 0; i < sizeof(code) / sizeof(unsigned char); ++i) {
        print_instr(code[i]);
        assert(i + 1 < 32);
        instr_store[i + 1] = code[i];
    }
    cout << endl;

    // Windows "Press any key to continue ..."
    system("PAUSE");
    cout << endl;

    PC = 0;
    while (true) {
        // Fetch and Decode
        const unsigned char instr = instr_store[++PC];
        icode = get_icode(instr);
        valA = get_valA(instr);

        cout << "PC = " << (int)PC << endl;
        cout << "Executing instruction ";
        print_instr(instr);

        // Halt?
        if (icode == HLT) {
            break;
        }

        // mem_read
        mem_read = (icode == LOAD);

        // mem_write
        mem_write = (icode == STR);

        // func
        if (icode == SUB) {
            func = 1;
        } else {
            func = 0;
        }

        // valM
        if (mem_read) {
            valM = data_memory[valA];
        }

        // aluA
        if (icode == ADD || icode == SUB || icode == JP || icode == JPZ || icode == STR) {
            aluA = accum;
        } else if (icode == LOAD) {
            aluA = valM;
        } else {
            aluA = 0;
        }

        // aluB
        if (icode == ADD || icode == SUB || icode == MOV) {
            aluB = valA;
        } else {
            aluB = 0;
        }

        // valE
        if (!func) {
            valE = aluA + aluB;
        } else {
            valE = aluA - aluB;
        }

        cout << "mem_read  = " << mem_read << endl;
        cout << "mem_write = " << mem_write << endl;
        if (mem_read) {
            cout << "valM = " << (unsigned int)valM << endl;
        }
        cout << "aluA = " << (unsigned int)aluA << endl;
        cout << "aluB = " << (unsigned int)aluB << endl;
        cout << "valE = " << (unsigned int)valE << endl;

        // Memory write
        if (mem_write) {
            data_memory[valA] = valE;
        }

        // Branch
        if (icode == JP) {
            PC = valA;
        } else if (icode == JPZ && !accum) {
            PC = valA;
        }
        cout << "newPC = " << (unsigned int)PC << endl;

        // Update accumulator
        accum = valE;
        cout << "accum = " << (unsigned int)accum << endl;
        cout << endl;
    }
    
    cout << endl;
    cout << "Final accumulator value:" << endl;
    cout << "accum = " << (unsigned int)accum << endl;
    return 0;
}