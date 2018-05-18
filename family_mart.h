#ifndef MART
#define MART
#include <vector>
#include <string>
#include "Shop.cpp"
class Instruct{
    public:
        Instruct();
        Instruct(string, vector<string>);
        string type;
        vector<string> params;
        ~Instruct();
};

class Family_mart{
    float sale_amount;
    map<string, Shop*> shop_list;
    public:
        Family_mart();
        Family_mart(string);
        Family_mart(float, map<string, Shop*>);
        void purchase(string);
        void sell(string);
        void open_shop();
        float get_amount();
        void print_shops();
        void print_shop_warehouse(string);
        ~Family_mart();
};
#endif