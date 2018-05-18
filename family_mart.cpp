#include <fstream>
#include <sstream>
#include "family_mart.h"
using namespace std;

Instruct::Instruct(){
    type="sell";
}

Instruct::Instruct(string typ, vector<string> paras){
    type=typ;
    params=paras;
}

Instruct::~Instruct(){
    //cout<<"[Instruct destructed]"<<endl;
}

Family_mart::Family_mart(){
    sale_amount=0;
}

Family_mart::Family_mart(string file_name){
    sale_amount=0;

    ifstream file(file_name.c_str());
    string line;
    getline(file, line);
    istringstream iss(line);
    string name;
    Shop *shop;
    iss>>name;
    if(shop_list.count(name)){
        shop=shop_list[name];
    }else{
        shop=new Shop(name);
        shop_list.insert(pair<string, Shop*>(name, shop));
    }

    vector<Item*> items;
    while(getline(file, line)){
        istringstream iss(line);
        string name, date;
        float price;
        int life;
        const string std_name="name";
        iss>>name;
        if(name.compare(std_name)==0 || name.length()==0){
            continue;
        }

        iss>>price;
        iss>>life;
        iss>>date;
        Item *item=new Item(name, price, life, date);
        items.push_back(item);
    }

    shop->purchase(items);
    //cout<<shop_list["SHOP1"]->get_name()<<endl;
}

Family_mart::Family_mart(float amount, map<string, Shop*> shops){
    sale_amount=amount;
    shop_list=shops;
}

void Family_mart::open_shop(){
    int num=shop_list.size()+1;
    string name="SHOP";
    stringstream ss;
    ss<<name<<num;
    name=ss.str();
    shop_list.insert(pair<string, Shop*>(name, new Shop(name)));

    cout<<name<<" is open"<<endl;
}

void Family_mart::purchase(string file_name){
    ifstream file(file_name.c_str());
    string line;
    getline(file, line);
    istringstream iss(line);
    string type, shop_name;
    int num;
    Shop *shop;
    iss>>type>>num>>shop_name;
    if(shop_list.count(shop_name)){
        shop=shop_list[shop_name];
    }else{
        cout<<"There is no this shop"<<endl;
        return;
    }

    vector<Item*> items;
    while(getline(file, line)){
        istringstream iss(line);
        string name, date;
        float price;
        int life;
        //const string std_name="name";
        iss>>name;
        if(name=="name" || name.length()==0){
            continue;
        }

        iss>>price;
        iss>>life;
        iss>>date;
        Item *item=new Item(name, price, life, date);
        items.push_back(item);
    }

    shop->purchase(items);
}

void Family_mart::sell(string file_name){
    ifstream file(file_name.c_str());
    string line;

    vector<Item*> items;
    while(getline(file, line)){
        int n=sale_amount/55;

        if(line.substr(line.find(' ')+1).find(' ')==string::npos){
            string type, shop_name;
            istringstream iss(line);
            iss>>type>>shop_name;
            Shop *shop;
            if(shop_list.count(shop_name)){
                shop=shop_list[shop_name];
            }else{
                cout<<"There is no such shop and we are not able to sell these products!"<<endl;
                break;
            }

            vector<string> names;
            while(getline(file, line)){
                istringstream iss(line);
                string name;
                iss>>name;
                if(name.length()==0){
                    break;
                }

                names.push_back(name);
            }

            sale_amount+=shop->sell(names, 1);
        }else{
            string type, shop_name;
            float discount;
            istringstream iss(line);
            iss>>type>>discount>>shop_name;

            Shop *shop;
            if(shop_list.count(shop_name)){
                shop=shop_list[shop_name];
            }else{
                cout<<"There is no "<<shop_name<<" so we are not able to sell these products!"<<endl;
                break;
            }

            vector<string> names;
            while(getline(file, line)){
                istringstream iss(line);
                string name;
                iss>>name;
                if(name.length()==0){
                    break;
                }

                names.push_back(name);
            }

            sale_amount+=shop->sell(names, discount);
        }

        if((((int)(sale_amount/55))-n) && Shop::warehouse_num<=100)
            open_shop();

    }
}

float Family_mart::get_amount(){
    return sale_amount;
}

void Family_mart::print_shops(){
    map<string, Shop*>::iterator it;
    for(it=shop_list.begin(); it!=shop_list.end(); it++){
        cout<<it->first<<" ";
    }
    cout<<endl;
}

void Family_mart::print_shop_warehouse(string name){
    if(shop_list.count(name)){
        shop_list[name]->print();
    }else{
        cout<<"There is no such shop!"<<endl;
    }
}

Family_mart::~Family_mart(){
    map<string, Shop*>::iterator it;
    for(it=shop_list.begin(); it!=shop_list.end(); it++){
        delete it->second;
    }

    cout<<"Family Mart has been destructed"<<endl;
}

int main(){
    cout<<"Welcome To Family Mart!"<<endl;
    cout<<"--------------------------"<<endl;
    Family_mart *family_mart=new Family_mart("shop.txt");
    
    while(1){
        cout<<"--------------------------"<<endl;
        cout<<"Family-Mart>";
        Instruct ins=Instruct();
        cin>>ins.type;
        if(ins.type=="purchase"){
            string para;
            cin>>para;
            ins.params.push_back(para);
            family_mart->purchase(ins.params[0].c_str());
        }else if(ins.type=="sell"){
            string para;
            cin>>para;
            ins.params.push_back(para);
            family_mart->sell(ins.params[0].c_str());
        }else if(ins.type=="show_sale_amount"){
            cout<<family_mart->get_amount()<<endl;
        }else if(ins.type=="show_all_shop_name"){
            family_mart->print_shops();
        }else if(ins.type=="show_shop_warehouse"){
            string para;
            cin>>para;
            ins.params.push_back(para);
            family_mart->print_shop_warehouse(ins.params[0]);
        }else if(ins.type=="show_warehouse_num"){
            cout<<Shop::warehouse_num<<endl;
        }else if(ins.type=="quit"){
            break;
        }else{
            cout<<"Please input something meaningful"<<endl;
        }
    }

    delete family_mart;
}