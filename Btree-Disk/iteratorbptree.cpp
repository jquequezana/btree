//
//  iteratorbptree.cpp
//  Btree-Disk
//
//  Created by Jan Quequezana on 26/04/13.
//  Copyright (c) 2013 Jan Quequezana. All rights reserved.
//

#ifdef __Btree_Disk__iteratorbptree__


template <class BPT>
IteratorBPTree<BPT>::IteratorBPTree() {
    node_index_ = 0;
    pagemanager_ = 0;
}

template <class BPT>
IteratorBPTree<BPT>::IteratorBPTree(const Self& obj) :
    node_it_(obj.node_it_),
    node_index_(obj.node_index_),
    pagemanager_(obj.pagemanager_) {
}

template <class BPT>
IteratorBPTree<BPT>::IteratorBPTree(const Node& node_it, PageManager* pagemanager) {
    node_it_ = node_it;
    node_index_ = 0;
    pagemanager_ = pagemanager;
    
}

template <class BPT>
typename IteratorBPTree<BPT>::Self& IteratorBPTree<BPT>::operator++ (int) {
    if (node_index_ < node_it_.count - 1) {
        ++node_index_;
    }
    else if (node_it_.next == -1) { // Last node
        node_it_.page_index = -1;
    }
    else { // No Last node
        pagemanager_->recover(node_it_.next, node_it_);
        node_index_ = 0;
    }
    return *this;
}

template <class BPT>
typename IteratorBPTree<BPT>::Type IteratorBPTree<BPT>::operator* () {
    return node_it_.data[node_index_];
}

template <class BPT>
bool IteratorBPTree<BPT>::operator!= (const Self& it) {
    return node_it_.page_index != it.node_it_.page_index;
}



#endif