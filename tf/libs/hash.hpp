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
int Hash (int movieId, int size)
{
    // funcao hash que mapeia a chave
    return (movieId % size);
}
// inserir um item na tabela
void insertTitle(ListNodeTitle *pLista[], int movieId, string title, vector<string> genres, float rating, int size)
{
    int index;
    ListNodeTitle *pNode;                                              //nodo livre
    //calcula hash
    index = Hash(movieId, size);

    //procura filme na lista encadeada
    if (pLista[index]->full == false)
    {//caso não exista nodo
        pLista[index] = newNodoTitle(movieId, title, genres, rating, size);   //cria um novo nodo
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

/////////////////////////////////////////////////////////////////////////

// #include <vector>
// #include <string>

// int hashingUM(int n, int size){
//     return int(n%size);
// }

// int hashingT(string tag, int size){
//     int i = 0, hash = 0;

//     for(auto& c : tag){
//         if(c != ' '){
//             hash = (int(c) + 127 * hash) % size;    
//         }
//     }
//     return int(hash);
// }

// int insertChainUT(int hash, std::vector<std::string> tuple, std::vector<std::vector<std::string>> table){
//     int tag = 0;

//     for(auto& node : table){
//         if (stoi(node[0]) == hash){
//             for(auto& subnode : node){
//                 if(subnode == tuple[0]){

//                 }
//             }
//         }
//     }
// }

// int insertChainM(int hash, std::vector<std::string> tuple, std::vector<std::vector<std::string>> table){
//     int tag = 0;

//     for(auto& node : table){
//         if (stoi(node[0]) == hash){
//             if(node.size()>2){
//                 for(auto&)
//             }
//         }
//     }
// }

// std::vector<std::string> searchChainUM(int id, std::vector<std::vector<std::string>> table, int size){
//     int hash = hashingUM(id,size);

//     for(auto& node : table){
//         if (stoi(node[0]) == hash){
//                 if(id == stoi(node[1]])){
                    
//                 }
//             }
//         }
//     }
// }