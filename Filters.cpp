/*
    -----   CS213 - 2023 - Assignment 1 - Part 1 .    -----

    Maya Fouad Fathy    20220270    mayafouad2004@gmail.com

    Anas Abdelnasser Ibrahim    20220071    Elessilyanas@gmail.com

*/

#include <bits/stdc++.h>
#include "bmplib.cpp"
using namespace std;

unsigned char image[SIZE][SIZE]; // that will open
unsigned char new_image[SIZE][SIZE]; // that will save

// open and save image:
void Open_GS_Image(){
    char ImageFileName[100];
    cout << "Enter The Source Image File Name\n";// enter target file name
    cin >> ImageFileName;
    strcat(ImageFileName, ".bmp");// add to it .bmp extension and load image
    readGSBMP(ImageFileName, image);
}
void Save_GS_Image(){
    char ImageFileName[100];
    cout << "Enter The Target Image File Name\n"; // enter target file name
    cin >> ImageFileName;
    strcat(ImageFileName, ".bmp");// add to it .bmp extension and load image
    writeGSBMP(ImageFileName, new_image);
}

// ----- Gray Scale Bitmap Filters -----

// 1. Black and White Image :
void Black_GS_White(){
    Open_GS_Image();
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (image[i][j] > 127)new_image[i][j] = 255; // convert the greater than the average to a white pixel
            else new_image[i][j] = 0;    // convert the lower than the average to a black pixel  
        }
    }
    Save_GS_Image();
}
// 4. Flip Image Horizontally and Vertically :
void Flip (){
    Open_GS_Image();
    cout << "To Flip the Image Horizontally Enter (1), Vertically Enter (2) \n";
    int n; cin >> n;
    if(n == 1){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                new_image[i][j] = image[i][abs(SIZE-j)]; 
                // convert the place of column 
        }
    }
    }
    else{
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                new_image[i][j] = image[abs(SIZE-i)][j]; 
                // convert the place of row 
        }
    }
    }
    Save_GS_Image();
}
// 7. Detect Image Edges :
void Edges(){
    Open_GS_Image();
    // convert the image to Black and white 
    unsigned char new_image2[SIZE][SIZE]; 
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (image[i][j] > 127)new_image2[i][j] = 255; 
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
// view all filters:
void view (){
    cout << "Filters :\n"; 
    cout << "1: Black and White Image\n"; 
    cout << "2: Invert Image\n"; 
    cout << "3: Merge Images\n"; 
    cout << "4: Black and White Image\n"; 
    cout << "5: Black and White Image\n"; 
    cout << "6: Black and White Image\n"; 
    cout << "7: Detect Image Edges\n"; 
    cout << "8: Black and White Image\n"; 
    cout << "9: Black and White Image\n"; 
    cout << "10: Black and White Image\n"; 
    cout << "11: Black and White Image\n"; 
    cout << "12: Black and White Image\n"; 
    cout << "13: Black and White Image\n"; 
    cout << "14: Black and White Image\n"; 
    cout << "15: Black and White Image\n"; 
    cout << "Enter The Number Of Filter\n"; 
    int n; cin >> n;
    switch (n)
    {
    case 1:{
        Black_GS_White();
        break;}
    case 2:{
        Flip ();
        break;}
    case 7:{
        Edges ();
        break;}    
    default:
        break;
    }
}

int main (){
    view ();
}
