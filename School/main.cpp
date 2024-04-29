#include <iostream>
#include "c_bmp.h"
#include "c_steganographe.h"
#include "bmpdef.h"

int main() {
    c_steganographe steganographe;
    
    std::cout << "Tentative de chargement de l'image..." << std::endl;
    if (steganographe.chargerimage("/Users/esw13/Documents/F13/Obsidian Vault/School/output.bmp")) {
        std::cout << "Image chargée avec succès." << std::endl;
        
        std::cout << "Affichage du nombre de pixels dans l'image..." << std::endl;
        std::cout << "Nombre de pixels dans l'image : " << steganographe.getNombreDePixels() << std::endl;

        std::cout << "Demande à l'utilisateur de choisir la méthode de stéganographie..." << std::endl;
        steganographe.choisirMethodeSteganographie();

        std::cout << "Tentative de sauvegarde de l'image encodée..." << std::endl;
        if (steganographe.sauverimageSous("output.bmp")) {
            std::cout << "Image encodée sauvegardée avec succès sous output.bmp." << std::endl;

            std::cout << "Tentative de décodage du message..." << std::endl;
            std::string decodedMessage = steganographe.LireOctetsBourrage().empty() ? steganographe.LireRGB() : steganographe.LireOctetsBourrage();
            std::cout << "Message extrait : " << decodedMessage << std::endl;
        } else {
            std::cerr << "Erreur lors de la sauvegarde de l'image encodée." << std::endl;
        }
    } else {
        std::cerr << "Erreur lors du chargement de l'image." << std::endl;
    }

    return 0;
}
