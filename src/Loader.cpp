#include "Loader.hpp"

#include <fstream>    // ouvrir et lire un fichier
#include <sstream>    // découper une ligne en morceaux
#include <stdexcept>  // exceptions
#include <string>     // convertir "185.5" en double

std::vector<Bar> loadBarsFromCSV(const std::string& path) {
    std::vector<Bar> bars;

    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Loader: cannot open file: " + path);
    }

    std::string line;
    // on lit la première ligne, qui contient les noms des colonnes, et on l'ignore 
    //et le curseur du fichier pointe maintenant sur la 1re ligne de données.
    std::getline(file, line);

    // une itération = une ligne = une Bar.
    //getline renvoie le flux, converti en bool : faux quand on atteint la fin
    while (std::getline(file, line)) {
        if (line.empty()) continue;              // ligne vide

        std::stringstream ss(line);  // la ligne est découpée en morceaux par le flux ss
        std::string field;           // on recoit chaque morceau un par un
        Bar b;                       // on va remplir cette Bar avec les morceaux

        std::getline(ss, field, ',');  b.date   = field;
        std::getline(ss, field, ',');  b.open   = std::stod(field);
        std::getline(ss, field, ',');  b.high   = std::stod(field);
        std::getline(ss, field, ',');  b.low    = std::stod(field);
        std::getline(ss, field, ',');  b.close  = std::stod(field);
        std::getline(ss, field, ',');  b.volume = std::stod(field);

        bars.push_back(b);  // copie b dans le vecteur
    }

    return bars;
}
