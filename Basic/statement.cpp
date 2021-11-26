/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include <string>
#include "statement.h"
#include"parser.h"
#include "../StanfordCPPLib/error.h"

using namespace std;

/* Implementation of the Statement class */

Statement::Statement() = default;

Statement::~Statement() = default;

void RemStatement::execute(EvalState &state,Program &program) {}

LetStatement::LetStatement(Expression *exp) {
    this->exp = exp;
}

void LetStatement::execute(EvalState &state,Program &program) {
    exp->eval(state);
}

PrintStatement::PrintStatement(Expression *exp) { this->exp = exp; }

void PrintStatement::execute(EvalState &state,Program &program) {
    int value = exp->eval(state);
    cout << value << endl;
    //delete exp;
}

InputStatement::InputStatement(string variable) {
    name = variable;
}


int stringToInt(string str) {
    istringstream stream(str);
    int value;
    stream >> value >> ws;
    if (stream.fail() || !stream.eof()) {
        error("INVALID NUMBER");
    }
    return value;
}


void InputStatement::execute(EvalState &state,Program &program) {
    cout << "?";
    string value;
    TokenScanner scanner;
    scanner.setInput(value);
    cin >> value;
    while (true) {
        //string sub_value=value.substr(1);
        getchar();
        try {
            int real_value = stringToInt(value);
            state.setValue(name, real_value);
            break;
        } catch (ErrorException &ex) {
            cerr << "Error: " << ex.getMessage() << endl;
            cout << "?";
            cin >> value;
        }
    }
}

int InputStatement::convert_string_(const string &x) {
    int ans;
    std::stringstream stream(x);
    stream >> ans;
    return ans;
}

GotoStatement::GotoStatement(string &line_num){
 line_num=stringToInt(line_num);
}

void GotoStatement::execute(EvalState &state,Program &program){
    if(program.goto_line(line_num)==-1)error("INVALID NUMBER");
}

void EndStatement::execute(EvalState &state, Program &program) {

}
