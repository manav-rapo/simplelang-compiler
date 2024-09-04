#include "lexer.h"
#include "parser.h"
#include "code_generator.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main() {
    string code;
    ifstream inputFile("input.txt"); // Open the input file

    if (!inputFile) {
        cerr << "Error: Could not open the input file." << endl;
        return 1;
    }

    stringstream buffer;
    buffer << inputFile.rdbuf(); // Read the file into a stringstream
    code = buffer.str(); // Convert the stringstream into a string

    inputFile.close(); // Close the file

    Lexer lexer(code);
    Parser parser(lexer);
    ast* root = parser.parse();

    CodeGenerator generator;
    generator.generate(root);

    delete root; // Clean up

    return 0;
}
