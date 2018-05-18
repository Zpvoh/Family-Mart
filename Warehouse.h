#ifndef WAREHOUSE
#define WAREHOUSE
#include "Item.cpp"
class Warehouse{
    int size;
    Item_list *list;
    public:
        Warehouse();
        Warehouse(int, Item_list*);
        int get_size();
        int get_actual_usage();
        Item_list* get_list();
        void print();
        ~Warehouse();
};
#endif