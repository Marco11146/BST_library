bool BST_search(Node* radice, int key){

    Node* current{radice};

    while(current != nullptr){
        if(key < current->data){
            current = current->lchild;
        } else if(key > current->data){
            current = current->rchild;
        } else{
            return true;
        }
    }

    return false;
}