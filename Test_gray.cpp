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
    Open_GS_Image();
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (image[i][j] > 127)
                new_image[i][j] = 255; // convert the greater than the average to a white pixel
            else 
                new_image[i][j] = 0;    // convert the lower than the average to a black pixel  
        }
    }
    Save_GS_Image();
}

// 2. Invert Image :
void GS_Invert(){
    Open_GS_Image();
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++)
            new_image[i][j] = 255 - image[i][j]; // turn every pixel to its opposite level of brightness
    }
    Save_GS_Image();
}

// 3. Merge Images:
void GS_Merge(){
    Open_GS_Image();
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
    Save_GS_Image();
}

// 4. Flip Image Horizontally and Vertically :
void GS_Flip (){
    Open_GS_Image();
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
    Save_GS_Image();
}

// 5. Darken And Lighten Image :
void GS_Darken_And_Lighten(){
    Open_GS_Image();
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
    Save_GS_Image();
}

// 6. Rotate Image :
void GS_Rotate(){
    Open_GS_Image();
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
    Save_GS_Image();
}

// 7. Detect Image Edges :
void GS_Edges(){
    Open_GS_Image();
    unsigned char new_image2[SIZE][SIZE]; 
    // convert the image to Black and white
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (image[i][j] > 127)
                new_image2[i][j] = 255;
            else
                new_image2[i][j] = 0;    
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if(new_image2[i][j] == 0 && new_image2[i-1][j] == 0  && new_image2[i+1][j] == 0 && new_image2[i][j-1] == 0 && new_image2[i][j+1] == 0){
                new_image[i][j] = 255;
            }
            else if(new_image2[i][j] == 0 ) 
                new_image[i][j] = 0;
            else 
                new_image[i][j] = 255;
        }
    }
    Save_GS_Image();
}

// 8. Enlarge Image :
void GS_Enlarge(){
    Open_GS_Image();
    short Quarter;
    cout << "\nWhich quarter to enlarge 1, 2, 3 or 4 ? \n";
    cin >> Quarter;
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            switch(Quarter){
                case 1:
                    new_image[i][j] = image[i / 2][j / 2]; // each pixel of the original image is divided to 4 pixels in the new image.
                    break;
                case 2:
                    new_image[i][j] = image[i / 2][(SIZE/2 + j / 2)]; // (size / 2 + j) to reach second quarter.
                    break;
                case 3:
                    new_image[i][j] = image[SIZE / 2 + i / 2][j / 2]; // (size / 2 + i) to reach third quarter.
                    break;
                case 4:
                    new_image[i][j] = image[SIZE / 2 + i / 2][SIZE/2 + j / 2]; // (size / 2 + i) and (size / 2 + j) to reach fourth quarter.
                    break;
            }
        }
    }
    Save_GS_Image();
}

// 9.shrink image :
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

// a. Mirror :
void GS_Mirror(){
    Open_GS_Image();
    cout << "\nEnter The Number Of Part\n";
    cout << "(1) Left\n";
    cout << "(2) Right\n";
    cout << "(3) Upper\n";
    cout << "(4) Lower\n";
    int n;
    cin >> n;
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
                new_image[SIZE-i][j] = image[i][j]; // make the upper= the dowen  
                new_image[i][j] = image[i][j];
            }
        }
    }
    Save_GS_Image();
}

// b. Shuffle Image :
void GS_Shuffle(){
    Open_GS_Image();
    int arr[4];
    cout << "\nNew order of quarters ? \n";
    cin >> arr[0] >> arr[1] >> arr[2] >> arr[3];

    for(int i = 0; i < SIZE / 2; i++){
        for(int j = 0; j < SIZE / 2; j++){

            switch(arr[0]){ // first quarter of the new image.
                case 1: // equal it with first quarter of the orignal image.
                    new_image[i][j] = image[i][j]; 
                    break;
                case 2: // equal it with second quarter of the orignal image.     
                    new_image[i][j] = image[i][SIZE /2 + j];
                    break;
                case 3: // equal it with third quarter of the orignal image.
                    new_image[i][j] = image[SIZE / 2 + i][j];
                    break;
                case 4: // equal it with fourth quarter of the orignal image.
                    new_image[i][j] = image[SIZE / 2 + i][SIZE /2 + j];
                    break;
                }
            switch(arr[1]){ // second quarter of the new image.
                case 1:
                    new_image[i][SIZE / 2 + j] = image[i][j];
                    break;
                case 2:                        
                    new_image[i][SIZE / 2 + j] = image[i][SIZE /2 + j];
                    break;
                case 3:
                    new_image[i][SIZE / 2 + j] = image[SIZE / 2 + i][j];
                    break;
                case 4:
                    new_image[i][SIZE / 2 + j] = image[SIZE / 2 + i][SIZE /2 + j];
                    break;
                }
            switch(arr[2]){ // third quarter of the new image.
                case 1:
                    new_image[SIZE / 2 + i][j] = image[i][j];
                    break;                    
                case 2:                        
                    new_image[SIZE / 2 + i][j] = image[i][SIZE /2 + j];
                    break;
                case 3:
                    new_image[SIZE / 2 + i][j] = image[SIZE / 2 + i][j];
                    break;
                case 4:
                    new_image[SIZE / 2 + i][j] = image[SIZE / 2 + i][SIZE /2 + j];
                    break;
                }
            switch(arr[3]){ // fourth quarter of the new image.
                case 1:
                    new_image[SIZE / 2 + i][SIZE /2 + j] = image[i][j];
                    break;                    
                case 2:                        
                    new_image[SIZE / 2 + i][SIZE /2 + j] = image[i][SIZE /2 + j];
                    break;
                case 3:
                    new_image[SIZE / 2 + i][SIZE /2 + j] = image[SIZE / 2 + i][j];
                    break;
                case 4:
                    new_image[SIZE / 2 + i][SIZE /2 + j] = image[SIZE / 2 + i][SIZE /2 + j];
                    break;
                }
            }
        }
    Save_GS_Image();
}

// c.blur image
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

// d. Crop Image :
void GS_Crop(){
    Open_GS_Image();
    cout << "\nEnter The Starting Position\n";
    int x, y; 
    cin >> x >> y;
    cout << "\nEnter Width And Length\n";
    int w, l; 
    cin >> w >> l;
    for(int i = y; i < y+l; i++){ //start row = y, end row = l+y. looping over l rows make the length.
        for(int j = x; j < x+w; j++){//start column = x, end column = x+w. looping over w columns make the width.
            new_image[i][j] = image[i][j];
        }
    }
    Save_GS_Image();
}

char Choice = '1';
void DoProcess(){
    cout << "\nPlease select a filter to apply or 0 to exit : \n";
    cin >> Choice;

    switch(Choice){
        case('1'):
            GS_Black_White();
            break; 
        case('2'):
            GS_Invert();
            break;
        case('3'):
            GS_Merge();
            break;
        case('4'):
            GS_Flip();
            break;
        case('5'):
            GS_Darken_And_Lighten();
            break;
        case('6'):
            GS_Rotate();
            break;
        case('7'):
            GS_Edges();
            break;
        case('8'):
            GS_Enlarge();
            break;
        case('9'):
            GS_Shrink();
            cout << 9;
            break;
        case('a'):
            GS_Mirror();
            break;
        case('b'):
            GS_Shuffle();
            break;
        case('c'):
            GS_Blur();
            cout << 12;
            break;
        case('d'):
            GS_Crop();
            break;
        case('e'):
            cout << 14;
            break;
        case('f'):
            cout << 15;
            break;
        case('0'):
            break;
    }
}

// view all filters:
void view(){

    cout << "\nWelcome To Our Image Processing Tool, There Are Many Filters :\n\n";  
    cout << "1- Black & White Filter\n";
    cout << "2- Invert Filter\n";
    cout << "3- Merge Filter \n";
    cout << "4- Flip Image\n";
    cout << "5- Darken and Lighten Image \n";
    cout << "6- Rotate Image\n";
    cout << "7- Detect Image Edges \n";
    cout << "8- Enlarge Image\n";
    cout << "9- Shrink Image\n";
    cout << "a- Mirror 1/2 Image\n";
    cout << "b- Shuffle Image\n";
    cout << "c- Blur Image\n";
    cout << "d- Crop Image\n";
    cout << "e- Skew Image Right  \n";
    cout << "f- Skew Image Up  \n";
    cout << "0- Exit\n";

    DoProcess();
}

int main (){

    while(Choice != '0')
        view (); 
       
}
