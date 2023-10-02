#include <iostream>
#include <opencv2/opencv.hpp>

int main(int, char**){
  cv::Mat image;
  cv::Vec3b val;

  image= cv::imread("biel.png",cv::IMREAD_COLOR);
  if(!image.data)
    std::cout << "A imagem não foi aberta" << std::endl;
  
  int cols, rows, x1, x2, y1 ,y2;
  
  cols = image.cols;
  rows = image.rows;

  std::cout << "O tamanho da imagem, em pixels, que será editada é: " << cols << "x" << rows << std::endl;

  while (true){
    std::cout << "Dessa forma, defina, respectivamente, as coordenadas x e y dos pontos P1 e P2." << std::endl;
	std::cout << "x1 = ";
	std::cin >> x1;
	std::cout << "y1 = ";
	std::cin >> y1;
	
	// Verifique se os pontos estão dentro dos limites da imagem
    if (x1 < 0 || x1 >= cols || y1 < 0 || y1 >= rows) {
      std::cout << "Pelo menos um dos pontos está fora dos limites da imagem." << std::endl;
    } else {
      std::cout << "x2 = ";
      std::cin >> x2;
      std::cout << "y2 = ";
      std::cin >> y2;

      // Verifique se os pontos formam um retângulo válido
      if (x2 < 0 || x2 >= cols || y2 < 0 || y2 >= rows || x1 >= x2 || y1 >= y2) {
        std::cout << "Os pontos não formam um retângulo válido." << std::endl;
      } else {
        break;  // As coordenadas são válidas, saia do loop
      }
    }  
  }
  
  cv::namedWindow("janela", cv::WINDOW_AUTOSIZE);

  for(int i=x1;i<x2;i++){
    for(int j=y1;j<y2;j++){
	  val = image.at<cv::Vec3b>(i,j);

      val[0] = 255 - val[0];
      val[1] = 255 - val[1];
      val[2] = 255 - val[2];
      image.at<cv::Vec3b>(i,j)= val;
    }
  }
  
  cv::imshow("janela", image);  
  cv::waitKey();
  
  cv::imwrite("biel_negativo.png", image);
  
  return 0;
}