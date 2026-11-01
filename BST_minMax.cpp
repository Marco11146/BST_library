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

Node* findMin(Node* radice){
    if(radice == nullptr){
        return radice;
    }

    Node* parent{nullptr};
    Node* current{radice};

    while(current != nullptr){
        parent = current;
        current = current->lchild;
    }

    return parent;
}

Node* findMax(Node* radice){
    if(radice == nullptr){
        return radice;
    }

    Node* parent{nullptr};
    Node* current{radice};

    while(current != nullptr){
        parent = current;
        current = current->rchild;
    }

    return parent;
}