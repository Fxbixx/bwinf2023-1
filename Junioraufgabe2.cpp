#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using std::string;
using std::vector;


int main(){
    int maximumRowLenght, maximumColumnLenght;
    string tempStorage;

    int txt;
    std::cout << "Welches Bild soll entschluesselt werden?, 1,2,3,4,5,6,7: ";
    std::cin >> txt;
    std::fstream sampleImage("bild0" + std::to_string(txt) + ".ppm");
    sampleImage >> tempStorage >> maximumRowLenght >> maximumColumnLenght >> tempStorage;


    vector<vector<int>> image;
    vector<int> rgb(3);
    for(int i = 0; i<maximumRowLenght*maximumColumnLenght; i++){
        sampleImage >> rgb[0] >> rgb[1] >> rgb[2];
        image.push_back(rgb);
    }

    string word = "";

    int r;
    int g = 1;
    int b = 1;
    int currentRowPos = 0;
    int currentColumnPos = 0;
    
while(g!= 0 || b !=0){
    //Extrahiere die RGB-Werte des aktuellen Pixel
    r = image[currentColumnPos * maximumRowLenght + currentRowPos][0];
    g = image[currentColumnPos * maximumRowLenght + currentRowPos][1]; 
    b = image[currentColumnPos * maximumRowLenght + currentRowPos][2];

    //Ueberpruefe, ob der ASCII-Wert im gueltigem Bereich liegt
    if(r<128){
        word += char(r);
    }
    //Aktualisierung der Position fuer den naechsten Pixel
    currentRowPos = (currentRowPos + g) % maximumRowLenght;
    currentColumnPos = (currentColumnPos + b) % maximumColumnLenght;
}
    std::cout << word << '\n';
    std::system("pause");
}

