//
//  btreedisk.h
//  Btree-Disk
//
//  Created by Jan Quequezana on 26/04/13.
//  Copyright (c) 2013 Jan Quequezana. All rights reserved.
//

#ifndef __Btree_Disk__btreedisk__
#define __Btree_Disk__btreedisk__

#include "pagemanager.h"
#include "btnodedisk.h"

template <class T, int ORDER>
class BTreeDisk {
public:
    typedef BTNodeDisk<T, ORDER> Node;
    typedef long Header;
    
    BTreeDisk(PageManager& page_manager);    
    void Insert (const T& value);
    void Print (long page_index = 1);

    
private:
    Node CreateNode();
    int Insert (const T& value, long page_index);
    void InsertDataInNode (const T& value, int index, Node& node);
    void SplitRoot ();
    void SplitNode (Node& node, int index);
    bool NodeIsOverflow (Node& node);
    void WriteNode (long page_index,  Node& node_data);
    void ReadNode (long page_index, Node& node_data);
        
    Header header_;
    Node root_;
    PageManager& page_manager_;
    int order_ = ORDER;
};

#include "btreedisk.cpp"



#endif /* defined(__Btree_Disk__btreedisk__) */
