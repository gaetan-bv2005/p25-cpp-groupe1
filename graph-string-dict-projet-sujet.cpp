// Un dernier projet sur les graphes.
// Vous devez représenter un graphe sous la forme de liste d'adjacence, constitué de sommets nommés
// et d'arêtes portant une valeur numérique (double) entre ces sommets.

// Dans un graphe sous la forme de liste d'adjacence:
//    - le graphe possède le vecteur de ses sommets;
//    - chaque sommet possède le vecteurs des arêtes dont il est le sommet de départ.

// Vous devez coder les class Vertex, Edge et Graph, avec les consignes suivantes:
//    0) ne mettez pas d'attributs en public
//       ne mettez pas de méthodes pour accéder aux attributs
//       mais utilisez friend au besoin

//    1) les sommets sont identifiés par leurs noms qui sont des std::string

//    2) vous devez utiliser des std::vector pour les listes de sommets et d'arêtes
//       a) Vous devez donc conserver une correspondance entre le nom d'un sommet et son indice dans le graphe
//          pour cela le graphe possède une std::unordered_map<std::string, int> comme montré ci-dessous

//    3) vous utilisez new et delete pour les Vertex et Edge dans le graphe.

//    4) vous devez proposer une méthode de la classe Graph qui lise un graphe écrit dans un fichier
//       comme exemple, regardez la fonction read_graph ci-dessous

//    5) vous devez implémenter un parcours de ce graphe en profondeur (déjà fait en cours)
//       pour stocker les sommets déjà visités utilisez un std::set

//    6) vos devez implémenter une méthode de Graph qui construit la matrice d'adjacence du graphe
//       vous stockez cette matrice comme attribut du graphe
//       utilisez votre class Matrix ou codez-en une

//    7) appliquez à cette matrice d'adjacence l'Algorithme de Floyd-Warshall
//  https://fr.wikipedia.org/wiki/AlgorithmedeFloyd-Warshall
// qui calcule les plus courts chemins entre tous les sommets d'un graphe

//   8) IA générative:
//    a) N'utilisez pas d'IA générative pour générer votre code sauf pour des choses
//       très ciblées/spécifique mais pas pour générer tout un code !
//    b) quand vous faites générer une partie très spécifique de code, vous devez:
//       i) indiquer que c'est de l'IA
//       ii) relire, debugger, tester et donc comprendre exactement tout le code
//       iii) ne pas laisser de construction c++ que vous ne maîtrisez pas

//   9) une fois le programme complètement codé,
//      i) utilisez une IA générative pour générer un code avec les mêmes contraintes que le vôtre
//         mettez ce code dans un fichier du même nom que celui du projet avec "_IA" avant le .cpp ou le .h
//      ii) relisez-le et notez dans le fichier les endroit que vous ne comprenez pas
//          ou qui sont très différents de ce que vous avez utilisé en cours
//      iii) demandez à l'IA de vous expliquer ces endroits et mettez l'explication dans votre fichier
//      Mettez dans votre repo ce ou ces fichiers aussi (avec donc _IA avant le '.' du suffixe '***_IA.cpp" ou "***_IA.h")

// Cette fonction read_triplet lit une suite de triplets:
//           from_1 to_1 value_1 from_2 to_2 value_2 ... from_n to_n value_n
//    où les value_i sont des doubles e.g. 3.14159
//    où from_i et to_i sont des mots SANS espace e.g. Le_Havre mais pas Le Havre ou "Le Havre"
// voir fichier graph0.gr






#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <unordered_map>
#include <set>
#include <limits>
class Vertex;
class Graph;
class Edge;





class Matrix {
    int nb_lines;
    int nb_columns;
    std::vector<std::vector<double>> data;

public: 
    
    Matrix() : nb_lines(0), nb_columns(0) {} 
    Matrix(int lines, int columns) : nb_lines(lines), nb_columns(columns), data(lines, std::vector<double>(columns, std::numeric_limits<double>::infinity())) {}
          
    friend class Graph;
    friend Matrix Floyd_Warshall(const Matrix& M);
};

class Edge {
    double edge_weight;
    std::vector<Vertex*> vertex_list;
    Edge(double value, std::vector<Vertex*> list = {}) 
        : edge_weight(value), vertex_list(list) {}

    friend class Graph;
    friend class Vertex;
};

class Vertex {
    std::string vertex_name;
    std::vector<Edge*> edge_list;
    Vertex(std::string name, std::vector<Edge*> list = {}) 
        : vertex_name(name), edge_list(list) {}

    friend class Graph;
    friend class Edge;
};




class Graph {
    std::vector<Vertex*> all_vertex;
    std::vector<Edge*> all_edge;
    std::unordered_map<std::string, int> vertex_to_indice;
    std::string graph_name;
    
    Matrix adj_matrix_data;

public:
    Graph() {}


    

    ~Graph() {
        for (Vertex* v : all_vertex) {
            delete v;
        }
        for (Edge* e : all_edge) {
            delete e;
        }
    }

    std::pair<bool, int> research_vertex(const std::string &name) {
        for (int i = 0; i < all_vertex.size(); i++) {
            if (all_vertex[i]->vertex_name == name) {
                return {true, i}; 
            }
        }
        return {false, -1};
    }

    void add_edge(const std::string &begin, const std::string &end, double value) {


        Edge *e = new Edge(value, std::vector<Vertex*>{});
        Vertex *v_begin = nullptr;
        Vertex *v_end = nullptr;
        
        std::pair<bool, int> resul_research_begin = research_vertex(begin);
        std::pair<bool, int> result_research_end = research_vertex(end);

        if (resul_research_begin.first == false) {
            v_begin = new Vertex(begin, std::vector<Edge*>{});
            all_vertex.push_back(v_begin);
            vertex_to_indice[begin] = all_vertex.size()-1 ;
            v_begin->edge_list.push_back(e);
        }
        else {
            v_begin = all_vertex[resul_research_begin.second];
            v_begin->edge_list.push_back(e);
        }

        if (result_research_end.first == false) {
            v_end = new Vertex(end, std::vector<Edge*>{});
            all_vertex.push_back(v_end);
            vertex_to_indice[end] = all_vertex.size()-1 ;
        }
        else {
            v_end = all_vertex[result_research_end.second];
            v_end->edge_list.push_back(e);
        }

        e->vertex_list.push_back(v_begin);
        e->vertex_list.push_back(v_end);
        all_edge.push_back(e);    
    }    
    
    void dfs() {
        




        std::set<Vertex*> discovered;
        std::vector<Vertex*> to_explore;

        Vertex* startNode = all_vertex[0];
        to_explore.push_back(startNode);
        discovered.insert(startNode);
        
        while (!to_explore.empty()) {
            Vertex* v = to_explore.back();
            to_explore.pop_back();
            for (Edge* e : v->edge_list) {
                Vertex* neighbor = e->vertex_list[1];
                
                if (discovered.find(neighbor) == discovered.end()) {
                    discovered.insert(neighbor);
                    to_explore.push_back(neighbor);
                }
            }
        }
    }

    
    
    void build_adj_matrix() {
        int n = all_vertex.size();
        adj_matrix_data = Matrix(n, n);
        
        for(int i = 0; i < n; ++i) {
            adj_matrix_data.data[i][i] = 0.0; 
        }

        for (int i = 0; i < all_edge.size(); i++) {
            Edge* e = all_edge[i];
            Vertex* start = e->vertex_list[0];
            Vertex* end = e->vertex_list[1];
            
            int start_index = vertex_to_indice[start->vertex_name];
            int end_index = vertex_to_indice[end->vertex_name];
            adj_matrix_data.data[start_index][end_index] = e->edge_weight;
        }
    }

};

Matrix Floyd_Warshall(const Matrix& M) {
    int n = M.nb_lines;
    Matrix W = M; 
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) { 
                if (W.data[i][j] > W.data[i][k] + W.data[k][j]) {
                    W.data[i][j] = W.data[i][k] + W.data[k][j];
                }
            }
        }
    }
    return W;
}


Graph read_triplet(const std::string &filename)
{
    Graph g;
    std::cout << "read_triplet(" << filename << ")" << std::endl;

    // on essaie d'ouvrir le fichier en lecture
    // pour cela on crée un objet de type std::ifstream (input file stream)
    //    et le constructeur ouvre le fichier
    std::ifstream file(filename);

    if (not file.is_open())
    {
        // si le fichier n'a pas pu être ouvert, on s'en va e.g. par une exception
        throw std::runtime_error(std::string("file ") + filename + std::string(" not found"));
    }

    // si on est arrivé là c'est que le fichier est ouvert, on va le lire
    // on sait qu'il contient le graphe sur une ligne sous la forme de triplets: from to value
    // e.g. Paris Lyon 100 Paris Nice 200 Paris ...

    // from, to sont des strings et value un double
    // on réserve trois variables pour lire ces valeurs
    std::string from, to;
    double value;

    while (file >> from >> to >> value) // tant qu'on a un triplet (les 2 strings et l'int) à lire
    // notons que l'expression "file >> var" a comme valeur l'état du fichier après la lecture de var
    {
        std::cout << from << " " << to << " " << value << std::endl;
        g.add_edge(from, to, value);
        // là on l'affiche simplement l'arête, mais il faut l'ajouter au graphe !
        // g.add_vertex(from, to, value);
    }
    std::cout << std::endl;

    file.close(); // on ferme le fichier

    // Attention ça échouera si vous mettez un nom de ville avec un espace (ou une tabulation)
    // (même si vous mettez des " " autour), en effet
    //    - quand une std::string est lue, la lecture se fait jusqu'au premier espace
    //      si vous mettez "Le Havre" ça fera deux mots donc ça échouera
    //      il faudra mettre Le_Havre

    return g;
}

int main()
{

    // LECTURE DU GRAPHE
    Graph graph = read_triplet("graph0.gr");
    graph.dfs();

    // EXEMPLE D'UTILISATION D'UN DICTIONNAIRE STD::UNORDERED_MAP
    // voici un exemple d'utilisation d'un dictionnaire pour stocker:
    //    - comme clé les noms des sommets
    //    - comme valeur son indice dans le vector
    std::unordered_map<std::string, int> srt_to_indice;
    int i = 0;
    // "Paris" "Nice" 350.50
    srt_to_indice["Paris"] = i;
    i = i + 1;

    srt_to_indice["Nice"] = i;
    i = i + 1;

    // ou utilisez auto pour l'inférence de type (le type est généré)
    std::unordered_map<std::string, int>::iterator search_paris = srt_to_indice.find("Paris");
    if (search_paris != srt_to_indice.end())
        std::cout << "found Paris\n"
                  << search_paris->first << ' ' << search_paris->second << '\n';
    else
        std::cout << "Paris not found\n";

    auto search = srt_to_indice.find("Antibes");
    if (search != srt_to_indice.end())
        std::cout << "Antibes found\n"
                  << search->first << ' ' << search->second << '\n';
    else
        std::cout << "Antibes not found\n";

    // On accède à un l'indice d'un sommet
    std::cout << srt_to_indice["Paris"] << std::endl;

    // accès aux éléments du dictionnaire
    for (auto &e : srt_to_indice) // & pour éviter de recopier l'objet
    {
        std::cout << "key: " << e.first
                  << " value: " << e.second << std::endl;
    }

    // 2) accès par std::get<0> et std::get<1>
    // à préférer à first et second
    for (auto &e : srt_to_indice)
    {
        std::cout << "key: " << std::get<0>(e)
                  << " value: " << std::get<1>(e) << std::endl;
    }

    // EXEMPLE D'UTILISATION D'UN STD::SET
    std::set<int> visited;
    visited.insert(2);

    std::set<int>::iterator search_0 = visited.find(0);
    if (search_0 != visited.end())
        std::cout << "Found 0\n";
    else
        std::cout << "0 not found\n";

    std::set<int>::iterator search_2 = visited.find(2);
    if (search_2 != visited.end())
        std::cout << "found 2\n";
    else
        std::cout << "2 not found\n";

    return 0;
}

/*

mettre dans le fichier graph0.gr par exemple
Paris Lyon 100.56 Paris Nice 200.50 Paris Marseille 140.20 Paris Toulouse 200.8
Paris Le_Havre 120 Lyon Nice 80.50 Lyon Marseille 50
Marseille Nice 70 Marseille Toulouse 80 Toulouse Nice 100

*/