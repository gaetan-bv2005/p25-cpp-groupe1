#include <iostream>
#include <vector>

struct Vertex;
struct Edge;







struct Vertex
{

    int name ;
    std::vector<Edge*>adj_vector;
    Vertex(int id) : name(id){};
};

struct Edge{

    double weight; ;
    Vertex* begin;
    Vertex* end;

    Edge(Vertex* debut, Vertex* fin,double poids) : begin(debut), end(fin), weight(poids){}


};

struct Graphe {

    std::vector<Vertex*> vertices;
    
    void addEdge (int begin, int end, double value){

        bool begin_already_exist = false;
        bool end_already_exist = false;
        Vertex* u = nullptr;
        Vertex* b = nullptr;

        for (Vertex* v : vertices){
            int n = v->name;
            if (n == begin) {
                begin_already_exist = true;
                u = v;
            }
            if (n == end) {
                end_already_exist = true;
                b= v ;
            }   
        }  
            
        
    
        
        if (begin_already_exist == false) {
            u = new Vertex(begin);
            vertices.push_back(u);
        }
            

        if (end_already_exist == false) {
            b = new Vertex(end);
            vertices.push_back(b) ;
        }
        
        Edge* new_edge = new Edge(u, b, value);
        u->adj_vector.push_back(new_edge);    
        b->adj_vector.push_back(new_edge);    
            
    }
    
    void print() {
        for (Vertex* v : vertices){
            std::cout << "Vertex " << v->name << " connected to: ";
            std::cout << std::endl;
        }
    }

} 


int main()
 {
    Graphe g;

    g.addEdge(1,5,17.9);
    g.addEdge(5,3,23.9);
    g.addEdge(3,4,16.9);
    g.addEdge(4,0,699.9);
    g.print();
    return 0;
}



