//
//  btreedisk.cpp
//  Btree-Disk
//
//  Created by Jan Quequezana on 26/04/13.
//  Copyright (c) 2013 Jan Quequezana. All rights reserved.
//

#ifdef __Btree_Disk__btreedisk__

template <class T, int ORDER>
BTreeDisk<T, ORDER>::BTreeDisk(PageManager& page_manager) : page_manager_(page_manager) {
    order_ = ORDER;
    page_manager_.recover(0, header_);
    page_manager_.recover(1, root_);
    if (page_manager_.is_empty()) {
        header_ = 0;
    }
}

template <class T, int ORDER>
void BTreeDisk<T, ORDER>::Insert (const T& value) {
    if (header_ == 0) {
        root_ = CreateNode();
        WriteNode(root_.page_index, root_);
    }
    int overflow = Insert(value, root_.page_index);
    if (overflow) {
        SplitRoot();
    }
}

template <class T, int ORDER>
int BTreeDisk<T, ORDER>::Insert (const T& value, long page_index) {
    Node node;
    ReadNode(page_index, node);
    int index = 0;
    while (index < node.count && node.data[index] < value) {
        index++;
    }
    if (node.children[index] != 0) {
        int overflow = Insert(value, node.children[index]);
        if (overflow) {
            SplitNode(node, index);
        }
    }
    else {
        InsertDataInNode(value, index, node);
        WriteNode(page_index, node);
    }
    return NodeIsOverflow(node);
}

template <class T, int ORDER>
void BTreeDisk<T, ORDER>::InsertDataInNode (const T& value, int index, Node& node) {
    int i = node.count;
    while (i > index) {
        node.data[i] = node.data[i - 1];
        node.children[i + 1] = node.children[i];
        --i;
    }
    node.data[i] = value;
    node.children[i + 1] = node.children[i];
    node.count++;
}

template <class T, int ORDER>
void BTreeDisk<T, ORDER>::SplitRoot () {
    Node node_root;
    ReadNode(root_.page_index, node_root);
    Node& node_in_overflow = node_root;
    
    Node child_one = CreateNode();
    Node child_two = CreateNode();
    
    int pos = 0;
    int iter = 0;
    int i;
    for (i = 0; iter < order_ / 2 ; i++) {
        child_one.children[i] = node_in_overflow.children [iter];
        child_one.data[i] = node_in_overflow.data [iter];
        child_one.count++;        
        iter++;
    }
    child_one.children[i] = node_in_overflow.children[iter];
    child_two.next = node_in_overflow.next;
    
    if (child_one.children[0] == 0)  {
        child_one.next = child_two.page_index;
    }
    else {
        iter++;
    }
    for (i = 0; iter < order_ + 1; i++) {
        child_two.children[i] = node_in_overflow.children[iter];
        child_two.data[i] = node_in_overflow.data[iter];
        child_two.count++;
        
        iter++;
    }
    child_two.children[i] = node_in_overflow.children[iter];
    
    node_root.children[pos] = child_one.page_index;
    node_root.data[0] = node_in_overflow.data[order_ / 2];
    node_root.children[pos + 1] = child_two.page_index;
    node_root.count = 1;
    
    WriteNode(node_root.page_index, node_root);
    WriteNode(child_one.page_index, child_one);
    WriteNode(child_two.page_index, child_two);
}

template <class T, int ORDER>
void BTreeDisk<T, ORDER>::SplitNode (Node& node, int index) {
    long page_index = node.children[index];
    Node node_in_overflow;
    ReadNode(page_index, node_in_overflow);
    Node& child_one = node_in_overflow;
    child_one.count = 0;
    Node child_two = CreateNode();
    
    int iter = 0;
    int i;
    for (i = 0; iter < order_ / 2 ; i++) {
        child_one.children[i] = node_in_overflow.children [iter];
        child_one.data[i] = node_in_overflow.data [iter];
        child_one.count++;
        iter++;
    }
    
    child_one.children[i] = node_in_overflow.children[iter];
    
    InsertDataInNode(node_in_overflow.data[iter], index, node);
    
    child_two.next = node_in_overflow.next;
    
    if (child_one.children[0] == 0)  {
        child_one.next = child_two.page_index;
    }
    else {
        iter++;
    }
    
    for (i = 0; iter < order_ + 1; i++) {
        child_two.children[i] = node_in_overflow.children[iter];
        child_two.data[i] = node_in_overflow.data[iter];
        child_two.count++;
        iter++;
    }
    child_two.children[i] = node_in_overflow.children[iter];
    
    node.children[index] = child_one.page_index;
    node.children[index + 1] = child_two.page_index;
    
    
    WriteNode(node.page_index, node);
    WriteNode(child_one.page_index, child_one);
    WriteNode(child_two.page_index, child_two);
}


template <class T, int ORDER>
typename BTreeDisk<T, ORDER>::Node BTreeDisk<T, ORDER>::CreateNode() {
    // Incrementar el header (se agrega un nuevo elemento)
    header_++;                      // Incrementando el header en memoria
    page_manager_.save(0, header_); // Guardando header en disco
    
    // Creando un nuevo nodo en memoria
    Node new_node;
    new_node.page_index = header_;  // El indice del nuevo nodo es el tamano de la estructura
    return new_node;
}


template <class T, int ORDER>
bool BTreeDisk<T, ORDER>::NodeIsOverflow (Node& node) {
    return node.count > order_;
}

template <class T, int ORDER>
void BTreeDisk<T, ORDER>::WriteNode (long page_index,  Node& node) {
    page_manager_.save(page_index, node);
}

template <class T, int ORDER>
void BTreeDisk<T, ORDER>::ReadNode (long page_index, Node& node) {
    page_manager_.recover(page_index, node);
}


/*
 * Iterators
 */

template <class T, int ORDER>
typename BTreeDisk<T, ORDER>::iterator BTreeDisk<T, ORDER>::begin () {
    Node node;
    ReadNode(root_.page_index, node);
    // Going to the leaf ... left;
    while (node.children[0] != 0) {
        ReadNode(node.children[0], node);
    }
    iterator itbegin(node, &page_manager_);
    return itbegin;
}

template <class T, int ORDER>
typename BTreeDisk<T, ORDER>::iterator BTreeDisk<T, ORDER>::end () {
    Node node_end;
    iterator itend(node_end, &page_manager_);
    return itend;
}


#endif