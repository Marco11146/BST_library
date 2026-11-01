struct Node{
    int data;
    Node* lchild;
    Node* rchild;
    Node(int k){
        data = k;
        lchild = nullptr;
        rchild = nullptr;
    }
};

Node* insert(Node* radice, int n){
    if(radice == nullptr){
        return new Node(n);
    }

    Node* parent{nullptr};
    Node* current{radice};

    while(current != nullptr){
        parent = current;
        if(n < current->data){
            current = current->lchild;
        } else if(n > current->data){
            current = current->rchild;
        } else{
            return radice;
        }
    }
    if(n < parent->data){
        parent->lchild = new Node(n);
    } else if(n > parent->data){
        parent->rchild = new Node(n);
    }
    return radice;
}