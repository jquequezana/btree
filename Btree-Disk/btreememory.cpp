//
//  btreememory.cpp
//  Btree-Disk
//
//  Created by Jan Quequezana on 26/04/13.
//  Copyright (c) 2013 Jan Quequezana. All rights reserved.
//

#ifdef Btree_Disk_btreememory_h

template <class T, int ORDER>
BTreeMemory<T, ORDER>::BTreeMemory() : root_(0) {
    
}

template <class T, int ORDER>
void BTreeMemory<T, ORDER>::Insert (const T& value) {
    if (root_ == 0) {
        root_ = new Node();
    }
    else {
        int overflow = root_->Insert(value);
        if (overflow) {
            SplitRoot();
        }
    }
}

template <class T, int ORDER>
void BTreeMemory<T, ORDER>::SplitRoot () {
    Node* node_in_overflow = root_;
    Node* child1 = new Node();
    Node* child2 = new Node();
    
    int pos = 0;
    int iter = 0;
    int i;
    for (i = 0; iter < ORDER / 2 ; i++) {
        child1->children_[i] = node_in_overflow->children_[iter];
        child1->data_[i] = node_in_overflow->data_[iter];
        child1->count_++;
        iter++;
    }
    child1->children_[i] = node_in_overflow->children_[iter];
    iter++; 
    for (i = 0; iter < ORDER + 1; i++) {
        child2->children_[i] = node_in_overflow->children_[iter];
        child2->data_[i] = node_in_overflow->data_[iter];
        child2->count_++;
        
        iter++;
    }
    child2->children_[i] = node_in_overflow->children_[iter];
    
    root_->children_[pos] = child1;
    root_->data_[0] = node_in_overflow->data_[ORDER / 2];
    root_->children_[pos+1] = child2;
    root_->count_ = 1;
}

template <class T, int ORDER>
void BTreeMemory<T, ORDER>::Print(Node* ptr) {
    if (ptr) {
        int i;
        Print(ptr->children_[0]);
        for (i = 0; i < ptr->count_; i++) {
            std::cout << ptr->data_[i] << " ";
            Print(ptr->children_[i+1]);
        }

    }
}

#endif