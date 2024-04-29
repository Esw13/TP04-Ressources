#include <iostream>
#include <fstream>
#include <string>
#include <opencv2/opencv.hpp>

// Utilisation d'OpenCV pour la manipulation d'image

std::string pixelToChar(unsigned char pixel, const std::string &chars) {
    // Échelle de 0 à 255 divisée par le nombre de caractères disponibles
    size_t index = static_cast<size_t>((pixel / 255.0) * (chars.size() - 1));
    return std::string(1, chars[index]);
}

int main() {
    cv::Mat image = cv::imread("/Users/esw13/Documents/F13/Obsidian Vault/art/jerem.jpeg", cv::IMREAD_GRAYSCALE);
    if (image.empty()) {
        std::cerr << "Image not found or unable to open" << std::endl;
        return -1;
    }

    std::string chars = "@%#*+=-:. ";
    std::ofstream outFile("ascii_art1.txt");
    std::string asciiArt;

    // Réduire l'image pour qu'elle corresponde à un rendu en ASCII
    cv::Mat resized;
    int newWidth = 100; // Largeur souhaitée
    cv::resize(image, resized, cv::Size(newWidth, image.rows * newWidth / image.cols / 2));

    for (int i = 0; i < resized.rows; ++i) {
        for (int j = 0; j < resized.cols; ++j) {
            unsigned char pixel = resized.at<unsigned char>(i, j);
            asciiArt += pixelToChar(pixel, chars);
        }
        asciiArt += '\n';
    }

    outFile << asciiArt;
    outFile.close();

    std::cout << "ASCII Art saved to ascii_art.txt" << std::endl;
    return 0;
}
