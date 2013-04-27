//
//  iteratorbptree.h
//  Btree-Disk
//
//  Created by Jan Quequezana on 26/04/13.
//  Copyright (c) 2013 Jan Quequezana. All rights reserved.
//

#ifndef __Btree_Disk__iteratorbptree__
#define __Btree_Disk__iteratorbptree__
#include "pagemanager.h"

template <class BPT>
class IteratorBPTree {
    public:
    typedef typename BPT::Node Node;
    typedef typename BPT::Type Type;
    typedef IteratorBPTree<BPT> Self;
    
    IteratorBPTree();
    IteratorBPTree(const Self& obj);
    IteratorBPTree(const Node& node_it, PageManager* pagemanager);
    
    Self& operator++ (int);
    Type operator* ();
    bool operator!= (const Self& it);
    
    
    private:
    PageManager* pagemanager_;
    Node node_it_;
    long node_index_;
};

#include "iteratorbptree.cpp"
#endif /* defined(__Btree_Disk__iteratorbptree__) */
