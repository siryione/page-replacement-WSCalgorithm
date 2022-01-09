#include <memory>
#include "Process.hpp"
#include "System.hpp"


void System::read(std::shared_ptr<Process> process, int virtual_page_address){
    VirtualPage* virtual_page = &(process->virtual_pages[virtual_page_address]);
    mmu.read(virtual_page);
}


void System::write(std::shared_ptr<Process> process, int virtual_page_address){
    VirtualPage* virtual_page = &(process->virtual_pages[virtual_page_address]);
    mmu.write(virtual_page);
}


void System::kill(std::shared_ptr<Process> process){
    for(int i =0; i < process->virtual_page_count; i++){
        mmu.free(&(process->virtual_pages[i]));
    }
}