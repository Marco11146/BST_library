// Esercitazione (90 minuti): refactoring di un BST, da struct a classi - classe 4C
// Nome/Codice: Hasanaj Marco
//
// Trasforma la libreria del Binary Search Tree: la struct Node diventa una classe con
// attributi privati e le funzioni libere diventano metodi di una nuova classe BST.
// I nomi dei metodi sono quelli scritti qui sotto e usati da main.cpp: decidi tu
// parametri e tipo restituito, guardando anche come li usa main.cpp.
// NON modificare main.cpp. Consegna SOLO questo file (bst.cpp).
// Se un metodo non riesci a scriverlo, lascia almeno una versione vuota
// (che restituisce un valore qualsiasi) per far compilare il programma.

#include <iostream>
using namespace std;

// =====================================================================
// PARTE A - la classe Node (circa 15 minuti)
// =====================================================================

class Node {
private:
    // TODO 1 - gli attributi: la chiave (int) e i puntatori ai due figli.
    //          Usa gli stessi nomi della struct originale: data, left, right.
    int data;
    Node* left;
    Node* right;
public:
    // TODO 1 - costruttore Node
    //          Riceve la chiave. All'inizio il nodo non ha figli (entrambi i puntatori valgono nullptr).
    //          Dai al parametro un nome diverso da quello dell'attributo.
    Node(int key){
        data = key;
        left = nullptr;
        right = nullptr;
    }
    // TODO 2 - getData, getLeft, getRight
    //          Restituiscono la chiave, il figlio sinistro e il figlio destro.
    int getData() const{
        return data;
    }
    Node* getLeft() const{
        return left;
    }
    Node* getRight() const{
        return right;
    }
    // TODO 3 - setData, setLeft, setRight
    //          Modificano la chiave e collegano il figlio sinistro e il figlio destro.
    //          setLeft e setRight ricevono l'indirizzo di un nodo (o nullptr per scollegare).
    void setData(int key){
        data = key;
    }
    void setLeft(Node* n){
        left = n;
    }
    void setRight(Node* n){
        right = n;
    }
    // TODO 4 - isLeaf
    //          Dice se il nodo e' una foglia, cioe' se non ha nessun figlio.
    bool isLeaf(){
        if(left == nullptr && right == nullptr){
            return true;
        }
        return false;
    }
};

// =====================================================================
// PARTE B - la classe BST: struttura, inserimento, ricerca, visita (circa 30 minuti)
// L'albero conosce solo la radice e il numero di nodi: da fuori non si vede nessun Node.
// =====================================================================

class BST {
private:
    Node* root;         // radice dell'albero, nullptr se l'albero e' vuoto
    int numNodi;        // numero di chiavi presenti

    // Qui puoi aggiungere funzioni di appoggio private (per esempio quelle ricorsive,
    // che hanno bisogno di ricevere un nodo come argomento).
    void inOrderHelper(Node* root){
        if(root == nullptr){
            return;
        }
        inOrderHelper(root->getLeft());
        cout << root->getData() << " ";
        inOrderHelper(root->getRight());
    }
    int heightHelper(Node* root){
        if(root == nullptr){
            return 0;
        }

        int leftHeight = heightHelper(root->getLeft());
        int rightHeight = heightHelper(root->getRight());

        if(leftHeight > rightHeight){
            return 1 + leftHeight;
        } else{
            return 1 + rightHeight;
        }
    }
    Node* removeHelper(Node* current, int key, bool &rimosso){
        if(current == nullptr){
            return nullptr;
        }
        if(key < current->getData()){
            current->setLeft(removeHelper(current->getLeft(), key, rimosso));
        }
        else if(key > current->getData()){
            current->setRight(removeHelper(current->getRight(), key, rimosso));
        }
        else{
            rimosso = true;
            if(current->getLeft() == nullptr && current->getRight() == nullptr){
                delete current;
                return nullptr;
            } else if(current->getLeft() == nullptr){
                Node* temp = current->getRight();
                delete current;
                return temp;
            } else if(current->getRight() == nullptr){
                Node* temp = current->getLeft();
                delete current;
                return temp;
            } else{
                Node* successore = current->getRight();
                while(successore->getLeft() != nullptr){
                    successore = successore->getLeft();
                }
                current->setData(successore->getData());
                bool successoreRimosso = false;
                current->setRight(removeHelper(current->getRight(), successore->getData(), successoreRimosso));
            }
        }
        return current;
    }
    int contaFoglieHelper(Node* current){
        if(current == nullptr){
            return 0;
        }
        if(current->isLeaf()){
            return 1;
        }
        return contaFoglieHelper(current->getLeft()) + contaFoglieHelper(current->getRight());
    }
    int contaIntervalloHelper(Node* current, int low, int high){
        if(current == nullptr){
            return 0;
        }

        int count = 0;

        if(current->getData() >= low && current->getData() <= high){
            count++;
        }

        if(current->getData() > low){
            count += contaIntervalloHelper(current->getLeft(), low, high);
        }

        if(current->getData() < high){
            count += contaIntervalloHelper(current->getRight(), low, high);
        }

        return count;
    }

public:
    // TODO 5 - costruttore BST, isEmpty, size
    //          Il costruttore crea un albero vuoto. isEmpty dice se l'albero e' vuoto,
    //          size restituisce quante chiavi contiene.
    BST(){
        root = nullptr;
        numNodi = 0;
    }
    bool isEmpty(){
        if(root == nullptr){
            return true;
        }
        return false;
    }
    int size(){
        return numNodi;
    }
    // TODO 6 - insert
    //          Riceve una chiave e la inserisce al posto giusto creando un nuovo Node con new.
    //          Niente duplicati: se la chiave e' gia' presente non fa nulla.
    //          Dice se la chiave e' stata inserita.
    bool insert(int key){
        if(root == nullptr){
            root = new Node(key);
            numNodi++;
            return true;
        }

        Node* parent{nullptr};
        Node* current{root};

        while(current != nullptr){
            parent = current;

            if(key < current->getData()){
                current = current->getLeft();
            } else if(key > current->getData()){
                current = current->getRight();
            } else{
                return false;
            }
        }

        if(key < parent->getData()){
            parent->setLeft(new Node(key));
        } else{
            parent->setRight(new Node(key));
        }

        numNodi++;
        return true;
    }
    // TODO 7 - search
    //          Dice se una chiave e' presente nell'albero (non modifica l'albero).
    bool search(int key){
        if(root == nullptr){
            return false;
        }

        Node* current{root};

        while(current != nullptr){
            if(key < current->getData()){
                current = current->getLeft();
            } else if(key > current->getData()){
                current = current->getRight();
            } else{
                return true;
            }
        }
        return false;
    }
    // TODO 8 - inOrder
    //          Stampa su cout tutte le chiavi in ordine crescente (visita inorder),
    //          ciascuna seguita da uno spazio. Se l'albero e' vuoto non stampa nulla.
    //          Non va a capo: ci pensa il main.
    void inOrder(){
        inOrderHelper(root);
    }
    // TODO 9 - height
    //          Restituisce l'altezza dell'albero, cioe' il numero di nodi del cammino piu' lungo
    //          dalla radice a una foglia. Albero vuoto: 0.
    int height(){
        return heightHelper(root);
    }
    // TODO 10 - minimo, massimo
    //          Restituiscono la chiave piu' piccola e quella piu' grande.
    //          Per un albero vuoto restituiscono -1 (nell'esercizio le chiavi sono sempre positive).
    int minimo(){
        if(root == nullptr){
            return -1;
        }

        Node* parent{nullptr};
        Node* current{root};

        while(current != nullptr){
            parent = current;
            current = current->getLeft();
        }
        return parent->getData();
    }
    int massimo(){
        if(root == nullptr){
            return -1;
        }

        Node* parent{nullptr};
        Node* current{root};

        while(current != nullptr){
            parent = current;
            current = current->getRight();
        }
        return parent->getData();
    }
    // =================================================================
    // PARTE C - cancellazione e memoria (circa 30 minuti)
    // =================================================================

    // TODO 11 - remove
    //          Elimina una chiave dall'albero e dice se esisteva. Gestisci i tre casi:
    //          nodo senza figli, con un figlio, con due figli (si sostituisce la chiave con
    //          quella del successore). Ogni nodo tolto va liberato con delete.
    bool remove(int key){
        bool rimosso = false;
        root = removeHelper(root, key, rimosso);

        if(rimosso){
            numNodi--;
        }
        return rimosso;
    }
    // TODO 12 - svuota
    //          Libera con delete tutti i nodi e riporta l'albero allo stato vuoto.
    //          Deve poter essere chiamata anche due volte di fila senza danni.
    void svuota(){
        while(root != nullptr){
            Node* current = root;

            if(current->getLeft() != nullptr){
                Node* sinistro = current->getLeft();

                current->setLeft(sinistro->getRight());
                sinistro->setRight(current);
                root = sinistro;
            } else{
                root = current->getRight();
                delete current;
            }
        }
        numNodi = 0;
    }
    // TODO 13 - contaFoglie
    //          Restituisce quante foglie ha l'albero (usa isLeaf). Albero vuoto: 0.
    int contaFoglie(){
        return contaFoglieHelper(root);
    }
    // BONUS TODO 14 - contaIntervallo
    //          Riceve due chiavi low e high e restituisce quante chiavi dell'albero sono comprese
    //          tra low e high (estremi inclusi). Sfrutta la proprieta' del BST: non serve
    //          visitare i sottoalberi che non possono contenere chiavi dell'intervallo.
    int contaIntervallo(int low, int high){
        if(low > high){
            return 0;
        }
        return contaIntervalloHelper(root, low, high);
    }
};

// =====================================================================
// PARTE D - domande e controllo finale (circa 15 minuti)
// Rispondi qui sotto, in due o tre righe ciascuna.
// =====================================================================
//
// 1) Perche' gli attributi di Node sono private? Cosa si guadagna rispetto alla struct,
//    in cui qualunque funzione poteva scrivere in data, left e right?
//    Risposta: Per impedire che vengano modificati direttamente dall'esterno. 
//              Si guadagna la possibilità di rendere gli attributi non direttamente
//              accessibili dall'esterno.
//
// 2) Nella struct la radice veniva passata come argomento a ogni funzione; nella classe
//    BST la radice e' un attributo. Cosa cambia per chi usa l'albero (guarda il main)?
//    Risposta: Chi usa l'albero non deve più passare la radice come argomento a ogni funzione.
//
// 3) Perche' di solito un metodo ricorsivo come insert o inOrder ha bisogno di una funzione di appoggio
//    privata che riceve un nodo, e non puo' essere scritto direttamente come metodo pubblico?
//    Risposta: Perché le funzioni di appoggio possono ricevere un nodo come parametro e richiamarsi 
//              ricorsivamente sui suoi figli.
//
// 4) Chi e' responsabile di liberare i nodi creati con new? In quale momento lo si fa,
//    e cosa succederebbe se ci si dimenticasse?
//    Risposta: La classe BST. Lo si fa quando si vuole rimuovere un nodo o svuotare 
//              l'albero. Se ci si dimentica, avverrà un memory leak.