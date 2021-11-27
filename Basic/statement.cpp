/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include <string>
#include <sstream>
#include "statement.h"
#include"parser.h"
#include "../StanfordCPPLib/error.h"

using namespace std;

/* Implementation of the Statement class */

int stringToInt(string str);

Statement::Statement() = default;

Statement::~Statement() = default;

RemStatement::RemStatement(int &line_num) {
    line_num = line_num;
}

void RemStatement::execute(EvalState &state, Program &program) {
    program.set_goto_flag(false);
}

LetStatement::LetStatement(Expression *exp) {
    this->exp = exp;
}

void LetStatement::execute(EvalState &state, Program &program) {
    program.set_goto_flag(false);
    exp->eval(state);
}

PrintStatement::PrintStatement(Expression *exp) { this->exp = exp; }

void PrintStatement::execute(EvalState &state, Program &program) {
    program.set_goto_flag(false);
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

void InputStatement::execute(EvalState &state, Program &program) {
    program.set_goto_flag(false);
    cout << " ? ";
    string value;
    TokenScanner scanner;
    string line;
    getline(cin, line);
    istringstream iss(line);
    value = line;
    scanner.setInput(value);

    while (true) {
        try {
            int real_value = stringToInt(value);
            state.setValue(name, real_value);
            break;
        } catch (ErrorException &ex) {
            cout << ex.getMessage() << endl;
            cout << " ? ";
            getline(cin, line);
            istringstream iss(line);
            value = line;
            scanner.setInput(value);
        }
    }
}

int InputStatement::convert_string_(const string &x) {
    int ans;
    std::stringstream stream(x);
    stream >> ans;
    return ans;
}

GotoStatement::GotoStatement(int &line_num_) {
    this->line_num = line_num_;
}

void GotoStatement::execute(EvalState &state, Program &program) {
    program.set_present_line_num(this->line_num);
    program.set_goto_flag(true);
    if (program.get_now() == -1)error("LINE NUMBER ERROR");
}

void EndStatement::execute(EvalState &state, Program &program) {
    program.set_goto_flag(false);
    program.set_present_line_num(-1);
}

IfStatement::IfStatement(string &line) {
//    this->flag = flag;
//    this->line_num = line_num;
    this->line = line;
}

void IfStatement::execute(EvalState &state, Program &program) {
    string content = line.substr(6);
    string lhs, rhs, op, then_statement;
    int i = 0, j = 0;
    while (content[i] != '>' && content[i] != '=' && content[i] != '<')i++;
    while (!(content[j] == 'T' && content[j + 1] == 'H' && content[j + 2] == 'E' &&
             content[j + 3] == 'N'))
        j++;
    lhs = content.substr(0,i - 1);
    op = content.substr(i, 1);
    rhs = content.substr(i + 2, j-i-3);
    then_statement=content.substr(j,content.size()-j);
    line_num=stringToInteger(then_statement.substr(4));
    TokenScanner lhs_scanner, rhs_scanner;
    int lhs_value, rhs_value;
    lhs_scanner.ignoreWhitespace();
    lhs_scanner.scanNumbers();
    rhs_scanner.ignoreWhitespace();
    rhs_scanner.scanNumbers();
    lhs_scanner.setInput(lhs);
    rhs_scanner.setInput(rhs);
    Expression *lhs_exp = parseExp(lhs_scanner);
    Expression *rhs_exp = parseExp(rhs_scanner);
    lhs_value = lhs_exp->eval(state);
    rhs_value = rhs_exp->eval(state);
    if (op == "=") {
        if (lhs_value == rhs_value)flag = true;
        else flag = false;
    } else if (op == ">") {
        if (lhs_value > rhs_value)flag = true;
        else flag = false;
    } else if (op == "<") {
        if (lhs_value < rhs_value)flag = true;
        else flag = false;
    }
    if (flag) {
        program.set_present_line_num(this->line_num);
        program.set_goto_flag(true);
        if (program.get_now() == -1)error("LINE NUMBER ERROR");
    } else program.set_goto_flag(false);
}
