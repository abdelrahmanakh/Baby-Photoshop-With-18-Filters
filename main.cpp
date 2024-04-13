/*
 * FCAI – Structured Programming – 2024 - Assignment 3 - Part 1
 * Program Name: CS112_A3_Part1_S3_S4_20230593_20230587_20230794.cpp
 * Program Description: Image Filter Program
 * Last Modification Date: 27/03/2024
 * Authors: Abdelrahman Ahmed Samir Mohamed Ali, 20230593, Group:A, Sec.no:3
 *          Saleem Sami Saleem Aljerjawi, 20230794, Group:A, Sec.no:4
 *          Mazen Mohamed Abdelsalam Ali Elsheikh, 20230587, Group:A, Sec.no:4
 * TA:      Ahmed Foad Lotfy
 * Who did what: Mazen: The Menu of the previous delivery & Print function & Grayscale Filter & Lighten and Darken filter & Edge detection
 *               Abdelrahman: flip  & black_and_white Filters
 *               Saleem: Invert & Rotate Filters
 * Emails:
 *        Mazen: 11410120230587@stud.cu.edu.eg
 *        Abdelrahman: 20230593@stud.fci-cu.edu.eg
 *        Saleem: 20230794@stud.fci-cu.edu.eg
*/
#include <iostream>
#include <cstdlib>
#include "Image_Class.h"
#include "vector"

using namespace std;

void printImage(Image &image, string imageName) {
    string option;
    cout << "A: Modify on the current image\n";
    cout << "B: Modify in a new image\n";
    while (true) {
        getline(cin, option);
        if (option == "A" || option == "a") {
            image.saveImage(imageName);
            cout << "The filter is applied successfully\n";
            return;
        } else if (option == "B" || option == "b") {
            while (true) {
                string newName;
                cout << "Enter the image file name of the new file\n";
                getline(cin, newName);
                try {
                    image.saveImage(newName);
                    cout << "The filter is applied successfully!\n";
                }
                catch (const invalid_argument &e) {
                    continue;
                }
                return;
            }
        } else {
            cout << "Enter a valid option\n";
            continue;
        }
    }
}

void grayscale_conversion(Image &image, string imageName, bool print) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            int value = 0.299 * image(i, j, 0) + 0.587 * image(i, j, 1) + 0.114 * image(i, j, 2);
            for (int k = 0; k < image.channels; ++k)
                image(i, j, k) = value;
        }
    }
    if (print)
        printImage(image, imageName);
}

void black_and_white(Image &image, string imageName) {
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            unsigned int avg = 0;
            for (int k = 0; k < 3; k++) {
                avg += image(i, j, k);
            }
            avg /= 3;
            if (avg >= 128)
                avg = 255;
            else
                avg = 0;
            for (int k = 0; k < 3; k++) {
                image(i, j, k) = avg;
            }
        }
    }
    printImage(image, imageName);
}

void flip_horizontally(Image &image, string imageName) {
    Image img(imageName), img2(imageName);
    for (int i = 0, x = img2.width - 1; i < img2.width; i++, x--) {
        for (int j = 0; j < img2.height; j++) {
            for (int k = 0; k < 3; k++) {
                int v = img2(x, j, k);
                img(i, j, k) = v;
            }
        }
    }
    printImage(img, imageName);
}

void flip_vertically(Image &image, string imageName) {
    Image img(imageName), img2(imageName);
    for (int i = 0; i < img2.width; i++) {
        for (int j = 0, y = img.height - 1; j < img2.height; j++, y--) {
            for (int k = 0; k < 3; k++) {
                int v = img2(i, y, k);
                img(i, j, k) = v;
            }
        }
    }
    printImage(img, imageName);
}

void flip(Image &image, string imageName) {
    cout << "Enter the type of flipping you want\n";
    cout << "A: Horizontal\n";
    cout << "B: Verticel\n";
    while (true) {
        string option;
        getline(cin, option
        );
        if (option == "A" || option == "a")
            flip_horizontally(image, imageName
            );
        else if (option == "B" || option == "b")
            flip_vertically(image, imageName
            );
        else {
            cout << "Enter a valid option\n";
            continue;
        }
        break;
    }
}

void invert_image(Image &image, string imageName) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned int inv_r = 255 - image(i, j, 0);
            unsigned int inv_g = 255 - image(i, j, 1);
            unsigned int inv_b = 255 - image(i, j, 2);

            image(i, j, 0) = inv_r;
            image(i, j, 1) = inv_g;
            image(i, j, 2) = inv_b;
        }
    }

    printImage(image, imageName);
}

void rotateImage90(Image &image, string imageName) {
    Image adjusted_img(image.height, image.width);

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {

                int new_i = j;
                int new_j = image.width - 1 - i;


                adjusted_img(new_i, new_j, k) = image(i, j, k);
            }
        }
    }
    printImage(adjusted_img, imageName);
}

void rotateImage180(Image &image, string imageName) {
    Image adjusted_img(image.width, image.height);

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {

                int new_i = image.width - 1 - i;
                int new_j = image.height - 1 - j;

                adjusted_img(new_i, new_j, k) = image(i, j, k);
            }
        }
    }
    printImage(adjusted_img, imageName);
}

void rotateImage270(Image &image, string imageName) {
    Image adjusted_img(image.height, image.width);

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {

                int new_i = image.height - 1 - j;
                int new_j = i;

                adjusted_img(new_i, new_j, k) = image(i, j, k);
            }
        }
    }
    printImage(adjusted_img, imageName);
}

void rotate(Image &image, string imageName) {
    cout << "Enter the degree of rotation you want\n";
    cout << "A: 90\n";
    cout << "B: 180\n";
    cout << "C: 270\n";
    while (true) {
        string degree;
        getline(cin, degree);
        if (degree == "A" || degree == "a")
            rotateImage90(image, imageName);
        else if (degree == "B" || degree == "b")
            rotateImage180(image, imageName);
        else if (degree == "C" || degree == "c")
            rotateImage270(image, imageName);
        else {
            cout << "Enter a valid option\n";
            continue;
        }
        break;
    }
}

void lighten_image(Image &image, string imageName) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                int newValue = 1.5 * image(i, j, k);
                newValue = min(newValue, 255);
                image(i, j, k) = newValue;
            }
        }
    }
    printImage(image, imageName);
}

void darken_image(Image &image, string imageName) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                int newValue = 0.5 * image(i, j, k);
                newValue = max(newValue, 0);
                image(i, j, k) = newValue;
            }
        }
    }
    printImage(image, imageName);
}

void edge_detection(Image &image, string imageName) {
    grayscale_conversion(image, imageName, false);
    Image modified_image(imageName);

    int dx[3][3] = {{-1, 0, 1},
                    {-2, 0, 2},
                    {-1, 0, 1}};
    int dy[3][3] = {{1,  2,  1},
                    {0,  0,  0},
                    {-1, -2, -1}};

    int threshold = 110;
    for (int i = 1; i < image.width - 1; ++i) {
        for (int j = 1; j < image.height - 1; ++j) {

            int x_value = 0;
            for (int l = 0; l < 3; ++l) {
                for (int r = 0; r < 3; ++r) {
                    x_value += dx[l][r] * image(i + r - 1, j + l - 1, 0);
                }
            }

            int y_value = 0;
            for (int l = 0; l < 3; ++l) {
                for (int r = 0; r < 3; ++r) {
                    y_value += dy[l][r] * image(i + r - 1, j + l - 1, 0);
                }
            }

            int r_value = sqrt(x_value * x_value + y_value * y_value);
            if (r_value > threshold) {
                for (int k = 0; k < 3; ++k)
                    modified_image(i, j, k) = 0;
            }
            else {
                for (int k = 0; k < 3; ++k)
                    modified_image(i, j, k) = 255;
            }

        }
    }

    printImage(modified_image, imageName);
}

int main() {
    while (true) {
        cout << "A: Choose an image to edit\nB: Exit\n";
        string option;
        getline(cin, option);
        if (option == "B" || option == "b")
            return 0;
        if (option != "A" && option != "a") {
            cout << "Enter a valid option\n";
            continue;
        }
        string imageName;
        cout << "Enter the image file name you want to upload\n";
        getline(cin, imageName);
        Image image;
        try {
            image.loadNewImage(imageName);
        }
        catch (const invalid_argument &e) {
            continue;
        }
        cout << "Choose the filter you want to apply\n";
        cout << "1: Grayscale Conversion\n";
        cout << "2: Black and White\n";
        cout << "3: Invert Image\n";
        cout << "4: Flip Image\n";
        cout << "5: Rotate Image\n";
        cout << "6: Lighten Image\n";
        cout << "7: Darken Image\n";
        cout << "8: Detect Image Edges\n";

        while (true) {
            string filter;
            getline(cin, filter);
            if (filter == "1")
                grayscale_conversion(image, imageName, true);
            else if (filter == "2")
                black_and_white(image, imageName);
            else if (filter == "3")
                invert_image(image, imageName);
            else if (filter == "4")
                flip(image, imageName);
            else if (filter == "5")
                rotate(image, imageName);
            else if (filter == "6")
                lighten_image(image, imageName);
            else if (filter == "7")
                darken_image(image, imageName);
            else if (filter == "8")
                edge_detection(image, imageName);
            else {
                cout << "Enter a valid option\n";
                continue;
            }
            break;
        }
    }
}
