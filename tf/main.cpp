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

void swap(ListNodeTitle* a, ListNodeTitle* b)
{
    ListNodeTitle t = *a;
    *a = *b;
    *b = t;
}

int partition (vector<ListNodeTitle> arr, int low, int high)
{
    int pivot = arr[high].ratingTotal;
    int i = (low - 1);
 
    for (int j = low; j <= high- 1; j++)
    {
        if (arr[j].ratingTotal <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(vector<ListNodeTitle> arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int partitionR (vector<ListNodeTitle> arr, int low, int high)
{
    int pivot = arr[high].ratingTotal;
    int i = (low - 1);
 
    for (int j = low; j <= high- 1; j++)
    {
        if (arr[j].ratingTotal >= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSortR(vector<ListNodeTitle> arr, int low, int high)
{
    if (low < high)
    {
        int pi = partitionR(arr, low, high);
        quickSortR(arr, low, pi - 1);
        quickSortR(arr, pi + 1, high);
    }
}

void printn(vector<ListNodeTitle> movies, int n){
    std::cout << "Title |   Genres  |   Rating  |   Count\n";
    for(int h = 0; h < n; h++){
        std::cout << movies[h].title << "   |   ";
        for(auto& gen : movies[h].genres){
            std::cout << gen << "|";
        }
        std::cout << "  |   " << movies[h].rating << " |   " << movies[h].count << "\n"; 
    }
}

void movieSearch(ListNodeTitle *titleTable[], string genre, int n, int size, string type){
    ListNodeTitle *aux;
    vector<ListNodeTitle> movies;

    for(int k = 0; k < size; k++){
        aux = titleTable[k];
        do{
            for(int l=0; l<aux->genres.size() && aux->count>1000; l++){
                if(!genre.compare(aux->genres[l])){
                    movies.push_back(*aux);
                }
            }
            aux=aux->next;
        }while(aux != NULL);
    }
    if(!type.compare("shit")){
        quickSortR(movies, 0, movies.size()-1);
    }
    else{
        quickSort(movies, 0, movies.size()-1);
    }
    printn(movies,n);
}

void yearSearch(ListNodeTitle *titleTable[], int year, int size){
    ListNodeTitle *aux;

    std::cout << "movieId   |   Title |   Rating\n";
    for(int g = 0; g < size; g++){
        aux = titleTable[g];
        do{
            if(aux->date==year){
                std::cout << aux->movieId << "  |   ";
                std::cout << aux->title << "  |   ";
                std::cout << aux->rating << "  |   " << "\n";
            }
            aux=aux->next;
        }while(aux != NULL);
    }
}

int main(void){

    regex rgx1("user (\\d*)$"), rgx2("movie ([^\\n]*)$"), rgx3("tags ([^\\n]*)$"), rgx4("top(\\d*) \\'([^\\n]*)\\'$"), rgx5("year (\\d*)$"), 
            rgx6("shittiest(\\d*) \\'([^\\n]*)\\'$"), rgxAux("\\'(.*?)\\'");
    ifstream f1("./data/minirating.csv"), f2("./data/movie_clean.csv"), f3("./data/tag_clean.csv");
    CsvParser parser1(f1), parser2(f2), parser3(f3);
    vector<int> movies, sizes = { 1000 , 1000, 1000 };
    bool first = true;
    int hash, id, date;
    float rating;
    string todo, split, noquote, genre, n;
    smatch matches;
    TrieNode *tree = novoNode(' ');
    ListNodeTag *tagTable[sizes[2]], *aux3;
    ListNodeTitle *titleTable[sizes[0]], *aux;
    ListNodeUser *userTable[sizes[1]], *aux2;
    vector<string> genres, tags;

    // fase 1
    for(int u = 0; u<sizes[0]; u++){
        titleTable[u] = newNodoTitle(-1, " ", genres, -1, -1, false);
    }
    for(int u = 0; u<sizes[1]; u++){
        userTable[u] = newNodoUser(-1, -1, -1, false);
    }
    for(int u = 0; u<sizes[2]; u++){
        tagTable[u] = newNodoTag(-1, " ", false);
    }

    for (auto& row : parser1){                       // userId,movieId,rating,timestamp
        if (first)                                   // pula o header do arquivo
            { first = false; continue; }
        id = stoi(row[1]);
        rating = stof(row[2]);
        insertTitle(titleTable, id, "", genres, rating, -1, sizes[0]);
        insertUser(userTable, id, rating, stoi(row[0]), sizes[1]);
    }
    first = true;
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
            noquote = row[1];
            noquote.erase(0,row[1].size()-5);
            noquote.erase(noquote.size()-1,1);
            date = stoi(noquote);
            noquote = row[2];
            // std::cout << noquote << "\n";
            // while ((pos = noquote.find('|')) != string::npos) {
            //     noquote = noquote.substr(0, pos);
            //     std::cout << noquote << std::endl;
            //     noquote.erase(0, pos + 1);
            // } <------------------------------------------------------------------------------------------------------XXXX
            genres.push_back(noquote);
            updateTitle(titleTable, id, row[1], genres, date, sizes[0]);
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
            // hash = Hash(stoi(matches[1].str()),sizes[1]);
            // for(int i = 0; i < userTable[hash]->ls.movieId.size(); i++){
            //     std::cout << userTable[hash]->ls.rating[i] << "     ";
            //     aux = searchTitle(titleTable,userTable[hash]->ls.movieId[i], sizes[0]);
            //     std::cout << aux->title << "    " << aux->ratingTotal << "  " << aux->count << "\n" 
            // }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            // aux2 = searchUser(userTable, stoi(matches[1].str()), sizes[1]);
            // if(aux2){
            //     std::cout << "Rating        Title       Global      Count";
            //     for(int i = 0; i < aux2->ls.movieId.size(); i++){
            //         aux = searchTitle(titleTable, aux2->ls.movieId[i], sizes[0]);
            //         std::cout << userTable[hash]->ls.rating[i] << "     ";
            //         std::cout << aux->title << "    " << aux->rating << "  " << aux->count << "\n"; 
            //     }
            // }
            // else{
            //     std::cout << "No user found!\n";
            // }
        }
        else if(regex_match(todo, matches, rgx2)){   //movie search
            noquote = matches[1].str() + " ";
            char *mov = &noquote[0];
            TrieNode *subtree = search(tree, mov);
            if(subtree){
                std::cout << "  movieId   |       title       |       genres      | ratings |   count   \n";
                get_all_ids(subtree, movies);
                for(auto& mov : movies){
                    std::cout << mov << "\n";
                    // aux = searchTitle(titleTable, mov, sizes[0]);
                    // std::cout << aux->movieId << "  " << aux->title << "    ";
                    // for(int i = 0; i<aux->genres.size(); i++){
                    //     std::cout << aux->genres[i];
                    //     if(i!=aux->genres.size()-1){
                    //         std::cout << "|";
                    //     }
                    // }
                    // std::cout << "  " << aux->rating << "   " << aux->count << "\n";
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
                tags.push_back(noquote);
                split = matches.suffix();
            }
            std::cout << "      title       |       genres      |   rating  |   count   \n";
            for(int i = 0; i < tags.size(); i++){
                aux3 = searchTag(tagTable, tags[i], sizes[2]);
                if(aux3){
                    for(int j = 0; j < aux3->movieId.size(); j++){
                        aux = searchTitle(titleTable, aux3->movieId[j], sizes[0]);
                        if(aux){
                            std::cout << aux->title << "    |   ";
                            for(int l = 0; l < aux->genres.size(); l++){
                                std::cout << aux->genres[l];
                                if(l != aux->genres.size()-1){
                                    std::cout << "|";
                                }
                            }
                            std::cout << "  |   " << aux->rating << "   |   " << aux->count << "\n";
                        }
                    }
                }
            }
        }
        else if(regex_match(todo, matches, rgx4)){   //top nth from genre
            genre = matches[2];
            n = matches[1];
            movieSearch(titleTable, genre, stoi(n), sizes[0], "not");
        }
        else if(regex_match(todo, matches, rgx5)){   //year search
            yearSearch(titleTable, stoi(matches[1]),  sizes[0]);
        }
        else if(regex_match(todo, matches, rgx6)){  //shittiest search
            genre = matches[2];
            n = matches[1];
            movieSearch(titleTable, genre, stoi(n), sizes[0], "shit");

        }
        else{
            std::cout << "Invalid command, try again.\n";
        }
    }
    std::cout << "Goodbye :)\n";
    f1.close();
    f2.close();
    f3.close();
}