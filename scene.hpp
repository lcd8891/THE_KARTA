#pragma once
#include "translate.hpp"
#include <fstream>
#include <locale>
#include <string>
#include <sstream>
#include <codecvt>
#include <vector>
#include <map>
#include <functional>
#include <SFML/Graphics.hpp>
#include <thread>
#include <cmath>

void уведомить(std::wstring str);
ничего включить_хит(std::string _да);

#define TO_WSTRING(STR) std::wstring(STR.begin(),STR.end())
#define ошибка_парсинга(аллала) обосратся ошибочка(L"Ошибка парсирования сцены!\n"+TO_WSTRING(path)+L":"+std::to_wstring(строчка)+L": "+аллала);

extern sf::RenderWindow window;
std::string wstring_to_string(const std::wstring& wstr);

ничего разбить_строку(стринги &str,std::vector<стринги> &слова){
    слова.clear();
    std::wstringstream ss(str);
    стринги тпм;
    while(ss >> тпм){
        слова.push_back(тпм);
    }
}
стринги получить_строку(std::vector<стринги> &слова,unsigned откуда){
    стринги стр;
    for(int i = откуда;i<стр.size();i++){
        if(i!=слова.size()){
            стр+=слова[i]+L" ";
        }else{
            стр+=слова[i];
        }
    }
    return стр;
}

класс Сцена{
    private:
    std::vector<std::function<bool()>> функции;
    sf::Color фон;  
    std::map<std::string,sf::Sprite> спрайты;
    ничего выполнять_задачу(){
        if(функции[ид_функции]()){
            ид_функции++;
            кадры_функции=0;
        };
    }
    ничего добавить_задачу(std::function<bool()> f){
        функции.push_back(f);
    }

    public:
    unsigned ид_функции{0}, кадры{0},кадры_функции{0};
    ничего загрузить_сцену(std::string path){
        функции.clear();
        std::wifstream file("./res/scenes/"+path+".txt");
        if(!file.is_open())обосратся ошибочка(L"Сцена не грузится!");
        file.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));
        стринги str;
        unsigned строчка = 0;
        std::vector<стринги> слова;
        
        try{
            while(getline(file,str)){
                if(str.empty())continue;
                разбить_строку(str,слова);
                if(слова.empty()) continue;

                if(слова[0]==L"фон"){
                    if(слова.size() < 1){
                        ошибка_парсинга(L"Кол-во аргументов не вовпадает\nфон <цвет> / фон <красный> <зелёный> <синий> <альфа> / фон <красный> <зелёный> <синий>")
                    }else if(слова[1]==L"чёрный"){
                        добавить_задачу([this]() -> bool {
                            фон = sf::Color::Black;
                            return true;
                        });
                    }else if(слова[1]==L"белый"){
                        добавить_задачу([this]() -> bool {
                            фон = sf::Color::White;
                            return true;
                        });
                    }else if(слова[1]==L"серый"){
                        добавить_задачу([this]() -> bool {
                            фон = {125,125,125};
                            return true;
                        });
                    }else if(слова.size()==3){
                        добавить_задачу([this,r = std::stoi(слова[1]),b = std::stoi(слова[3]),g = std::stoi(слова[2])]() -> bool {
                            фон = {r,g,b};
                            return true;
                        });
                    }else if(слова.size()==4){
                        добавить_задачу([this,r = std::stoi(слова[1]),b = std::stoi(слова[3]),g = std::stoi(слова[2]),a = std::stoi(слова[4])]() -> bool {
                            фон = {r,g,b,a};
                            return true;
                        });
                    }else{
                        ошибка_парсинга(L"Кол-во аргументов не вовпадает\nфон <цвет> \nфон <красный> <зелёный> <синий> <альфа> \nфон <красный> <зелёный> <синий>")
                    }
                }else if(слова[0] == L"ждать"){
                    if(слова.size()==2){
                        добавить_задачу([a = &кадры_функции,t = (int)(round(std::stoi(слова[1])/16.6))]() -> bool {
                            return *a >= t;
                        });
                    }else{
                        ошибка_парсинга(L"Кол-во аргументов не вовпадает\nждать <мильсекунды>")
                    }
                }else if(слова[0] == L"создать"){
                    if(слова.size()==6){
                        if(слова[1]==L"спрайт"){
                            
                        }
                    }else{
                        ошибка_парсинга(L"Кол-во аргументов не вовпадает\nсоздать спрайт индендификатор ид_текстуры X Y")
                    }
                }else if(слова[0] == L"музыка"){
                    if(слова.size()==2){
                        добавить_задачу([a = wstring_to_string(слова[1])]() -> bool {
                            включить_хит(a);
                            return true;
                        });
                    }else{
                        ошибка_парсинга(L"Кол-во аргументов не вовпадает\nмузыка название")
                    }
                }else if(слова[0] == L"заголовок"){
                    if(слова.size()>1){
                        добавить_задачу([a = &кадры_функции,b = получить_строку(слова,1)]() -> bool {
                            
                            return true;
                        });
                    }else{
                        ошибка_парсинга(L"Кол-во аргументов не вовпадает\nзаголовок строка...")
                    }
                }else{
                    ошибка_парсинга(L"Неизвестная задача!");
                }
            }
        }catch(std::exception &e){
            ошибка_парсинга(L"Неизвестная ошибка");
        }
        file.close();
        кадры=0;
        кадры_функции=0;
        ид_функции=0;
    }
    bool кадр(){
        window.clear(фон);
        for(auto &ит : спрайты){
            window.draw(ит.second);
        }
        if(ид_функции >= функции.size())return true;
        кадры_функции++;
        выполнять_задачу();
        кадры++;
        return false;
    }
};