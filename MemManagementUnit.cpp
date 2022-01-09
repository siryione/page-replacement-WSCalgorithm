#include "MemManagementUnit.hpp"
#include "VirtualPage.hpp"

MemManagementUnit::MemManagementUnit(int physical_page_count){
    this->virtual_current_time = 0;
    this->arrow_index = 0;
    this->physical_page_count = physical_page_count;
    PageTableEntry free_entry = {.physical_address = 0, .virtual_page = nullptr};
    this->page_table = std::vector<PageTableEntry>();
    for(int physical_page_address = 0; physical_page_address < physical_page_count; physical_page_address++){
        free_entry.physical_address = physical_page_address;
        page_table.push_back(free_entry);
    }
}


void MemManagementUnit::read(VirtualPage* virtual_page_ptr){
    int physical_address = get_or_change_physical_page(virtual_page_ptr);
    // read physical page from memory
    virtual_page_ptr->reference_bit = true;
    virtual_page_ptr->last_use_time = virtual_current_time;

    virtual_current_time++;
}


void MemManagementUnit::write(VirtualPage* virtual_page_ptr){
    int physical_address = get_or_change_physical_page(virtual_page_ptr);
    // write to physical page
    virtual_page_ptr->reference_bit = true;
    virtual_page_ptr->modification_bit = true;
    virtual_page_ptr->last_use_time = virtual_current_time;

    virtual_current_time++;
}


int MemManagementUnit::get_or_change_physical_page(VirtualPage* virtual_page){
    if(virtual_page->presense_bit){
        return virtual_page->physical_page_address;
    }

    //page fault
    page_fault_count++;
    for(int page_index = 0; page_index < physical_page_count; page_index++){
        if(page_table[page_index].virtual_page == nullptr){
            page_table[page_index].virtual_page = virtual_page;
            virtual_page->physical_page_address = page_table[page_index].physical_address;
            virtual_page->presense_bit = true;
            return virtual_page->physical_page_address;
        }
    }

    bool is_page_found = false;
    PageTableEntry* candidate;
    int max_age = -1;
    for(int i = 0; i < physical_page_count; i++){
        int time_diff = virtual_current_time - page_table[arrow_index].virtual_page->last_use_time;
        if(page_table[arrow_index].virtual_page->reference_bit){
            page_table[arrow_index].virtual_page->last_use_time = virtual_current_time;
        }
        else if(!page_table[arrow_index].virtual_page->reference_bit && time_diff > T){
            candidate = &page_table[arrow_index];
            is_page_found = true;
        }
        else if(!is_page_found && max_age < time_diff){
            candidate = &page_table[arrow_index];
            max_age = time_diff;
        }
        arrow_index++;
        if(arrow_index >= physical_page_count){
            arrow_index = 0;
        }
    }

    if(!is_page_found&& max_age == -1){
        candidate = &page_table[arrow_index];
    }
    //save physiscal page to swap file
    candidate->virtual_page->presense_bit = false;
    candidate->virtual_page = virtual_page;
    virtual_page->presense_bit = true;
    virtual_page->physical_page_address = candidate->physical_address;
    
    return candidate->physical_address;
}


void MemManagementUnit::free(VirtualPage* virtual_page_ptr){
    if(virtual_page_ptr->presense_bit){
        int physical_page = virtual_page_ptr->physical_page_address;
        page_table[physical_page].virtual_page = nullptr;
        virtual_page_ptr->presense_bit = false;
    }
}
