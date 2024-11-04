#include <opencv2/opencv.hpp>
#include <iostream>
#include <thread> 
#include <chrono>
#include "color.h"

int main() {
    // Load an image
    cv::Mat image = cv::imread("image.jpg", cv::IMREAD_COLOR); // Loads an image in BGR format
    
    // Check if the image was loaded successfully
    if (image.empty()) {
        std::cerr << "Error: Could not open or find the image!" << std::endl;
        return -1;
    }

    // Get the image dimensions
    int rows = image.rows;
    int cols = image.cols;

    Color black = Color(0, 0, 0);
    Color red = Color(255, 0, 0);

    // Iterate through the image and get the pixel values
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            // Access the pixel at (i, j)
            cv::Vec3b pixel = image.at<cv::Vec3b>(i, j); // Vec3b stores BGR values

            pixel[0] = red.blue; 
            pixel[1] = red.green; 
            pixel[2] = red.red; 

            image.at<cv::Vec3b>(i, j) = pixel;

            // Print out the BGR values
            std::cout << "Pixel at (" << i << ", " << j << ") - "
                      << "B: " << static_cast<int>(pixel[0]) << ", "
                      << "G: " << static_cast<int>(pixel[1]) << ", "
                      << "R: " << static_cast<int>(pixel[2]) << std::endl;

            // std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    cv::imshow("Manipulated Image", image);
    cv::waitKey(0);

    std::string outputPath = "output_image.jpg";
    bool isSaved = cv::imwrite(outputPath, image); // Save the image as a JPEG

    // Check if the image was saved successfully
    if (isSaved) {
        std::cout << "Image successfully saved to " << outputPath << std::endl;
    } else {
        std::cerr << "Error: Could not save the image!" << std::endl;
    }

    return 0;
}
