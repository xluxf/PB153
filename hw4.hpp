#define BRICK_BENCHMARK_REG
#define BRICK_BENCHMARK_MAIN

// benchmark of hashtables

#define SIZE 65536

struct bitvector_set_uint16_t
{

    bool table[SIZE];

    bitvector_set_uint16_t() {
        for (int i = 0; i < SIZE; i++) {
            table[i] = false;
        }
    }

    void insert( uint16_t c ) { 
        table[int(c)] = true;
    }

    void erase( uint16_t c ) { 
        table[int(c)] = false;
    }

    int count( uint16_t c ) {

        return table[int(c)];
    }

    bitvector_set_uint16_t operator&( const bitvector_set_uint16_t &o ) { 

        bitvector_set_uint16_t res;
        for (int i = 0; i < SIZE; i++) {

            res.table[i] = this->table[i] && o.table[i];
        }
        return res;
    }

    bitvector_set_uint16_t operator|( const bitvector_set_uint16_t &o ) { 

        bitvector_set_uint16_t res;
        for (int i = 0; i < SIZE; i++) {

            res.table[i] = this->table[i] || o.table[i];
        }
        return res;

    }
};

struct InnerNode
{
    InnerNode(bool end) : end(end) {}
    InnerNode(){
        for (int i = 0; i < 4; i++) {
            succesor[i] = NULL; // unnecessary
            leaf[i] = 0; // unnecessary
        }
    }

    bool end;
    InnerNode * succesor[4];
    uint64_t leaf[4];

    
};


struct NibbletrieSetUint16
{

    InnerNode root;


    NibbletrieSetUint16() {  
    }

    void insert( uint16_t number ) { 

        InnerNode * ptr = &root;

        for (uint i = 1; i <= 4; i++) {
            uint index = (number >> uint(16 - 2*i)) % 4;
            
            if ( ptr == NULL ) {
                ptr = new InnerNode();
            }
            
            ptr = ptr->succesor[index];
        }

        uint index = (number >> 10 ) & 0x11;

        uint shift = number & 0x111111;
        ptr->leaf[index] |= 1 << shift;

    }



    NibbletrieSetUint16 operator|( const NibbletrieSetUint16 &o ) { 

        NibbletrieSetUint16 res;

        // projit vsechny vrstvy
        // pokud v alespon jedne existuje Node, vytvorit jej
        // pokud existuje jen v jedne, zkopirovat ho

        return res;

    }
};



// to same na 16bitech
// set 16 jako bitset
// nible_trie ??
// - union, insert
// 



