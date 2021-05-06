#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <regex>
#include "./libs/parser.hpp"
#include "./libs/hash.hpp"
#include "./libs/trie.hpp"

using namespace aria::csv;
using namespace std;

int main(void){

    vector<vector<vector<string>>> tables;
    vector<float> size;
    regex rgx1("user (\\d*)$"), rgx2("movie ([^\\n]*)$"), rgx3("tags ([^\\n]*)$"), rgx4("top(\\d*) \\'([^\\n]*)\\'$"), rgxAux("\\'(.*?)\\'");
    ifstream f1("./data/minirating.csv"), f2("./data/movie_clean.csv"), f3("./data/tag_clean.csv");
    CsvParser parser1(f1), parser2(f2), parser3(f3);
    bool first = true;
    int hash;
    string todo, split, noquote, genre, n;
    smatch matches;

    // fase 1

    tables.resize(3);

    for (auto& row : parser1){
        if (first)                                   // pula o header do arquivo
            { first = false; continue; }
        // hash = 
        // tables[0].push_back({row[0],row[1],row[2]}); // insere na tabela a tupla
    }
    first = true;
    for (auto& row : parser2){
        if (first)
            { first = false; continue; }
        // std::cout << row[0] << " " << row[1] << " " << row[2];
        // std::cout << endl;
    }
    first = true;
    for (auto& row : parser3){
        if (first)
            { first = false; continue; }
        // std::cout << row[0] << " " << row[1] << " " << row[2] << " " << row[3];
        // std::cout << endl;
    }

    // fase 2

    while(true){
        std::cout << "What do you want to do?\n(X) - Exit\n";
        getline(cin,todo);

        if (!todo.compare("X") or !todo.compare("x")){
            break;
        }
        else if(regex_match(todo, matches, rgx1)){   //user ratings
            std::cout << matches[1];
        }
        else if(regex_match(todo, matches, rgx2)){   //movie search
            std::cout << matches[1];
        }
        else if(regex_match(todo, matches, rgx3)){   //tag search
            split = matches[1];
            while(regex_search(split, matches, rgxAux))
            {
                noquote = matches[0];
                noquote.erase(0,1);
                noquote.erase(noquote.size()-1,1);
                std::cout << noquote << std::endl;
                split = matches.suffix();
            }
        }
        else if(regex_match(todo, matches, rgx4)){   //top nth from genre
            std::cout << matches[1] << "|" << matches[2] << "\n";
            genre = matches[2];
            n = matches[1];
            for(int j = 0; j < stoi(n); j++){
                std::cout << j;
            }
        }
        else{
            std::cout << "Invalid command, try again.\n";
        }
    }
    std::cout << "Goodbye :)\n";
}