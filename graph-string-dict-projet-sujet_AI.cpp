#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include <fstream>
#include <limits>
#include <iomanip>

// Déclarations anticipées pour permettre les amitiés (friend)
class Vertex;
class Graph;

// ==========================================
// CLASSE EDGE
// ==========================================
class Edge {
    friend class Vertex;
    friend class Graph;

private:
    Vertex* destination;
    double weight;

    // Constructeur privé : seul Graph (via Vertex) pourra instancier une arête
    Edge(Vertex* dest, double w) : destination(dest), weight(w) {}
};

// ==========================================
// CLASSE VERTEX
// ==========================================
class Vertex {
    friend class Graph;

private:
    std::string name;
    std::vector<Edge*> edges;

    // Constructeur privé : seul Graph pourra instancier un sommet
    Vertex(const std::string& n) : name(n) {}

    // Destructeur : nettoie la mémoire de ses propres arêtes
    ~Vertex() {
        for (Edge* e : edges) {
            delete e;
        }
    }
};

// ==========================================
// CLASSE MATRIX
// ==========================================
class Matrix {
    friend class Graph;

private:
    std::vector<std::vector<double>> data;

    // Construit une matrice carrée initialisée à l'infini, avec des 0 sur la diagonale
    Matrix(int size = 0) {
        double inf = std::numeric_limits<double>::infinity();
        data.assign(size, std::vector<double>(size, inf));
        for (int i = 0; i < size; ++i) {
            data[i][i] = 0.0;
        }
    }
};

// ==========================================
// CLASSE GRAPH
// ==========================================
class Graph {
private:
    std::vector<Vertex*> vertices;
    std::unordered_map<std::string, int> name_to_index;
    Matrix adj_matrix;

    // Méthode utilitaire pour trouver ou créer un sommet dynamiquement
    Vertex* get_or_create_vertex(const std::string& name) {
        auto search = name_to_index.find(name);
        if (search != name_to_index.end()) {
            return vertices[search->second]; // Sommet existant
        }
        
        // Création d'un nouveau sommet
        Vertex* v = new Vertex(name);
        int index = vertices.size();
        vertices.push_back(v);
        name_to_index[name] = index;
        return v;
    }

    // Fonction récursive interne pour le parcours DFS
    void dfs_recursive(Vertex* v, std::set<std::string>& visited) {
        visited.insert(v->name);
        std::cout << v->name << " ";

        for (Edge* e : v->edges) {
            if (visited.find(e->destination->name) == visited.end()) {
                dfs_recursive(e->destination, visited);
            }
        }
    }

public:
    Graph() {}

    // 3) Gestion de la mémoire : suppression des sommets (qui supprimeront leurs arêtes)
    ~Graph() {
        for (Vertex* v : vertices) {
            delete v;
        }
    }

    // Ajout d'une arête (crée les sommets si nécessaire)
    void add_edge(const std::string& from, const std::string& to, double weight) {
        Vertex* v_from = get_or_create_vertex(from);
        Vertex* v_to = get_or_create_vertex(to);
        
        // 3) Instanciation dynamique avec 'new'
        v_from->edges.push_back(new Edge(v_to, weight));
    }

    // 4) Méthode de lecture depuis un fichier
    void read_file(const std::string& filename) {
        std::cout << "Lecture du fichier: " << filename << std::endl;
        std::ifstream file(filename);

        if (!file.is_open()) {
            throw std::runtime_error("Fichier " + filename + " introuvable.");
        }

        std::string from, to;
        double value;

        while (file >> from >> to >> value) {
            add_edge(from, to, value);
        }
        file.close();
    }

    // 5) Parcours en profondeur (DFS) avec std::set
    void dfs() {
        std::set<std::string> visited;
        std::cout << "\n--- Parcours DFS ---" << std::endl;
        
        // On boucle sur tous les sommets au cas où le graphe soit non connexe
        for (Vertex* v : vertices) {
            if (visited.find(v->name) == visited.end()) {
                dfs_recursive(v, visited);
            }
        }
        std::cout << std::endl;
    }

    // 6) Construction de la matrice d'adjacence
    void build_adjacency_matrix() {
        int n = vertices.size();
        adj_matrix = Matrix(n); // Réinitialise la matrice à la bonne taille

        for (int i = 0; i < n; ++i) {
            Vertex* u = vertices[i];
            for (Edge* e : u->edges) {
                int j = name_to_index[e->destination->name];
                adj_matrix.data[i][j] = e->weight;
            }
        }
        std::cout << "\n--- Matrice d'adjacence construite ---\n";
    }

    // 7) Algorithme de Floyd-Warshall
    void floyd_warshall() {
        int n = vertices.size();
        
        // Application de l'algorithme
        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    double dist_ik = adj_matrix.data[i][k];
                    double dist_kj = adj_matrix.data[k][j];
                    
                    if (dist_ik != std::numeric_limits<double>::infinity() && 
                        dist_kj != std::numeric_limits<double>::infinity()) {
                        
                        if (adj_matrix.data[i][j] > dist_ik + dist_kj) {
                            adj_matrix.data[i][j] = dist_ik + dist_kj;
                        }
                    }
                }
            }
        }

        // Affichage des plus courts chemins
        std::cout << "\n--- Matrice de Floyd-Warshall (Plus courts chemins) ---\n";
        
        // En-tête des colonnes
        std::cout << std::setw(10) << " ";
        for (int i = 0; i < n; ++i) {
            std::string name = vertices[i]->name;
            // Tronquer pour l'affichage si le nom est long
            if(name.length() > 8) name = name.substr(0, 8) + ".";
            std::cout << std::setw(10) << name;
        }
        std::cout << "\n";

        // Lignes
        for (int i = 0; i < n; ++i) {
            std::string name = vertices[i]->name;
            if(name.length() > 8) name = name.substr(0, 8) + ".";
            std::cout << std::setw(10) << name;
            
            for (int j = 0; j < n; ++j) {
                if (adj_matrix.data[i][j] == std::numeric_limits<double>::infinity()) {
                    std::cout << std::setw(10) << "INF";
                } else {
                    std::cout << std::setw(10) << adj_matrix.data[i][j];
                }
            }
            std::cout << "\n";
        }
    }
};

// ==========================================
// FONCTION MAIN
// ==========================================
int main() {
    // 1. Préparation d'un fichier de test
    std::ofstream out("graph0.gr");
    out << "Paris Lyon 100.56\nParis Nice 200.50\nParis Marseille 140.20\nParis Toulouse 200.8\n"
        << "Paris Le_Havre 120\nLyon Nice 80.50\nLyon Marseille 50\n"
        << "Marseille Nice 70\nMarseille Toulouse 80\nToulouse Nice 100\n";
    out.close();

    // 2. Utilisation de la classe Graph
    try {
        Graph graph;
        
        // Lecture du graphe
        graph.read_file("graph0.gr");
        
        // Parcours
        graph.dfs();
        
        // Matrice et Algorithme
        graph.build_adjacency_matrix();
        graph.floyd_warshall();
        
    } catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }

    return 0;
}