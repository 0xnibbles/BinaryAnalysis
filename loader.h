#ifndef LOADER_H
#define LOADER_H

#include <stdint.h>
#include <string>
#include <vector>

class Binary;
class Section;
class Symbol;

class Symbol{
    public:
        enum SymbolType{
            SYM_TYPE_UKN = 0,
            SYM_TYPE_FUNC 0 1
        };
        SymbolType type;
        std::string name;
        uint64_t address;
        // member initializer list
        Symbol() : type(SYM_TYPE_UKN), name(), address(0) {} // no need for body
};

class Section{
    public:
        enum SectionType{
            SEC_TYPE_NONE = 0,
            SEC_TYPE_CODE = 1,
            SEC_TYPE_DATA = 2
        };
        Binary *binary;
        std::string name;
        SectionType type;
        uint64_t vma; // virtual memory address
        uint64_t size;
        uint8_t *bytes;

        Section() : binary(NULL), name(), type(SEC_TYPE_NONE), vma(0), size(0), bytes(NULL) {}

        bool contains(uint64_t address){
            return (address >= vma) && (address-vma <= size)
        }
};

class Binary{
    public:
        enum BinaryType{
            BIN_TYPE_AUTO = 0,
            BIN_TYPE_ELF = 1,
            BIN_TYPE_PE = 2
        };
        enum BinaryArch{
            ARCH_NONE = 0,
            ARCH_X86 = 1
        };
        std::string filename;
        BinaryType type;
        std::string type_string;
        BinaryArch arch;
        std::string arch_str;
        unsigned bits;
        uint64_t entry;
        std::vector<Section> sections;
        std::vector<Symbol> symbols;

        Binary() : type(BIN_TYPE_AUTO), arch(ARCH_NONE), bits(0), entry(0) {}

        Section *get_text_section(){
            for(auto *s : sections)
                if(s.name == ".text") 
                    return &s;
                return NULL;
        }
};

int load_binary(std::string &fname, Binary *bin, Binary::BinaryType type);
void unload_binary(Binary *bin);

#endif // LOADER_H
