#include <iostream>
#include <vector>
#include <random>
#include <iterator>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <dirent.h>
// #include <filesystem>

// #define BOOST_FILESYSTEM_VERSION 3
// #define BOOST_FILESYSTEM_NO_DEPRECATED 
// #include <boost/filesystem.hpp>

// namespace fs = boost::filesystem;

// /**
//  * \brief   Return the filenames of all files that have the specified extension
//  *          in the specified directory and all subdirectories.
//  */
// std::vector<fs::path> get_all(fs::path const & root, std::string const & ext)
// {
//     std::vector<fs::path> paths;

//     if (fs::exists(root) && fs::is_directory(root))
//     {
//         for (auto const & entry : fs::recursive_directory_iterator(root))
//         {
//             if (fs::is_regular_file(entry) && entry.path().extension() == ext)
//                 paths.emplace_back(entry.path().filename());
//         }
//     }

//     return paths;
// }            

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

bool getFileContent(std::string fileName, std::vector<std::string> & vecOfStrs)
{
    // Open the File
    std::ifstream in(fileName.c_str());
    // Check if object is valid
    if(!in)
    {
        std::cerr << "Cannot open the File : "<<fileName<<std::endl;
        return false;
    }
    std::string str;
    // Read the next line from File untill it reaches the end.
    while (std::getline(in, str))
    {
        // Line contains string of length > 0 then save it in vector
        if(str.size() > 0)
            vecOfStrs.push_back(str);
    }
    //Close The File
    in.close();
    return true;
}

int main()
{
    std::vector <std::string> filename;
    std::string path = "/home/ravi/Ubuntu-WSL-20/PSML/benchmarks/comp/2019/CLIA_Track/from_2018/";
    std::ifstream in("SygusFileNames.txt");
    bool file = getFileContent("SygusFileNames.txt", filename);
    if(file)
    {
        // Print the vector contents
        std::string program="\0";
        std::string result;
        std::string cmd;
        std::string execTime;
        std::string name;
        // auto t1, t2, duration;
        int i=0;
        for(std::string & line : filename)
        {
            i++;
            // std::cout<<line<<std::endl;
            cmd = "timeout 60s cvc4 /home/ravi/Ubuntu-WSL-20/PSML/benchmarks/comp/2019/CLIA_Track/from_2018/"+line+" 2> /dev/null";
            auto t1 = std::chrono::high_resolution_clock::now();
            result = runCVC4(cmd);
            auto t2 = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
            execTime = std::to_string(duration);
            name = "SynthesisTime4CLIA(Timeout=60sec).csv";

            if(result == "\0")
            {
                // std::cout<<"Error: Timeout";
                writeToCSV(name, "\n"+std::to_string(i)+","+line+","+"Timeout"+","+execTime, true);
            }
            else if (result == "unknown\n")
            {
                writeToCSV(name, "\n"+std::to_string(i)+","+line+","+"unknown"+","+execTime, true);
            }
            else
            {
                program = result.substr(6, result.size() - 6);
                program.erase(std::remove(program.begin(), program.end(), '\n'), program.end());
                writeToCSV(name, "\n"+std::to_string(i)+","+line+","+program+","+execTime, true);
            }
        }
    }
    
    
}