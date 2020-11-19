#include <iostream>
#include <fstream>
#include <stdexcept>
#include <stdio.h>
#include <cstdlib>
#include <cstdio>
#include <memory>
#include <stdexcept>

std::string exec(std::string command) {
   char buffer[128];
   std::string result = "";

   // Open pipe to file
   FILE* pipe = popen(command.c_str(), "r");
   if (!pipe) {
      return "popen failed!";
   }

   // read till end of process:
   while (!feof(pipe)) {

      // use buffer to read and add to result
      if (fgets(buffer, 128, pipe) != NULL)
         result += buffer;
   }

   pclose(pipe);
   return result;
}

void filePutContents(const std::string& name, const std::string& content, bool append = false) {
    std::ofstream outfile;
    if (append)
        outfile.open(name, std::ios_base::app);
    else
        outfile.open(name);
    outfile << content;
}

int main(int argc, char* argv[])
{

    std::string j = argv[1];
    std::cout<<"str"+j<<"\n";
    for(int i=0; i<1; i++)
    {
        std::string name = "randomconstraint"+j+".csv";
        std::ofstream file("Dataset/"+name);
        file << j;
        // file << "Constraints"<<","<<"Programs"<<"\n";
        // file << "(and (< x (f x y)) (< x (f x y)))"<<","<<" unsat (define-fun f ((x Int) (y Int)) Int (+ 1 x))"<<"\n";
        filePutContents(name, "Constraints,Programs\n", true);
    }
 
    std::string result = exec("timeout 0.1s cvc4 /home/ravi/Ubuntu-WSL-20/PSML/benchmarks/comp/2019/CLIA_Track/from_2018/test21.sl 2> /dev/null");
    if(result == "\0")
    {
        std::cout<<"Error: Timeout";
    }
    else
    {
        std::string program = result.substr(6, result.size() - 6);
        std::cout << program;
    }
    
    std::string templateFile = "(set-logic LIA)\n(synth-fun f ((x Int) (y Int)) Int)\n(declare-var x Int)\n(declare-var y Int)\n(constraint $$)\n(check-synth)";
    size_t index = 0;
    std::cout<<"\n";
    std::string rep = "(kya hai?)";
    while (true) {
        /* Locate the substring to replace. */
        index = templateFile.find("$$", index);
        if (index == std::string::npos) break;

        /* Make the replacement. */
        templateFile.replace(index, 2, rep);

        /* Advance index forward so the next iteration doesn't pick it up as well. */
        index += 3;
    }
    
    // std::cout<<templateFile;
    // std::cout << result;
}