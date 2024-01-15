#pragma once
#include "bmpdef.h"
#include <fstream>

// bmpdef.h
#pragma once

struct pixel {
    unsigned char m_rouge;
    unsigned char m_vert;
    unsigned char m_bleu;
    // Autres membres si nécessaire
};

struct enteteFichier {
    unsigned char m_nbMagique;
    unsigned int m_taille;
    unsigned int m_reserve;
    unsigned int m_offset;
    // Autres membres si nécessaire
};

struct entetelmage {
    unsigned int m_tailleEntete;
    unsigned int m_largeur;
    unsigned int m_hauteur;
    unsigned int m_margeur;
    unsigned short m_minbPlans;
    unsigned short m_resolution;
    unsigned int m_compression;
    unsigned int m_tailleImage;
    unsigned int m_horizontal;
    unsigned int m_vertical;
    unsigned int m_nbCouleurs;
    unsigned int m_nbCouleursImp;
    // Autres membres si nécessaire
};


