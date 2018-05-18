#include "Item.h"

Item::Item(){
    name="";
    price=0;
    shelf_life=0;
    production_date="";
}

Item::Item(string n, float p, int life, string date){
    name=n;
    price=p;
    shelf_life=life;
    production_date=date;
}

string Item::get_name(){
    return name;
}

float Item::get_price(){
    return price;
}

int Item::get_life(){
    return shelf_life;
}

string Item::get_date(){
    return production_date;
}

void Item::print(){
    cout<<name<<" "<<price<<" "<<shelf_life<<" "<<production_date<<endl;
}

Item::~Item(){
    cout<<name<<" has been destructed"<<endl;
}

Item_list::Item_list(){
    size=0;
}

int Item_list::get_size(){
    return size;
}

void Item_list::add_item(Item *item){
    if(list.count(item->get_name())){
        list[item->get_name()].push_back(item);
    }else{
        vector<Item*> v;
        v.push_back(item);
        list.insert(pair<string, vector<Item*> >(item->get_name(), v));
    }
    size++;
}

Item *Item_list::find_item(string name){
    if(list.count(name)){
        return list[name].front();
    }

    return new Item();
}

bool Item_list::delete_item(string name){
    if(list.count(name)){
        delete *list[name].begin();
        list[name].erase(list[name].begin());
        if(list[name].empty()){
            list.erase(name);
        }
        size--;
        return true;
    }

    return false;
}

void Item_list::print(){
    map<string, vector<Item*> >::iterator it;
    for(it=list.begin(); it!=list.end(); it++){
        vector<Item*> v=it->second;
        vector<Item*>::iterator item_it;
        for(item_it=v.begin(); item_it!=v.end(); item_it++){
            (*item_it)->print();
        }
    }
}

Item_list::~Item_list(){
    map<string, vector<Item*> >::iterator it;
    for(it=list.begin(); it!=list.end(); it++){
        string name=it->first;
        while(list.count(name)){
            delete_item(name);
        }
    }
    cout<<"Item_list has been destructed"<<endl;
}