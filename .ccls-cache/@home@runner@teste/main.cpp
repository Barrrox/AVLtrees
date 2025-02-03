#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;



class node
{
private:

  node *esq, *dir; 
  int chave;
  int altura;


public:
  node(int chave)
  {
    this->chave = chave;
    esq = NULL;
    dir = NULL;
    altura = 1;
  }

  int getChave() { return chave; }

  node* getEsq() { return esq; }

  node* getDir() { return dir; }

  void setEsq(node *no) { esq = no;}

  void setDir(node *no) { dir = no; }

  void setChave(int chave) { this->chave = chave; }

  void setAltura(){
    int alturaEsq = esq ? esq->getAltura() : 0;
    int alturaDir = dir ? dir->getAltura() : 0;
    altura = 1 + max(alturaEsq, alturaDir);
  }

  int getAltura(){ return this->altura; }

};






class arvoreAVL
{
private:
  node *raiz;
public:
  arvoreAVL() { raiz = NULL; }
  // métodos de inserção
  void inserir(int chave);
  node* inserirAux(node *no, int chave);
  node *getRaiz()
  {
    return raiz;
  }
  void setRaiz(node *no){ this->raiz = no; }
  // percurso!!
  void emOrdem();
  void emOrdemAux(node* no, int altura);
  void preOrdem(node* no);
  void posOrdem(node* no);
  //o método de remoção/exclusão de nó pela chave
  void remover(int chave);
  node* remocao(node *no, int chave);
  // método auxiliar para encontrar o sucessor do nó
  node* sucessor(node* no);
  node* antecessor(node *no);
  int getAltura(node *no);
  node* rotacaoEsq(node *no);
  node* rotacaoDir(node *no);
  node* rotacaoDuploEsq(node *no); // Left-right
  node* rotacaoDuploDir(node *no);	// Right-left

};

void arvoreAVL::remover(int chave){
  raiz = remocao(raiz, chave);
}

node* arvoreAVL::remocao(node* no, int chave) {
  // Caso base: árvore nula
  if (no == NULL)
    return no;

  // Determinar a subárvore para remoção
  if (chave < no->getChave()) {
    no->setEsq(remocao(no->getEsq(), chave));
  } 
  else if (chave > no->getChave()) {
    no->setDir(remocao(no->getDir(), chave));
  } 
  else {
    // Caso 01: Nó folha
    if (no->getEsq() == NULL && no->getDir() == NULL) {
      delete no;
      return NULL;
    }
    // Caso 02: Nó com um único filho
    if (no->getEsq() == NULL) {
      node* temp = no->getDir();
      delete no;
      return temp;
    } 
    else if (no->getDir() == NULL) {
      node* temp = no->getEsq();
      delete no;
      return temp;
    }

    // Caso 03: Nó com dois filhos
    node* s = antecessor(no);
    no->setChave(s->getChave());
    no->setEsq(remocao(no->getEsq(), s->getChave()));
  }

  // Atualizar altura do nó
  int alturaEsq = no->getEsq() ? no->getEsq()->getAltura() : 0;
  int alturaDir = no->getDir() ? no->getDir()->getAltura() : 0;
  no->setAltura();

  // Recalcular o fator de balanceamento (FB)
  int FB = alturaEsq - alturaDir;

  // Rotação para corrigir desbalanceamento
  if (FB > 1) { // Nó está desbalanceado para a esquerda
    int FBEsq = no->getEsq()->getEsq() ? no->getEsq()->getEsq()->getAltura() : 0;
    int FBEsqDir = no->getEsq()->getDir() ? no->getEsq()->getDir()->getAltura() : 0;

    if (FBEsq >= FBEsqDir) {
      return rotacaoDir(no); // LL
    } else {
      no->setEsq(rotacaoEsq(no->getEsq()));
      return rotacaoDir(no); // LR
    }
  }

  if (FB < -1) { // Nó está desbalanceado para a direita
    int FBDirEsq = no->getDir()->getEsq() ? no->getDir()->getEsq()->getAltura() : 0;
    int FBDir = no->getDir()->getDir() ? no->getDir()->getDir()->getAltura() : 0;

    if (FBDir >= FBDirEsq) {
      return rotacaoEsq(no); // RR
    } else {
      no->setDir(rotacaoDir(no->getDir()));
      return rotacaoEsq(no); // RL
    }
  }

  return no;
}


// //remove o nó de acordo com a chave e retorna
// node* arvoreAVL::remocao(node* no, int chave)
// {
//   //árvore nula
//   if (no == NULL)
//     return no;
//   // verificar qual subárvore a chave se encontra
//   if (no->getChave() > chave)
//   {	// vai para a subarvoreAVL da esquerda
//     no->setEsq(remocao(no->getEsq(), chave));
//   }
//   else if (no->getChave() < chave)
//   {	// subarvoreAVL da direita
//     no->setDir(remocao(no->getDir(), chave));
//   }
//   else // o no atual é o que contém a chave
//   {
//     // caso 01-> nó folha, não tem filhos
//     if (no->getEsq() == NULL && no->getDir() == NULL)
//     {
//       delete no;
//       return NULL;
//     }
//     // caso 02 -> só tem 1 filho
//     else
//     {
//       // só tem filho da direita
//       if (no->getEsq() == NULL)
//       {
//         //substituir pelo filho da direita
//         node *tmp = no->getDir();
//         delete no;
//         return tmp;
//       }
//       // filho da esquerda
//       else if (no->getDir() == NULL)
//       {
//         //substituir pelo esquerda
//         node* tmp = no->getEsq();
//         delete no;
//         return tmp;
//       }
//       //caso 03 -> nó possui 2 filhos
//       else
//       {
//         // encontrar o no substituto
//         node *s = antecessor(no);
//         no->setChave(s->getChave());
//         no->setEsq(remocao(no->getEsq(), s->getChave()));
//       }
//       // return no;
//     }
//     return no;
//   }

//   int FB;
//   no->setAltura();
//   int alturaEsq = no->getEsq() ? no->getEsq()->getAltura() : 0;
//   int alturaDir = no->getDir() ? no->getDir()->getAltura() : 0;
//   FB = alturaEsq - alturaDir;

//   if (FB > 1 && chave < no->getEsq()->getChave()) {
//       return rotacaoDir(no); // LL
//   }
//   if (FB > 1 && chave > no->getEsq()->getChave()) {
//       no->setEsq(rotacaoEsq(no->getEsq()));
//       return rotacaoDir(no); // LR
//   }
//   if (FB < -1 && chave > no->getDir()->getChave()) {
//       return rotacaoEsq(no); // RR
//   }
//   if (FB < -1 && chave < no->getDir()->getChave()) {
//       no->setDir(rotacaoDir(no->getDir()));
//       return rotacaoEsq(no); // RL
//   }

//     return no;
// }

node* arvoreAVL::sucessor(node* no)
{
  // sucessor, nó mais a esquerda da subárvore da direita
  //sucessor nunca tem filho esquerdo!
  no = no->getDir();
  while(no != NULL && no->getEsq() != NULL)
    no = no->getEsq();
  return no;
}

node* arvoreAVL::antecessor(node *no)
{
  //antecessor o nó mais a direita da subárvore esquerda
  no = no->getEsq();
  while(no != NULL && no->getDir() != NULL)
    no = no->getDir();
  return no;
}

void arvoreAVL::emOrdem(){
  emOrdemAux(this->getRaiz(),0);
}
  
void arvoreAVL::emOrdemAux(node* no, int altura)
{
  if (no != NULL)
  {
    emOrdemAux(no->getEsq(), altura + 1);
    cout << no->getChave() << "," <<  altura << endl;
    emOrdemAux(no->getDir(), altura + 1);
  }
}



void arvoreAVL::preOrdem(node *no)
{
  if (no != NULL)
  {
    for(int i = 0; i < no->getAltura(); i++)
      cout << "---|";
    cout << no->getChave() << endl;
    preOrdem(no->getEsq());
    preOrdem(no->getDir());
  }
}

void arvoreAVL::posOrdem(node *no)
{
  if (no != NULL)
  {
    posOrdem(no->getEsq());
    posOrdem(no->getDir());
    for(int i = 0; i < no->getAltura(); i++)
      cout << "---|";
    cout << no->getChave() << endl;
  }
}

void arvoreAVL::inserir(int chave) {
  raiz = inserirAux(raiz, chave);
}

node* arvoreAVL::inserirAux(node* no, int chave) {
  if (no == NULL)
      return new node(chave);

  if (chave < no->getChave()) {
      no->setEsq(inserirAux(no->getEsq(), chave));
  } else if (chave > no->getChave()) {
      no->setDir(inserirAux(no->getDir(), chave));
  } else {
      cout << "Esse valor já existe na árvore.\n";
      return no;
  }
  
  int FB;
  no->setAltura();
  int alturaEsq = no->getEsq() ? no->getEsq()->getAltura() : 0;
  int alturaDir = no->getDir() ? no->getDir()->getAltura() : 0;
  FB = alturaEsq - alturaDir;

  if (FB > 1 && chave < no->getEsq()->getChave()) {
      return rotacaoDir(no); // LL
  }
  if (FB > 1 && chave > no->getEsq()->getChave()) {
      no->setEsq(rotacaoEsq(no->getEsq()));
      return rotacaoDir(no); // LR
  }
  if (FB < -1 && chave > no->getDir()->getChave()) {
      return rotacaoEsq(no); // RR
  }
  if (FB < -1 && chave < no->getDir()->getChave()) {
      no->setDir(rotacaoDir(no->getDir()));
      return rotacaoEsq(no); // RL
  }

  return no;
}

node* arvoreAVL::rotacaoEsq(node* no) {
    node* novaRaiz = no->getDir();
    no->setDir(novaRaiz->getEsq());
    novaRaiz->setEsq(no);

    no->setAltura();
    novaRaiz->setAltura();

    return novaRaiz;
}

node* arvoreAVL::rotacaoDir(node* no) {
  node* novaRaiz = no->getEsq();
  no->setEsq(novaRaiz->getDir());
  novaRaiz->setDir(no);

  no->setAltura();
  novaRaiz->setAltura();

  return novaRaiz;
}

node* arvoreAVL::rotacaoDuploEsq(node* no) {
  no->setDir(rotacaoDir(no->getDir()));
  return rotacaoEsq(no);
}

node* arvoreAVL::rotacaoDuploDir(node* no) {
  no->setEsq(rotacaoEsq(no->getEsq()));
  return rotacaoDir(no);
}


int main() {
    arvoreAVL avl;
    string linha;

    // Lê linha por linha da entrada padrão (stdin)
    while (getline(cin, linha)) {
        istringstream iss(linha);
        char operacao;
        int valor;

        if (!(iss >> operacao >> valor)) continue; // Ignorar linhas inválidas
      
        // avl.emOrdem();
        // cout << endl;
      
        if (operacao == 'i') {
            avl.inserir(valor); // Inserir na árvore AVL
        } else if (operacao == 'r') {
            avl.remover(valor); // Remover da árvore AVL
        }
    }

    // Escrever a árvore em ordem na saída padrão (stdout)
    avl.emOrdem();
    cout << endl; // Para garantir que a saída seja concluída corretamente

    return 0;
}
