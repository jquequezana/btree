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
    srand(1);
    PageManager pg("/tmp/index.dat");
    BTreeDisk<int, 3> bt(pg);
    int limit = 200;
    for (int i = 0; i < limit; i++) {
        bt.Insert(rand() % limit);
    }

    BTreeDisk<int, 3>::iterator it;
    for (it = bt.begin(); it != bt.end(); it++) {
        cout << *it << endl;
    }
    return 0;
}