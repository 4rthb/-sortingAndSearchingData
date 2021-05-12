#include <bits/stdc++.h>
#include <string>

using namespace std;
/*
Estrutura: Tabela Hash
Funções:
   - inserit: insere novos nodos 
   - search: pesquisa
*/

/*fase 1*/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~ESTRUTURAS~~~~~~~~~~~~~~~~~~~~~~~~~~~~
struct strMovie
{//estrutura filme
    int movieId;                
    string title;
    float ratingTotal;
    float rating;
    int count;   
    vector<string> genres;      //vetor com lista de generos       
}
struct ListNodeTitle
{
    //nodo da lista encadeada
    bool full = false;          //caso já tenha sido preenchida
    strMovie* movieStr;         //estrutura 
    int date;                   //data da avaliação 
    ListNodeTitle* next;
};

struct movieRatings
{          
    vector<strMovie> movie;    //vetor com lista de estruturas de filmes              
    vector<float> rating;       //vetor com lista de avaliações
};

struct ListNodeUser
{//estrutura para pesquisa de user id
    //nodo da lista encadeada
    bool full = false;          //caso já tenha sido preenchida
    int userId; 
    movieRatings* ls;            //lista de ratings do user
    ListNodeUser* next;         //proximo user
};

struct ListNodeTag
{//estrutura para pesquisa de tag
    //nodo da lista encadeada
    bool full = false;          //caso já tenha sido preenchida
    string tag;
    vector<strMovie> movie;   //vetor de estruturas de filmes     
    ListNodeTag* next;
};
struct TopGenre
{
    strMovie* movie;             //estruturas de filmes  
    TopGenre* next;
    TopGenre* pre;
}
struct ListNodeGenre
{//estrutura para pesquisa de geneno 
    //nodo da lista encadeada
    bool full = false;          //caso já tenha sido preenchida
    string genre;
    TopGenre* root;          //Top lista de filmes encadeada      
    ListNodeGenre* next;
};

//********************************************************TITULO**********************************************************
int Hash(int Id, int size)
{
    // funcao hash que mapeia a chave
    return (int)(Id % size);
}

struct strMovie* newMovie(int movieId, string title, vector<string> genres, float rating, int date)
{
    //retorna um novo nodo (inicializado com null)
    struct strMovie *pNode =  new strMovie;
    pNode->movieId = movieId;
    pNode->title = title;
    pNode->genres = genres;
    pNode->ratingTotal = rating;
    pNode->rating = rating;
    pNode->count = 1;
    pNode->date = date;

    return pNode;
}

struct ListNodeTitle* newNodoTitle(strMovie* movie)
{
    //retorna um novo nodo (inicializado com null)
    struct ListNodeTitle *pNode =  new ListNodeTitle;
    pNode->full = true;
    pNode->movieStr = movie;
    pNode->next = NULL;

    return pNode;
}

// inserir um item na tabela
void insertTitle(ListNodeTitle *pLista[], strMovie* movie, int size)
{
    int index;
    ListNodeTitle *pNode;                                                       //nodo livre
    //calcula hash
    index = Hash(movie->movieId, size);

    //procura filme na lista encadeada
    if (pLista[index]->full == false)
    {//caso não exista nodo
        pLista[index] = newNodoTitle(movie);                                    //cria um novo nodo
        return;                                                                 //fim da inserção
    }
    pNode = pLista[index];                                                      //ponteiro livre recebe end da lista 
    while(pNode)
    {//enquanto não chegar ao fim da lista
        if(pNode->movieStr->movieId == movie->movieId)                                   
        {//caso seja o nodo do filme, recalcular rating
            pNode->movieStr->ratingTotal = pNode->movieStr->ratingTotal + movie->rating;         //soma o total de rating
            pNode->movieStr->count = pNode->movieStr->count + 1;                          //soma mais um ao numero de ratings
            pNode->movieStr->rating = pNode->movieStr->ratingTotal / pNode->movieStr->count;        //recalcula o rating médio
            return;                                                             //fim da inserção
        }
        pNode = pNode->next;                                                    //move para o seguinte
    }
    //chegou ao fim da lista
    pNode = newNodoTitle(movie);                                                //cria um novo nodo
    return;                                                                     //fim da inserção
}

ListNodeTitle* searchTitle(ListNodeTitle *pLista[], int movieId, int size){
    //realiza pesquisa pelo titulo, um titulo por vez
    int hash = Hash(movieId, size);             //calcula hash
    ListNodeTitle* aux = pLista[hash];          //ponteiro que aponta para nodo da lista encadeada
    
    do{
        if(aux->movieStr->movieId == movieId){  //caso encontre o nodo do filme 
            return aux;                         //retorna o ponteiro que aponta o nodo do filme
        }
        aux=aux->next;                          //caso não seja o nodo so filme, segue adiante
    }while(aux);                                //realizar enquanto não chegar ao fim da lista
    return NULL;
}

//********************************************************USER*********************************************************
struct ListNodeUser* newNodoUser(strMovie* movie, float rating, int userId)
{
    //retorna um novo nodo (inicializado com null)
    struct ListNodeUser *pNode =  new ListNodeUser;
    pNode->full = true;
    pNode->userId = userId;
    pNode->next=NULL;
    pNode->ls.movie.push_back(movie);     //add a lista de filmes
    pNode->ls.rating.push_back(rating);     //add a lista de avaliações
    return pNode;
}

void insertUser(ListNodeUser *pLista[], strMovie* movie, float rating, int userId, int size)
{//inserir User na tabela
    int index;
    ListNodeUser *pNode;                                        //nodo livre
    //calcula hash
    index = Hash(userId, size);                                 //calcula hash

    if (pLista[index]->full == false)
    {//caso não exista nodo
        pLista[index] = newNodoUser(movie, rating, userId);   
        return;                                                       
    }
    //caso exista nodo
    pNode = pLista[index];                                      //recebe end da lista                                      
    while(pNode)                                                //enquanto não chegar no fim da lista
    {
        if(pNode->userId == userId)                             //caso encontre o user                          
        {
            pNode->ls.movie.push_back(movie);               //adiciona filme 
            pNode->ls.rating.push_back(rating);                 // e sua avaliacao
            return;                                             //fim da inserção
        }
        pNode = pNode->next;                                    //move para o seguinte, caso não encontre
    }
    //chegou ao fim da lista
    pNode = newNodoUser(movie, rating, userId);               //cria um novo nodo
    return;                                                     //fim da inserção
}

ListNodeUser* searchUser(ListNodeUser *pLista[], int userId, int size){
    //realiza pesquisa de user
    int hash = Hash(userId, size);
    ListNodeUser* aux = pLista[hash];
    
    do{
        if(aux->userId==userId){
            return aux;
        }
        aux=aux->next;
    }while(aux);
    return NULL;
}

//********************************************************TAG**********************************************************
int HashWord(string word, int size){
    //calcula hash de uma string
    int hash = 0;
    for(auto& c : word){
        hash = (int(c) + 127 * hash) % size; 
    }
    return int(hash);
}

struct ListNodeTag* newNodoTag(strMovie* movie, string tag)
{
    //retorna um novo nodo (inicializado com null)
    struct ListNodeTag *pNode =  new ListNodeTag;
    pNode->full = true;
    pNode->next=NULL;
    pNode->movie.push_back(movie);
    pNode->tag=tag;
    return pNode;
}

void insertTag(ListNodeTag *pLista[], strMovie* movie, string tag, int size)
{// inserir um item na tabela
    int index;
    ListNodeTag *pNode;                                              //nodo livre
    //calcula hash
    index = HashWord(tag, size);

    if (pLista[index]->full == false)
    {//caso não exista nodo
        pLista[index] = newNodoTag(movie, tag);   
        return;                                                       
    }
    pNode = pLista[index];                                             
    while(pNode)
    {
        if(!pNode->tag.compare(tag))                                   
        {
            pNode->movie.push_back(movie);      
            return;                                                     //fim da inserção
        }
        pNode = pNode->next;                                            //move para o seguinte
    }
    //chegou ao fim da lista
    pNode = newNodoTag(movie, tag);                                   //cria um novo nodo
    return;                                                             //fim da inserção
}

ListNodeTag* searchTag(ListNodeTag *pLista[], string tag, int size){
    int hash = HashWord(tag, size);
    ListNodeTag* aux = pLista[hash];
    
    do{
        if(!aux->tag.compare(tag)){
            return aux;
        }
        aux=aux->next;
    }while(aux);
    return NULL;
}

//*******************************************************GENERO*********************************************************
struct ListNodeGenre* newNodoGenre(strMovie *movie, string genre)
{
    //retorna um novo nodo (inicializado com null)
    struct ListNodeGenre *pNode =  new ListNodeGenre;
    pNode->full = true;
    pNode->next = NULL;
    pNode->root = newNodoTopGenre(movie);
    pNode->genre = genre;
    return pNode;
}

struct TopGenre* newNodoTopGenre(strMovie *movie) 
{
    //retorna um novo nodo (inicializado com null)
    struct TopGenre *pNode =  new TopGenre;
    pNode->movie = movie;
    pNode->next = NULL;
    pNode->pre = NULL;
    return pNode;
}

void insertTopList(ListNodeGenre *pNode, strMovie *movie)
{   
    ListNodeGenre *newNodo, *aux;
    newNodo->root = newNodoTopGenre(movie);
    if(newNodo->root->movie->rating > pNode->root->movie->rating)
    {//caso o novo filme seja maior que o nodo raiz
        newNodo->root->next = pNode->root;        //novo nodo aponta para raiz
        pNode->root->pre = newNodo->root;         
        pNode->root = newNodo->root;
        return;
    }
    aux = pNode;
    //enquanto o codigo do novo elemento for maior que o codigo do ptaux e o prox nao for null
    while(newNodo->root->movie->rating > aux->root->movie->rating && aux->root->next)
    {
        aux->root = aux->root->next;
    }
    if(newNodo->root->movie->rating < aux->root->movie->rating )//no meio
    {
        newNodo->root->pre = aux->root->pre;
        newNodo->root->next = aux->root;
        aux->root->pre = newNodo->root;
        newNodo->root->pre->next = newNodo->root;
        return;
    }
    else//se chegar no fim da lista
    {
        aux->root->next = newNodo->root;
        newNodo->root->pre = aux->root;
        return;
    }
}
void insertGenre(ListNodeGenre *pLista[], strMovie *movie, string genre, int size)
{// inserir um item na tabela
    int index;
    ListNodeGenre *pNode;                                              //nodo livre
    //calcula hash
    index = HashWord(genre, size);

    if (pLista[index]->full == false)
    {//caso não exista nodo
        pLista[index] = newNodoGenre(movie, genre);   
        return;                                                       
    }
    pNode = pLista[index];                                             
    while(pNode)
    {
        if(!pNode->genre.compare(genre))                                //caso encontre o nodo                                   
        {//adicionar o filme na lista encadeada ordenada
            insertTopList(pNode, movie);     
            return;                                                     //fim da inserção
        }
        pNode = pNode->next;                                            //move para o seguinte
    }
    //chegou ao fim da lista
    pNode = newNodoGenre(movie, genre);                                 //cria um novo nodo
    return;                                                             //fim da inserção
}

ListNodeGenre* searchGenre(ListNodeGenre *pLista[], string genre, int size){
    int hash = HashWord(genre, size);
    ListNodeGenre* aux = pLista[hash];
    
    do{
        if(!aux->genre.compare(genre)){
            return aux;
        }
        aux=aux->next;
    }while(aux);
    return NULL;
}