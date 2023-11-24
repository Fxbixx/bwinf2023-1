#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>

using std::vector;
using std::string;

const int BAUSTEIN_BREITE = 2;

//FUNKTION FUER DIE VERSCHIEDENEN ZUSTAENDE DER LAMPEN
vector<string> binary(int n){   //n ist die Anzhal der Q's
    vector<string> possibilities;
    vector<bool> s(n, 0);
    string a;
    for(int i = 0;i < (1 << n); i++){
        for(int j = n - 1; j>=0;j--){
            s[j] = (( i >> (n-1-j)) & 1);
        }
        a = "";
        for(bool bit: s){
            a += (bit ? '1' : '0');
        }
        possibilities.push_back(a);
    }
    return possibilities;
}

//FUNKTION FUER "BB"
std::pair<int,int> blue(int l1, int l2){
    int b1 = 0;
    int b2 = 0;
    if(l1){
        b1 = 1;
    }
    if(l2){
        b2 = 1;
    }
    return std::make_pair(b1,b2);
}

//FUNKTION FUER "Rr"
std::pair<int,int> redR(int l1, int l2){
    int b1 = 0;
    int b2 = 0;
    if(!l1){
        b1 = 1;
        b2 = 1;
    }
    return std::make_pair(b1,b2);
}

//FUNKTION FUER "rR"
std::pair<int,int> redr(int l1, int l2){
    int b1 = 0;
    int b2 = 0;
    if(!l2){
        b1 = 1;
        b2 = 1;
    }
    return std::make_pair(b1,b2);
}

//FUNKTION FUER "WW"
std::pair<int, int> white(int l1, int l2){
    if(l1 && l2){
        return std::make_pair(0,0);
    }
    else{
        return std::make_pair(1,1);
    }
}


//PRINTET FUER JEDEN ZUSTAND DEN ZUGEHOERIGEN ZUSTAND DER L's AUS
void solve(string condition, vector<int> pos_q, vector<int> pos_l, int width, int height,vector<vector<char>> nandu){
    std::pair<int,int> w;
    std::pair<int,int> b;
    std::pair<int,int> r;
    std::pair<int,int> R;

    vector<int> currentBitmask(width, 0);
    vector<int> previusBitmask(width, 0);

    for(int i = 0;i<pos_q.size();i++){
        currentBitmask[pos_q[i]] = condition[i]-48;
        previusBitmask[pos_q[i]] = condition[i]-48;
    }

    int currentPosWidth;
    for(int currentPosHeight = 1;currentPosHeight<height-1;currentPosHeight++){
        currentPosWidth = 0;
        while(currentPosWidth<width){
            switch (nandu[currentPosHeight][currentPosWidth]){
                case 'X':
                    currentBitmask[currentPosWidth] = 0;
                    currentPosWidth++;
                    break;
                case 'W':
                    w = {white(previusBitmask[currentPosWidth], previusBitmask[currentPosWidth+1])};
                    currentBitmask[currentPosWidth] = w.first;
                    currentBitmask[currentPosWidth+1] = w.second;
                    currentPosWidth+=BAUSTEIN_BREITE;
                    break;
                case 'B':
                    b = {blue(previusBitmask[currentPosWidth], previusBitmask[currentPosWidth+1])};
                    currentBitmask[currentPosWidth] = b.first;
                    currentBitmask[currentPosWidth+1] = b.second;
                    currentPosWidth+=BAUSTEIN_BREITE;
                    break;
                case 'R':
                    R = {redR(previusBitmask[currentPosWidth], previusBitmask[currentPosWidth+1])};
                    currentBitmask[currentPosWidth] = R.first;
                    currentBitmask[currentPosWidth+1] = R.second;
                    currentPosWidth+=BAUSTEIN_BREITE;
                    break;
                case 'r':
                    r = {redr(previusBitmask[currentPosWidth], previusBitmask[currentPosWidth+1])};
                    currentBitmask[currentPosWidth] = r.first;
                    currentBitmask[currentPosWidth+1] = r.second;
                    currentPosWidth+=BAUSTEIN_BREITE;
                    break;
            }
            previusBitmask = currentBitmask;
        }
    }
    string end = "";
    for(int i = 0;i<pos_l.size();i++){
        end += std::to_string(previusBitmask[pos_l[i]]);
    }
    std::cout << condition << " => " << end <<'\n';
    return;
}

int main(){
    string txt;
    std::cout << "Welche Nandu-Datei moechtest du ausfuehren? 1, 2, 3, 4, 5: ";
    std::cin >> txt;
    std::fstream sample("nandu" + txt + ".txt");

    int width, height;
    sample >> width >> height;

    vector<vector<char>> nandu(height, vector<char>(width));

    vector<int> pos_q;
    vector<int> pos_l;
    char temp;

    //INPUT + INFORMATION UEBER Q UND L
    for(int i = 0; i<height;i++){
        for(int j = 0;j<width;j++){
            sample >> nandu[i][j];

            if(nandu[i][j] == 'Q'){
                pos_q.push_back(j);
                sample >> temp;
            }
            if(nandu[i][j] == 'L'){
                pos_l.push_back(j);
                sample >> temp;
            }
        }
    }

    vector<string> possibilities = binary(pos_q.size());

    for(string s:possibilities){
        solve(s, pos_q, pos_l, width, height, nandu);
    }

    std::system("pause");
}
