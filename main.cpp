#include <iostream>
#include <vector>
#include <random>
#include <iterator>
//Header only libraries
#include "expressionAst.h"
// #include "expressionVisitors.h"

template<typename Iter, typename RandomGenerator>
Iter select_randomly(Iter start, Iter end, RandomGenerator& g) {
    std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
    std::advance(start, dis(g));
    return start;
}

template<typename Iter>
Iter select_randomly(Iter start, Iter end) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return select_randomly(start, end, gen);
}

int main()
{
    int numOfParam = 2; // Initial Operands;
    int numOfConst = 0;
    int numOfUninterpretedFunct = 1;
    int numOfOperator = 6;


    FormulaVar *x = new FormulaVar("x");
    FormulaVar *y = new FormulaVar("y");
    
    std::vector<Formula *> ArithmaticOperandList;
    ArithmaticOperandList.push_back(x);
    ArithmaticOperandList.push_back(y);

    std::vector<Formula *> ComparisonOperandList;
    std::vector<Formula *> LogicalOperandList;

    ArithmaticOperator *Plus = new ArithmaticOperator("+");
    ArithmaticOperator *Minus = new ArithmaticOperator("-");
    std::vector<ArithmaticOperator *> ArithmaticOperatorList;
    ArithmaticOperatorList.push_back(Plus);
    ArithmaticOperatorList.push_back(Minus);

    ComparisonOperator *LT = new ComparisonOperator("<");
    ComparisonOperator *GT = new ComparisonOperator(">");
    ComparisonOperator *LEQ = new ComparisonOperator("<=");
    ComparisonOperator *GEQ = new ComparisonOperator(">=");
    ComparisonOperator *EQ = new ComparisonOperator("=");
    std::vector<ComparisonOperator *> ComparisonOperatorList;
    ComparisonOperatorList.push_back(LT);
    ComparisonOperatorList.push_back(GT);
    ComparisonOperatorList.push_back(LEQ);
    ComparisonOperatorList.push_back(GEQ);
    ComparisonOperatorList.push_back(EQ);

    LogicalOperator *And = new LogicalOperator("and");
    LogicalOperator *Or = new LogicalOperator("or");
    std::vector<LogicalOperator *> LogicalOperatorList;
    LogicalOperatorList.push_back(And);
    LogicalOperatorList.push_back(Or);

    FunctionOperator *f = new FunctionOperator("f");
    FormulaBinaryExp *exp1;
    exp1 = new FormulaBinaryExp(*select_randomly(ArithmaticOperandList.begin(), ArithmaticOperandList.end()), *select_randomly(ArithmaticOperandList.begin(), ArithmaticOperandList.end()), f);
    ArithmaticOperandList.push_back(exp1);

    for(int i = 0; i<numOfOperator; i+=3)
    {
        std::cout<<i<<"\n";
        exp1 = new FormulaBinaryExp(*select_randomly(ArithmaticOperandList.begin(), ArithmaticOperandList.end()), *select_randomly(ArithmaticOperandList.begin(), ArithmaticOperandList.end()), *select_randomly(ArithmaticOperatorList.begin(), ArithmaticOperatorList.end()));
        ArithmaticOperandList.push_back(exp1);
        exp1 = new FormulaBinaryExp(*select_randomly(ArithmaticOperandList.begin(), ArithmaticOperandList.end()), *select_randomly(ArithmaticOperandList.begin(), ArithmaticOperandList.end()), *select_randomly(ComparisonOperatorList.begin(), ComparisonOperatorList.end()));
        ComparisonOperandList.push_back(exp1);
        exp1 = new FormulaBinaryExp(*select_randomly(ComparisonOperandList.begin(), ComparisonOperandList.end()), *select_randomly(ComparisonOperandList.begin(), ComparisonOperandList.end()), *select_randomly(LogicalOperatorList.begin(), LogicalOperatorList.end()));
        LogicalOperandList.push_back(exp1);
    }
    
    LogicalOperandList.back()->prettyPrinter();
    std::cout<<"\n";
    std::string constraint = LogicalOperandList.back()->formulaToString();
    std::cout<<constraint;
    std::cout<<"\n";

    //new and delete. malloc and free. preferably don't mix.
    // free memory
    delete x;
    delete y;
    delete Plus;
    delete Minus;
    delete LT;
    delete GT;
    delete LEQ;
    delete GEQ;
    delete EQ;
    delete And;
    delete Or;
    delete exp1;
    // delete exp2;
    // delete exp3;
}