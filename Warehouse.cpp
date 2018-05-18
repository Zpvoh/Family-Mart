#include "Warehouse.h"

Warehouse::Warehouse(){
    size=25;
    list=new Item_list();
    cout<<size<<" Warehouse has been constructed"<<endl;
}

Warehouse::Warehouse(int s, Item_list *l){
    bool sentence1=l->get_size()==25 || l->get_size()==50 || l->get_size()==100;
    bool sentence2=l->get_size()<=s;
    size=(sentence1 && sentence2)?s:25;
    list=(sentence1 && sentence2)?l:new Item_list();
    cout<<size<<" Warehouse has been constructed"<<endl;
}

void Warehouse::print(){
    list->print();
}

int Warehouse::get_size(){
    return size;
}

int Warehouse::get_actual_usage(){
    return list->get_size();
}

Item_list *Warehouse::get_list(){
    return list;
}

Warehouse::~Warehouse(){
    cout<<size<<" Warehouse has been destructed"<<endl;
}