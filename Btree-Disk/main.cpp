//
//  main.cpp
//  Btree-Disk
//
//  Created by Jan Quequezana on 24/04/13.
//  Copyright (c) 2013 Jan Quequezana. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include "btreedisk.h"
#include "pagemanager.h"

using namespace std;
int main(int argc, const char * argv[]) {
 
    PageManager pg("/tmp/index.dat", 64);
    srand(1);
    BTreeDisk<int, 850> a(pg);
    int limit = 100000;
    for (int i = 0; i < limit; i++) {
        a.Insert(rand() % limit);
    }
    a.Print();
    
    return 0;
}

