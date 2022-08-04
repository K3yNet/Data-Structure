#include <iostream>
using namespace std;

// função de hash utilizada para cálculo da posição
int funcaoHash(int chave, int capacidade) {
    int h = 0;
    h = chave % capacidade;
    return h;
}

// classe noh armazena um par chave/valor em uma tabela hash
// com tratamento de colisão por encadeamento
class noh {
    friend class tabelaHash;
    private:
        int chave;
        string valor;
        noh* proximo;
    public:
        noh(){
            chave = 0;
            valor = "";
            proximo = NULL;
        }
};

// tabela hash com colisão por encadeamento (usando lista implícita)
class tabelaHash {
    private:
        // vetor de ponteiros de nós (lista implícita para tratar colisões)
        noh** elementos;
        int capacidade;
    public:
        // construtor padrão
        tabelaHash(int cap = 100);
        // destrutor
        ~tabelaHash();
        // insere um valor v com chave c
        void insere(int c, string v);
        // recupera um valor associado a uma dada chave
        string recupera(int c);
        // percorrendo a tabela hash (para fins de depuração)
        void percorre();
};

// construtor padrão
tabelaHash::tabelaHash(int cap) {
    elementos = new noh*[cap];
    capacidade = cap;

    for (int i = 0; i < cap; i++) {
        elementos[i] = NULL;
    }
}

// destrutor
tabelaHash::~tabelaHash() {
    for (int i=0; i < capacidade; i++) {
        noh* atual = elementos[i];

        // percorre a lista removendo todos os nós
        while (atual != NULL) {
            noh* aux = atual;
            atual = atual-> proximo;
            delete aux;
        }
    }
    delete[] elementos;
}

// insere um valor v com chave c
void tabelaHash::insere(int c, string v) {
    
    int posicao = funcaoHash(c,capacidade);
    noh * aux = new noh;
    aux = elementos[posicao];
    if(elementos[posicao] == NULL){
        elementos[posicao] = new noh;
        elementos[posicao]->chave = c;
        elementos[posicao]->valor = v;
    }
    else{
        while(aux->proximo != NULL){
            aux = aux->proximo;
        }
        aux->proximo = new noh;
        aux->proximo->chave = c;
        aux->proximo->valor = v;
    }
}

// recupera um valor associado a uma dada chave
string tabelaHash::recupera(int c) {
    int posicao = funcaoHash(c,capacidade);
    string concatenado ="";
    noh *aux = elementos[posicao];
    while(aux != NULL){
     if(aux->chave == c)
        concatenado = aux->valor;
    aux = aux->proximo;
    }
    return concatenado;
}

// percorrendo a tabela hash (para fins de depuração)
void tabelaHash::percorre( ) {
    noh* atual;
    for (int i = 0; i < capacidade; i++) {
        int z = 0;
        cout << "Posicao " << i << ": ";
        atual = elementos[i];
        while (atual != NULL) {
            cout << atual->chave << " "
                 << atual->valor;
            if (atual->proximo != NULL and z == 0)
            {
                z++;
                atual = atual->proximo;
                cout << endl;
                cout << "Lista de colisao: "
                     << atual->chave << " "
                     << atual->valor;
            }
            if (atual->proximo != NULL and z != 0)
            {
                atual = atual->proximo;
                cout << ", "
                     << atual->chave << " "
                     << atual->valor;
            }
            atual = atual->proximo;
        }
        cout << endl;
    }
    cout << "-----------------------";
}


int main( ) {
    int capacidade;
    cout << "Insira a capacidade: ";
    cin >> capacidade;

    tabelaHash hash(capacidade);
    int chave;
    string valor;

    char opcao;
    cin >> opcao;

    while (opcao != 'Q') {
        cout << "[I] Inserir [R] Recuperar String [P] Percorrer [Q] Exit";
        switch(opcao) {
            case 'I':
                cout << "Insira a Chave: ";
                cin >> chave;
                cout << "Insira a String: ";
                cin >> valor;
                hash.insere(chave,valor);
                break;
            case 'R':
                cout << "Insira a Chave: ";
                cin >> chave;
                cout << hash.recupera(chave) << endl;
                break;
            case 'P':
                hash.percorre();
                break;
        }
        cin >> opcao;
    }

    return 0;
}