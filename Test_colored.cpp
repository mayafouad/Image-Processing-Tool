/*
    ----- FCAI – OOP Programming – 2023 - Assignment 1 -----

    Program Name : Filters.cpp

    Last Modification Date : 09/10/2023

    Maya Fouad Fathy    20220270    mayafouad2004@gmail.com

    Anas Abdelnasser    20220071    Elessilyanas@gmail.com

    Menna Abdelkarim    20210607    mannaabdelkarim0@gmail.com

    Purpose : Image processing tool.
*/

#include <bits/stdc++.h>
#include "bmplib.cpp"
using namespace std;

unsigned char c_image[SIZE][SIZE][RGB];
unsigned char new_c_image[SIZE][SIZE][RGB];
unsigned char new_image[SIZE][SIZE];

void Save_GS_Image(){
    char ImageFileName[100];
    cout << "\nEnter The Target Image File Name\n"; // enter target file name
    cin >> ImageFileName;
    strcat(ImageFileName, ".bmp");// add to it .bmp extension and load image
    writeGSBMP(ImageFileName, new_image);
}

void Open_RGB_Image(){
    char ImageFileName[100];
    cout << "\nEnter The Source Image File Name\n";// enter target file name
    cin >> ImageFileName;
    strcat(ImageFileName, ".bmp");// add to it .bmp extension and load image
    readRGBBMP(ImageFileName, c_image);
}

void Save_RGB_Image(){
    char ImageFileName[100];
    cout << "\nEnter The Target Image File Name\n"; // enter target file name
    cin >> ImageFileName;
    strcat(ImageFileName, ".bmp");// add to it .bmp extension and load image
    writeRGBBMP(ImageFileName, new_c_image);
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

// RGB Filters----------------------------------

// 1. Black and White Image :
void RGB_Black_White(){
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int sum = 0;
            for(int k = 0; k < RGB; k++)
               sum += c_image[i][j][k];
            if((sum/3) > 127)
                new_image[i][j] = 255;
            else 
                new_image[i][j] = 0;
        }
    }
    for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for(int k = 0; k <RGB; k++){
                    new_c_image[i][j][k]=new_image[i][j];
                }
            }
    }

// 2. Invert Image :
void RGB_Invert_Filter(){
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++) {
            for(int k = 0; k < RGB; k++)
                new_c_image[i][j][k] = 255 - c_image[i][j][k];
        }
    }
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++) {
            for(int k = 0; k < RGB; k++)
                c_image[i][j][k] = new_c_image[i][j][k];
        }
    }
}

//3. merge images:
void RGB_Merge(){
    unsigned char image2[SIZE][SIZE][RGB];         // declare the images we need .
    char mergeImageFileName[100];            // load second Image.
    cout << "\nPlease enter name of image file to merge with :\n";
    cin >> mergeImageFileName;
    strcat (mergeImageFileName, ".bmp");     // add ".bmp" to second image .
    readRGBBMP(mergeImageFileName, image2);  // and load it .

    for (int i = 0; i < SIZE; i++) {         // merge two photos .
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; ++k) {
                new_c_image[i][j][k] = (c_image[i][j][k] + image2[i][j][k]) / 2;
            }
        }
    }

    for (int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; ++k) {
                c_image[i][j][k] = new_c_image[i][j][k];
            }
        }
    }
}

// 4. Flip Image Horizontally and Vertically :
void RGB_Flip (){
    cout << "To Flip the Image Horizontally Enter (1), Vertically Enter (2) \n";
    int n;
    n = ReadIntNumberBetween(1,2);
    if(n == 1){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for(int k = 0; k <RGB; k++)
                    new_c_image[i][j][k] = c_image[i][abs(SIZE-j)][k]; 
                // convert the place of column 
            }
        }
    }
    else{
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for(int k = 0; k <RGB; k++)
                    new_c_image[i][j][k] = c_image[abs(SIZE-i)][j][k]; 
                // convert the place of row 
            }
        }
    }
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++) {
            for(int k = 0; k < RGB; k++)
                c_image[i][j][k] = new_c_image[i][j][k];
        }
    }
}

// 5. Darken And Lighten Image :
void RGB_Darken_And_Lighten_Image(){
    int Choice;
    cout << "\nEnter (1) to darken the image, Enter (2) to lighten it :\n";
    Choice = ReadIntNumberBetween(1, 2);
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++) {
            for(int k = 0; k < RGB; k++){
                if(Choice == 1)
                    new_c_image[i][j][k] = c_image[i][j][k] * 0.5; // darken the image by 50%
                else if(Choice == 2)
                    new_c_image[i][j][k] = (255 + c_image[i][j][k]) / 2; // lighten the image by 50%
            }
        }
    }
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++) {
            for(int k = 0; k < RGB; k++)
                c_image[i][j][k] = new_c_image[i][j][k];
        }
    }
}

// 6. Rotate Image :
void RGB_Rotate(){
    int rot_Choice = 1 ;
    cout << "\nEnter (1) for 90 degree rotation\n"
            "Enter (2) for 180 degree rotation\n"
            "Enter (3) for 270 degree rotation\n";
    rot_Choice = ReadIntNumberBetween(1,3);

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++){
            for(int k = 0; k <RGB; ++k){

                switch(rot_Choice) {
                    case 1 :                          // 90 degree rotation .
                        new_c_image[i][j][k] = c_image[SIZE - 1 - j][i][k];
                        break;
                    case 2 :                           // 180 degree rotation .
                        new_c_image[i][j][k] =c_image[SIZE - 1 - i][SIZE - 1 - j][k];
                        break ;
                    case 3 :                          // 270 degree rotation .
                        new_c_image[i][j][k] = c_image[j][SIZE - 1 - i][k];
                        break;
                    default :
                        break;
                }
            }
        }
    }
    for (int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; ++k){
               c_image[i][j][k]= new_c_image[i][j][k];
            }
        }
    }
}

// 7. Detect Image Edges :
void RGB_Edges(){
    // convert the image to Black and white 
    unsigned char new_image2[SIZE][SIZE]; 
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int sum=0;
            for(int k = 0; k < RGB; k++)
               sum += c_image[i][j][k];
            if(sum/3 > 127)
                new_image2[i][j] = 255;
            else 
                new_image2[i][j] = 0;
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if(new_image2[i][j] == 0 && new_image2[i-1][j] ==0  
            && new_image2[i+1][j] == 0 && new_image2[i][j-1] == 0 && new_image2[i][j+1] == 0){
                new_image[i][j] = 255;
            }
            else if(new_image2[i][j] == 0 ) 
                new_image[i][j] = 0;
            else 
                new_image[i][j] = 255;
        }
    }
    for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for(int k = 0; k <RGB; k++){
                    new_c_image[i][j][k]=new_image[i][j];
                }
            }
    }
}

// 8. Enlarge Image :
void RGB_Enlarge(){
    short Quarter;
    cout << "\nWhich quarter to enlarge 1, 2, 3 or 4 ? \n";
    Quarter = ReadIntNumberBetween(1,4);
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            for(int k = 0; k < RGB; k++){
                switch(Quarter){
                    case 1:
                        new_c_image[i][j][k] = c_image[i / 2][j / 2][k]; // each pixel of the original image is divided to 4 pixels in the new image.
                        break;
                    case 2:
                        new_c_image[i][j][k] = c_image[i / 2][(SIZE/2 + j / 2)][k]; // (size / 2 + j) to reach second quarter.
                        break;
                    case 3:
                        new_c_image[i][j][k] = c_image[SIZE / 2 + i / 2][j / 2][k]; // (size / 2 + i) to reach third quarter.
                        break;
                    case 4:
                        new_c_image[i][j][k] = c_image[SIZE / 2 + i / 2][SIZE/2 + j / 2][k]; // (size / 2 + i) and (size / 2 + j) to reach fourth quarter.
                        break;
                }
            }
        }
    }
    for (int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            for(int k = 0; k < RGB; k++)
            c_image[i][j][k] = new_c_image[i][j][k];
        }
    }
}

//9.shrink image
void RGB_Shrink () {
    unsigned char image2[SIZE][SIZE][RGB];
    int choice;                    // read the user choice .
    cout << "\tfor 1/2 shrink photo select 1: \n";
    cout << "\tfor 1/3 shrink photo select 2:\n";
    cout << "\tfor 1/4 shrink photo select 3: \n";
    cin >> choice;
    for (int i = 0; i < SIZE; ++i) {       //make all pixels in image2
        for (int j = 0; j < SIZE; ++j) {    // array are white 255 .
            for (int k = 0; k < RGB; ++k) {
                image2[i][j][k] = 255;
            }
        }
    }
    if (choice == 1) {                   // 1/2 shrink photo .
        for (int i = 0; i < SIZE; i += 2) {
            for (int j = 0; j < SIZE; j += 2) {
                for (int k = 0; k < RGB; ++k) {
                    image2[i / 2][j / 2][k] = c_image[i][j][k];
                }
            }
        }

    } else if (choice == 2) {             // 1/3 shrink photo .
        for (int i = 0; i < SIZE; i += 3) {
            for (int j = 0; j < SIZE; j += 3) {
                for (int k = 0; k < RGB; ++k) {
                    image2[i / 3][j / 3][k] = c_image[i][j][k];
                }
            }
        }

    } else if (choice == 3) {            // 1/4 shrink photo .
        for (int i = 0; i < SIZE; i += 4) {
            for (int j = 0; j < SIZE; j += 4) {
                for (int k = 0; k < RGB; ++k) {
                    image2[i / 4][j / 4][k] =c_image[i][j][k];
                }
            }
        }

    }
    for (int i = 0; i < SIZE; i++) {   //save the new photo.
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; ++k) {
                new_c_image[i][j][k] = image2[i][j][k];
            }
        }
    }
}

// 10. Mirror :
void RGB_Mirror(){
    cout << "\nEnter The Number Of Part\n";
    cout << "(1) Left\n";
    cout << "(2) Right\n";
    cout << "(3) Upper\n";
    cout << "(4) Lower\n";
    int n;
    n = ReadIntNumberBetween(1,4);
    if(n == 1){
        for(int i = 0; i < SIZE; i++){
            for(int j = 0; j <= SIZE/2; j++){
                for(int k = 0; k < RGB; k++){ // loop over the left part 
                new_c_image[i][j][k] = c_image[i][j][k]; 
                new_c_image[i][SIZE-j][k] = c_image[i][j][k];} // make the most right = the left
            }
        }
    }
    else if(n == 2){
        for(int i = 0; i < SIZE; i++){
            for(int j = SIZE/2; j < SIZE; j++){
                for(int k = 0; k < RGB; k++){ // loop over the right part 
                new_c_image[i][SIZE-j][k] = c_image[i][j][k]; // make  the left = the right 
                new_c_image[i][j][k] = c_image[i][j][k];}
            }
        }
    }
    else if(n == 3){
        for(int i = 0; i <= SIZE/2; i++){ // loop over the upper part 
            for(int j = 0; j < SIZE; j++){
                for(int k = 0; k < RGB; k++){
                new_c_image[i][j][k] = c_image[i][j][k];
                new_c_image[SIZE-i][j][k] = c_image[i][j][k];} // make the most down = the upper
            }
        }
    }
    else {
        for(int i = SIZE/2; i < SIZE ; i++){ // loop over the lower part 
            for(int j = 0; j < SIZE; j++){
                for(int k = 0; k < RGB; k++){
                new_c_image[SIZE-i][j][k] = c_image[i][j][k]; // make the upper = the dowen  
                new_c_image[i][j][k] = c_image[i][j][k];}
            }
        }
    }
}

// 11. Shuffle Image :
void RGB_Shuffle(){
    int arr[4];
    cout << "\nNew order of quarters ? \n";
    cin >> arr[0] >> arr[1] >> arr[2] >> arr[3];
    for(int i = 0; i < SIZE / 2; i++){
        for(int j = 0; j < SIZE / 2; j++){
            for(int k = 0; k < RGB; k++){
                switch(arr[0]){ // first quarter of the new image.
                    case 1: // equal it with first quarter of the orignal image.
                        new_c_image[i][j][k] = c_image[i][j][k]; 
                        break;
                    case 2: // equal it with second quarter of the orignal image.     
                        new_c_image[i][j][k] = c_image[i][SIZE /2 + j][k];
                        break;
                    case 3: // equal it with third quarter of the orignal image.
                        new_c_image[i][j][k] = c_image[SIZE / 2 + i][j][k];
                        break;
                    case 4: // equal it with fourth quarter of the orignal image.
                        new_c_image[i][j][k] = c_image[SIZE / 2 + i][SIZE /2 + j][k];
                        break;
                }
                switch(arr[1]){ // second quarter of the new image.
                    case 1:
                        new_c_image[i][SIZE / 2 + j][k] = c_image[i][j][k];
                        break;
                    case 2:                        
                        new_c_image[i][SIZE / 2 + j][k] = c_image[i][SIZE /2 + j][k];
                        break;
                    case 3:
                        new_c_image[i][SIZE / 2 + j][k] = c_image[SIZE / 2 + i][j][k];
                        break;
                    case 4:
                        new_c_image[i][SIZE / 2 + j][k] = c_image[SIZE / 2 + i][SIZE /2 + j][k];
                        break;
                }
                switch(arr[2]){ // third quarter of the new image.
                    case 1:
                        new_c_image[SIZE / 2 + i][j][k] = c_image[i][j][k];
                        break;                    
                    case 2:                        
                        new_c_image[SIZE / 2 + i][j][k] = c_image[i][SIZE /2 + j][k];
                        break;
                    case 3:
                        new_c_image[SIZE / 2 + i][j][k] = c_image[SIZE / 2 + i][j][k];
                        break;
                    case 4:
                        new_c_image[SIZE / 2 + i][j][k] = c_image[SIZE / 2 + i][SIZE /2 + j][k];
                        break;
                }
                switch(arr[3]){ // fourth quarter of the new image.
                    case 1:
                        new_c_image[SIZE / 2 + i][SIZE /2 + j][k] = c_image[i][j][k];
                        break;                    
                    case 2:                        
                        new_c_image[SIZE / 2 + i][SIZE /2 + j][k] = c_image[i][SIZE /2 + j][k];
                        break;
                    case 3:
                        new_c_image[SIZE / 2 + i][SIZE /2 + j][k] = c_image[SIZE / 2 + i][j][k];
                        break;
                    case 4:
                        new_c_image[SIZE / 2 + i][SIZE /2 + j][k] = c_image[SIZE / 2 + i][SIZE /2 + j][k];
                        break;
                }
            }
        }
    }
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++) {
            for(int k = 0; k < RGB; k++)
                c_image[i][j][k] = new_c_image[i][j][k];
        }
    }
}

//12. blur image:
void RGB_Blur() {
    long long avg=0;
    for (int i = 0; i < SIZE; i++) {      //rows for loop.
        for (int j = 0; j < SIZE; j++) {  // columns for loop .
            for (int m=0;m<3;m++){
                for (int k = i; k < i+7; k++) {
                    for (int l = j; l < j+7; l++)  // iterate every 7*7 pixels .
                        avg+=(c_image[k][l][m]);
                }
                avg=avg/49;      // calculate the average " sum /49" .
               new_c_image[i][j][m]=avg;
                avg=0;
            }
        }
    }
}

// 13. Crop Image :
void RGB_Crop(){
    cout << "\nEnter The Starting Position\n";
    int x, y; 
    x = ReadIntNumber(); y = ReadIntNumber();
    cout << "\nEnter Width And Length\n";
    int w, l; 
    w = ReadIntNumber(); l = ReadIntNumber();
    for(int i = 0; i < SIZE; i++){ 
        for(int j = 0; j < SIZE; j++){
            for(int k = 0; k < RGB; k++){
            new_c_image[i][j][k] = 255;}
        }
    }
    for(int i = y; i < y+l; i++){ //start row = y, end row = l+y. looping over l rows make the length.
        for(int j = x; j < x+w; j++){
            for(int k = 0; k < RGB; k++){//start column = x, end column = x+w. looping over w columns make the width.
            new_c_image[i][j][k] = c_image[i][j][k];}
        }
    }
}

// 14. Skew image right :
void RGB_Skew_Right(){
    cout << "\nPlease enter degree to skew right :\n";
    double degree; 
    cin >> degree;
    degree = degree * M_PI / 180; // Turn angle to radian.
    double start = tan(degree) * 256; // The point where the first column of the new image will start with.
    double step = start / 256;        // A number that will be decreased from the start to skew the image.
    unsigned char temp_image[SIZE][SIZE + (int) start][RGB]; 
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE + (int) start; j++){
            for(int k = 0; k < RGB; k++)
                temp_image[i][j][k] = 255; // fill the pixels with white.
        }
    }
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            for(int k = 0; k < RGB; k++)
                temp_image[i][j + (int) start][k] = c_image[i][j][k]; 
        } // fill the temp image with the pixels of the original image.
        start -= step; // that will make the image reach last row.
    }
    start = tan(degree) * 256;
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE + (int) start; j++){
            for(int k = 0; k < RGB; k++)
            // filling the image with the pixels of the new image with making sure columns never exceed 255.
            new_c_image[i][(j * 255)/(255 + (int)start)][k] = temp_image[i][j][k];
        }
    }
    for (int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            for(int k = 0; k < RGB; k++)
            c_image[i][j][k] = new_c_image[i][j][k];
        }
    }
}

// 15. Skew image up :
    void RGB_Skew_Up() {
        cout << "Enter degree to skew up: \n";    //ask the user to enter the degree.
        double degree;
        cin >> degree;
        degree = degree * M_PI / 180;   // convert degrees to radians.
        double start = tan(degree) * 256;
        double step = tan(degree);
        unsigned char temp_image[SIZE + (int) start][SIZE][RGB];
        for (int i = 0; i < SIZE + (int) start; i++) {  //initialize the image with the white pixels 255.
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < RGB; k++)
            }         temp_image[i][j][k] = 255;
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < RGB; k++)
                    temp_image[j + (int) start][i][k] = image[j][i][k];
            }
            start -= step;  // decrease the _start_ value to skew the next row.
        }
        start = tan(degree) * 256;
        for (int i = 0; i < SIZE + (int) start; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < RGB; k++)
                    new_c_image[(i * 255) / ((int) start + 255)][j][k] =temp_image[i][j][k];
            }
        }
        for(int i = 0; i < SIZE; i++){
            for (int j = 0; j < SIZE; j++){
                for (int k = 0; k < RGB; k++){
                    c_image[i][j][k] = new_c_image[i][j][k];
            }
        }
    }

int Choice = 1;
void DoProcess(){
    cout << "\nPlease select a filter to apply or 0 to exit : \n";
    Choice = ReadIntNumberBetween(0,17);
    switch(Choice){
        case(1):
            RGB_Black_White();
            break; 
        case(2):
            RGB_Invert_Filter();
            break;
        case(3):
            RGB_Merge();
            break;
        case(4):
            RGB_Flip();
            break;
        case(5):
            RGB_Darken_And_Lighten_Image();
            break;
        case(6):
            RGB_Rotate();
            break;
        case(7):
            RGB_Edges();
            break;
        case(8):
            RGB_Enlarge();
            break;
        case(9):
           RGB_Shrink();
            break;
        case(10):
            RGB_Mirror();
            break;
        case(11):
            RGB_Shuffle();
            break;
        case(12):
            RGB_Blur();
            break;
        case(13):
           RGB_Crop();
            break;
        case(14):
            RGB_Skew_Right();
            break;
        case(15):
		RGB_Skew_Up();
            cout << 15;
            break;
        case(16):
            Save_RGB_Image();
            break;
        case(17):
            Open_RGB_Image();
            break;
        case(0):
            break;
    }
}

// view all filters:
void view(){

    cout << "\n1- Black & White Filter\n";
    cout << "2- Invert Filter\n";
    cout << "3- Merge Filter \n";
    cout << "4- Flip Image\n";
    cout << "5- Darken and Lighten Image \n";
    cout << "6- Rotate Image\n";
    cout << "7- Detect Image Edges \n";
    cout << "8- Enlarge Image\n";
    cout << "9- Shrink Image\n";
    cout << "10- Mirror 1/2 Image\n";
    cout << "11- Shuffle Image\n";
    cout << "12- Blur Image\n";
    cout << "13- Crop Image\n";
    cout << "14- Skew Image Right  \n";
    cout << "15- Skew Image Up  \n";
    cout << "16- Save the image to a file\n";
    cout << "17- Open Another image\n";
    cout << "0- Exit\n";

    DoProcess();
}

int main (){
    
    cout << "Welcome To Our Image Processing Tool.\n";
    Open_RGB_Image();
    while(Choice != 0)
        view (); 

}
