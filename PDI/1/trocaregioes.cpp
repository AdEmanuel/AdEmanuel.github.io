#include <iostream>
#include <opencv2/opencv.hpp>

int main(int, char**){
  cv::Mat image;
  cv::Vec3b aux;
  
  image= cv::imread("Lena.png",cv::IMREAD_COLOR);
  if(!image.data)
    std::cout << "nao abriu imagem.png" << std::endl;

  cv::namedWindow("janela", cv::WINDOW_AUTOSIZE);

  for (int i = 0; i < image.rows/2; i++) {
    for (int j = 0; j < image.cols/2; j++) {
      aux = image.at<cv::Vec3b>(i,j);
      image.at<cv::Vec3b>(i,j) = image.at<cv::Vec3b>(i+image.rows/2,j+image.cols/2);
      image.at<cv::Vec3b>(i+image.rows/2,j+image.cols/2) = aux;

      aux = image.at<cv::Vec3b>(i+image.rows/2,j);
      image.at<cv::Vec3b>(i+image.rows/2,j) = image.at<cv::Vec3b>(i,j+image.cols/2);
      image.at<cv::Vec3b>(i,j+image.cols/2) = aux;
	}
  }
  
  cv::imshow("janela", image);  
  cv::waitKey();
  
  cv::imwrite("Lena_trocaregioes.png", image);
  
  return 0;
}
