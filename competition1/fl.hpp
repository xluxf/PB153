#include "../hashTables.h"
#include <algorithm>

struct fl
{

	bool table[256];

	fl() {
		for (int i = 0; i < 256; i++) {
			table[i] = false;
		}
	}

    void insert( char c ) { 
    	table[int(c)] = true;
    }

    void erase( char c ) { 
    	table[int(c)] = false;
    }

    int count( char c ) {

    	return table[c] == true;
    }

    fl operator&( const fl &o ) { 

    	fl res;
    	for (int i = 0; i < 256; i++) {
    		if (this->table[i] && o.table[i])
    			res.table[i] = true;
    		else 
    			res.table[i] = false;
    	}
    	return res;
    }

    fl operator|( const fl &o ) { 

    	fl res;
    	for (int i = 0; i < 256; i++) {
    		if (this->table[i] || o.table[i])
    			res.table[i] = true;
    		else 
    			res.table[i] = false;
    	}
    	return res;

  	}
};



// to same na 16bitech
// set 16 jako bitset
// nible_trie ??
// - union, insert
// 