#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <regex>
#include "./libs/parser.hpp"
#include "./libs/hash.hpp"
#include "./libs/trie.hpp"

using namespace aria::csv;

int main(void){

    std::vector<std::vector<std::vector<std::string>>> tables;
    std::vector<float> size;
    std::ifstream f1("./data/minirating.csv"), f2("./data/movie_clean.csv"), f3("./data/tag_clean.csv");
    CsvParser parser1(f1), parser2(f2), parser3(f3);
    bool first = true;

    // fase 1

    tables.resize(3);

    for (auto& row : parser1){
        if (first)                                   // pula o header do arquivo
            { first = false; continue; }
        tables[0].push_back({row[0],row[1],row[2]}); // insere na tabela a tupla
    first = true;
    for (auto& row : parser2){
        if (first)
            { first = false; continue; }
        std::cout << row[0] << " " << row[1] << " " << row[2];
        std::cout << std::endl;
    }
    first = true;
    for (auto& row : parser3){
        if (first)
            { first = false; continue; }
        std::cout << row[0] << " " << row[1] << " " << row[2] << " " << row[3];
        std::cout << std::endl;
    }
}