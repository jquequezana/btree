//
//  btnode.h
//  Btree-Disk
//
//  Created by Jan Quequezana on 25/04/13.
//  Copyright (c) 2013 Jan Quequezana. All rights reserved.
//

#ifndef Btree_Disk_btnode_h
#define Btree_Disk_btnode_h

template <class T, int ORDER>
class BTNode {
    public:
    typedef BTNode<T, ORDER> Self;
    
    BTNode ();
    void Insert (int index, const T& value);
    int Insert (const T& value);
    void Split (int index);
    bool IsOverflow ();
    
    int count_;
    T data_[ORDER + 1];
    Self* children_[ORDER + 2];
};

#include "btnode.cpp"
#endif
