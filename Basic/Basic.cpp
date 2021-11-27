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
    //cout << "Stub implementation of BASIC" << endl;
    while (true) {
        try {
            string input = getLine();
            if (input.empty())
                return 0;
            processLine(input, program, state);
        } catch (ErrorException &ex) {
            cout << ex.getMessage() << endl;
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
        program.initializer();
        while (program.get_now() != -1) {
            auto now = program.getParsedStatement(program.get_now());
            if (now == nullptr)break;  // TODO 出现不明原因的问题，并在表面上解决了问题。
            now->execute(state, program);
            program.goto_next_line();
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
                    Expression *exp = parseExp(scanner);
                    if (scanner.nextToken() != "LET") {
                        auto *Let = new LetStatement(exp);
                        //Let->execute(state, program);
                        program.setParsedStatement(line_number, Let);
                    } else error("SYNTAX ERROR");
                    //delete Let;
                } else if (second == "PRINT") {
                    Expression *exp = parseExp(scanner);
                    auto *Print = new PrintStatement(exp);
                    program.setParsedStatement(line_number, Print);
                    //Print->execute(state, program);
                    //delete Print;
                } else if (second == "INPUT") {
                    string third = scanner.nextToken();
                    auto *Input = new InputStatement(third);
                    //Input->execute(state, program);
                    program.setParsedStatement(line_number, Input);
                } else if (second == "GOTO") {
                    int to_line_num = stringToInteger(scanner.nextToken());
                    auto *Auto = new GotoStatement(to_line_num);
                    program.setParsedStatement(line_number, Auto);
                } else if (second == "IF") {
                    auto *If = new IfStatement(line);
                    program.setParsedStatement(line_number, If);
                } else if (second == "REM") {
                    auto *Rem = new RemStatement(line_number);
                    program.setParsedStatement(line_number, Rem);
                } else if (second == "END") {
                    auto *End = new EndStatement();
                    program.setParsedStatement(line_number, End);
                } else if (second.empty()) {}
                else error("SYNTAX ERROR");
            } else error("SYNTAX ERROR");
        } else if (scanner.getTokenType(first) == WORD) {
            if (first == "LET") {
                Expression *exp = parseExp(scanner);
                scanner.ignoreWhitespace();
                exp->eval(state);
            } else if (first == "PRINT") {
                Expression *exp = parseExp(scanner);
                auto *Print = new PrintStatement(exp);
                Print->execute(state, program);
                delete Print;
            } else if (first == "INPUT") {
                string second = scanner.nextToken();
                auto *Input = new InputStatement(second);
                Input->execute(state, program);
                delete Input;
            } else error("SYNTAX ERROR");
        } else error("SYNTAX ERROR");
    }
}

int convert_string_to_int(const std::string &x) {
    int ans;
    std::stringstream stream(x);
    stream >> ans;
    return ans;
}

