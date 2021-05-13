#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <regex>
#include "./libs/parser.hpp"
#include "./libs/hash.hpp"
#include "./libs/trie.hpp"
#include <chrono>

using namespace aria::csv;
using namespace std;
using namespace std::chrono;

void swap(ListNodeTitle* a, ListNodeTitle* b)
{
    ListNodeTitle t = *a;
    *a = *b;
    *b = t;
}

int partition (vector<ListNodeTitle>& arr, int low, int high)
{
    float pivot = arr[high].rating;
    int i = (low - 1);
 
    for (int j = low; j <= high- 1; j++)
    {
        if (arr[j].rating >= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(vector<ListNodeTitle>& arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int partitionR (vector<ListNodeTitle>& arr, int low, int high)
{
    float pivot = arr[high].rating;
    int i = (low - 1);
 
    for (int j = low; j <= high- 1; j++)
    {
        if (arr[j].rating <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSortR(vector<ListNodeTitle>& arr, int low, int high)
{
    if (low < high)
    {
        int pi = partitionR(arr, low, high);
        quickSortR(arr, low, pi - 1);
        quickSortR(arr, pi + 1, high);
    }
}

void printn(vector<ListNodeTitle> movies, int n){
    string genre;
    int colWidth = 15;

    cout << setfill('*') << setw(12*colWidth) << "*" << endl;
    cout << setfill(' ') << fixed;
    cout << setw(6*colWidth) << "Title" << setw(3*colWidth) << "Genres" << setw(colWidth) << "Ratings"
            << setw(colWidth) << "Count" << endl;
    cout << setfill('*') << setw(12*colWidth) << "*" << endl; 
    cout << setfill(' ') << fixed;
    // std::cout << "      Title     |       Genres    |   Rating  |   Count \n";
    
    for(int h = 0; h < n; h++){
        genre.clear();
        // std::cout << movies[h].title << "   |   ";
        for(auto& gen : movies[h].genres){
            genre+=gen+"|";
            // std::cout << gen << "|";
        }
        // std::cout << "  |   " << movies[h].rating << " |   " << movies[h].count << "\n"; 
        cout << setw(6*colWidth) << movies[h].title << setw(3*colWidth) << genre << setw(colWidth) << setprecision(2) << movies[h].rating
            << setw(colWidth) << movies[h].count << endl;
    }
}

void movieSearch(ListNodeTitle *titleTable[], string genre, int n, int size, string type){
    ListNodeTitle *aux;
    vector<ListNodeTitle> movies;

    for(int k = 0; k < size; k++){
        aux = titleTable[k];
        do{
            for(int l=0; l<aux->genres.size() && aux->count>1000; l++){
            // for(int l=0; l<aux->genres.size(); l++){
                if(!genre.compare(aux->genres[l])){
                    movies.push_back(*aux);
                }
            }
            aux=aux->next;
        }while(aux != NULL);
    }
    if(!movies.size()){
        std::cout << "No movies found!\n";
        return;
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
    int colWidth = 15;

    cout << setfill('*') << setw(10*colWidth) << "*" << endl;
    cout << setfill(' ') << fixed;
    cout << setw(colWidth) << "MovieId" << setw(6*colWidth) << "Title" << setw(colWidth) << "Ratings" << setw(colWidth) << "Count" << endl;
    cout << setfill('*') << setw(10*colWidth) << "*" << endl; 
    cout << setfill(' ') << fixed;

    // std::cout << "movieId   |   Title |   Rating\n";
    for(int g = 0; g < size; g++){
        aux = titleTable[g];
        do{
            if(aux->date==year){
                cout << setw(colWidth) << aux->movieId << setw(6*colWidth) << aux->title << setw(colWidth) << setprecision(2) << aux->rating
            << setw(colWidth) << aux->count << endl;

                // std::cout << aux->movieId << "  |   ";
                // std::cout << aux->title << "  |   ";
                // std::cout << aux->rating << "  |   " << "\n";
            }
            aux=aux->next;
        }while(aux != NULL);
    }
}

int main(void){

    regex rgx1("user (\\d*)$"), rgx2("movie ([^\\n]*)$"), rgx3("tags ([^\\n]*)$"), rgx4("top(\\d*) \\'([^\\n]*)\\'$"), rgx5("year (\\d*)$"), 
            rgx6("shit(\\d*) \\'([^\\n]*)\\'$"), rgxAux("\\'(.*?)\\'");
    ifstream f1("./data/rating.csv"), f2("./data/movie_clean.csv"), f3("./data/tag_clean.csv");
    CsvParser parser1(f1), parser2(f2), parser3(f3);
    vector<int> movies, sizes = { 105019 , 180001, 50671 };
    bool first = true;
    int hash, id, date, pos, tam, auxI, colWidth = 15;
    float rating;
    string todo, split, noquote, genre, n;
    smatch matches;
    TrieNode *tree = novoNode(' ');
    ListNodeTag *tagTable[sizes[2]], *aux3;
    ListNodeTitle *titleTable[sizes[0]], *aux;
    ListNodeUser *userTable[sizes[1]], *aux2;
    vector<string> genres, tags;
    auto start = high_resolution_clock::now();

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
            try{
                date = stoi(noquote);
            } catch(invalid_argument e){
                date = 0;
            }
            noquote = row[2];

            tam = 0;
            auxI = -1;
            while(tam > auxI){
                auxI = tam;
                pos = noquote.find("|", tam);
                genres.push_back(noquote.substr(tam, pos-tam));
                tam = pos+1;
            }

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

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Tempo de pre-processamento: " << (float)duration.count()/1000000 << " segundos"<< endl;

    // fase 2
    while(true){
        std::cout << "What do you want to do?\n(X) - Exit\n";
        getline(cin,todo);

        if (!todo.compare("X") or !todo.compare("x")){
            break;
        }
        else if(regex_match(todo, matches, rgx1)){   //user ratings
            aux2 = searchUser(userTable, stoi(matches[1].str()), sizes[1]);
            if(aux2){
                cout << setfill('*') << setw(10*colWidth) << "*" << endl;
                cout << setfill(' ') << fixed;
                cout << setw(colWidth) << "Rating" << setw(6*colWidth) << "Title" << setw(colWidth) << "Global" << setw(colWidth) << "Count" << endl;
                cout << setfill('*') << setw(10*colWidth) << "*" << endl; 
                cout << setfill(' ') << fixed; 
                
                // std::cout << "  Rating    |       Title       |       Global  |   Count   \n";
                for(int i = 0; i < aux2->ls.movieId.size(); i++){
                    aux = searchTitle(titleTable, aux2->ls.movieId[i], sizes[0]);
                    cout << setprecision(1) << setw(colWidth) << aux2->ls.rating[i] << setw(6*colWidth) << aux->title << setw(colWidth) << setprecision(2)
                     << aux->rating << setw(colWidth) << aux->count << endl; 

                    // std::cout << aux2->ls.rating[i] << "    |   ";
                    // std::cout << aux->title << "    |   " << aux->rating << "   |   " << aux->count << "\n"; 
                }
            }
            else{
                std::cout << "No user found!\n";
            }
        }
        else if(regex_match(todo, matches, rgx2)){   //movie search
            noquote = matches[1].str();
            char *mov = &noquote[0];
            TrieNode *subtree = search(tree, mov);
            if(subtree){
                cout << setfill('*') << setw(13*colWidth) << "*" << endl;
                cout << setfill(' ') << fixed;
                cout << setw(colWidth) << "MovieId" << setw(6*colWidth) << "Title" << setw(3*colWidth) << "Genres" << setw(colWidth) << "Ratings"
                        << setw(colWidth) << "Count" << endl;
                cout << setfill('*') << setw(13*colWidth) << "*" << endl; 
                cout << setfill(' ') << fixed;

                // std::cout << "  movieId   |       title       |       genres      | ratings |   count   \n";
                get_all_ids(subtree, movies);
                for(auto& mov : movies){
                    aux = searchTitle(titleTable, mov, sizes[0]);
                    if(aux){
                        cout << setw(colWidth) << aux->movieId << setw(6*colWidth) << aux->title << setw(3*colWidth);
                        genre.clear();
                        // std::cout << aux->movieId << "  |   " << aux->title << "    |   ";
                        for(int i = 0; i<aux->genres.size(); i++){
                            genre += aux->genres[i];
                            // std::cout << aux->genres[i];
                            if(i!=aux->genres.size()-1){
                                genre += "|";
                            }
                        }
                        cout << genre << setw(colWidth) << aux->rating << setw(colWidth) << aux->count << endl;
                        genre.clear();
                        // std::cout << "  |   " << aux->rating << "   |   " << aux->count << "\n";
                    }
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
                cout << setfill('*') << setw(12*colWidth) << "*" << endl;
                cout << setfill(' ') << fixed;
                cout << setw(6*colWidth) << "Title" << setw(3*colWidth) << "Genres" << setw(colWidth) << "Ratings"
                        << setw(colWidth) << "Count" << endl;
                cout << setfill('*') << setw(12*colWidth) << "*" << endl; 
                cout << setfill(' ') << fixed;

            // std::cout << "      title       |       genres      |   rating  |   count   \n";
            for(int i = 0; i < tags.size(); i++){
                aux3 = searchTag(tagTable, tags[i], sizes[2]);
                if(aux3){
                    for(int j = 0; j < aux3->movieId.size(); j++){
                        aux = searchTitle(titleTable, aux3->movieId[j], sizes[0]);
                        if(aux){
                            genre.clear();
                            // std::cout << aux->title << "    |   ";
                            for(int l = 0; l < aux->genres.size(); l++){
                                // std::cout << aux->genres[l];
                                genre+=aux->genres[l];
                                if(l != aux->genres.size()-1){
                                    // std::cout << "|";
                                    genre+= "|";
                                }
                            }
                            // std::cout << "  |   " << aux->rating << "   |   " << aux->count << "\n";
                            cout << setw(6*colWidth) << aux->title << setw(3*colWidth) << genre << setw(colWidth) << aux->rating
                                << setw(colWidth) << aux->count << endl;
                            genre.clear();
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
        else if(regex_match(todo, matches, rgx6)){  //shit search
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