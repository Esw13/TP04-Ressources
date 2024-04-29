#ifndef BMPDEF_H
#define BMPDEF_H



#include <iostream>
#include <string>
#include <vector>
#include "bmpdef.h"  
#include "c_bmp.h"

class c_bmp {
private:
    std::string m_nomFichier;
    enteteFichier m_headFile;
    entetelmage m_headImage;
    std::vector<Pixel> m_pixels;
    std::vector<char> m_octetsBourrage;

public:
    c_bmp();
    c_bmp(const std::string& nomFichier);
    void setOctetsBourrage(const std::vector<char>& octetsBourrage);
    std::vector<Pixel> getPixels() const;
    void setPixels(const std::vector<Pixel>& pixels);
    int chargerFichier(const std::string& nomFichier);
    bool sauverFichier();
    bool sauverFichierSous(const std::string& nomFichier);
    int getHeadFile();
    entetelmage getHeadImage();
    int setheadFile(enteteFichier& entete);
    int setHeadlmage(entetelmage& entete);
    void getimage(const char* donnees, int taille);
    void getimage(const Pixel* pl, int taillePixel);
    bool setimage(const char* donnees, int taille);
    bool setimage(const Pixel* pl, int taillePixel);
    
   
};

#endif // BMPDEF_H