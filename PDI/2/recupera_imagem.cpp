#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char**argv) {
  cv::Mat imagemEscondida, imagemFinal;
  cv::Vec3b valEscondida, valFinal;
  int nbits = 5;

  imagemFinal = cv::imread(argv[1], cv::IMREAD_COLOR);
  
   if (imagemFinal.empty()) {
    std::cout << "imagem nao carregou corretamente" << std::endl;
    return (-1);
  }

  const char* arg2 = argv[2];
  std::string nome_imagem = arg2;
  nome_imagem += ".png";
  
  imagemEscondida = imagemFinal.clone();
  
  for (int i = 0; i < imagemFinal.rows; i++) {
    for (int j = 0; j < imagemFinal.cols; j++) {

	  valFinal = imagemFinal.at<cv::Vec3b>(i, j);
	  
      valEscondida[0] = valFinal[0] << nbits;
      valEscondida[1] = valFinal[1] << nbits;
      valEscondida[2] = valFinal[2] << nbits;
	  
      imagemEscondida.at<cv::Vec3b>(i, j) = valEscondida;
	  
    }
  }

  imwrite(nome_imagem, imagemEscondida);

  return 0;
}
