// c_bmp.h
#pragma once

#include <iostream>
#include <string>
#include "bmpdef.h"  // Inclusion du fichier de définition des structures

class c_bmp {
private:
    std::string m_nomFichier;
    enteteFichier m_headFile;
    entetelmage m_headImage;
    //pixel m_Image*
    std::vector<pixel> m_pixels;  // Vecteur pour stocker les pixels de l'image


public:
    c_bmp();
    c_bmp(const std::string& nomFichier);

    int chargerFichier(const std::string& nomFichier);
    bool sauverFichier();
    bool sauverFichierSous(const std::string& nomFichier);
    int getHeadFile();
    entetelmage getHeadImage();
    void getimage(const char* donnees, int taille);
    void getimage(const char* pl, int taillePixel);
    int setheadFile(enteteFichier& entete);
    int setHeadlmage(entetelmage& entete);
    bool setimage(const char*** donnees, int taille);
    bool setimage(const char* pl, int taillePixel);
};

