//
//  main.cpp
//  Btree-Disk
//
//  Created by Jan Quequezana on 24/04/13.
//  Copyright (c) 2013 Jan Quequezana. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include "btreememory.h"
using namespace std;
int main(int argc, const char * argv[])
{
    srand(1);
    BTreeMemory<int, 3> a;
    int limit = 100;
    for (int i = 0; i < limit; i++) {
        a.Insert(rand() % limit);
    }
    a.Print(a.root());

    return 0;
}

