
#include "c_steganographe.h"
#include <bitset>
#include "bmpdef.h"
#include "c_bmp.h"

// Définition des membres de la classe c_steganographe
c_steganographe::c_steganographe() {
    // Initialisation des membres
    m_pixels.clear();
    m_octetsBourrage.clear();
}
void c_steganographe::choisirMethodeSteganographie() {
    int choix;
    std::cout << "Choisissez l'opération à effectuer : \n";
    std::cout << "1. Cacher le message avec les pixels\n";
    std::cout << "2. Cacher le message avec les octets de bourrage\n";
    std::cout << "3. Lire le message caché dans les pixels\n";
    std::cout << "4. Lire le message caché dans les octets de bourrage\n";
    std::cout << "Votre choix : ";

    while (!(std::cin >> choix) || choix < 1 || choix > 4) {
        std::cout << "Veuillez saisir une option valide (1 à 4) : ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (choix == 1) {
        std::string messageToHide;
        std::cout << "Entrez le message à cacher avec les pixels : ";
        std::getline(std::cin, messageToHide);
        EcrireRGB(messageToHide);
    } else if (choix == 2) {
        std::string messageToHide;
        std::cout << "Entrez le message à cacher avec les octets de bourrage : ";
        std::getline(std::cin, messageToHide);
        EcrireOctetsBourrage(messageToHide);
    } else if (choix == 3) {
        std::string decodedMessage = LireRGB();
        std::cout << "Message extrait des pixels : " << decodedMessage << std::endl;
    } else if (choix == 4) {
        std::string decodedMessage = LireOctetsBourrage();
        std::cout << "Message extrait des octets de bourrage : " << decodedMessage << std::endl;
    }
}

// Implémentation de getNombrePixels

// Dans c_steganographe.cpp
size_t c_steganographe::getNombreDePixels() const {
    return m_c_bmp.getPixels().size();
}

size_t c_steganographe::getNombrePixels() const {
    return m_pixels.size();
}

bool c_steganographe::EcrireRGB(const std::string& message) {
    std::string bits;
    for (char c : message) {
        std::bitset<8> charBits(c);
        bits += charBits.to_string();
    }

    if (bits.length() > m_pixels.size()) {
        std::cerr << "Message trop long pour être caché dans l'image." << std::endl;
        return false;
    }

    for (size_t i = 0; i < bits.length(); ++i) {
        unsigned char& bleu = m_pixels[i].m_bleu;
        bleu = (bleu & 0xFE) | (bits[i] == '1' ? 1 : 0);
    }

    return true;
}



bool c_steganographe::EcrireOctetsBourrage(const std::string& message) {
    std::string bits;
    for (char c : message) {
        std::bitset<8> charBits(c);
        bits += charBits.to_string();
    }

    if (bits.length() > m_octetsBourrage.size() * 8) {
        std::cerr << "Message trop long pour être caché dans les octets de bourrage." << std::endl;
        return false;
    }

    for (size_t i = 0; i < bits.length(); i++) {
        m_octetsBourrage[i / 8] = (m_octetsBourrage[i / 8] & 0xFE) | (bits[i] == '1' ? 1 : 0);
    }

    return true;
}


bool c_steganographe::chargerimage(const std::string& nomFichier) {
    int chargementResultat = m_c_bmp.chargerFichier(nomFichier);
    if (chargementResultat == 1) { // Si le chargement est un succès, on met à jour les pixels.
        m_pixels = m_c_bmp.getPixels();
        return true;
    } else {
        std::cerr << "Échec du chargement de l'image. Code d'erreur: " << chargementResultat << std::endl;
        return false;
    }
}


bool c_steganographe::sauverimageSous(const std::string& nomFichier) {
    // Mettez à jour les pixels dans la classe c_bmp
    m_c_bmp.setPixels(m_pixels);

    // Utilisez la classe c_bmp pour sauvegarder l'image sous un nouveau nom
    return m_c_bmp.sauverFichierSous(nomFichier);
}

bool c_steganographe::sauverimage() {
    // Mettez à jour les pixels dans la classe c_bmp
    m_c_bmp.setPixels(m_pixels);

    // Utilisez la classe c_bmp pour sauvegarder l'image avec le nom de fichier actuel
    return m_c_bmp.sauverFichier();
}
std::string c_steganographe::LireOctetsBourrage() {
    std::string bits;
    for (auto& octet : m_octetsBourrage) {
        bits.push_back((octet & 0x01) + '0');
    }

    return convertBitsToText(bits);
}



std::string c_steganographe::LireRGB() {
    std::string bits;
    for (auto& pixel : m_pixels) {
        bits.push_back((pixel.m_bleu & 0x01) + '0');
    }

    return convertBitsToText(bits);
}

std::string c_steganographe::convertBitsToText(const std::string& bits) {
    std::string text;
    for (size_t i = 0; i < bits.size(); i += 8) {
        std::bitset<8> byte(bits.substr(i, 8));
        text.push_back(static_cast<char>(byte.to_ulong()));
    }
    return text;
}
