/*
    ----- FCAI – OOP Programming – 2023 - Assignment 1 -----

    Program Name : Filters.cpp

    Last Modification Date : 09/10/2023

    Maya Fouad Fathy    20220270    mayafouad2004@gmail.com

    Anas Abdelnasser    20220071    Elessilyanas@gmail.com

    Menna Abdelkarim    20210607    mannaabdelkarim@gmail.com

    Purpose : Advancing Problem Solving Skills.
*/

#include <bits/stdc++.h>
#include "bmplib.cpp"
using namespace std;

unsigned char image[SIZE][SIZE]; // that will open
unsigned char new_image[SIZE][SIZE]; // that will save

// open and save image:
void Open_GS_Image(){
    char ImageFileName[100];
    cout << "\nEnter The Source Image File Name\n";// enter target file name
    cin >> ImageFileName;
    strcat(ImageFileName, ".bmp");// add to it .bmp extension and load image
    readGSBMP(ImageFileName, image);
}

void Save_GS_Image(){
    char ImageFileName[100];
    cout << "\nEnter The Target Image File Name\n"; // enter target file name
    cin >> ImageFileName;
    strcat(ImageFileName, ".bmp");// add to it .bmp extension and load image
    writeGSBMP(ImageFileName, new_image);
}

bool IsNumberBetween(int Number, int From, int To){
	if (Number >= From && Number <= To)
		return true;
	else
		return false;
}

int ReadIntNumber(string ErrorMessage = "\nInvalid Input, Enter again :\n"){
	int Number;
	while (!(cin >> Number)){
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << ErrorMessage;
	}
	return Number;
}

int ReadIntNumberBetween(int From, int To, string ErrorMessage = "\nInvalid Input, Enter again :\n"){
	int Number = ReadIntNumber();
	while (!IsNumberBetween(Number, From, To)){
		cout << ErrorMessage;
		Number = ReadIntNumber();
	}
	return Number;
}

// ----- Gray Scale Bitmap Filters -----

// 1. Black and White Image :
void GS_Black_White(){
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (image[i][j] > 127)
                new_image[i][j] = 255; // convert the greater than the average to a white pixel
            else 
                new_image[i][j] = 0;    // convert the lower than the average to a black pixel  
        }
    }
    for (int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++)
            image[i][j] = new_image[i][j];
    }
}

// 2. Invert Image :
void GS_Invert(){
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++)
            new_image[i][j] = 255 - image[i][j]; // turn every pixel to its opposite level of brightness
    }
    for (int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++)
            image[i][j] = new_image[i][j];
    }
}

// 3. Merge Images:
void GS_Merge(){
    unsigned char image2[SIZE][SIZE];         // declare the images we need .
    char mergeImageFileName[100];            // load second Image.
    cout << "\nPlease enter name of image file to merge with :\n";
    cin >> mergeImageFileName;
    strcat (mergeImageFileName, ".bmp");     // add ".bmp" to second image .
    readGSBMP (mergeImageFileName, image2);  // and load it .

    for (int i = 0; i < SIZE; i++) {         // merge two photos .
        for (int j = 0; j < SIZE; j++) 
            new_image[i][j] = (image[i][j] + image2[i][j]) / 2;
    }

    for (int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++)
            image[i][j] = new_image[i][j];
    }
}

// 4. Flip Image Horizontally and Vertically :
void GS_Flip (){
    int n;
    cout << "\nTo Flip the Image Horizontally Enter (1), Vertically Enter (2) :\n";
    n = ReadIntNumberBetween(1, 2);
    switch(n){
        case 1:
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) 
                    new_image[i][j] = image[i][abs(SIZE-j)]; // convert the place of column 
            }
            break;
        case 2:
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++)
                    new_image[i][j] = image[abs(SIZE-i)][j]; // convert the place of row 
            }
    }

    for (int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++)
            image[i][j] = new_image[i][j];
    }
}

// 5. Darken And Lighten Image :
void GS_Darken_And_Lighten(){
    int Choice;
    cout << "\nEnter (1) to darken the image, Enter (2) to lighten it :\n";
    Choice = ReadIntNumberBetween(1, 2);
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++) {
            if(Choice == 1)
                new_image[i][j] = image[i][j] * 0.5; // darken the image by 50%.
            else if(Choice == 2)
                new_image[i][j] = (255 + image[i][j]) / 2; // lighten the image by 50%.
        }
    }

    for (int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++)
            image[i][j] = new_image[i][j];
    }
}

// 6. Rotate Image :
void GS_Rotate(){
    int rot_Choice = 1 ;
    cout << "\nEnter (1) for 90 degree rotation\n"
            "Enter (2) for 180 degree rotation\n"
            "Enter (3) for 270 degree rotation\n";
    rot_Choice = ReadIntNumberBetween(1,3);

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
    for (int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++)
            image[i][j] = new_image[i][j];
    }
}

int Choice = 1;
void DoProcess(){
    cout << "\nPlease select a filter to apply or 0 to exit : \n";
    Choice = ReadIntNumberBetween(0,8);

    switch(Choice){
        case(1):
            GS_Black_White();
            break; 
        case(2):
            GS_Invert();
            break;
        case(3):
            GS_Merge();
            break;
        case(4):
            GS_Flip();
            break;
        case(5):
            GS_Darken_And_Lighten();
            break;
        case(6):
            GS_Rotate();
            break;
        case(7):
            Save_GS_Image();
            break;
        case(8):
            Open_GS_Image();
            break;
        case(0):
            break;
    }
}

// view all filters:
void view(){

    cout << "\nThere Are Many Filters :\n\n";  
    cout << "1- Black & White Filter\n";
    cout << "2- Invert Filter\n";
    cout << "3- Merge Filter \n";
    cout << "4- Flip Image\n";
    cout << "5- Darken and Lighten Image \n";
    cout << "6- Rotate Image\n";
    cout << "7- Save the image to a file\n";
    cout << "8- Open Another image\n";
    cout << "0- Exit\n";

    DoProcess();
}

int main (){
    
    cout << "Welcome To Our Image Processing Tool.\n";
    Open_GS_Image();
    while(Choice != 0)
        view (); 
       
}
