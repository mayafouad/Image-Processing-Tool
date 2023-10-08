/*
    ------   CS213 - 2023 - Assignment 1 - Part 1 .    ------

    Maya Fouad Fathy    20220270    mayafouad2004@gmail.com

    Anas Abdelnasser    20220071    Elessilyanas@gmail.com

    Menna Abdelkarim    20210607    mannaabdelkarim0@gmail.com
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

 // 3. Merge Images:
void GS_Merge(){
    Open_GS_Image();
    unsigned char image2[SIZE][SIZE];         // declare the images we need .
    unsigned char image3 [SIZE][SIZE];
    char mergeImageFileName[100];            // load second Image.
    cout << "\nEnter the source image2 file name :\n";
    cin >> mergeImageFileName;
    strcat (mergeImageFileName, ".bmp");     // add ".bmp" to second image .
    readGSBMP (mergeImageFileName, image2);  // and load it .

    for (int i = 0; i < SIZE; i++) {         // merge two photos .
        for (int j = 0; j < SIZE; j++) {
            image3[i][j] = (image[i][j] + image2[i][j]) / 2;
        }
    }
    for (int i =0 ;i<SIZE;i++){               // put the new image in the original image .
        for (int j=0 ; j< SIZE;j++){
            new_image[i][j]=image3[i][j];
        }
    }
    Save_GS_Image();
}


//6. Rotate Image :
void GS_Rotate(){
    Open_GS_Image();
    int rot_Choice = 1 ;
    cout << "\n\tSelect 1 for 90 degree rotation\n"
            "\tSelect 2 for 180 degree rotation\n"
            "\tSelect 3 for 270 degree rotation\n";
    cin >> rot_Choice;                         // user input of the rotation choice menu .

    while (rot_Choice < 1 || rot_Choice > 3){

        cout << "\nInvalid input, please re-enter a valid one :\n";
        cin >> rot_Choice;            // if the user input not valid ;re-load rotation choice menu +.
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            switch(rot_Choice) {
                case 1 :                          // 90 degree rotation .
                    new_image[i][j] = image[SIZE - 1 - j][i];
                    break;
                case 2 :                           // 180 degree rotation .
                    new_image[i][j] = image[SIZE - 1 - i][SIZE - 1 - j];
                    break ;
                case 3 :                          // 270 degree rotation .
                     new_image[i][j] = image[j][SIZE - 1 - i] ;
                    break;
                default :
                    break;
            }
        }
    }
    Save_GS_Image();
}

//9.shrink image
void GS_Shrink () {
     Open_GS_Image();
     unsigned char image2[SIZE][SIZE];
    int choice ;                    // read the user choice .
    cout <<"\tfor 1/2 shrink photo select 1: \n";
    cout <<"\tfor 1/3 shrink photo select 2:\n";
    cout <<"\tfor 1/4 shrink photo select 3: \n";
    cin >> choice;
    for (int i = 0; i < SIZE; ++i) {       //make all pixels in image2
        for (int j = 0; j < SIZE; ++j) {  // array are white 255 .
            image2[i][j]=255;
        }
    }
    if (choice == 1){                   // 1/2 shrink photo .
        for (int i = 0; i < SIZE; i+=2) {
            for (int j = 0; j < SIZE; j+=2) {
                image2[i / 2][j / 2] = image[i][j];
            }
        }

    }
    else if (choice == 2){             // 1/3 shrink photo .
        for (int i = 0; i < SIZE; i+=3) {
            for (int j = 0; j < SIZE; j+=3) {
                image2[i / 3][j / 3] = image[i][j];
            }
        }

    }
    else if (choice == 3){            // 1/4 shrink photo .
        for (int i = 0; i < SIZE; i+=4) {
            for (int j = 0; j < SIZE; j+=4) {
                image2[i / 4][j /4 ] = image[i][j];
            }
        }

    }
    for (int i =0 ;i<SIZE;i++){   //save the new photo.
        for (int j=0 ; j< SIZE;j++)
           new_image[i][j]=image2[i][j];
        }
        Save_GS_Image();
    }


//c.blur image
void GS_Blur () {
    Open_GS_Image();
    long long avg=0;   // declare a variable to store the sum .
    for (int i = 0; i < SIZE; i++) {  //rows for loop.
        for (int j = 0; j < SIZE; j++) { // columns for loop .
            for (int k = i; k < i+7; k++) {
                for (int l = j; l < j+7; l++) { // iterate every 7*7 pixels .
                    avg+=(image[k][l]);
                }
            }
            avg=avg/49;    // calculate the average " sum /49" .
           new_image[i][j]=avg;
            avg=0;
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
    cout << "6: rotate image filter\n";
    cout << "7: Detect Image Edges\n";
    cout << "8: Black and White Image\n";
    cout << "9: shrink image filter\n";
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
     case 3:{
        GS_Merge();
            break;
        }
     case 6:{
         GS_Rotate();;
             break;
        }
     case (9):{
         GS_Shrink();
            break;
     } 
    case (c):{
         GS_Blur();
            break;
     }
        
    }



int main (){

    while(number != 0){
        view ();
    }

}
