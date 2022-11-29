#include <iostream>
#include <iomanip>
#include <stdexcept>
#include<fstream>
#include<list>
#include<unordered_map>
#include<set>

using namespace std;

class AcademiaChino {
private:
    struct InfoPersona {
        int clase;
        list<string>::iterator it;
    };
    list<string> alumnos_grupo[8];
    unordered_map<string, InfoPersona> info_alumno;
    set<string> grad;
public:
    //O(1)
    void nuevo_estudiante(string dni, int grupo) {
        if (info_alumno.count(dni)) {
            throw domain_error("Estudiante existente");
        }
        if (1 > grupo || grupo >= 7) {
            throw domain_error("Grupo incorrecto");
        }

        alumnos_grupo[grupo].push_back(dni);
        list<string>::iterator it = alumnos_grupo[grupo].end();
        it--;
        info_alumno.insert({ dni, {grupo, it }});
    }

    void promocionar(string dni) {
        auto it = info_alumno.find(dni);
        if (it == info_alumno.end()) {
            throw domain_error("Estudiante no existente");
        }
        if (it->second.clase == 7) {
            throw domain_error("Estudiante ya graduado");
        }
        int c = it->second.clase;
        list<string>& clase = alumnos_grupo[c];
        clase.erase(it->second.it);
        c++;
        it->second.clase=c;
        alumnos_grupo[c].push_back(dni);
        list<string>::iterator l = alumnos_grupo[c].end();
        l--;
        info_alumno[dni] = { c, l };

        if (c == 7) grad.insert(dni);
    }

    int grupo_estudiante(string dni) {
        auto it = info_alumno.find(dni);
        if (it == info_alumno.end()) {
            throw domain_error("Estudiante no existente");
        }
        if (it->second.clase == 7) {
            throw domain_error("Estudiante ya graduado");
        }
        return it->second.clase;
    }

    set<string> graduados() {
        return grad;
    }

    string novato(int grupo) {
        if (0 > grupo || grupo >= 7) {
            throw domain_error("Grupo incorrecto");
        }
        if (alumnos_grupo[grupo].empty()) {
            throw domain_error("Grupo vacio");
        }

        return alumnos_grupo[grupo].back();
    }

};

bool resuelveCaso() {
    // leer los datos de la entrada
    string opcion;
    cin >> opcion;
    if (!std::cin)
        return false;

    AcademiaChino academia;
    string dni;
    int grupo;
    while (opcion != "FIN") {
        try {
            if (opcion == "nuevo_estudiante") {
                cin >> dni >> grupo;
                academia.nuevo_estudiante(dni, grupo);
            }
            else if (opcion == "grupo_estudiante") {
                cin >> dni;
                int grupo = academia.grupo_estudiante(dni);
                cout << dni << " esta en el grupo " << grupo << endl;
            }
            else if (opcion == "promocionar") {
                cin >> dni;
                academia.promocionar(dni);
            }
            else if (opcion == "graduados") {
                set<string> alumnos = academia.graduados();
                cout << "Lista de graduados: ";
                for (auto it : alumnos) {
                    cout << it << " ";
                }
                cout << endl;
            }
            else if (opcion == "novato") {
                cin >> grupo;
                string dniN = academia.novato(grupo);
                cout << "Novato de " << grupo << ": " << dniN << endl;
            }
        }
        catch (domain_error &ex) {
            cout << "ERROR: " << ex.what() << endl;
        }
        cin >> opcion;
    }
    // escribir sol

    cout << "---" << endl;
    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    while (resuelveCaso())
        ;


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}
