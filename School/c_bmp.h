#pragma once

#pragma pack(push, 1)

struct Pixel {
    unsigned char m_rouge;
    unsigned char m_vert;
    unsigned char m_bleu;   
};

struct enteteFichier {
    unsigned char m_nbMagique[2]; // "BM"
    unsigned int m_taille;
    unsigned short m_reserve1;
    unsigned short m_reserve2;
    unsigned int m_offset;

    enteteFichier(); // Déclaration du constructeur
};

struct entetelmage {
    unsigned int m_tailleEntete;
    unsigned int m_largeur;
    unsigned int m_hauteur;
    unsigned short m_planes;
    unsigned short m_resolution;
    unsigned int m_compression;
    unsigned int m_tailleImage;
    unsigned int m_horizontal;
    unsigned int m_vertical;
    unsigned int m_nbCouleurs;
    unsigned int m_nbCouleursImp;

    entetelmage(); // Déclaration du constructeur
};

#pragma pack(pop)
