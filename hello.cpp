#include <iostream>

int main() {

    //1. Déclarer une variable pour stocker le nom
    std::string nom;
    //2 Demander le nom à l'utilisateur 
    std::cout <<"Quel est votre nom ?";

    //3 Lire l'entrée clavier et la stocker dans la variable 'nom'
    std::cin >> nom ;

    //4 Saluer l'utilisateur par son nom
    std::cout << "Bonjour, " <<nom<<"!";
    
    return 0;
}



