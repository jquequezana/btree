//
//  btnodedisk.h
//  Btree-Disk
//
//  Created by Jan Quequezana on 26/04/13.
//  Copyright (c) 2013 Jan Quequezana. All rights reserved.
//

#ifndef __Btree_Disk__btnodedisk__
#define __Btree_Disk__btnodedisk__

template <class T, int ORDER>
struct BTNodeDisk {
    BTNodeDisk() {
        count = 0;
        page_index = -1;
        next = -1;
        for (int i = 0; i < ORDER + 2; i++) {
            children[i] = 0;
        }
    }
    long page_index;
    long children[ORDER + 2];
    long next;
    int count;
    T data[ORDER + 1];
};
#endif /* defined(__Btree_Disk__btnodedisk__) */
