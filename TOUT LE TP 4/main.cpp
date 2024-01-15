
#include <iostream>
#include "c_bmp.h"
#include "c_steganographe.h"

int main() {
    // Chargement de l'image
    c_steganographe steganographe;
    if (steganographe.chargerimage("input.bmp")) {
        std::cout << "Image chargée avec succès." << std::endl;

        // Message à cacher
        std::string messageToHide = "Hello, world!";

        // Encodage du message
        steganographe.EcrireRGB(messageToHide);

        // Sauvegarde de l'image encodée
        if (steganographe.sauverimageSous("output.bmp")) {
            std::cout << "Image encodée sauvegardée avec succès." << std::endl;

            // Décode le message
            std::string decodedMessage = steganographe.LireRGB();
            std::cout << "Message extrait : " << decodedMessage << std::endl;
        } else {
            std::cerr << "Erreur lors de la sauvegarde de l'image encodée." << std::endl;
        }
    } else {
        std::cerr << "Erreur lors du chargement de l'image." << std::endl;
    }

    return 0;
}
