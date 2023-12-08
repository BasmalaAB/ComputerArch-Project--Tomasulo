#pragma once
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <vector>
#include <cstdint>
#include <unordered_map>
using namespace std;
class RISC {
private:
    const int zero = 0;
    int n;
    int32_t programCounter;
    vector<vector<string>> instruction_table;
    vector<vector<string>> Res_Stations;
    bool branch_pred;
    int clock_Cycle;
    unordered_map<string, int16_t> registers;

public:

    RISC() {
        clock_Cycle = 0;
        n = 5;
        branch_pred = false;
        programCounter = 0;
        registers["R0"] = zero;
        registers["R1"] = 0;
        registers["R2"] = 0;
        registers["R3"] = 0;
        registers["R4"] = 0;
        registers["R5"] = 0;
        registers["R6"] = 0;
        registers["R7"] = 0;

        Res_Stations.resize(11, vector<string>(8)); // Resize and initialize 2D vector

        Res_Stations[0][0] = "LOAD1";
        Res_Stations[1][0] = "LOAD2";
        Res_Stations[2][0] = "STORE1";
        Res_Stations[3][0] = "STORE2";
        Res_Stations[4][0] = "BNE";
        Res_Stations[5][0] = "CALL"; //CALL/RET
        Res_Stations[6][0] = "ADD1";
        Res_Stations[7][0] = "ADD2";
        Res_Stations[8][0] = "ADD3";
        Res_Stations[9][0] = "NAND";
        Res_Stations[10][0] = "DIV";

        for (int j = 0; j < 11; j++) {
            Res_Stations[j][1] = "N";
        }

        for (int i = 2; i < 8; i++) {
            for (int j = 0; j < 11; j++) {
                Res_Stations[j][i] = "";
            }
        }
    }

    void setNumInstructions(int num) {
        if (num >= 1)
        {
            n = num;
        }
        else cout << "Invalid number of instructions. Please input again";
    }

    void readFile(ifstream& file, string text, vector<string>& to_read) {
        file.open(text);
        if (file.is_open()) {
            cout << "Successfully accessed program" << endl;
        }
        else {
            cout << "!error accessing file!" << endl;
            exit(-1);
        }
        cout << endl;
        string line;
        while (!file.eof()) {
            getline(file, line);
            to_read.push_back(line);
        }
        inst_setUp(to_read);
    }

    void inst_setUp(vector<string> to_read) {
        instruction_table.resize(n, vector<string>(5)); // Resize and initialize 2D vector //issue, start exec, end exec, write back (each column)

        for (int i = 0; i < n; i++) {
            instruction_table[i][0] = to_read[i]; // Assign value directly to the instructions
            cout << instruction_table[i][0] << " ";
        }
    }
};

//We need to output the following:
//1. A table listing the clock cycle time at which each instruction was: issued, started execution, finished execution, and was written
//2. The total execution time expressed as the number of cycles spanned
//3. The IPC 
//4. The branch misprediction percentage

int main()
{
    RISC R;
    //specify file we will read from, or input instructions manually
    int num = 0;

    cout << "Please enter number of instructions: " << endl;
    cin >> num;

    vector<string> instructions;
    instructions.resize(num);

    R.setNumInstructions(num);
    string ans = "";
    cout << "Would you like to enter the instructions (yes), or read instructions from file? (no)" << endl;
    cin >> ans;

    if (ans == "yes")
    {
        cout << "Please enter instructions with no spaces (comma separated)!" << endl;
        for (int i = 0; i < num; i++)
        {
            cin >> instructions[i];
        }
        R.inst_setUp(instructions);
        cout << "Setting up instructions";
    }
    else if (ans == "no")
    {
        //function for reading instructions from specific file
        //R.readFile() 
    }
}


