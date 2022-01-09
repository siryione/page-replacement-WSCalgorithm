#ifndef MMU
#define MMU
#include "vector"
#include "constants.hpp"
#include "VirtualPage.hpp"

struct PageTableEntry{
    int physical_address;
    VirtualPage* virtual_page;
};


class MemManagementUnit{
    int physical_page_count;
    std::vector<PageTableEntry> page_table;
    int get_or_change_physical_page(VirtualPage* virtual_page);
    int virtual_current_time;
    int arrow_index;
public:
    int page_fault_count;
    MemManagementUnit(int physicalPageCount);
    void read(VirtualPage* virtual_page_ptr);
    void write(VirtualPage* virtual_page_ptr);
    void free(VirtualPage* virtual_page_ptr);
};

#endif
