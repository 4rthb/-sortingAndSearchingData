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
struct ListNodeTitle
{
    //nodo da lista encadeada
    bool full = false;          //caso já tenha sido preenchida
    int movieId;                //
    string title;
    vector<string> genres;              //genero
    float ratingTotal;
    float rating;
    int count;          
    int date;                   //data da avaliação 
    ListNodeTitle* next;
};

struct movieRatings
{          
    vector<int> movieId;                
    vector<float> rating;     
};

struct ListNodeUser
{
    //nodo da lista encadeada
    bool full = false;          //caso já tenha sido preenchida
    int userId; 
    movieRatings ls;            
    ListNodeUser* next;
};

struct ListNodeTag
{
    //nodo da lista encadeada
    bool full = false;          //caso já tenha sido preenchida
    string tag;
    int movieId;                   //data da avaliação 
    ListNodeTag* next;
};

struct ListNodeGenre
{
    //nodo da lista encadeada
    bool full = false;          //caso já tenha sido preenchida
    int movieId;                   //data da avaliação 
    ListNodeGenre* next;
};

struct ListNodeTitle* newNodoTitle(int movieId, string title, vector<string> genres, float rating, int date)
{
    //retorna um novo nodo (inicializado com null)
    struct ListNodeTitle *pNode =  new ListNodeTitle;
    bool full = true;
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
int Hash(int Id, int size)
{
    // funcao hash que mapeia a chave
    return (int)(Id % size);
}
// inserir um item na tabela
void insertTitle(ListNodeTitle *pLista[], int movieId, string title, vector<string> genres, float rating, int date, int size)
{
    int index;
    ListNodeTitle *pNode;                                              //nodo livre
    //calcula hash
    index = Hash(movieId, size);

    //procura filme na lista encadeada
    if (pLista[index]->full == false)
    {//caso não exista nodo
        pLista[index] = newNodoTitle(movieId, title, genres, rating, date);   //cria um novo nodo
        return;                                                         //fim da inserção
    }
    pNode = pLista[index];                                              //ponteiro livre recebe end da lista 
    while(pNode)
    {//enquanto não chegar ao fim da lista
        if(pNode->movieId == movieId)                                   
        {//caso seja o nodo do filme, recalcular rating
            pNode->ratingTotal = pNode->ratingTotal + rating;           //soma o total de rating
            pNode->count = pNode->count + 1;                            //soma mais um ao numero de ratings
            pNode->rating = pNode->ratingTotal / pNode->count;          //recalcula o rating médio
            return;                                                     //fim da inserção
        }
        pNode = pNode->next;                                            //move para o seguinte
    }
    //chegou ao fim da lista
    pNode = newNodoTitle(movieId, title, genres, rating, size);               //cria um novo nodo
    return;                                                             //fim da inserção
}

ListNodeTitle* searchTitle(ListNodeTitle *pLista[], int movieId, int size){
    int hash = Hash(movieId, size);
    ListNodeTitle* aux = pLista[hash];
    
    do{
        if(aux->movieId==movieId){
            return aux;
        }
        aux=aux->next;
    }while(aux);
    return NULL;
}

struct ListNodeUser* newNodoUser(int movieId, float rating, int userId)
{
    //retorna um novo nodo (inicializado com null)
    struct ListNodeUser *pNode =  new ListNodeUser;
    bool full = true;
    pNode->userId = userId;
    pNode->next=NULL;
    return pNode;
}
// inserir um item na tabela
void insertUser(ListNodeUser *pLista[], int movieId, float rating, int userId, int size)
{
    int index;
    ListNodeUser *pNode;                                              //nodo livre
    //calcula hash
    index = Hash(userId, size);

    if (pLista[index]->full == false)
    {//caso não exista nodo
        pLista[index] = newNodoUser(movieId, rating, userId);   
        return;                                                       
    }
    pNode = pLista[index];                                             
    while(pNode)
    {
        if(pNode->userId == userId)                                   
        {
            pNode->ls.movieId.push_back(movieId);   
            pNode->ls.rating.push_back(rating);    
            return;                                                     //fim da inserção
        }
        pNode = pNode->next;                                            //move para o seguinte
    }
    //chegou ao fim da lista
    pNode = newNodoUser(movieId, rating, userId);               //cria um novo nodo
    return;                                                             //fim da inserção
}

ListNodeUser* searchUser(ListNodeUser *pLista[], int userId, int size){
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

int HashWord(string word, int size){
    int hash = 0;
    for(auto& c : word){
        hash = (int(c) + 127 * hash) % size; 
    }
    return int(hash);
}

