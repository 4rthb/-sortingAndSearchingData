#include <bits/stdc++.h>
using namespace std;
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
    struct TrieNode *pNode =  (struct TrieNode*) malloc(sizeof( struct TrieNode ));
    pNode->key = char_key;
    pNode->is_end = false;
    pNode->movieId = -1;
    pNode->children = NULL;
    pNode->children_left = NULL;
    pNode->children_right = NULL;

    return pNode;
}
  
// caso não exista, inserir chave
// se existe, marcar a o nodo com o movieId
void insert(struct TrieNode** root, char *word, int movieId)
{
    // arvore vazia
    if (!(*root))
        *root = novoNode(*word);
  
    // se a key eh menor que caractere,
    // insere o caractere na subtree da esquerda
    if ((*word) < (*root)->key)
        insert(&( (*root)->children_left ), word, movieId);
  
    // se a key eh maior que caractere,
    // insere o caractere na subtree da direita
    else if ((*word) > (*root)->key)
        insert(&( (*root)->children_right ), word, movieId);
  
    // se a key eh igual ao caractere
    else
    {
        if (*(word+1))
            insert(&( (*root)->children ), word+1,movieId);
  
        // the last character of the word
        else
            (*root)->is_end = true;
            (*root)->movieId = movieId;

    }
}
  

/*fase 2*/
// retorna o nodo que aponta para o fim do nome ou prefixo dado na pesquisa
TrieNode* search(struct TrieNode *root, char *word)
{
    if (!root)
        return NULL;
  
    if (*word < (root)->key)
        return search(root->children_left, word);
  
    else if (*word > (root)->key)
        return search(root->children_right, word);
  
    else
    {
        if (*(word+1) == '\0')
            return root;
  
        return search(root->children, word+1);
    }
}

// preenche lista de filmes com todos os filhos do nodo passado
void get_ids(struct TrieNode *node, vector<int> &movies){
    if(node->is_end==true){
        movies.push_back(node->movieId);
    }
    if (!node){
        return;
    }
    if(node->children){
        get_ids(node->children, movies);
    }
    if(node->children_right){
        get_ids(node->children_right, movies);
    }
    if(node->children_left){
        get_ids(node->children_left, movies);
    }
}

// preenche lista de filmes com todos os filhos do nodo passado
void get_all_ids(struct TrieNode *node, vector<int> &movies){
    if(node->is_end==true){
        movies.push_back(node->movieId);
    }
    if (!node){
        return;
    }
    if(node->children){
        get_ids(node->children, movies);
    }
}

