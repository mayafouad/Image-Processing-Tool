void skew(){
    Open_GS_Image();
    cout << "\nEnter degree : ";
    double degree; 
    cin >> degree;
    degree = degree * M_PI / 180;
    double mov = tan(degree) * 256;
    double step = mov / 256;
    unsigned char img[SIZE][SIZE + (int)mov];
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE + (int)mov; j++)
            img[i][j] = 255;
    }
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++)
            img[i][j + (int) mov] = image[i][j];
        mov -= step;
    }
    mov = tan(degree) * 256;
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE + (int)mov; j++)
            new_image[i][(j*255)/(255+(int)mov)] = img[i][j];
    }
    Save_GS_Image();
}
