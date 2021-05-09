#include <bits/stdc++.h>

/*
Estrutura: Arvore trie 
Funções:
    - insert: insere novas palavras na arvore
    - search: pesquisa palavras na trie
*/

/*fase 1*/
struct TrieNode 
{
   //um nodo numa estrutura arvore
    char key;                           //caractere a ser guardado
    bool is_end;                        //caso o nodo seja o fim da palavra
    int movieId;                        //idica o id da palavra, apenas quando 
    struct TrieNode *children;          //igual a char 
    struct TrieNode *children_left;     //menor que char
    struct TrieNode *children_right;    //maior que char
};

// retorna um novo nodo (inicializado com nulls)
struct TrieNode *novoNode(char char_key)
{
    struct TrieNode *pNode =  new TrieNode;
    pNode->key = char_key;
    pNode->is_end = false;
    pNode->movieId = NULL;
    pNode->children = NULL;
    pNode->children_left = NULL;
    pNode->children_right = NULL;

    return pNode;
}
  
// caso não exista, inserir chave
// se existe, marcar a o nodo com o movieId
void insert(struct TrieNode *root, string word, int movieId)
{
    struct TrieNode *pNode = root;                      //recebe ponteiro para raiz
    char char_key;                                      //recebe a chave
    for (int i = 0; i < word.length(); i++)             //percorre a palavra 
    {
        char_key = word[i];                             //recebe o char na posicao i
        if (pNode == NULL)                              //caso o nodo não exita 
        {
            pNode = novoNode(char_key);                 //criar nodo novo
            pNode = pNode->children;                    //segue para o proximo nodo        
        }    
        else                                            //caso o nodo exista
        {
            if (char_key == pNode->key)                 //caso o char for igual a chave do nodo
            {
                pNode = pNode->children;                //segue para o proximo nodo 
            }
            else
            {
                if (char_key < pNode->key)              //caso o char for menor que a chave do nodo
                {      
                    pNode = pNode->children_left;       //segue para o proximo nodo
                }
                else
                {
                    if (char_key > pNode->key)          //caso o char for maior que a chave do nodo 
                    {   
                        pNode = pNode->children_right;  //segue para o proximo nodo
                    }
                }                
            }
        }
    }
    // marcar fim da palavra
    pNode->is_end = true;
    pNode->movieId = movieId;
}
  

/*fase 2*/
// retorna o nodo que aponta para o fim do nome ou prefixo dado na pesquisa
TrieNode* search(struct TrieNode *root, string word)
{
    struct TrieNode *pNode = root;
  
    char char_key;                                      //recebe a chave
    for (int i = 0; i < word.length(); i++)             //percorre a palavra 
    {
        char_key = word[i];                             //recebe o char na posicao i
        if (pNode == NULL)                              //caso o nodo não exita 
        {
            return false;
        }    
        else                                            //caso o nodo exista
        {
            if (char_key == pNode->key)                 //caso o char for igual a chave do nodo
            {
                pNode = pNode->children;                //segue para o proximo nodo 
            }
            else
            {
                if (char_key < pNode->key)              //caso o char for menor que a chave do nodo
                {      
                    pNode = pNode->children_left;       //segue para o proximo nodo
                }
                else
                {
                    if (char_key > pNode->key)          //caso o char for maior que a chave do nodo 
                    {   
                        pNode = pNode->children_right;  //segue para o proximo nodo
                    }
                }                
            }
        }
    }
    return pNode;
}
  
//um nodo da lista encadeada movieId
struct MovieList
{
    int movieId;                            //idica o id da palavra 
    struct MovieList *next;                 //proximo id
};

// retorna um novo nodo (inicializado com nulls)
struct MovieList *newNode(int movieId)
{
    struct MovieList *pNode =  new MovieList;
    pNode->movieId = movieId;               //idica o id da palavra 
    pNode->next = NULL;                     //proximo id

    return pNode;
}

/* 
função:
recebe: ponteiro do nodo final da pesquisa e end da lista encadeada onde colocara os movieId encontrados 
*/
void movie_found(TrieNode *pNode, MovieList *pList)
{
    if(pNode->is_end)
    {//caso o nodo seja o fim de uma palavra 
            pList = newNode(pNode->movieId);            //criar nodo novo e colocar o movieId
            pList = pList->next;                        //segue para o proximo nodo        
    }    
    movie_found(pNode->children_left, pList);
    movie_found(pNode->children, pList);
    movie_found(pNode->children_right, pList);
}