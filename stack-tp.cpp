#include <iostream>

// Nous allons implémenter une pile d'entiers de manière très basique.
// Nous la complexifierons par la suite.

// La pile est constituée:
//    - d'un tableau d'entier, avec sa taille et son nombre d'éléments empilés
//    - des quatre fonctions: push, pop, top, print, is_empty et is_full
//      (qui testent si la pile est resp. vide ou pleine)
//      il faut les utiliser dans votre code de push et pop

void print(int stack[], int size, int nb)
// cette fonction affiche les entiers empilés
{
    std::cout << "[";
    
    for (int i = 0; i < nb; i += 1)
    { 
        std::cout << stack[i] << " "; 
    }
    std::cout << "]" << std::endl; 
}

// renvoie true si la pile est vide, false sinon
bool is_empty(int stack[] , int size , int nb)
{
    return nb == 0 ;
}

// renvoie true si la pile est pleine, false sinon
bool is_full(int stack[] , int size , int nb)
{
    return nb == size ;
}


void push(int stack[], int size, int &nb, int value)
// cette fonction ajoute un entier à la pile passé en argument
// elle doit s'assurer que la pile n'est pas pleine avant d'empiler
// elle lance une exception si problème
{
 
    if (is_full(stack, size, nb) == true)
    {
        throw std::overflow_error("Erreur [push]: La pile est pleine.");
    }
    else 
       {
        stack[nb] = value;
        nb += 1;
        }
}


int top(int stack[], int size, int nb) // (cette fonction ne dépile pas)
// cette fonction retourne l'entier en haut de la pile (le dernier empilé)
// à la sortie de cette fonction l'élément retourné reste dans la pile
// elle doit s'assurer que la pile n'est pas vide avant de la dépiler
// elle lance une exception si problème
{
 
    if (is_empty(stack, size, nb) == true)
    {
 
        throw std::underflow_error("Erreur [top]: La pile est vide.");
    }
    else 
    {
        return stack[nb - 1];
    }
}

int pop(int stack[], int size, int &nb) 
{
 
    if (is_empty(stack, size, nb) == true)
    {

        throw std::underflow_error("Erreur [pop]: La pile est vide.");
    }
    else 
    {
        int a = stack[nb - 1];
        nb = nb - 1; 
        return a;
    }
}


int main()
{
    
    const int size = 5;
    int stack[size];
    int nb = 0;


    try
    {
        print(stack, size, nb); // Affiche: []
        push(stack, size, nb, -17);
        print(stack, size, nb); 


        std::cout << "Top: " << top(stack, size, nb) << std::endl; 



        int e = pop(stack, size, nb);
        std::cout << "Pop: " << e << std::endl; // Affiche: Pop: -17
        print(stack, size, nb); // Affiche: []

        push(stack, size, nb, 20);
        push(stack, size, nb, -78);
        push(stack, size, nb, -9);
        push(stack, size, nb, -56);
        push(stack, size, nb, -9); // La pile est pleine (5 éléments)
        print(stack, size, nb); 

 
        push(stack, size, nb, 68);
    }
    catch (std::overflow_error &e) // Pile pleine
    {
        std::cerr << "EXCEPTION ATTRAPÉE (Pile Pleine): " << e.what() << std::endl;
    }
    catch (std::underflow_error &e) // Pile vide
    {
        std::cerr << "EXCEPTION ATTRAPÉE (Pile Vide): " << e.what() << std::endl;
    }

}