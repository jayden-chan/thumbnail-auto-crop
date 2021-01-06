#include <cstdlib>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/opencv.hpp>
#include <stdio.h>

using namespace std;

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("usage: DisplayImage.out <Image_Path>\n");
        return EXIT_FAILURE;
    }

    auto image = cv::imread(argv[1], 1);
    if (!image.data) {
        printf("No image data \n");
        return EXIT_FAILURE;
    }

    if (image.cols / image.rows > (16 / 9)) {
        fprintf(stderr, "Image is wider than 16:9, can't crop this because I "
                        "didn't write the code to do that");
        return EXIT_FAILURE;
    }

    auto face_cascade =
        cv::CascadeClassifier("haarcascade_frontalface_default.xml");

    auto gray = cv::Mat();
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

    vector<cv::Rect> faces;
    face_cascade.detectMultiScale(gray, faces, 1.3, 5);

    auto centerY = 0.0;

    /* debug -- draw boxes around the faces */
    for (size_t i = 0; i < faces.size(); i++) {
        centerY += faces[i].y + ((double)faces[i].height / 2);
        cv::rectangle(image, faces[i], cv::Scalar(0, 255, 0), 3);
    }

    centerY /= faces.size();

    /* debug -- draw line at center Y coord */
    cv::line(image, cv::Point(0, centerY), cv::Point(image.cols, centerY),
             cv::Scalar(255, 0, 0));

    auto crop_width = image.cols;
    auto crop_height = image.cols * (9.0 / 16.0);
    double crop_y;

    if (centerY + crop_height / 2 > image.rows) {
        crop_y = image.rows - crop_height;
    } else if (centerY - crop_height / 2 < 0) {
        crop_y = 0;
    } else {
        crop_y = centerY - crop_height / 2;
    }

    auto crop_area = cv::Rect(0, crop_y, crop_width, crop_height);
    cv::rectangle(image, crop_area, cv::Scalar(255, 0, 255));
    cv::imwrite("output.png", image(crop_area));

    return EXIT_SUCCESS;
}
