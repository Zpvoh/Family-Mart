#ifndef SHOP
#define SHOP
#include "Warehouse.cpp"
class Shop{
    string name;
    Warehouse *warehouse;
    public:
        Shop();
        Shop(string);
        static int warehouse_num;
        string get_name();
        void init_warehouse();
        bool upgrade();
        bool downgrade();
        void purchase(vector<Item*>);
        float sell(vector<string>, float);
        void print();
        ~Shop();
};
#endif