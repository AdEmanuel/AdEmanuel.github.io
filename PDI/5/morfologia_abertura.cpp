#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char** argv) {
    cv::Mat image, abertura;
    cv::Mat str;

    if (argc != 2) {
        std::cout << "morfologia entrada saida\n";
        return -1;
    }

    image = cv::imread(argv[1], cv::IMREAD_UNCHANGED);

    if (image.empty()) {
        std::cout << "Erro ao carregar a imagem: " << argv[1] << std::endl;
        return -1;
    }

    str = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 12));

    cv::morphologyEx(image, abertura, cv::MORPH_OPEN, str);

    cv::Mat matArray[] = {image, abertura};
    cv::hconcat(matArray, 2, image);

    cv::imwrite("079.png", image);

    cv::waitKey();
    return 0;
}

