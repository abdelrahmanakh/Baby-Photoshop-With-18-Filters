#include <iostream>
#include <cstdlib>
#include "Image_Class.h"
using namespace std;

void black_and_white(string image_name){
    Image img(image_name);
    for(int i=0;i<img.width;i++){
        for(int j=0;j<img.height;j++){
            unsigned int avg=0;
            for(int k=0;k<3;k++){
                avg += img(i,j,k);
            }
            avg/=3;
            if(avg>=128)
                avg=255;
            else
                avg=0;
            for(int k=0;k<3;k++){
                img(i,j,k)=avg;
            }
        }
    }
    string name="1.jpg";
    img.saveImage(name);
    system(name.c_str());
}

void flip_horizontally(string image_name){
    Image img(image_name),img2(image_name);
    for(int i=0,x=img2.width-1;i<img2.width;i++,x--){
        for(int j=0;j<img2.height;j++){
            for(int k=0;k<3;k++){
                int v=img2(x,j,k);
                img(i,j,k)=v;
            }
        }
    }
    string name="1.jpg";
    img.saveImage(name);
    system(name.c_str());
}

void flip_vertically(string image_name){
    Image img(image_name),img2(image_name);
    for(int i=0;i<img2.width;i++){
        for(int j=0,y=img.height-1;j<img2.height;j++,y--){
            for(int k=0;k<3;k++){
                int v=img2(i,y,k);
                img(i,j,k)=v;
            }
        }
    }
    string name="1.jpg";
    img.saveImage(name);
    system(name.c_str());
}

void invert_image(string image_name) {
    cout << "Enter the name of the image along with its extension:";
    cin >> image_name;

    Image image(image_name);

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

    cout << "Please enter image name to store the new image (with extension):\n";
    cin >> image_name;
    image.saveImage(image_name);

}
void rotateImage90(string image_name) {
    Image image(image_name);

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


    adjusted_img.saveImage(image_name);
}

void rotateImage180(string image_name) {

    Image image(image_name);


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


    adjusted_img.saveImage(image_name);
}

void rotateImage270(string image_name) {

    Image image(image_name);


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


    adjusted_img.saveImage(image_name);
}



int main() {
    flip_horizontally("arrow.jpg");
    return 0;
}
