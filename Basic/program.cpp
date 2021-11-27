/*
 * File: program.cpp
 * -----------------
 * This file is a stub implementation of the program.h interface
 * in which none of the methods do anything beyond returning a
 * value of the correct type.  Your job is to fill in the bodies
 * of each of these methods with an implementation that satisfies
 * the performance guarantees specified in the assignment.
 */

#include <string>
#include "program.h"
#include "statement.h"
#include "../StanfordCPPLib/vector.h"
#include "../StanfordCPPLib/map.h"

//unordered_map<int, Statement*> stmt_storage;
//unordered_map<int, string> line_getter;
//Set<int> line_num_list;

using namespace std;

Program::Program() = default;

Program::~Program() = default;

void Program::clear() {
    // Replace this stub with your own code
    line_getter.clear();
    line_num_list.clear();
    stmt_storage.clear();
}

void Program::addSourceLine(int lineNumber, const string &line) {
    // Replace this stub with your own code
    TokenScanner scanner;
    scanner.setInput(line);
    scanner.nextToken();
    if (line_num_list.find(lineNumber) != line_num_list.end()) {
        line_getter.erase(lineNumber);
        if (!scanner.hasMoreTokens()) {
            line_num_list.erase(lineNumber);
        } else line_getter.emplace(lineNumber, line);
    } else {
        if (scanner.hasMoreTokens()) {
            line_num_list.insert(lineNumber);
            line_getter.emplace(lineNumber, line);
        }
    }


}

void Program::removeSourceLine(int lineNumber) {
    // Replace this stub with your own code
    if (line_num_list.find(lineNumber) != line_num_list.end()) {
        line_getter.erase(lineNumber);
        line_num_list.erase(lineNumber);
    }
}

string Program::getSourceLine(int lineNumber) {
    // Replace this stub with your own code
    if (line_num_list.find(lineNumber) == line_num_list.end()) return "";
    else {
        string ans = line_getter[lineNumber];
        return ans;
    }
}

void Program::setParsedStatement(int lineNumber, Statement *stmt) {
    // Replace this stub with your own code
    if (line_num_list.find(lineNumber) != line_num_list.end()) {
        stmt_storage[lineNumber] = stmt;
    } else std::cout << "SYNTAX ERROR" << std::endl;
}

//void Program::removeSourceLine(int lineNumber) {

Statement *Program::getParsedStatement(int lineNumber) {
    if (line_num_list.find(lineNumber) != line_num_list.end()) {
        return stmt_storage[lineNumber];
    } else return nullptr;  // Replace this stub with your own code
}

int Program::getFirstLineNumber() {
    if (!line_num_list.empty()) return *(line_num_list.begin());
    else return -1;
    // Replace this stub with your own code
}

int Program::getNextLineNumber(int lineNumber) {
    present_line_iterator = line_num_list.find(lineNumber);
    if (present_line_iterator != line_num_list.end()) {
        present_line_iterator++;
        return *present_line_iterator;
    } else return -1;
    // Replace this stub with your own code
}

int Program::get_now() {
    return present_line_num;
}

void Program::initializer() {
    if (line_num_list.begin() != line_num_list.end()) {
        present_line_num = *(line_num_list.begin());
        goto_flag = false;
    } else present_line_num = -1;
}

void Program::set_present_line_num(int lineNumber) {
    if (line_num_list.find(lineNumber) != line_num_list.end()) {
        present_line_num = lineNumber;
    } else present_line_num = -1;
}

void Program::goto_next_line() {
    if ((present_line_num != -1) && (!goto_flag)) {
        present_line_num = getNextLineNumber(present_line_num);
    }
}

void Program::set_goto_flag(bool opt) {
    goto_flag = opt;
}


