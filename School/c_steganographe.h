#ifndef C_STEGANOGRAPHE_H
#define C_STEGANOGRAPHE_H
#include "bmpdef.h"
#include <string>
#include <vector>
#include "c_bmp.h"  
// Déclaration de la classe c_steganographe
class c_steganographe {
public:
    c_steganographe();
    void choisirMethodeSteganographie();
   // void EcrireRGB(const std::string& message);
   // void EcrireOctetsBourrage(const std::string& message);
    bool chargerimage(const std::string& nomFichier);
    bool sauverimageSous(const std::string& nomFichier);
    bool sauverimage();
    bool EcrireRGB(const std::string& message);
    bool EcrireOctetsBourrage(const std::string& message);
    std::string LireOctetsBourrage();
    std::string LireRGB();
    // Ajoutez cette déclaration dans la classe c_steganographe
    size_t getNombrePixels() const;
    size_t getNombreDePixels() const;


private:
    std::string convertBitsToText(const std::string& bits);
    std::vector<Pixel> m_pixels;  
    std::vector<char> m_octetsBourrage;
    c_bmp m_c_bmp;  
};

#endif  // C_STEGANOGRAPHE_H
