
#include "c_steganographe.h"

// Définition des membres de la classe c_steganographe
c_steganographe::c_steganographe() {
    // Initialisation des membres
    m_pixels.clear();
    m_octetsBourrage.clear();
}
void c_steganographe::EcrireRGB(const std::string& message){
    size_t messageIndex = 0;

    // Parcourez chaque pixel de l'image
    for (size_t i = 0; i < m_pixels.size(); ++i) {
        // Récupérez les composantes RGB du pixel
        unsigned char& rouge = m_pixels[i].m_rouge;
        unsigned char& vert = m_pixels[i].m_vert;
        unsigned char& bleu = m_pixels[i].m_bleu;

        // Vérifiez si le message n'a pas encore été entièrement codé
        if (messageIndex < message.size()) {
            // Récupérez le bit à cacher dans le message
            char bitMessage = message[messageIndex++] - '0';

            // Modifiez la composante bleue en fonction du bit à cacher
            if (bitMessage == 0) {
                // Si le bit à cacher vaut 0, assurez-vous que la composante bleue se termine par 0
                bleu &= 0xFE;  // Effacez le bit de poids faible
            } else {
                // Si le bit à cacher vaut 1, assurez-vous que la composante bleue se termine par 1
                bleu |= 0x01;  // Ajoutez le bit de poids faible
            }
        }
    }
}


void c_steganographe::EcrireOctetsBourrage(const std::string& message) {
    // Obtenez une copie des octets de bourrage de l'image
    std::vector<char> octetsBourrageCopie(m_octetsBourrage);

    // Convertissez le message en une séquence de bits
    std::bitset<8> bitsetMessage;
    for (size_t i = 0; i < message.size(); ++i) {
        bitsetMessage = message[i];
        
        // Modifiez les bits de l'octet de bourrage avec les bits du message
        for (size_t j = 0; j < 8; ++j) {
            // Effacez le bit de l'octet de bourrage
            octetsBourrageCopie[i * 8 + j] &= 0xFE;
            // Ajoutez le bit du message à l'octet de bourrage
            octetsBourrageCopie[i * 8 + j] |= bitsetMessage[j];
        }
    }

    // Mettez à jour les octets de bourrage dans l'objet c_bmp
    m_c_bmp.setOctetsBourrage(octetsBourrageCopie);
}


bool c_steganographe::chargerimage(const std::string& nomFichier) {
    // Utilisez la classe c_bmp pour charger l'image
    if (m_c_bmp.chargerFichier(nomFichier) > 0) {
        // L'image a été chargée avec succès, mettez à jour les pixels
        m_pixels = m_c_bmp.getPixels();
        return true;
    }

    return false;
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
    std::string message;  // Initialisez la chaîne de caractères pour stocker le message lu

    // Parcourez les octets de bourrage et extrayez les bits les moins significatifs
    for (char octet : m_octetsBourrage) {
        // Récupérez les bits les moins significatifs
        char bitsMessage = octet & 0x01;
        // Ajoutez le bit au message
        message.push_back(bitsMessage);
    }

    return message;
}

std::string c_steganographe::LireRGB()  {
    std::string message;  // Initialisez la chaîne de caractères pour stocker le message lu

    // Parcourez chaque pixel de l'image
    for (size_t i = 0; i < m_pixels.size(); ++i) {
        // Récupérez la composante bleue du pixel
        unsigned char bleu = m_pixels[i].m_bleu;

        // Ajoutez le bit de poids faible de la composante bleue au message
        message.push_back((bleu & 0x01) + '0');
    }

    return message;
}