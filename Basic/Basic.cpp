/*
 * File: Basic.cpp
 * ---------------
 * This file is the starter project for the BASIC interpreter.
 */

#include <cctype>
#include <iostream>
#include <string>
#include "exp.h"
#include "parser.h"
#include "program.h"
#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/tokenscanner.h"

#include "../StanfordCPPLib/simpio.h"
#include "../StanfordCPPLib/strlib.h"

using namespace std;

/* Function prototypes */

void processLine(string line, Program &program, EvalState &state);

int convert_string_to_int(const std::string &x);

/* Main program */

int main() {
    EvalState state;
    Program program;
    cout << "Stub implementation of BASIC" << endl;
    while (true) {
        try {
            string input = getLine();
            if (input.empty())
                return 0;
            processLine(input, program, state);
        } catch (ErrorException &ex) {
            cerr << "Error: " << ex.getMessage() << endl;
        }
    }
    return 0;
}

/*
 * Function: processLine
 * Usage: processLine(line, program, state);
 * -----------------------------------------
 * Processes a single line entered by the user.  In this version of
 * implementation, the program reads a line, parses it as an expression,
 * and then prints the result.  In your implementation, you will
 * need to replace this method with one that can respond correctly
 * when the user enters a program line (which begins with a number)
 * or one of the BASIC commands, such as LIST or RUN.
 */

void processLine(string line, Program &program, EvalState &state) {
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    scanner.setInput(line);

    if (line == "QUIT") exit(0);
    else if (line == "LIST") {
        int it = program.getFirstLineNumber();
        if (it != -1) {
            while (!program.getSourceLine(it).empty()) {
                std::cout << program.getSourceLine(it) << std::endl;
                it = program.getNextLineNumber(it);
            }
        }
    } else if (line == "RUN") {
        int it = program.getFirstLineNumber();
        if (it != -1) {
            program.goto_line(it);
            while (it!=-1) {
                auto now=program.getParsedStatement(it);

                now->execute(state);
                it = program.getNextLineNumber(it);
            }
        }
    } else if (line == "CLEAR") {
        program.clear();
        state.Clear();
    } else if (line == "HELP") {
        cout << "Yet another basic interpreter" << endl;
    } else {
        std::string first = scanner.nextToken();
        if (scanner.getTokenType(first) == NUMBER) {
            string second = scanner.nextToken();
            int line_number = convert_string_to_int(first);
            if (line_number > 0) {
                program.addSourceLine(line_number, line);

                if (second == "LET") {
                    cout << scanner.nextToken() << endl;
                    Expression *exp = parseExp(scanner);
                    auto *Let = new LetStatement(exp);
                    Let->execute(state);
                    //delete Let;
                } else if (second == "PRINT") {
                    Expression *exp = parseExp(scanner);
                    auto *Print = new PrintStatement(exp);
                    program.setParsedStatement(line_number, Print);
                    Print->execute(state);
                    //delete Print;
                } else if (second == "INPUT") {
                    string third = scanner.nextToken();
                    auto *Input = new InputStatement(third);
                    Input->execute(state);
                    delete Input;
                    //delete Input;
                } else if(second == "GOTO"){

                }else if (second == "REM" || second == "END"||second.empty()) {
                }else error("SYNTAX ERROR");
            } else error("SYNTAX ERROR");
        }
        else if (scanner.getTokenType(first) == WORD) {
            if (first == "LET") {
                Expression *exp = parseExp(scanner);
                auto *Let = new LetStatement(exp);
                Let->execute(state);
                delete Let;
            } else if (first == "PRINT") {
                Expression *exp = parseExp(scanner);
                auto *Print = new PrintStatement(exp);
                Print->execute(state);
                delete Print;
            } else if (first == "INPUT") {
                string second = scanner.nextToken();
                auto *Input = new InputStatement(second);
                Input->execute(state);
                delete Input;
            } else error("SYNTAX ERROR");
        } else error("SYNTAX ERROR");
    }

//    Expression *exp = parseExp(scanner);
//    int value = exp->eval(state);
//    cout << value << endl;
//    delete exp;
}

int convert_string_to_int(const std::string &x) {
    int ans;
    std::stringstream stream(x);
    stream >> ans;
    return ans;
}

