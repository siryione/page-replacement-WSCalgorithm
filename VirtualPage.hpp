#ifndef VP
#define VP

struct VirtualPage{
    int virtual_page_address;
    int physical_page_address;
    int last_use_time;
    bool reference_bit;
    bool presense_bit;
    bool modification_bit;
};

#endif
