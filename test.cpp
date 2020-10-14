#include <iostream>
#include <fstream>

int main()
{
    int i;
    for(i=0; i<4; i++)
    {
        std::string name = "randomconstraint"+std::to_string(i)+".csv";
        std::ofstream file("Dataset/"+name);
    }
}