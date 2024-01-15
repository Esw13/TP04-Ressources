
#include "c_bmp.h"

// Définition des constructeurs
enteteFichier::enteteFichier() :
    
     m_nbMagique(0),
    m_taille(0),
    m_reserve(0),
    m_offset(0)
    {
        
    }


c_bmp::c_bmp() : m_nomFichier("default.bmp"),  // Par exemple, un nom de fichier par défaut
    m_headFile(),  // Appelle le constructeur par défaut de enteteFichier pour initialiser ses membres
    m_headImage(),  // Appelle le constructeur par défaut de entetelmage pour initialiser ses membres
    m_pixels()  // Le vecteur de pixels est initialisé par son constructeur par défaut
{
}

c_bmp::c_bmp(const std::string& nomFichier) : m_nomFichier(nomFichier)  {
    // Vous pouvez ajouter d'autres initialisations ici si nécessaire
    if (chargerFichier(nomFichier) == 0) {
        // Gérez le cas où le chargement du fichier échoue, par exemple, lancez une exception ou affichez un message d'erreur.
        std::cerr << "Échec du chargement du fichier : " << nomFichier << std::endl;
        // Vous pouvez ajouter d'autres actions nécessaires en cas d'échec
    }
}

// Définition des méthodes de la classe c_bmp
int c_bmp::chargerFichier(const std::string& nomFichier) {
        std::ifstream fichier(nomFichier, std::ios::binary);
        
        if (!fichier.is_open()) {
            std::cerr << "Impossible d'ouvrir le fichier " << nomFichier << std::endl;
            return 0;
        }

        // Lire l'en-tête du fichier BMP
        fichier.read(reinterpret_cast<char*>(&m_headFile), sizeof(enteteFichier));

        // Lire l'en-tête de l'image BMP
        fichier.read(reinterpret_cast<char*>(&m_headImage), sizeof(entetelmage));

        // Calculer la taille en pixels
        size_t tailleEnPixels = m_headImage.m_largeur * m_headImage.m_hauteur;

        // Allouer de l'espace pour stocker les pixels
        m_pixels.resize(tailleEnPixels);

        // Lire les pixels de l'image (sans tenir compte des octets de bourrage)
        fichier.read(reinterpret_cast<char*>(m_pixels.data()), tailleEnPixels * sizeof(pixel));

        // Fermer le fichier
        fichier.close();

        return tailleEnPixels;
    }
}

bool c_bmp::sauverFichier() {
        std::ofstream fichier(m_nomFichier, std::ios::binary | std::ios::trunc);

        if (!fichier.is_open()) {
            std::cerr << "Impossible d'ouvrir le fichier " << m_nomFichier << " pour écriture." << std::endl;
            return false;
        }

        // Écrire l'en-tête du fichier BMP
        fichier.write(reinterpret_cast<char*>(&m_headFile), sizeof(enteteFichier));

        // Écrire l'en-tête de l'image BMP
        fichier.write(reinterpret_cast<char*>(&m_headImage), sizeof(entetelmage));

        // Écrire les pixels de l'image
        fichier.write(reinterpret_cast<char*>(m_pixels.data()), m_pixels.size() * sizeof(pixel));

        // Fermer le fichier
        fichier.close();

        std::cout << "L'image a été sauvegardée avec succès." << std::endl;

        return true;
    }

}
bool c_bmp::sauverFichierSous(const std::string& nomFichier) {
        std::ofstream fichier(nouveauNomFichier, std::ios::binary | std::ios::trunc);

        if (!fichier.is_open()) {
            std::cerr << "Impossible d'ouvrir le fichier " << nouveauNomFichier << " pour écriture." << std::endl;
            return false;
        }

        // Mettre à jour le nom du fichier dans l'objet c_bmp
        m_nomFichier = nouveauNomFichier;

        // Écrire l'en-tête du fichier BMP
        fichier.write(reinterpret_cast<char*>(&m_headFile), sizeof(enteteFichier));

        // Écrire l'en-tête de l'image BMP
        fichier.write(reinterpret_cast<char*>(&m_headImage), sizeof(entetelmage));

        // Calculer la largeur réelle en octets d'une ligne de pixels, en prenant en compte les octets de bourrage
        size_t largeurReelle = m_headImage.m_largeur * sizeof(pixel);
        size_t bourrage = 4 - (largeurReelle % 4);
        if (bourrage == 4) {
            bourrage = 0;
        }

        // Écrire les pixels de l'image avec les octets de bourrage
        for (size_t ligne = 0; ligne < m_headImage.m_hauteur; ++ligne) {
            fichier.write(reinterpret_cast<char*>(&m_pixels[ligne * m_headImage.m_largeur]), largeurReelle);
            // Ajouter les octets de bourrage
            fichier.write(reinterpret_cast<char*>(new char[bourrage]), bourrage);
        }

        // Fermer le fichier
        fichier.close();

        std::cout << "L'image a été sauvegardée sous un autre nom avec succès." << std::endl;

        return true;
    }

}
int c_bmp::getHeadFile() {
    // Implémentation à ajouter
    return 0;  // Valeur de retour fictive
}

entetelmage c_bmp::getHeadImage() {
    return m_headImage;
}

void c_bmp::getimage(const char* donnees, int taille) {
    // Assurez-vous que la taille est correcte
    if (taille != m_headImage.m_largeur * m_headImage.m_hauteur * sizeof(pixel)) {
        std::cerr << "Taille incorrecte pour les données de l'image." << std::endl;
        return;
    }

    // Copiez les données dans le vecteur m_pixels
    std::memcpy(m_pixels.data(), donnees, taille);

    std::cout << "Données de l'image copiées avec succès." << std::endl;
}

void c_bmp::getimage(const char* pl, int taillePixel){
    // Assurez-vous que la taille est correcte
    if (taillePixel != m_headImage.m_largeur * m_headImage.m_hauteur) {
        std::cerr << "Taille incorrecte pour les pixels de l'image." << std::endl;
        return;
    }

    // Copiez les pixels bruts dans le vecteur m_pixels
    std::memcpy(m_pixels.data(), pl, taillePixel * sizeof(pixel));

    std::cout << "Pixels de l'image copiés avec succès." << std::endl;
}

int c_bmp::setheadFile(enteteFichier& entete) int c_bmp::setheadFile(enteteFichier& entete) {
    // Mettez à jour les membres de l'objet c_bmp avec les valeurs de l'enteteFichier
    m_headFile.m_nbMagique = entete.m_nbMagique;
    m_headFile.m_taille = entete.m_taille;
    m_headFile.m_reserve = entete.m_reserve;
    m_headFile.m_offset = entete.m_offset;

    // Vous pouvez ajouter des vérifications de validité ici si nécessaire

    // Retournez une valeur pour indiquer le succès (ou l'échec) de l'opération
    // Vous pouvez utiliser un code d'erreur spécifique ou simplement un booléen selon vos besoins
    return 1;  // Remplacez par une valeur appropriée
}


int c_bmp::setHeadlmage(entetelmage& entete) {
    // Mettez à jour les membres de l'objet c_bmp avec les valeurs de l'entetelmage
    m_headImage.m_tailleEntete = entete.m_tailleEntete;
    m_headImage.m_largeur = entete.m_largeur;
    m_headImage.m_hauteur = entete.m_hauteur;
    m_headImage.m_bPlans = entete.m_bPlans;
    m_headImage.m_resolution = entete.m_resolution;
    m_headImage._compression = entete._compression;
    m_headImage.m_taillelmage = entete.m_taillelmage;
    m_headImage.m_horizontal = entete.m_horizontal;
    m_headImage.m_vertical = entete.m_vertical;
    m_headImage.m_nbCouleurs = entete.m_nbCouleurs;
    m_headImage.m_nbCouleursimp = entete.m_nbCouleursimp;

    // Vous pouvez ajouter des vérifications de validité ici si nécessaire

    // Retournez une valeur pour indiquer le succès (ou l'échec) de l'opération
    // Vous pouvez utiliser un code d'erreur spécifique ou simplement un booléen selon vos besoins
    return 1;  // Remplacez par une valeur appropriée
}

bool c_bmp::setimage(const char*** donnees, int taille) {
    // Assurez-vous que la taille correspond à la taille attendue des données de l'image
    if (taille != m_headImage.m_largeur * m_headImage.m_hauteur * sizeof(pixel)) {
        std::cerr << "Taille incorrecte pour les données de l'image." << std::endl;
        return false;
    }

    // Copiez les données brutes dans le vecteur m_pixels
    std::memcpy(m_pixels.data(), *donnees, taille);

    std::cout << "Données de l'image copiées avec succès." << std::endl;

    return true;
}
bool c_bmp::setimage(const char* pl, int taillePixel) {
    // Assurez-vous que la taille correspond à la taille attendue des pixels de l'image
    if (taillePixel != m_headImage.m_largeur * m_headImage.m_hauteur) {
        std::cerr << "Taille incorrecte pour les pixels de l'image." << std::endl;
        return false;
    }

    // Copiez les pixels bruts dans le vecteur m_pixels
    std::memcpy(m_pixels.data(), pl, taillePixel * sizeof(pixel));

    std::cout << "Pixels de l'image copiés avec succès." << std::endl;

    return true;
}