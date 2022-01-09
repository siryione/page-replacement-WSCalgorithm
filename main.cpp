#include <iostream>
#include <memory>
#include <queue>
#include "constants.hpp"
#include "System.hpp"


double rand_zero_to_one(){
    return (double)rand() / RAND_MAX;
}


int main(){
    srand(time(NULL));
    System system = System(PHYSICAL_PAGE_COUNT);
    std::queue<std::shared_ptr<Process>> process_queue = std::queue<std::shared_ptr<Process>>();
    int time_remain = 0;
    int processes_finished = 0;
    int id = 0;
    for(int i = 0; i < TIME;){
        if(rand_zero_to_one() < 0.1){
            id++;
            int burst_time = rand() % 20;
            std::shared_ptr<Process> p = std::shared_ptr<Process>(new Process(id, WORKING_SET_SIZE, VIRTUAL_PAGE_COUNT, burst_time));
            process_queue.push(p);
        }

        if(!process_queue.empty()){          
            std::shared_ptr<Process> process = process_queue.front();
            process_queue.pop();
            time_remain = QUANTUM;

            if(rand_zero_to_one() < 0.05){
                process->changeWorkingSet();
            }

            while(time_remain != 0){
                int virtual_page_address = 0;
                if(rand_zero_to_one() < 0.9){
                    int virtual_page_index = rand() % process->working_set_size;
                    virtual_page_address = process->virtual_pages[virtual_page_index].virtual_page_address;
                }
                else{
                    int virtual_page_index = rand() % (process->virtual_page_count - process->working_set_size) + process->working_set_size;
                    virtual_page_address = process->virtual_pages[virtual_page_index].virtual_page_address;
                }

                if(rand_zero_to_one() < 0.7){
                    system.read(process, virtual_page_address);
                }
                else{
                    system.write(process, virtual_page_address);
                }

                process->burst_time -= 1;
                time_remain -= 1;
                if(process->burst_time == 0){
                    processes_finished += 1;
                    break;
                }

                i++;
                if (i == TIME) break;
            }

            if(process->burst_time == 0){
                system.kill(process);
            }
            else{
                process_queue.push(process);
            }
        }
    }
    std::cout << system.get_page_fault_count() << std::endl;
    return 0;
}