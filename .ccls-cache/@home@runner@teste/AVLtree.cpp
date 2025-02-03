#include <iostream>
#include <algorithm>
using namespace std;



class node
{
private:

	node *esq, *dir; 
	int chave;
	int fatorDeBalanceamento;
	int altura;


public:
	node(int chave)
	{
		this->chave = chave;
		esq = NULL;
		dir = NULL;
		altura = 0;
		fatorDeBalanceamento = 0;
	}

	int getChave() { return chave; }

	node* getEsq() { return esq; }

	node* getDir() { return dir; }

	void setEsq(node *no) { esq = no;}

	void setDir(node *no) { dir = no; }

	void setChave(int chave) { this->chave = chave; }

	void setAltura();

	int getAltura();

	void setFB(int valor){ this->fatorDeBalanceamento = valor; }

	int getFB(){return fatorDeBalanceamento;}
};


void node::setAltura(){
    this->altura = 1 + max(this->getEsq()->getAltura(), this->getDir()->getAltura());
}
int node::getAltura(){

	if(this == NULL){
		return 0;
	}
	else{
		return this->altura;

	}
}


class arvoreAVL
{
private:
	node *raiz;
public:
	arvoreAVL()
	{
		raiz = NULL;
	}
	// métodos de inserção
	void inserir(int chave);
	void inserirAux(node *no, int chave);
	node *getRaiz()
	{
		return raiz;
	}
	// percurso!!
	void emOrdem(node* no);
	void preOrdem(node* no);
	void posOrdem(node* no);
	//o método de remoção/exclusão de nó pela chave
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

//remove o nó de acordo com a chave e retorna
node* arvoreAVL::remocao(node* no, int chave)
{
	//árvore nula
	if (no == NULL)
		return no;
	// verificar qual subárvore a chave se encontra
	if (no->getChave() > chave)
	{	// vai para a subarvoreAVL da esquerda
		no->setEsq(remocao(no->getEsq(), chave));
	}
	else if (no->getChave() < chave)
	{	// subarvoreAVL da direita
		no->setDir(remocao(no->getDir(), chave));
	}
	else // o no autal é o que contém a chave
	{
		// caso 01-> nó folha, não tem filhos
		if (no->getEsq() == NULL && no->getDir() == NULL)
		{
			delete no;
			return NULL;
		}
		// caso 02 -> só tem 1 filho
		else
		{
			// só tem filho da direita
			if (no->getEsq() == NULL)
			{
				//substituir pelo filho da direita
				node *tmp = no->getDir();
				delete no;
				return tmp;
			}
			// filho da esquerda
			else if (no->getDir() == NULL)
			{
				//substituir pelo esquerda
				node* tmp = no->getEsq();
				delete no;
				return tmp;
			}
			//caso 03 -> nó possui 2 filhos
			else
			{
				// encontrar o no substituto
				node *s = antecessor(no);
				no->setChave(s->getChave());
				no->setEsq(remocao(no->getEsq(), s->getChave()));
			}
			return no;
		}
		return no;
	}
	
    return no;
}

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

void arvoreAVL::emOrdem(node* no)
{
	if (no != NULL)
	{
		emOrdem(no->getEsq());
		for(int i = 0; i < no->getAltura(); i++)
			cout << "---|";
		cout << no->getChave() << ", " << no->getAltura() << ", " << no->getFB()  << endl;
		emOrdem(no->getDir());
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

void arvoreAVL::inserir(int chave)
{
	//inserção na árvore vazia
	if (raiz == NULL)
		raiz = new node(chave);
	else // nao ta vazia
		inserirAux(raiz, chave);
}

void arvoreAVL::inserirAux(node *no, int chave)
{
	//inserir a esquerda
	//verifica se o valor é MENOR do que a raiz
	if (chave < no->getChave())
	{
		//verificar se existe filho da esquerda
		if (no->getEsq() == NULL)
		{
			node *novo_no = new node(chave);
			no->setEsq(novo_no); //filho da esquerda
		}
		else //se tiver um filho, esse filho é a raiz da subarvoreAVL
		{
			//percorre recursivamente
			inserirAux(no->getEsq(), chave);
		}
	} //direita
	else if(chave > no->getChave())
	{
		if (no->getDir() == NULL)
		{
			node *novo_no = new node(chave);
			no->setDir(novo_no);
		}
		else
		{
			inserirAux(no->getDir(), chave);
		}
	}
	else if (chave == no->getChave()) // se for igual nao insere na arvoreAVL
	{
		cout << "esse valor já existe!" << endl;
	}
 	
	no->setAltura();
	no->setFB(no->getEsq()->getAltura() - no->getDir()->getAltura());

	// Caso LEFT HEAVY
	if (no->getFB() > 1){
		
		// caso left-right heavy
		if(no->getChave() > no->getEsq()->getChave()){
			no = rotacaoDuploDir(no);
		} else { // caso left-left heavy
			no = rotacaoDir(no);
		}

	// Caso RIGHT HEAVY
	} else if (no->getFB() < -1){ 
		// caso right-left heavy
		
		if(no->getChave() < no->getDir()->getChave()){
			no = rotacaoDuploEsq(no);
		} else { //caso right-right heavy
			no = rotacaoEsq(no);
		}

	}

}

node *arvoreAVL::rotacaoEsq(node *no){

	node *aux = no;

	no = no->getDir();

	aux->setDir(no->getEsq());

	no->setEsq(aux);

    aux->setAltura();
	no->setAltura();

	return no;
}

node *arvoreAVL::rotacaoDir(node *no){

	node *aux = no;

	no = no->getEsq();

	aux->setEsq(no->getDir());

	no->setDir(aux);

    aux->setAltura();
	no->setAltura();

return no;
}

node *arvoreAVL::rotacaoDuploEsq(node *no){

	no = rotacaoDir(no->getDir());

	no = rotacaoEsq(no);
	
	return no;
}

node *arvoreAVL::rotacaoDuploDir(node *no){

	no = rotacaoEsq(no->getEsq());

	no = rotacaoDir(no);

	return no;

}




/* 

Passos para construção

    AVL trees são arvoreAVLs binarias de busca em que a diferença de altura entre  
    um nó só pode ser 1 ou 0.
    
    1. Adicionar o atributo altura nos nós.
    2. Adicionar o atribituo altura na árvore.
    
    Toda vez que é inserido um valor na árvore, ela deve ser rebalanceada
    
    3. Implementar inserção com rotação de árvore para 4 casos:
    
    Left-Left (LL)	
    The unbalanced node and its left child node are both left-heavy.
    A single right rotation.
    
    Right-Right (RR)
    The unbalanced node and its right child node are both right-heavy.	
    A single left rotation.
    
    Left-Right (LR)	
    The unbalanced node is left heavy, and its left child node is right heavy.	
    First do a left rotation on the left child node, then do a right rotation on the unbalanced node.
    
    Right-Left (RL)	
    The unbalanced node is right heavy, and its right child node is left heavy.	
    First do a right rotation on the right child node, then do a left rotation on the unbalanced node.
        
        
    


Passos na execução

    1. Adquirir dados da entrada, no formato "operação nó"
    2. Para cada dado, realizar a operação e armazenar em uma árvore
    3. Printar a arovre ao final no formato "nó altura"

*/

int main()
{
	arvoreAVL tree;
	tree.inserir(50);
	tree.emOrdem(tree.getRaiz());
	cout << "\n";
	tree.inserir(30);
	tree.emOrdem(tree.getRaiz());
	cout << "\n";
	tree.inserir(20);
	tree.emOrdem(tree.getRaiz());
	cout << "\n";
	// tree.inserir(90);
	// tree.emOrdem(tree.getRaiz());
	// cout << "\n";
	// tree.inserir(100);
	// tree.emOrdem(tree.getRaiz());
	// cout << "\n";
	// tree.inserir(120);
// 	tree.inserir(45);
// 	tree.inserir(37);
// 	tree.inserir(85);
// 	tree.inserir(100);

	tree.emOrdem(tree.getRaiz());
	cout << "\n";


	return 0;
}