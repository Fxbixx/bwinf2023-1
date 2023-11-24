#include <iostream>
#include <fstream>
#include <string> 
#include <queue>
#include <unordered_map>



int main(){
    int numOfGames, numOfBags;
    std::string txt;

    std::cout << "Welche wundertuete.txt wollen Sie ausfuehren? 0, 1, 2, 3, 4, 5: ";
    std::cin >> txt;

    std::fstream sample("wundertuete" + txt + ".txt");
    sample >> numOfBags >> numOfGames;

    std::queue<int> games;
    int bags[numOfBags][numOfGames];

    for(int i = 0;i<numOfBags;i++){
        for(int j = 0;j<numOfGames;j++){
            bags[i][j] = 0;                //setzt alle Elemente von jeder Tasche auf 0
        }
    }
    //INPUT ANZAHL DER SPIELE
    int tempInput;
    for(int i = 0;i<numOfGames;i++){
        sample >> tempInput;
        games.push(tempInput);
    }
    
    int currentBag = 0;
    int currentGame = 0;
    
    while(!games.empty()){
        int count = games.front() / numOfBags;
        int remainderCount = games.front() % numOfBags;
        games.pop();
        
        if(count){
            for(int i = 0;i<numOfBags;i++){
                bags[i][currentGame] += count;
            }
        }

        while(remainderCount){
            currentBag = currentBag % numOfBags;
            bags[currentBag][currentGame] +=1;
            remainderCount--;
            currentBag++;
        }
        currentGame++;
    }

    //COUNT DER GLEICHEN TASCHEN BZW ARRAYS
    std::unordered_map<std::string, int> arrayCount;
    
    for(int i = 0; i < numOfBags;i++){
        std::string key;
        for(int j = 0;j<numOfGames;j++){
            key += std::to_string(bags[i][j]);
            if(j < numOfGames-1){
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
    std::system("pause");
}
