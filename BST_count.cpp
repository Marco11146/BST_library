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

int countNodes(Node* radice) {
    if(radice == nullptr){
        return 0;
    }

    return 1 + countNodes(radice->lchild) + countNodes(radice->rchild);
}

int countLeaves(Node* radice){
    if(radice == nullptr){
        return 0;
    }

    if(radice->lchild == nullptr && radice->rchild == nullptr){
        return 1;
    }

    return countLeaves(radice->lchild) + countLeaves(radice->rchild);
}

int countInRange(Node* radice, const int &min, const int &max){
    if(radice == nullptr){
        return 0;
    }

    if(radice->data <= max && radice->data >= min){
        return 1 + countInRange(radice->lchild, min, max) + countInRange(radice->rchild, min, max);
    } else{
        return 0 + countInRange(radice->lchild, min, max) + countInRange(radice->rchild, min, max);
    }
}