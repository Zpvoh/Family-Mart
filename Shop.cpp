#include "Shop.h"

int Shop::warehouse_num=0;

Shop::Shop(){
    name="";
    warehouse=nullptr;
    //cout<<"hhh"<<endl;
}

Shop::Shop(string n){
    name=n;
    warehouse=nullptr;
}

void Shop::init_warehouse(){
    cout<<name<<" ";
    warehouse=new Warehouse();
    warehouse_num++;
}

string Shop::get_name(){
    return name;
}

bool Shop::upgrade(){
    if(warehouse->get_actual_usage()==warehouse->get_size()){
        bool is_level1=(warehouse->get_size()==25);
        bool is_level2=(warehouse->get_size()==50);
        bool is_level3=(warehouse->get_size()==100);

        int new_size=(is_level2)?100:(is_level1?50:0);

        if(!new_size)
            return false;

        cout<<name<<" ";
        Warehouse *new_house=new Warehouse(new_size, warehouse->get_list());
        cout<<name<<" ";
        delete warehouse;
        warehouse=new_house;

        return true;
    }

    return false;
}

bool Shop::downgrade(){
    bool is_level1=(warehouse->get_size()==25);
    bool is_level2=(warehouse->get_size()==50);
    bool is_level3=(warehouse->get_size()==100);

    int new_size=(is_level2)?25:(is_level3?50:0);

    if(!new_size)
        return false;

    if(warehouse->get_actual_usage()<=new_size){
        cout<<name<<" ";
        Warehouse *new_house=new Warehouse(new_size, warehouse->get_list());
        cout<<name<<" ";
        delete warehouse;
        warehouse=new_house;
        downgrade();

        return true;
    }

    return false;
}


void Shop::purchase(vector<Item*> list){
    if(warehouse==nullptr)
        init_warehouse();

    vector<Item*>::iterator it;
    for(it=list.begin(); it!=list.end(); it++){
        warehouse->get_list()->add_item(*it);
        upgrade();
    }
}

float Shop::sell(vector<string> sell_list, float discount){
    float amount=0;
    vector<string>::iterator it;
    for(it=sell_list.begin(); it!=sell_list.end(); it++){
        //cout<<"hello"<<endl;
        float actual_price=warehouse->get_list()->find_item(*it)->get_price()*discount;
        //cout<<actual_price<<endl;
        amount+=actual_price;
        warehouse->get_list()->delete_item(*it);
        downgrade();
    }

    return amount;
}

void Shop::print(){
    if(warehouse!=nullptr)
        warehouse->print();
    else
        cout<<"This shop does not possess a warehouse!"<<endl;
}

Shop::~Shop(){
    if(warehouse!=nullptr){
        delete warehouse->get_list();
        cout<<name<<" ";
        delete warehouse;
    }
    //cout<<name<<" has been destructed"<<endl;
}