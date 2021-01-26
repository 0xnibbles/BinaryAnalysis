#include <bfd.h>
#include "loader.h"

// parse a binary file into Binary object
int load_binary(std::string &fname, Binary *bin, Binary::BinaryType type){
    return load_binary_bfd(fname, bin, type);
}

void unload_binary(Binary *bin){
    size_t i;
    Section *sec;

    for(i=0; i < bin->sections.size(); i++){
        sec = &bin->sections[i];
        if(sec->bytes){
            free(sec->bytes);
        }
    }
}

