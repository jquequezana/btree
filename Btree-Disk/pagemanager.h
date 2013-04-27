//
//  pagemanager.h
//  Btree-Disk
//
//  Created by Jan Quequezana on 26/04/13.
//  Copyright (c) 2013 Jan Quequezana. All rights reserved.
//

#ifndef __Btree_Disk__pagemanager__
#define __Btree_Disk__pagemanager__

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;

class PageManager : protected fstream{
public:
	PageManager(string file_name) : fstream(file_name.data(), ios::in | ios::out | ios::binary )
	{
        empty = false;
        fileName = file_name;
        if(!good()) {
            empty = true;
            open(file_name.data(), ios::in | ios::out | ios::trunc | ios::binary );
        }
	}
	PageManager() {
		close();
	}
    bool is_empty() {
        return empty;
    }
    template<class Register>
    void save(const long &n ,Register &reg)
    {
        clear();
        seekp(n*sizeof(Register), ios::beg);
        write(reinterpret_cast<const char *> (&reg), sizeof(reg));
        
    }
    
    template<class Register>
    
    long save(Register &reg)
    {
        clear();
        seekp(0, ios::end);
        write(reinterpret_cast<const char *> (&reg), sizeof(reg));
        
        return page_id_count - 1;
    }
    
    template<class Register>
    
    bool recover(const long &n, Register &reg)
    {
        clear();
        seekg(n*sizeof(Register), ios::beg);
        read(reinterpret_cast< char *> (&reg), sizeof(reg));
        return gcount() > 0;
    }
    
    // Marca el registro como borrado:
    
    template<class Register>
    void erase(const long &n)
    {
        char mark;
        clear();
        mark = 'N';
        seekg(n*sizeof(Register), ios::beg);
        write(&mark, 1);
        
    }
    
    
private:
	string fileName;
    bool empty;
    long page_id_count;
    
};

#endif
