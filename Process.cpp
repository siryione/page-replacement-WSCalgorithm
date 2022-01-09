#include <algorithm>
#include "Process.hpp"


void Process::changeWorkingSet(){
    std::random_shuffle(virtual_pages.begin(), virtual_pages.end());
}
