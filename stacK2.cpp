#include <iostream>
class IntStack {
private:
    int size;      
    int top;       
    int* tab;      

public:
    
    IntStack(int s) : size{s}, top{0} {
        tab = new int[size];
    }

    
    ~IntStack() {
        delete[] tab;
    }
    IntStack(const IntStack& ri) : 
    size{ri.size}, 
    top{ri.top} 
    {
        tab = new int[size];
        for (int i = 0; i < top; ++i) 
        {
            tab[i] = ri.tab[i];
        }
    }

    IntStack& operator=(const IntStack& ri) {
        if (this != &ri) { 
            delete[] tab;
            size = ri.size;
            top = ri.top;
            tab = new int[size];
            for (int i = 0; i < top; ++i) {
                tab[i] = ri.tab[i];
            }
        }
        return *this;
    }
