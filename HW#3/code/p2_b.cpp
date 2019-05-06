// HW#3 Prob.2.(b)
// defect detection and correction
// Submissioin Date: March.03
// USCID: 8372-7611-20
// Name: Wenjun Li

// 1 input image: deer.raw
// 3 output images: deer_shrinking.raw, deer_correction.raw, deer_defect_detection.raw

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <typeinfo>
#include <cstring>
#include <cmath>
#include <sstream>
#include <iostream>

using namespace std;

int HitOrMiss(string pixel_stream,string mask[], int size){
    int i;
    for(i=0;i<size;i++){
        if(pixel_stream.compare(mask[i]) == 0){
            return 1;
        }
    }
    return 0;
}

int output_logic(int X, int M, int P){
    /**
     * @ input: X, M, P
     * @ output: G
     * return the final result of S/T
     */
    int G = 0;
    if(( (X == 1) && (!M || P)) == 1)
    {
        G = 255;
    }
    return G;
}

int main(int argc, char *argv[]) {

    FILE *file;
    int BytesPerPixel = 1;
    int size_r = 691;
    int size_c = 550;
    unsigned char Imagedata[size_r][size_c][BytesPerPixel];

    if (!(file=fopen("/Users/wenjun/ee569/hw3/deer.raw","rb"))) {
        cout << "Cannot open file: " <<endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), 691*550*1, file);
    fclose(file);

    //////////////////////////////////////////// ... Masks ... /////////////////////////////////////////////////
    string con_mask[58] = {"001010000", "100010000", "000010100", "000010001", "000011000", "010010000", "000110000", "000010010",
                           "001011000", "011010000", "110010000", "100110000", "000110100", "000010110", "000010011", "000011001",
                           "001011001", "111010000", "100110100", "000010111", "110011000", "010011001", "011110000", "001011010",
                           "011011000", "110110000", "000110110", "000011011", "110011001", "011110100", "111011000", "011011001",
                           "111110000", "110110100", "100110110", "000110111", "000011111", "001011011", "111011001", "111110100",
                           "100110111", "001011111", "011011011", "111111000", "110110110", "000111111", "111011011", "011011111",
                           "111111100", "111111001", "111110110", "110110111", "100111111", "001111111", "111011111", "111111101",
                           "111110111", "101111111"};

    string uncon_mask[332]={"101110111", "101111101", "111011101", "101111101", "101111001", "101110110", "100011111", "001011111",
                            "101111010", "100111110", "010011111", "001111011", "101111011", "101111110", "110011111", "001111111",
                            "101111100", "100110111", "001011111", "101011011", "101111101", "101110111", "101011111", "101011111",
                            "101111110", "100111111", "011011111", "101111011", "101111111", "101111111", "111011111", "101111111",
                            "111010001", "111010100", "100110101", "011010101", "111010010", "110011100", "010110101", "011110001",
                            "111010011", "111011100", "110110101", "011110101", "111010100", "110010101", "001110101", "111010001",
                            "111010101", "111010101", "101110101", "111010101", "111010110", "110011101", "011110101", "111110001",
                            "001010000", "100010000", "000010010", "000011000", "001011000", "011010000", "110010000", "100110000",
                            "000010110", "000010011", "000011001", "011110000", "110011000", "010011001", "001011010", "011010100",
                            "001011100", "110110001", "110010001", "100110001", "001110110", "001110100", "001010110", "100011011",
                            "100001011", "110110000", "110110001", "110110010", "110110011", "110110100", "110110101", "110110110",
                            "110111000", "110111001", "110111010", "110111011", "110111100", "110111101", "110111110", "110111111",
                            "111110000", "111110001", "111110010", "111110011", "111110100", "111110101", "111110110", "111110111",
                            "111111000", "111111001", "111111010", "111111011", "111111100", "111111101", "111111110", "111111111",
                            "010111000", "010111000", "000111010", "000111010", "010110010", "010110010", "010011010", "010011010",
                            "010111100", "010111001", "000111011", "000111110", "011110010", "010110011", "010011011", "011011010",
                            "110111000", "011111000", "001111010", "100111010", "110110010", "010110110", "010011110", "110011010",
                            "110111100", "011111001", "001111011", "100111110", "111110010", "010110111", "010011111", "111011010",
                            "111011100", "110010111", "001110111", "111010011", "111011101", "111010111", "101110111", "111010111",
                            "111011110", "110011111", "011110111", "111110011", "111011111", "111011111", "111110111", "111110111",
                            "111110001", "111110100", "100111101", "011011101", "111110010", "110111100", "010111101", "011111001",
                            "111110011", "111111100", "110111101", "011111101", "111110100", "110110101", "001111101", "111011001",
                            "111110101", "111110101", "101111101", "111011101", "111110110", "110111101", "011111101", "111111001",
                            "101010001", "101010100", "100010101", "001010101", "101010010", "100011100", "010010101", "001110001",
                            "101010011", "101011100", "110010101", "001110101", "101010100", "100010101", "001010101", "101010001",
                            "101010101", "101010101", "101010101", "101010101", "101010110", "100011101", "011010101", "101110001",
                            "101011110", "100011111", "011010111", "101110011", "101011111", "101011111", "111010111", "101110111",
                            "101110001", "101110100", "100011101", "001011101", "101110010", "100111100", "010011101", "001111001",
                            "101110011", "101111100", "110011101", "001111101", "101110100", "100110101", "001011101", "101011001",
                            "101110101", "101110101", "101011101", "101011101", "101110110", "100111101", "011011101", "101111001",
                            "111110111", "111111101", "111111101", "111111101", "111111001", "111110110", "100111111", "011011111",
                            "111111010", "110111110", "010111111", "011111011", "111111011", "111111110", "110111111", "011111111",
                            "101010111", "101011101", "111010101", "101110101", "000110100", "011011100", "100011001", "110110111",
                            "111010111", "111011101", "111110101", "111110101", "111011001", "111010110", "100110111", "011010111",
                            "111011010", "110011110", "010110111", "011110011", "111011011", "111011110", "110110111", "011110111",
                            "101010011", "101011101", "101010111", "101010111", "101010111", "111111100", "110110111", "001111111",
                            "111011011", "111111101", "111110111", "101111111", "111011111", "011110101", "101110011", "101011110",
                            "111111110", "110111111", "011111111", "111111011", "101011001", "101010110", "100010111", "001010111",
                            "101011010", "100011110", "010010111", "001110011", "101011011", "101011110", "110010111", "001110111",
                            "101011100", "100010111", "001010111", "111111111", "111111111", "111111111", "111111111", "110011101",
                            "010011100", "010110001", "001110010", "100011010", "010011101", "010110101", "001110011", "100011110",
                            "110011100", "011110001", "101110010", "101011010"};

    //////////////////////////////////////////// ... STK ... /////////////////////////////////////////////////
    int i, j, iter ;
    int Size_R = size_r + 2;
    int Size_C = size_c + 2;
    unsigned char img_extd[Size_R][Size_C][BytesPerPixel]; unsigned char output[size_r][size_c][1];
    unsigned char correction[size_r][size_c][1];
    int bond_map[size_r][size_c];// store bond number
    int m[Size_R][Size_C];       // extended mark map
    int M[size_r][size_c];       // mark map
    int P[Size_R][Size_C];       // P map
    string mark_stream;

    // convert original image to binary image
    for (i = 0; i < size_r; i++) {
        for (j = 0; j < size_c; j++) {
            correction[i][j][0] = Imagedata[i][j][0];
            Imagedata[i][j][0] = 255 - Imagedata[i][j][0];
        }
    }

    // convert original image to binary image
    for (i = 1; i < Size_R - 1; i++) {
        for (j = 1; j < Size_C - 1; j++) {
            if(Imagedata[i-1][j-1][0] == 255) { img_extd[i][j][0]=1; }
            else { img_extd[i][j][0]=0; }
        }
    }

    // ... Shrinking ...
    for(iter=0;iter<150;iter++)
    {
        // compute mark stream
        for (i = 1; i < size_r-1; i++) {
            for (j = 1; j < size_r-1; j++) {
                if (img_extd[i][j][0] == 1)
                {
                    bond_map[i - 1][j - 1] = 2*(img_extd[i-1][j][0]+img_extd[i][j+1][0]+img_extd[i][j-1][0]+img_extd[i+1][j][0])
                                             +(img_extd[i-1][j-1][0]+ img_extd[i-1][j+1][0]+img_extd[i+1][j-1][0]+img_extd[i + 1][j + 1][0]);
                }
                else { bond_map[i - 1][j - 1] = 0; }

                if (bond_map[i][j] != 0) {
                    M[i][j] = HitOrMiss((to_string(img_extd[i][j][0]) + to_string(img_extd[i][j+1][0]) + to_string(img_extd[i][j+2][0])
                                         + to_string(img_extd[i+1][j][0]) + to_string(img_extd[i+1][j+1][0]) + to_string(img_extd[i+1][j+2][0])
                                         + to_string(img_extd[i+2][j][0]) + to_string(img_extd[i+2][j+1][0]) + to_string(img_extd[i+2][j+2][0])), con_mask, 58);
                }
                else { M[i][j] = 0; }
            }
        }

        // put extended mark map to true size mark map
        for (i = 1; i < Size_R - 1; i++) {
            for (j = 1; j < Size_C - 1; j++) {
                m[i][j] = M[i - 1][j - 1];
            }
        }

        // compute P map
        for (i = 1; i < Size_R - 1; i++) {
            for (j = 1; j < Size_C - 1; j++) {
                mark_stream = to_string(m[i-1][j-1]) + to_string(m[i-1][j]) + to_string(m[i-1][j+1])
                              + to_string(m[i][j - 1]) + to_string(m[i][j]) + to_string(m[i][j + 1])
                              + to_string(m[i+1][j-1]) + to_string(m[i+1][j]) + to_string(m[i+1][j+1]);
                if (m[i][j] == 1) { P[i - 1][j - 1] = HitOrMiss(mark_stream, uncon_mask, 332); }
            }
        }

        // output
        for(i=0;i<size_r;i++) {
            for(j=0;j<size_c;j++) {
                output[i][j][0] = (unsigned char) output_logic(img_extd[i+1][j+1][0], M[i][j], P[i][j]);
                if(output[i][j][0] == 255) {img_extd[i+1][j+1][0] = 1;}
                else { img_extd[i+1][j+1][0] = 0;}
            }
        }

        // return to top, loop again
    }

    // output shrinking result image
    if (!(file=fopen("/Users/wenjun/ee569/hw3/deer_shrinking.raw","wb"))) {
        cout << "Cannot open file: " << endl;
        exit(1);
    }
    fwrite(output, sizeof(unsigned char), 691*550*1, file);
    fclose(file);


    // output correction result image
    for(i=0;i<size_r;i++){
        for(j=0;j<size_c;j++){
            if(output[i][j][0]==255 && output[i-1][j-1][0]==0 && output[i-1][j][0]==0 && output[i-1][j+1][0]==0 && output[i][j-1][0]==0 && output[i][j+1][0]==0 && output[i+1][j-1][0]==0 && output[i+1][j][0]==0 && output[i+1][j+1][0]==0)
            {
               correction[i][j][0] = 255;
            }

            if(correction[i][j][0]==255 && correction[i-1][j-1][0]==0 && correction[i-1][j][0]==0 && correction[i-1][j+1][0]==0 && correction[i][j-1][0]==0 && correction[i][j+1][0]==0 && correction[i+1][j-1][0]==0 && correction[i+1][j][0]==0 && correction[i+1][j+1][0]==0)
            {
                correction[i][j][0] = 0;
            }

        }
    }
    if (!(file=fopen("/Users/wenjun/ee569/hw3/deer_correction.raw","wb"))) {
        cout << "Cannot open file: " << endl;
        exit(1);
    }
    fwrite(correction, sizeof(unsigned char), 691*550*1, file);
    fclose(file);

    // output defect detection result image with a square around the defect
    for(i=0;i<size_r;i++){
        for(j=0;j<size_c;j++){
            if(output[i][j][0]==255 && output[i-1][j-1][0]==0 && output[i-1][j][0]==0 && output[i-1][j+1][0]==0 && output[i][j-1][0]==0 && output[i][j+1][0]==0 && output[i+1][j-1][0]==0 && output[i+1][j][0]==0 && output[i+1][j+1][0]==0)
            {
                correction[i-3][j-3][0] = 0; correction[i-3][j-2][0] = 0; correction[i-3][j-1][0] = 0; correction[i-3][j][0] = 0; correction[i-3][j+1][0] = 0; correction[i-3][j+2][0] = 0; correction[i-3][j+3][0] = 0;
                correction[i-2][j-3][0] = 0;                                                                                                                                                correction[i-2][j+3][0] = 0;
                correction[i-1][j-3][0] = 0;                                                                                                                                                correction[i-1][j+3][0] = 0;
                correction[i][j-3][0] = 0;                                                                                                                                                  correction[i][j+3][0] = 0;
                correction[i+1][j-3][0] = 0;                                                                                                                                                correction[i+1][j+3][0] = 0;
                correction[i+2][j-3][0] = 0;                                                                                                                                                correction[i+2][j+3][0] = 0;
                correction[i+3][j-3][0] = 0; correction[i+3][j-2][0] = 0; correction[i+3][j-1][0] = 0; correction[i+3][j][0] = 0; correction[i+3][j+1][0] = 0; correction[i+3][j+2][0] = 0; correction[i+3][j+3][0] = 0;

                correction[i][j][0] = 0;
            }

            if(correction[i][j][0]==255 && correction[i-1][j-1][0]==0 && correction[i-1][j][0]==0 && correction[i-1][j+1][0]==0 && correction[i][j-1][0]==0 && correction[i][j+1][0]==0 && correction[i+1][j-1][0]==0 && correction[i+1][j][0]==0 && correction[i+1][j+1][0]==0)
            {
                correction[i][j][0] = 0;
            }
        }
    }

    if (!(file=fopen("/Users/wenjun/ee569/hw3/deer_defect_detection_square.raw","wb"))) {
        cout << "Cannot open file: " << endl;
        exit(1);
    }
    fwrite(correction, sizeof(unsigned char), 691*550*1, file);
    fclose(file);

    return 0;
}

