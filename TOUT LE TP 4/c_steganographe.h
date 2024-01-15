#pragma once
// c_steganographe.h
#pragma once

#include <string>
#include <fstream>

class c_steganographe {
private:
    // Membres privés de la classe

public:
    c_steganographe();
    void EcrireRGB(const std::string& message);
    void EcrireOctetsBourrage(const std::string& message);
    bool chargerimage(const std::string& nomFichier);
    bool sauverimageSous(const std::string& nomFichier);
    bool sauverimage();
    std::string LireOctetsBourrage();
    std::string LireRGB();
    // Autres méthodes et membres publics
};
