#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <regex>
#include "./libs/parser.hpp"
#include "./libs/hash.hpp"
#include "./libs/trie.hpp"
#include <typeinfo>

using namespace aria::csv;
using namespace std;

int main(void){

    regex rgx1("user (\\d*)$"), rgx2("movie ([^\\n]*)$"), rgx3("tags ([^\\n]*)$"), rgx4("top(\\d*) \\'([^\\n]*)\\'$"), rgx5("year (\\d*)$"),
            rgxAux("\\'(.*?)\\'"), rgxAux2("\\s(\\d{4})"), rgAux3("\"|\\|(\\w+)\"|\\|");
    ifstream f1("./data/minirating.csv"), f2("./data/movie_clean.csv"), f3("./data/tag_clean.csv");
    CsvParser parser1(f1), parser2(f2), parser3(f3);
    vector<int> movies, sizes = { 1 , 1000000, int(sizeof(parser2)/sizeof(CsvParser)), 
                                int(sizeof(parser3)/sizeof(CsvParser))};
    bool first = true;
    int hash, id, date;
    float rating;
    string todo, split, noquote, genre, n;
    smatch matches;
    TrieNode *tree = novoNode(' ');
    ListNodeGenre *genTable[sizes[2]];
    ListNodeTag *tagTable[sizes[2]];
    ListNodeTitle *titleTable[sizes[0]], *aux;
    ListNodeUser *userTable[sizes[1]];
    vector<string> genres;

    // fase 1

    for (auto& row : parser1){                       // userId,movieId,rating,timestamp
        if (first)                                   // pula o header do arquivo
            { first = false; continue; }
        id = stoi(row[1]);
        rating = stof(row[2]);
        insertTitle(titleTable, id, "", genres, rating, -1, sizes[0]);
        insertUser(userTable, id, rating, stoi(row[0]), sizes[1]);
    }
    first = true;
    for(int j = 0; j < sizes[0]; j++){
        std::cout << titleTable[j]->movieId << "\n";
    }
    for (auto& row : parser2){                       //"movieId","title","genres"
        if (first)
            { first = false; continue; }
        id = stoi(row[0]);
        char * tab = new char [row[1].length()+1];
        strcpy (tab, row[1].c_str());
        insert(&tree, tab, id);

        aux=titleTable[Hash(id,sizes[0])];
        while(titleTable[Hash(id,sizes[0])]->next!=NULL && titleTable[Hash(id,sizes[0])]->movieId!=id){
            aux = titleTable[Hash(id,sizes[0])]->next;
        }
        if(aux->movieId==id && aux->date==-1){
            regex_match(row[1], matches, rgxAux2);
            date = stoi(matches[1]);
            regex_match(row[2], matches, rgAux3);
            for(int i = 1; i < matches.size(); i++){
                genres.push_back(matches[i]);
            }
            updateTitle(titleTable, id, row[1], genres, date, sizes[0]);
            for(auto& gen : genres){
                insertGenre(genTable,id,gen,sizes[2]);
            }
            genres.clear();
        }
    }
    first = true;
    for (auto& row : parser3){                       //"userId","movieId","tag","timestamp"
        if (first)
            { first = false; continue; }
        insertTag(tagTable, stoi(row[1]), row[2], sizes[2]);
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
            noquote = matches[1].str() + " ";
            char *mov = &noquote[0];
            TrieNode *subtree = search(tree, mov);
            if(subtree){
                get_all_ids(subtree, movies);
                for(auto& mov : movies){
                    std::cout << mov << "\n";
                }
                movies.clear();
            }
            else{
                std::cout << "Couldn't find match for the given preffix or name.\nPlease try again.\n";
            }

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
        else if(regex_match(todo, matches, rgx5)){   //year search
            std::cout << matches[1];
        }
        else{
            std::cout << "Invalid command, try again.\n";
        }
    }
    std::cout << "Goodbye :)\n";
}