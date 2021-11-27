/*
 * File: statement.h
 * -----------------
 * This file defines the Statement abstract type.  In
 * the finished version, this file will also specify subclasses
 * for each of the statement types.  As you design your own
 * version of this class, you should pay careful attention to
 * the exp.h interface, which is an excellent model for
 * the Statement class hierarchy.
 */

#ifndef _statement_h
#define _statement_h

#include "evalstate.h"
#include "exp.h"
#include "../StanfordCPPLib/tokenscanner.h"
#include "program.h"

class Program;

/*
 * Class: Statement
 * ----------------
 * This class is used to represent a statement in a program.
 * The model for this class is Expression in the exp.h interface.
 * Like Expression, Statement is an abstract class with subclasses
 * for each of the statement and command types required for the
 * BASIC interpreter.
 */

class Statement {

public:

/*
 * Constructor: Statement
 * ----------------------
 * The base class constructor is empty.  Each subclass must provide
 * its own constructor.
 */

    Statement();

/*
 * Destructor: ~Statement
 * Usage: delete stmt;
 * -------------------
 * The destructor deallocates the storage for this expression.
 * It must be declared virtual to ensure that the correct subclass
 * destructor is called when deleting a statement.
 */

    virtual ~Statement();

/*
 * Method: execute
 * Usage: stmt->execute(state);
 * ----------------------------
 * This method executes a BASIC statement.  Each of the subclasses
 * defines its own execute method that implements the necessary
 * operations.  As was true for the expression evaluator, this
 * method takes an EvalState object for looking up variables or
 * controlling the operation of the interpreter.
 */

    virtual void execute(EvalState &state, Program &program) = 0;

};

class RemStatement : public Statement {
public:
    int line_num;

    RemStatement(int &line_num);

    ~RemStatement() override = default;

    void execute(EvalState &state, Program &program) override;
};

class LetStatement : public Statement {
public:
    Expression *exp;

    LetStatement(Expression *exp);

    ~LetStatement() override = default;

    void execute(EvalState &state, Program &program) override;
};

class PrintStatement : public Statement {
public:
    Expression *exp;

    PrintStatement(Expression *exp);

    ~PrintStatement() override = default;

    void execute(EvalState &state, Program &program) override;
};

class InputStatement : public Statement {
public:
    string name;

    InputStatement(string variable);

    ~InputStatement() override = default;

    void execute(EvalState &state, Program &program) override;

    static int convert_string_(const std::string &x);
};

class EndStatement : public Statement {
public:
    EndStatement() = default;

    ~EndStatement() override = default;

    void execute(EvalState &state, Program &program) override;
};

class GotoStatement : public Statement {
public:
    int line_num;

    GotoStatement(int &line_num);

    ~GotoStatement() override = default;

    void execute(EvalState &state, Program &program) override;
};

class IfStatement : public Statement {
public:
    bool flag;
    int line_num;
    string line;

    IfStatement(string &line);

    ~IfStatement() override = default;

    void execute(EvalState &state, Program &program) override;
};



/*
 * The remainder of this file must consists of subclass
 * definitions for the individual statement forms.  Each of
 * those subclasses must define a constructor that parses a
 * statement from a scanner and a method called execute,
 * which executes that statement.  If the private data for
 * a subclass includes data allocated on the heap (such as
 * an Expression object), the class implementation must also
 * specify its own destructor method to free that memory.
 */

#endif
