#include <iostream>
#include <fstream>
#include <string> 
#include <queue>
#include <unordered_map>



int main(){
    int numbOfGames, numbOfBags;
    std::string txt;

    std::cout << "Welche wundertuete.txt wollen Sie ausfuehren? 0, 1, 2, 3, 4, 5: ";
    std::cin >> txt;

    std::fstream sample("wundertuete" + txt + ".txt");
    sample >> numbOfBags >> numbOfGames;

    std::queue<int> games;
    int bags[numbOfBags][numbOfGames];

    for(int i = 0;i<numbOfBags;i++){
        for(int j = 0;j<numbOfGames;j++){
            bags[i][j] = 0;                //setzt alle Elemente von jeder Tasche auf 0
        }
    }
    //INPUT ANZAHL DER SPIELE
    int temp;
    for(int i = 0;i<numbOfGames;i++){
        sample >> temp;
        games.push(temp);
    }


    int first1 = 0;
    int second2 = 0;
    
    while(!games.empty()){
        int count = games.front() / numbOfBags;
        int count_rest = games.front() % numbOfBags;
        games.pop();
        
        if(count){
            for(int i = 0;i<numbOfBags;i++){
                bags[i][second2] += count;
            }
        }

        while(count_rest){
            first1 = first1 % numbOfBags;
            bags[first1][second2] +=1;
            count_rest--;
            first1++;
        }
        second2++;
    }

    //COUNT DER GLEICHEN TASCHEN BZW ARRAYS
    std::unordered_map<std::string, int> arrayCount;
    
    for(int i = 0; i < numbOfBags;i++){
        std::string key;
        for(int j = 0;j<numbOfGames;j++){
            key += std::to_string(bags[i][j]);
            if(j < numbOfGames-1){
                key+= " ,";
            }
        }
        arrayCount[key]++;
    }

    //PRINT ANZAHL DER GLEICHEN TASCHEN + DIE TASCHEN SELBER
    for(const auto&pair: arrayCount){
        std::string key_bags = pair.first;
        int count = pair.second;
        std::cout << count << "x : [" << key_bags << "]\n";
    }
}
