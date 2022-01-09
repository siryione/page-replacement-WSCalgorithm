#ifndef PROCESS
#define PROCESS
#include "vector"
#include "MemManagementUnit.hpp"
#include "VirtualPage.hpp"

class Process{
public:
    int id;
    int working_set_size;
    int virtual_page_count;
    int burst_time;
    Process(){}
    Process(int id, int working_set_size, int virtual_page_count, int burst_time){
        this->id = id;
        this->working_set_size = working_set_size;
        this->virtual_page_count = virtual_page_count;
        this->burst_time = burst_time;
        for(int virtual_page_address = 0; virtual_page_address < virtual_page_count; virtual_page_address++){
            virtual_pages.push_back(VirtualPage{.virtual_page_address = virtual_page_address, .reference_bit = false, .presense_bit = false, .modification_bit= false});
        }
    }
    std::vector<VirtualPage> virtual_pages;
    void changeWorkingSet();
};

#endif
