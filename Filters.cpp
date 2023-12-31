/*
    ------   CS213 - 2023 - Assignment 1 - Part 1 .    ------

    Maya Fouad Fathy    20220270    mayafouad2004@gmail.com

    Anas Abdelnasser    20220071    Elessilyanas@gmail.com

    Menna Abdelkarim    20210607    mannaabdelkarim@gmail.com

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
void GS_Black_White(){
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
void GS_Flip (){
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
void GS_Edges(){
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
// 10. Mirror :
void GS_Mirror(){
    Open_GS_Image();
    cout << "Enter The Number Of Part\n";
    cout << "(1) Left\n";
    cout << "(2) Right\n";
    cout << "(3) Upper\n";
    cout << "(4) Lower\n";
    int n; cin >> n;
    if(n == 1){
        for(int i = 0; i < SIZE; i++){
            for(int j = 0; j <= SIZE/2; j++){ // loop over the left part 
                new_image[i][j] = image[i][j]; 
                new_image[i][SIZE-j] = image[i][j]; // make the most right = the left
            }
        }
    }
    else if(n == 2){
        for(int i = 0; i < SIZE; i++){
            for(int j = SIZE/2; j < SIZE; j++){ // loop over the right part 
                new_image[i][SIZE-j] = image[i][j]; // make  the left = the right 
                new_image[i][j] = image[i][j];
            }
        }
    }
    else if(n == 3){
        for(int i = 0; i <= SIZE/2; i++){ // loop over the upper part 
            for(int j = 0; j < SIZE; j++){
                new_image[i][j] = image[i][j];
                new_image[SIZE-i][j] = image[i][j]; // make the most down = the upper
            }
        }
    }
    else {
        for(int i = SIZE/2; i < SIZE ; i++){ // loop over the lower part 
            for(int j = 0; j < SIZE; j++){
                new_image[SIZE-i][j] = image[i][j]; // make the upper = the dowen  
                new_image[i][j] = image[i][j];
            }
        }
    }
    Save_GS_Image();
}
// 13. Crop Image :
void GS_Crop(){
    Open_GS_Image();
    cout << "Enter The Starting Position\n";
    int x, y; cin >> x >> y;
    cout << "Enter Width And Length\n";
    int w, l; cin >> w >> l;
    for(int i = y; i < y+l; i++){ //start row = y, end row = l+y. looping over l rows make the length.
        for(int j = x; j < x+w; j++){//start column = x, end column = x+w. looping over w columns make the width.
            new_image[i][j] = image[i][j];
        }
    }
    Save_GS_Image();
}
// view all filters:
int number = 1;
void view (){
    cout << "Welcome To Our Image Processing Tool, There Are Many Filters :\n";  
    cout << "1: Black and White Image\n"; 
    cout << "2: Invert Image\n"; 
    cout << "3: Merge Images\n"; 
    cout << "4: Flip Image\n"; 
    cout << "5: Black and White Image\n"; 
    cout << "6: Black and White Image\n"; 
    cout << "7: Detect Image Edges\n"; 
    cout << "8: Black and White Image\n"; 
    cout << "9: Black and White Image\n"; 
    cout << "10: Mirror Image\n"; 
    cout << "11: Black and White Image\n"; 
    cout << "12: Black and White Image\n"; 
    cout << "13: Crop Image\n"; 
    cout << "14: Black and White Image\n"; 
    cout << "15: Black and White Image\n"; 
    cout << "Enter The Number Of Filter, Or To Exist Press Zero.\n";
    cin >> number;
    switch (number)
    {
    case 1:{
        GS_Black_White();
        break;}
    case 4:{
        GS_Flip ();
        break;}
    case 7:{
        GS_Edges ();
        break;}  
    case 10:{
        GS_Mirror ();
        break;} 
    case 13:{
        GS_Crop ();
        break;}    
    default:
        break;
    }
}

int main (){

    while(number != 0){
        view (); 
    }
    
}
