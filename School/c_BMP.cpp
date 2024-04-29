#include <iostream>
#include "c_bmp.h"
#include "bmpdef.h"
#include <fstream>
#include <vector>



// Définition des constructeurs
enteteFichier::enteteFichier()
    : m_taille(0), m_reserve1(0), m_reserve2(0), m_offset(0) {
    m_nbMagique[0] = 'B';  // Habituellement, les fichiers BMP commencent par "BM"
    m_nbMagique[1] = 'M';
}

entetelmage::entetelmage() 
    : m_tailleEntete(40), m_largeur(0), m_hauteur(0), m_planes(1),
      m_resolution(0), m_compression(0), m_tailleImage(0),
      m_horizontal(0), m_vertical(0), m_nbCouleurs(0), m_nbCouleursImp(0) {}

c_bmp::c_bmp() : m_nomFichier("default.bmp"), m_headFile(), m_headImage(), m_pixels() {}

c_bmp::c_bmp(const std::string& nomFichier) : m_nomFichier(nomFichier) {
    if (chargerFichier(nomFichier) == 0) {
        std::cerr << "Échec du chargement du fichier : " << nomFichier << std::endl;
    }
}

int c_bmp::chargerFichier(const std::string& nomFichier) {
    std::ifstream fichier(nomFichier, std::ios::binary);
    if (!fichier.is_open()) {
        std::cerr << "Impossible d'ouvrir le fichier " << nomFichier << std::endl;
        return 0;
    }

    fichier.read(reinterpret_cast<char*>(&m_headFile), sizeof(enteteFichier));
    if (fichier.fail()) {
        std::cerr << "Erreur lors de la lecture de l'en-tête du fichier." << std::endl;
        return 0;
    }

    fichier.read(reinterpret_cast<char*>(&m_headImage), sizeof(entetelmage));
    if (fichier.fail()) {
        std::cerr << "Erreur lors de la lecture de l'en-tête de l'image." << std::endl;
        return 0;
    }

    fichier.seekg(m_headFile.m_offset, std::ios::beg);
    size_t tailleEnPixels = m_headImage.m_largeur * m_headImage.m_hauteur;
    m_pixels.resize(tailleEnPixels);
    size_t largeurReelle = m_headImage.m_largeur * sizeof(Pixel);
    size_t bourrage = (4 - (largeurReelle % 4)) % 4;

    for (size_t ligne = 0; ligne < m_headImage.m_hauteur; ++ligne) {
        fichier.read(reinterpret_cast<char*>(&m_pixels[ligne * m_headImage.m_largeur]), largeurReelle);
        fichier.ignore(bourrage);
        if (fichier.fail()) {
            std::cerr << "Erreur lors de la lecture des données des pixels à la ligne " << ligne << "." << std::endl;
            return 0;
        }
    }

    std::cout << "Le fichier a été complètement chargé sans erreurs." << std::endl;
    return 1;
}



bool c_bmp::sauverFichierSous(const std::string& nomFichier) {
    std::ofstream fichier(nomFichier, std::ios::binary | std::ios::trunc);

    if (!fichier.is_open()) {
        std::cerr << "Impossible d'ouvrir le fichier " << nomFichier << " pour écriture." << std::endl;
        return false;
    }

    m_nomFichier = nomFichier;

    fichier.write(reinterpret_cast<char*>(&m_headFile), sizeof(enteteFichier));
    fichier.write(reinterpret_cast<char*>(&m_headImage), sizeof(entetelmage));

    size_t largeurReelle = m_headImage.m_largeur * sizeof(Pixel);
    size_t bourrage = (4 - (largeurReelle % 4)) % 4;

    for (size_t ligne = 0; ligne < m_headImage.m_hauteur; ++ligne) {
        fichier.write(reinterpret_cast<const char*>(&m_pixels[ligne * m_headImage.m_largeur]), largeurReelle);
        if (bourrage > 0) {
            const char padding[4] = {0, 0, 0, 0};
            fichier.write(padding, bourrage);
        }
    }

    fichier.close();
    std::cout << "L'image a été sauvegardée sous un autre nom avec succès." << std::endl;
    return true;
}


int c_bmp::getHeadFile() {
    return m_headImage.m_largeur; 
}

entetelmage c_bmp::getHeadImage() {
    return m_headImage;
}



int c_bmp::setheadFile(enteteFichier& entete) {
    m_headFile.m_nbMagique[0] = entete.m_nbMagique[0];
    m_headFile.m_nbMagique[1] = entete.m_nbMagique[1];
    m_headFile.m_taille = entete.m_taille;
    m_headFile.m_reserve1 = entete.m_reserve1; // Mise à jour pour m_reserve1
    m_headFile.m_reserve2 = entete.m_reserve2; // Mise à jour pour m_reserve2
    m_headFile.m_offset = entete.m_offset;

    return 1;
}

int c_bmp::setHeadlmage(entetelmage& entete) {
    m_headImage.m_tailleEntete = entete.m_tailleEntete;
    m_headImage.m_largeur = entete.m_largeur;
    m_headImage.m_hauteur = entete.m_hauteur;
    m_headImage.m_planes = entete.m_planes; // Mise à jour pour m_planes
    m_headImage.m_resolution = entete.m_resolution;
    m_headImage.m_compression = entete.m_compression;
    m_headImage.m_tailleImage = entete.m_tailleImage;
    m_headImage.m_horizontal = entete.m_horizontal;
    m_headImage.m_vertical = entete.m_vertical;
    m_headImage.m_nbCouleurs = entete.m_nbCouleurs;
    m_headImage.m_nbCouleursImp = entete.m_nbCouleursImp;

    return 1;
}

void c_bmp::getimage(const char* donnees, int taille) {
    if (taille != m_headImage.m_largeur * m_headImage.m_hauteur * sizeof(Pixel)) {
        std::cerr << "Taille incorrecte pour les données de l'image." << std::endl;
        return;
    }

    std::memcpy(m_pixels.data(), donnees, taille);

    std::cout << "Données de l'image copiées avec succès." << std::endl;
}


void c_bmp::getimage(const Pixel* pl, int taillePixel) {
    if (taillePixel != m_headImage.m_largeur * m_headImage.m_hauteur) {
        std::cerr << "Taille incorrecte pour les pixels de l'image." << std::endl;
        return;
    }

    std::memcpy(m_pixels.data(), pl, taillePixel * sizeof(Pixel));

    std::cout << "Pixels de l'image copiés avec succès." << std::endl;
}

bool c_bmp::setimage(const char* donnees, int taille) {
    if (taille != m_headImage.m_largeur * m_headImage.m_hauteur * sizeof(Pixel)) {
        std::cerr << "Taille incorrecte pour les données de l'image." << std::endl;
        return false;  // Arrête l'exécution si la taille est incorrecte
    }

    std::memcpy(m_pixels.data(), donnees, taille);
    std::cout << "Données de l'image copiées avec succès." << std::endl;
    return true;
}
bool c_bmp::setimage(const Pixel* pl, int taillePixel) {
    if (taillePixel != m_headImage.m_largeur * m_headImage.m_hauteur) {
        std::cerr << "Taille incorrecte pour les pixels de l'image." << std::endl;
        return false;  // Arrête l'exécution si la taille est incorrecte
    }

    std::memcpy(m_pixels.data(), pl, taillePixel * sizeof(Pixel));
    std::cout << "Pixels de l'image copiés avec succès." << std::endl;
    return true;
}

std::vector<Pixel> c_bmp::getPixels() const {
    return m_pixels;
}
void c_bmp::setPixels(const std::vector<Pixel>& pixels) {
    m_pixels = pixels;
}
void c_bmp::setOctetsBourrage(const std::vector<char>& octetsBourrage) {
    m_octetsBourrage = octetsBourrage;
}
bool c_bmp::sauverFichier() {
    return sauverFichierSous(m_nomFichier);
}
