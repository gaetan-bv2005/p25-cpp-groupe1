#include <iostream>
#include <cstdlib>


int main(int argc, char *argv[])
{

 
    int i = 1;
    int somme = 0 ;

    if (argc == 1) 
    {
        std::cerr <<  "not enough arguments"<< std::endl;
    }
    while (i < argc)

    {
        somme = somme + std::stoi(argv[i]);
        std::cout << argv[i] << std::endl;
        i = i + 1;
    }
    std::cout << somme << std::endl;

    return 0;


}
