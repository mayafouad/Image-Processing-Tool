/*
    ------   CS213 - 2023 - Assignment 1 - Part 1 .    ------

    Maya Fouad Fathy    20220270    mayafouad2004@gmail.com

    Anas Abdelnasser    20220071    Elessilyanas@gmail.com

    Menna Abdelkarim    20210607    mannaabdelkarim@gmail.com

*/

#include <bits/stdc++.h>
#include "bmplib.cpp"
using namespace std;

unsigned char c_image[SIZE][SIZE][RGB];
unsigned char new_c_image[SIZE][SIZE][RGB];

void Open_RGB_Image(){
    char ImageFileName[100];
    cout << "Enter The Source Image File Name\n";// enter target file name
    cin >> ImageFileName;
    strcat(ImageFileName, ".bmp");// add to it .bmp extension and load image
    readRGBBMP(ImageFileName, c_image);
}
void Save_RGB_Image(){
    char ImageFileName[100];
    cout << "Enter The Target Image File Name\n"; // enter target file name
    cin >> ImageFileName;
    strcat(ImageFileName, ".bmp");// add to it .bmp extension and load image
    writeRGBBMP(ImageFileName, new_c_image);
}
// RGB Filters----------------------------------

// 1. Black and White Image :
void RGB_Black_White(){
    Open_RGB_Image();
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int sum=0;
            for(int k = 0; k < RGB; k++){
               sum +=c_image[i][j][k];
            }
            if(sum/3 > 127){
                new_image[i][j] = 255;}
            else new_image[i][j] = 0;

        }
    }
    Save_GS_Image();
}

// 4. Flip Image Horizontally and Vertically :
void RGB_Flip (){
    Open_RGB_Image();
    cout << "To Flip the Image Horizontally Enter (1), Vertically Enter (2) \n";
    int n; cin >> n;
    if(n == 1){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for(int k = 0; k <RGB; k++){
                new_c_image[i][j][k] = c_image[i][abs(SIZE-j)][k]; 
                // convert the place of column 
                }
        }
    }
    }
    else{
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for(int k = 0; k <RGB; k++){
                new_c_image[i][j][k] = c_image[abs(SIZE-i)][j][k]; 
                // convert the place of row 
                }
        }
    }
    }
    Save_RGB_Image();
}
// 7. Detect Image Edges :
void RGB_Edges(){
    Open_RGB_Image();
    // convert the image to Black and white 
    unsigned char new_image2[SIZE][SIZE]; 
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int sum=0;
            for(int k = 0; k < RGB; k++){
               sum +=c_image[i][j][k];
            }
            if(sum/3 > 127){
                new_image2[i][j] = 255;}
            else new_image2[i][j] = 0;

        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if(new_image2[i][j] == 0 && new_image2[i-1][j] ==0  
            && new_image2[i+1][j] == 0 && new_image2[i][j-1] == 0 && new_image2[i][j+1] == 0){
                new_image[i][j] = 255;}
            else if(new_image2[i][j] == 0 ) new_image[i][j] = 0;
            else new_image[i][j] = 255;
        }
    }
    Save_GS_Image();
}
