#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

#define STEP 5
#define JITTER 3
#define RAIO 3

int top_slider = 10;
int top_slider_max = 200;

char TrackbarName[50];

cv::Mat image, border, points;

void on_trackbar_canny(int, void*) {
    cv::Canny(image, border, top_slider, 3 * top_slider);
    cv::imshow("Canny", border);

    points = cv::Mat(image.rows, image.cols, CV_8U, cv::Scalar(255));

    // Desenho de círculos na imagem pontilhista
    for (int i = 0; i < image.rows; i += STEP) {
        for (int j = 0; j < image.cols; j += STEP) {
            int x = i + std::rand() % (2 * JITTER) - JITTER + 1;
            int y = j + std::rand() % (2 * JITTER) - JITTER + 1;
            int gray = image.at<uchar>(x, y);
            cv::circle(points, cv::Point(y, x), RAIO, CV_RGB(gray, gray, gray),
                       cv::FILLED, cv::LINE_AA);
        }
    }

    // Desenho de círuclos a partir de Canny
    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            if (border.at<uchar>(i, j) > 0) {
                int gray = image.at<uchar>(i, j);
                cv::circle(points, cv::Point(j, i), RAIO, CV_RGB(gray, gray, gray),
                           cv::FILLED, cv::LINE_AA);
            }
        }
    }

    // Aumenta os limiares do algoritmo de Canny
    for (int thresh = top_slider + 10; thresh <= top_slider_max; thresh += 10) {
        cv::Canny(image, border, thresh, 3 * thresh);

        for (int i = 0; i < image.rows; i++) {
            for (int j = 0; j < image.cols; j++) {
                if (border.at<uchar>(i, j) > 0) {
                    int gray = image.at<uchar>(i, j);
                    cv::circle(points, cv::Point(j, i), RAIO / 2, CV_RGB(gray, gray, gray),
                               cv::FILLED, cv::LINE_AA);
                }
            }
        }
    }

    cv::imshow("Pontilhismo", points);
}

int main(int argc, char** argv) {
    image = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);

    sprintf(TrackbarName, "Threshold inferior", top_slider_max);

    cv::namedWindow("Canny", 1);
    cv::createTrackbar(TrackbarName, "Canny",
                       &top_slider,
                       top_slider_max,
                       on_trackbar_canny);

    on_trackbar_canny(top_slider, 0);

    cv::waitKey();
    cv::imwrite("cannyborders.png", border);
    cv::imwrite("pontos.jpg", points);

    return 0;
}

