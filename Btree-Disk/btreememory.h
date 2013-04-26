//
//  btreememory.h
//  Btree-Disk
//
//  Created by Jan Quequezana on 24/04/13.
//  Copyright (c) 2013 Jan Quequezana. All rights reserved.
//

#ifndef Btree_Disk_btreememory_h
#define Btree_Disk_btreememory_h
#include "btnode.h"

template <class T, int ORDER>
class BTreeMemory {
  public:
    typedef T Type;
    typedef BTreeMemory<T, ORDER> Self;
    typedef BTNode<T, ORDER> Node;
    BTreeMemory();
    
    
    void Insert (const T& value);
    void SplitRoot ();
    void Print(Node* ptr);
    
    /* mutators */
    int order () { return order_; };
    Node* root() { return root_; };
    
  private:
    int order_ = ORDER;
    Node* root_;
};

#include "btreememory.cpp"


#endif
