/*
 * FCAI – Structured Programming – 2024 - Assignment 3 - Part 1
 * Program Name: CS112_A3_Part1_S3_S4_20230593_20230587_20230794.cpp
 * Program Description: Image Filter Program
 * Last Modification Date: 27/03/2024
 * Authors: Abdelrahman Ahmed Samir Mohamed Ali, 20230593, Group:A, Sec.no:3
 *          Saleem Sami Saleem Aljerjawi, 20230794, Group:A, Sec.no:4
 *          Mazen Mohamed Abdelsalam Ali Elsheikh, 20230587, Group:A, Sec.no:4
 * TA:      Ahmed Foad Lotfy
 * Who did what: Mazen: The Menu of the previous delivery & Print function & Grayscale Filter & Lighten and Darken filter & Edge detection & Merge filter
 *               Abdelrahman: the menu of this delivery & flip  & black_and_white & Crop & resize Filters
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

void printImage(Image image, string imageName) {
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

Image grayscale_conversion(Image image) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            int value = 0.299 * image(i, j, 0) + 0.587 * image(i, j, 1) + 0.114 * image(i, j, 2);
            for (int k = 0; k < image.channels; ++k)
                image(i, j, k) = value;
        }
    }
    return image;
}

Image black_and_white(Image image) {
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
    return image;
}

Image flip_horizontally(Image image) {
    Image img = image, img2 = image;
    for (int i = 0, x = img2.width - 1; i < img2.width; i++, x--) {
        for (int j = 0; j < img2.height; j++) {
            for (int k = 0; k < 3; k++) {
                int v = img2(x, j, k);
                img(i, j, k) = v;
            }
        }
    }
    return img;
}

Image flip_vertically(Image image) {
    Image img = image, img2 = image;
    for (int i = 0; i < img2.width; i++) {
        for (int j = 0, y = img.height - 1; j < img2.height; j++, y--) {
            for (int k = 0; k < 3; k++) {
                int v = img2(i, y, k);
                img(i, j, k) = v;
            }
        }
    }
    return img;
}

Image flip(Image image) {
    cout << "Enter the type of flipping you want\n";
    cout << "A: Horizontal\n";
    cout << "B: Verticel\n";
    while (true) {
        string option;
        getline(cin, option
        );
        if (option == "A" || option == "a")
            image = flip_horizontally(image
            );
        else if (option == "B" || option == "b")
            image = flip_vertically(image
            );
        else {
            cout << "Enter a valid option\n";
            continue;
        }
        break;
    }
    return image;
}

Image invert_image(Image image) {
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

    return image;
}

Image rotateImage90(Image image) {
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
    return adjusted_img;
}

Image rotateImage180(Image image) {
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
    return adjusted_img;
}

Image rotateImage270(Image image) {
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
    return adjusted_img;
}

Image rotate(Image image) {
    cout << "Enter the degree of rotation you want\n";
    cout << "A: 90\n";
    cout << "B: 180\n";
    cout << "C: 270\n";
    while (true) {
        string degree;
        getline(cin, degree);
        if (degree == "A" || degree == "a")
            image = rotateImage90(image);
        else if (degree == "B" || degree == "b")
            image = rotateImage180(image);
        else if (degree == "C" || degree == "c")
            image = rotateImage270(image);
        else {
            cout << "Enter a valid option\n";
            continue;
        }
        break;
    }
    return image;
}

Image lighten_image(Image image) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                int newValue = 1.5 * image(i, j, k);
                newValue = min(newValue, 255);
                image(i, j, k) = newValue;
            }
        }
    }
    return image;
}

Image darken_image(Image image) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                int newValue = 0.5 * image(i, j, k);
                newValue = max(newValue, 0);
                image(i, j, k) = newValue;
            }
        }
    }
    return image;
}

Image edge_detection(Image image) {
    image = grayscale_conversion(image);
    Image modified_image = image;

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
            } else {
                for (int k = 0; k < 3; ++k)
                    modified_image(i, j, k) = 255;
            }

        }
    }

    return modified_image;
}

Image blurImage(Image image) {
    Image blurredImage(image.width, image.height);
    int blurSize = 100;

    vector<vector<vector<int>>> pref(
            vector<vector<vector<int>>>(image.width + 1, vector<vector<int>>(image.height + 1, vector<int>(3, 0))));

    for (int i = 1; i <= image.width; ++i) {
        for (int j = 1; j <= image.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                pref[i][j][k] = pref[i - 1][j][k] + pref[i][j - 1][k] - pref[i - 1][j - 1][k] + image(i - 1, j - 1, k);
            }
        }
    }

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            int startX = max(0, i - blurSize / 2) + 1;
            int startY = max(0, j - blurSize / 2) + 1;
            int endX = min(image.width - 1, i + blurSize / 2) + 1;
            int endY = min(image.height - 1, j + blurSize / 2) + 1;

            int sumR = 0, sumG = 0, sumB = 0;
            int numPixels = (endX - startX + 1) * (endY - startY + 1);

            sumR = pref[endX][endY][0] - pref[startX - 1][endY][0] - pref[endX][startY - 1][0] + pref[startX - 1][startY - 1][0];
            sumG = pref[endX][endY][1] - pref[startX - 1][endY][1] - pref[endX][startY - 1][1] + pref[startX - 1][startY - 1][1];
            sumB = pref[endX][endY][2] - pref[startX - 1][endY][2] - pref[endX][startY - 1][2] + pref[startX - 1][startY - 1][2];

            int avgR = sumR / numPixels;
            int avgG = sumG / numPixels;
            int avgB = sumB / numPixels;

            blurredImage(i, j, 0) = avgR;
            blurredImage(i, j, 1) = avgG;
            blurredImage(i, j, 2) = avgB;
        }
    }
    return blurredImage;
}

Image crop(Image img) {
    int x, y, w, h;
    string sx,sy,sw,sh;
    while(true) {
        cout << "the image size is " << img.width << " X " << img.height
             << "\nEnter the position x,y where you want to start cropping:\n";
        cin >> sx >> sy;
        try {
            x = stoi(sx);
            y = stoi(sy);;
        }
        catch (invalid_argument const &e) {
            cout << "Please enter a number!\n";
            continue;
        }
        if(x>img.width||y>img.height){
            cout<<"This exceeds image dimensions!!\n";
            continue;
        }
        break;
    }
    while (true){
        cout << "the image size is " << img.width << " X " << img.height<< "\nEnter the dimensions of the new image:\n";
        cin >> sw >> sh;
        try{
            w = stoi(sw);
            h = stoi(sh);
        }
        catch (invalid_argument const &e){
            cout<<"Please enter a number!\n";
            continue;
        }
        if(w>img.width||h>img.height){
            cout<<"This exceeds image dimensions!!\n";
            continue;
        }
        break;
    }
    Image img2(w, h);
    for (int i = 0, a = x; i < w; i++, a++) {
        for (int j = 0, b = y; j < h; j++, b++) {
            for (int k = 0; k < 3; k++) {
                int v = img(a, b, k);
                img2(i, j, k) = v;
            }
        }
    }
    cin.ignore();
    return img2;
}

Image sunlight_filter(Image image) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            image(i, j, 2) = image(i, j, 2) * 0.75;
        }
    }
    return image;
}
Image purple_filter(Image image){
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            image(i,j,1) *=0.65;
        }
    }
    return image;
}
int main() {
    string imageName;
    Image image;
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
        cout << "Enter the image file name you want to upload\n";
        getline(cin, imageName);
        try {
            image.loadNewImage(imageName);
        }
        catch (const invalid_argument &e) {
            continue;
        }
        break;
    }
    while (true) {
        cout << "0: Load A new Image\n";
        cout << "1: Grayscale Conversion\n";
        cout << "2: Black and White\n";
        cout << "3: Invert Image\n";
        cout << "4: Flip Image\n";
        cout << "5: Rotate Image\n";
        cout << "6: Lighten Image\n";
        cout << "7: Darken Image\n";
        cout << "8: Detect Image Edges\n";
        cout << "9: Blur Image\n";
        cout << "10: Crop Image\n";
        cout << "11: Sunlight Image\n";
        cout << "12: Purple filter\n";
        cout << "13: Save Image\n";
        cout << "14: Exit\n";
        while (true) {
            string filter;
            getline(cin, filter);
            if (filter == "0") {
                while(true) {
                    cout << "Enter the image file name you want to upload\n";
                    getline(cin, imageName);
                    try {
                        image.loadNewImage(imageName);
                    }
                    catch (const invalid_argument &e) {
                        continue;
                    }
                    break;
                }
            } else if (filter == "1")
                image = grayscale_conversion(image);
            else if (filter == "2")
                image = black_and_white(image);
            else if (filter == "3")
                image = invert_image(image);
            else if (filter == "4")
                image = flip(image);
            else if (filter == "5")
                image = rotate(image);
            else if (filter == "6")
                image = lighten_image(image);
            else if (filter == "7")
                image = darken_image(image);
            else if (filter == "8")
                image = edge_detection(image);
            else if (filter == "9")
                image = blurImage(image);
            else if (filter == "10")
                image = crop(image);
            else if (filter == "11")
                image = sunlight_filter(image);
            else if (filter == "12")
                image = purple_filter(image);
            else if (filter == "13")
                printImage(image, imageName);
            else if (filter == "14")
                return 0;
            else {
                cout << "Enter a valid option\n";
                continue;
            }
            break;
        }
    }
}
