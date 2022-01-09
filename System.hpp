#ifndef SYSTEM
#define SYSTEM
#include "Process.hpp"
#include <memory>

class System
{
private:
    MemManagementUnit mmu;
public:
    System(int physical_page_count): mmu(physical_page_count){}
    int get_page_fault_count(){
        return mmu.page_fault_count;
    }
    void read(std::shared_ptr<Process> process, int virtual_page_adress);
    void write(std::shared_ptr<Process> process, int virtual_page_adress);
    void kill(std::shared_ptr<Process> process);
};

#endif
