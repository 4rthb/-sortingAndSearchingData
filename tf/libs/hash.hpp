#include <bits/stdc++.h>
#include <string>

#define N1 105019 
#define N2 180001
#define N3 50671
using namespace std;
/*
Estrutura: Tabela Hash
Funções:
   - inserit: insere novos nodos 
   - search: pesquisa
*/

/*fase 1*/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~ESTRUTURAS~~~~~~~~~~~~~~~~~~~~~~~~~~~~
struct ListNodeTitle
{
    //nodo da lista encadeada
    bool full = false;          //caso já tenha sido preenchida
    int movieId;                //
    string title;
    vector<string> genres;              //genre
    float ratingTotal;
    float rating;
    int count;          
    int date;                   //data da avaliação 
    ListNodeTitle* next;
};

struct movieRatings
{          
    vector<int> movieId;        //vetor com lista de titulos de filmes              
    vector<float> rating;       //vetor com lista de avaliações
};

struct ListNodeUser
{//estrutura para pesquisa de user id
    //nodo da lista encadeada
    bool full = false;          //caso já tenha sido preenchida
    int userId; 
    movieRatings ls;            //lista de ratings do user
    ListNodeUser* next;         //proximo user
};

struct ListNodeTag
{//estrutura para pesquisa de tag
    //nodo da lista encadeada
    bool full = false;          //caso já tenha sido preenchida
    string tag;
    vector<int> movieId;                
    ListNodeTag* next;
};

//****************************TITULO******************************
int Hash(int Id, int size)
{   
    // funcao hash que mapeia a chave
    return (int)(Id % size);
}

struct ListNodeTitle* newNodoTitle(int movieId, string title, vector<string> genres, float rating, int date, bool full)
{
    //retorna um novo nodo (inicializado com null)
    ListNodeTitle *pNode =  new ListNodeTitle();
    pNode->full = full;
    pNode->movieId = movieId;
    pNode->title = title;
    pNode->genres = genres;
    pNode->ratingTotal = rating;
    pNode->rating = rating;
    pNode->count = 1;
    pNode->date = date;
    pNode->next = NULL;

    return pNode;
}

// inserir um item na tabela
void insertTitle(ListNodeTitle *pLista[N1], int movieId, string title, vector<string> genres, float rating, int date, int size)
{
    int index;
    ListNodeTitle *pNode;                                                       //nodo livre
    //calcula hash
    index = Hash(movieId, size);
    
    //procura filme na lista encadeada
    if (pLista[index]->full == false)
    {//caso não exista nodo
        pLista[index] = newNodoTitle(movieId, title, genres, rating, date, true);     //cria um novo nodo
        return;                                                                 //fim da inserção
    }
    pNode = pLista[index];                                                      //ponteiro livre recebe end da lista 
    while(pNode)
    {//enquanto não chegar ao fim da lista
        if(pNode->movieId == movieId)                                   
        {//caso seja o nodo do filme, recalcular rating
            pNode->ratingTotal = pNode->ratingTotal + rating;                   //soma o total de rating
            pNode->count = pNode->count + 1;                                    //soma mais um ao numero de ratings
            pNode->rating = pNode->ratingTotal / pNode->count;                  //recalcula o rating médio
            return;                                                             //fim da inserção
        }
        pNode = pNode->next;                                                    //move para o seguinte
    }
    //chegou ao fim da lista
    pNode = newNodoTitle(movieId, title, genres, rating, size, true);                 //cria um novo nodo
    return;                                                                     //fim da inserção
}

void updateTitle(ListNodeTitle *pLista[N1], int movieId, string title, vector<string> genres, int date, int size){
    int hash = Hash(movieId,size);

    if(pLista[hash] && pLista[hash]->date==-1){
        pLista[hash]->genres=genres;
        pLista[hash]->title=title;
        pLista[hash]->date=date;
    }
}

ListNodeTitle* searchTitle(ListNodeTitle *pLista[N1], int movieId, int size){
    //realiza pesquisa pelo titulo, um titulo por vez
    int hash = Hash(movieId, size);         //calcula hash
    ListNodeTitle* aux = pLista[hash];      //ponteiro que aponta para nodo da lista encadeada
    
    do{
        if(aux->movieId==movieId){          //caso encontre o nodo do filme 
            return aux;                     //retorna o ponteiro que aponta o nodo do filme
        }
        aux=aux->next;                      //caso não seja o nodo so filme, segue adiante
    }while(aux);                            //realizar enquanto não chegar ao fim da lista
    return NULL;
}

//****************************USER*****************************
struct ListNodeUser* newNodoUser(int movieId, float rating, int userId, bool full)
{
    //retorna um novo nodo (inicializado com null)
    ListNodeUser *pNode =  new ListNodeUser();
    pNode->full = full;
    pNode->userId = userId;
    pNode->next=NULL;
    pNode->ls.movieId.push_back(movieId);   //move a lista de filmes
    pNode->ls.rating.push_back(rating);     //move a lista de avaliações
    return pNode;
}

void insertUser(ListNodeUser *pLista[N2], int movieId, float rating, int userId, int size)
{//inserir User na tabela
    int index;
    ListNodeUser *pNode;                                        //nodo livre
    //calcula hash
    index = Hash(userId, size);                                 //calcula hash

    if (pLista[index]->full == false)
    {//caso não exista nodo
        pLista[index] = newNodoUser(movieId, rating, userId, true);   
        return;                                                       
    }
    //caso exista nodo
    pNode = pLista[index];                                      //recebe end da lista                                      
    while(pNode)                                                //enquanto não chegar no fim da lista
    {
        if(pNode->userId == userId)                             //caso encontre o user                          
        {
            pNode->ls.movieId.push_back(movieId);               //adiciona filme 
            pNode->ls.rating.push_back(rating);                 // e sua avaliacao
            return;                                             //fim da inserção
        }
        pNode = pNode->next;                                    //move para o seguinte, caso não encontre
    }
    //chegou ao fim da lista
    pNode = newNodoUser(movieId, rating, userId, true);               //cria um novo nodo
    return;                                                     //fim da inserção
}

ListNodeUser* searchUser(ListNodeUser *pLista[N2], int userId, int size){
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

//****************************TAG******************************
int HashWord(string word, int size){
    //calcula hash de uma string
    int hash = 0;
    for(auto& c : word){
        hash = (int(c) + 127 * hash) % size; 
    }
    return int(hash);
}

struct ListNodeTag* newNodoTag(int movieId, string tag, bool full)
{
    //retorna um novo nodo (inicializado com null)
    ListNodeTag *pNode =  new ListNodeTag();
    pNode->full = full;
    pNode->next=NULL;
    pNode->movieId.push_back(movieId);
    pNode->tag=tag;
    return pNode;
}

void insertTag(ListNodeTag *pLista[N3], int movieId, string tag, int size)
{// inserir um item na tabela
    int index, is=0;
    ListNodeTag *pNode;                                              //nodo livre
    //calcula hash
    index = HashWord(tag, size);

    if (pLista[index]->full == false)
    {//caso não exista nodo
        pLista[index] = newNodoTag(movieId, tag, true);   
        return;                                                       
    }
    pNode = pLista[index];                                             
    while(pNode)
    {
        if(!pNode->tag.compare(tag))                                   
        {
            for(int i=0; i < pNode->movieId.size(); i++){
                if(pNode->movieId[i] == movieId){
                    is = 1;
                }
            }
            if(!is){
                pNode->movieId.push_back(movieId);      
            }
            return;                                                     //fim da inserção
        }
        pNode = pNode->next;                                            //move para o seguinte
    }
    //chegou ao fim da lista
    pNode = newNodoTag(movieId, tag, true);               //cria um novo nodo
    return;                                                             //fim da inserção
}

ListNodeTag* searchTag(ListNodeTag *pLista[N3], string tag, int size){
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
