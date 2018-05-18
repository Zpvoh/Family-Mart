#ifndef ITEM
#define ITEM
#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;
class Item{
    string name;
    float price;
    int shelf_life;
    string production_date;
    public:
        Item();
        Item(string, float, int, string);
        string get_name();
        float get_price();
        int get_life();
        string get_date();
        void print();
        ~Item();
};

class Item_list{
    map<string, vector<Item*> > list;
    int size;
    public:
        Item_list();
        int get_size();
        Item *find_item(string);
        void add_item(Item*);
        void print();
        bool delete_item(string);
        ~Item_list();
};
#endif