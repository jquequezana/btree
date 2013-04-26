//
//  btnode.cpp
//  Btree-Disk
//
//  Created by Jan Quequezana on 26/04/13.
//  Copyright (c) 2013 Jan Quequezana. All rights reserved.
//
#ifdef Btree_Disk_btnode_h


template <class T, int ORDER>
BTNode<T, ORDER>::BTNode() : count_(0) {
    for (int i = 0; i < ORDER + 2; ++i) {
        children_[i] = NULL;
    }
};

template <class T, int ORDER>
void BTNode<T, ORDER>::Insert(int index, const T& value) {
    int i = count_;
    while (i > index) {
        data_[i] = data_[i - 1];
        children_[i + 1] = children_[i];
        --i;
    }
    data_[i] = value;
    children_[i + 1] = children_[i];
    ++count_;
}

template <class T, int ORDER>
int BTNode<T, ORDER>::Insert(const T& value) {
    int index = 0;
    while(index < count_ && data_[index] < value  ) {
        index++;
    }
    if ( children_[index] != NULL) {
        int overflow = children_[index]->Insert(value);
        if (overflow == true) {
            Split(index);
        }
    }
    else {
        Insert(index, value);
    }
    return IsOverflow();
}


template <class T, int ORDER>
void BTNode<T, ORDER>::Split (int index) {
    Self* node_in_overflow = children_[index];
    Self* child1 = node_in_overflow;
    child1->count_ = 0;
    Self* child2 = new Self();
    
    
    int iter = 0;
    int i;
    for (i = 0; iter < ORDER / 2; i++) {
        child1->children_[i] = node_in_overflow->children_[iter];
        child1->data_[i] = node_in_overflow->data_[iter];
        child1->count_++;
        
        iter++;
    }
    child1->children_[i] = node_in_overflow->children_[iter];
    
    Insert(index, node_in_overflow->data_[iter]);

    iter++; // the middle element
    
    for (i = 0; iter < ORDER + 1; i++) {
        child2->children_[i] = node_in_overflow->children_[iter];
        child2->data_[i] = node_in_overflow->data_[iter];
        child2->count_++;
        iter++;
    }
    child2->children_[i] = node_in_overflow->children_[iter];
    
    children_[index] = child1;
    children_[index + 1] = child2;
    
}

template <class T, int ORDER>
bool BTNode<T, ORDER>::IsOverflow() {
    return count_ > ORDER;
}


#endif