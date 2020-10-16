#include <iostream>
#include <vector>
#include <random>
#include <iterator>
#include <fstream>
#include <chrono>
#include <algorithm>
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

std::string insertConstraint(std::string templateFile, std::string constraint)
{
    size_t index = 0;
    while (true) {
        /* Locate the substring to replace. */
        index = templateFile.find("$$", index);
        if (index == std::string::npos) break;

        /* Make the replacement. */
        templateFile.replace(index, 2, constraint);

        /* Advance index forward so the next iteration doesn't pick it up as well. */
        index += 3;
    }
    return templateFile;
}

std::string runCVC4(std::string command) {
    // std::cout<<command;
        

   char buffer[128];
   std::string result = "";

   // Open pipe to file
   FILE* pipe = popen(command.c_str(), "r");
   if (!pipe) {
      return "popen failed!";
   }

   // read till end of process:
   while (!feof(pipe)) {
    //    std::cout<<"in runCVC4\n";
      // use buffer to read and add to result
      if (fgets(buffer, 128, pipe) != NULL)
         result += buffer;
   }
    // std::cout<<"res: "<<result;
   pclose(pipe);
   return result;
}

void writeToCSV(const std::string& name, const std::string& content, bool append = false) {
    std::ofstream outfile;
    if (append)
        outfile.open(name, std::ios_base::app);
    else
        outfile.open(name);
    outfile << content;
}

int main(int argc, char* argv[])
{
    auto t1 = std::chrono::high_resolution_clock::now();

    std::string filenum = argv[1];
    std::string datapoints = argv[2];
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

    std::string templateFile = "(set-logic LIA)\n(synth-fun f ((x Int) (y Int)) Int)\n(declare-var x Int)\n(declare-var y Int)\n(constraint $$)\n(check-synth)";

    for(int i = 0; i<numOfOperator; i+=3)
    {
        // std::cout<<i<<"\n";
        exp1 = new FormulaBinaryExp(*select_randomly(ArithmaticOperandList.begin(), ArithmaticOperandList.end()), *select_randomly(ArithmaticOperandList.begin(), ArithmaticOperandList.end()), *select_randomly(ArithmaticOperatorList.begin(), ArithmaticOperatorList.end()));
        ArithmaticOperandList.push_back(exp1);
        exp1 = new FormulaBinaryExp(*select_randomly(ArithmaticOperandList.begin(), ArithmaticOperandList.end()), *select_randomly(ArithmaticOperandList.begin(), ArithmaticOperandList.end()), *select_randomly(ComparisonOperatorList.begin(), ComparisonOperatorList.end()));
        ComparisonOperandList.push_back(exp1);
        exp1 = new FormulaBinaryExp(*select_randomly(ComparisonOperandList.begin(), ComparisonOperandList.end()), *select_randomly(ComparisonOperandList.begin(), ComparisonOperandList.end()), *select_randomly(LogicalOperatorList.begin(), LogicalOperatorList.end()));
        LogicalOperandList.push_back(exp1);
    }
    
    // LogicalOperandList.back()->prettyPrinter();
    // std::cout<<"\n";
    std::string constraint = LogicalOperandList.back()->formulaToString();
    // std::cout<<constraint;
    // std::cout<<"\n";

    std::string sygusFile = insertConstraint(templateFile, constraint);

    std::string name = "randomlyGeneratedBenchmark_"+filenum+".sl";
    std::ofstream slFile("Dataset/"+name);
    slFile << sygusFile;
    slFile.close();
    
    std::string program="\0";
    std::string cmd = "timeout 0.1s cvc4 /home/ravi/Ubuntu-WSL-20/PSML/DatasetGeneration/Dataset/"+name+" 2> /dev/null";
    std::string result = runCVC4(cmd);

    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();

    std::string execTime = std::to_string(duration);
    name = "datasetGenerated"+datapoints+".csv";
    if(result == "\0")
    {
        // std::cout<<"Error: Timeout";
        writeToCSV(name, "\n"+filenum+","+constraint+","+"Timeout"+","+execTime, true);
    }
    else if (result == "unknown\n")
    {
        writeToCSV(name, "\n"+filenum+","+constraint+","+"unknown"+","+execTime, true);
    }
    else
    {
        program = result.substr(6, result.size() - 6);
        program.erase(std::remove(program.begin(), program.end(), '\n'), program.end());
        writeToCSV(name, "\n"+filenum+","+constraint+","+program+","+execTime, true);
    }

    
    // std::cout << "Execution Time: " << duration;
    // std::ofstream et("")

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