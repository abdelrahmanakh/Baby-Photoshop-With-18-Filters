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

int main() {
    flip_horizontally("arrow.jpg");
    return 0;
}
