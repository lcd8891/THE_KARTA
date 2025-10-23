#pragma once
#include "translate.hpp"
#include "drawing.hpp"
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

#define PI 3.14
#define PI2 1.57 

template<typename T>
T min(T a,T b){
    return (a < b) ? a : b;
}
void уведомить(std::wstring str);
ничего включить_хит(std::string _да);
ничего включить_звук(unsigned ци);

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
    unsigned size = слова.size();
    for(int i = откуда;i<size;i++){
        if(i!=size){
            стр+=слова[i]+L" ";
        }else{
            стр+=слова[i];
        }
    }
    return стр;
}

класс Сцена{
    private:
    sf::Color фон;  
    std::vector<std::function<bool()>> функции;
    std::map<std::string,sf::Sprite> спрайты;
    unsigned ид_функции{0}, кадры{0};
    цифорка кадры_функции{0};
    std::vector<std::function<bool()>> одновременно_функции;
    ничего выполнять_задачу(){
        if(одновременно_функции.empty()){
            if(функции[ид_функции]()){
                ид_функции++;
                кадры_функции=-1;
            };
        }else{
            bool некст = true;
            auto it = одновременно_функции.begin();
            while(it != одновременно_функции.end()){
                if(!(*it)()){
                    некст = false;
                }else{
                    it = одновременно_функции.erase(it);
                }
                ++it;
            }
            if(некст){
                ид_функции++;
                кадры_функции=-1;
                одновременно_функции.clear();
            };
        }
    }
    ничего добавить_задачу(std::function<bool()> f){
        функции.push_back(f);
    }

    public:
    ничего загрузить_сцену(std::string path){
        функции.clear();
        std::wifstream file("./res/scenes/"+path+".txt");
        if(!file.is_open())обосратся ошибочка(L"Сцена не грузится!");
        file.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));
        стринги str;
        unsigned строчка = 1;
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
                        добавить_задачу([this,r = (unsigned char)std::stoi(слова[1]),b = (unsigned char)std::stoi(слова[3]),g = (unsigned char)std::stoi(слова[2])]() -> bool {
                            фон = {r,g,b};
                            return true;
                        });
                    }else if(слова.size()==4){
                        добавить_задачу([this,r = (unsigned char)std::stoi(слова[1]),b = (unsigned char)std::stoi(слова[3]),g = (unsigned char)std::stoi(слова[2]),a = (unsigned char)std::stoi(слова[4])]() -> bool {
                            return true;
                        });
                    }else{
                        ошибка_парсинга(L"Кол-во аргументов не cовпадает\nфон <цвет> \nфон <красный> <зелёный> <синий> <альфа> \nфон <красный> <зелёный> <синий>")
                    }
                }else if(слова[0] == L"ждать"){
                    if(слова.size()==2){
                        добавить_задачу([a = &кадры_функции,t = (int)(std::stoi(слова[1])/16.6)]() -> bool {
                            return *a >= t;
                        });
                    }else{
                        ошибка_парсинга(L"Кол-во аргументов не cовпадает\nждать <мильсекунды>")
                    }
                }else if(слова[0] == L"спрайт"){
                    if(слова.size()==5){
                        добавить_задачу([id = wstring_to_string(слова[1]), tid = std::stoi(слова[2]),x = std::stoi(слова[3]),y = std::stoi(слова[4]),this]() -> bool {
                            спрайты[id] = sf::Sprite(текстуры[tid]);
                            спрайты[id].setPosition(x,y);
                            sf::Vector2u size = текстуры[tid].getSize();
                            спрайты[id].setOrigin(size.x / 2,size.y / 2);
                            return true;
                        });
                    }else{
                        ошибка_парсинга(L"Кол-во аргументов не cовпадает\nспрайт индендификатор ид_текстуры X Y")
                    }
                }else if(слова[0] == L"передвинуть"){
                    if(слова.size()==5){
                        std::string id = wstring_to_string(слова[1]);
                        sf::Vector2f смещение{sf::Vector2f(std::stof(слова[2]),std::stof(слова[3]))};
                        добавить_задачу([
                            id = id,
                            pos = смещение,
                            t = (int)(std::stoi(слова[4])/16.6),
                            нач_поз = sf::Vector2f(),
                            this
                        ]() mutable -> bool {
                            if(кадры_функции==0){нач_поз = спрайты[id].getPosition();}
                            float p = (float)(sin(PI2 * (кадры_функции / (float)t)));
                            sf::Vector2f нов_поз = {
                                нач_поз.x + pos.x * p,
                                нач_поз.y + pos.y * p
                            };
                            спрайты[id].setPosition(нов_поз);
                            return кадры_функции>=t;
                        });
                    }else{
                        ошибка_парсинга(L"Кол-во аргументов не cовпадает\nпередвинуть индендификатор на_X на_Y как_долго")
                    }
                }else if(слова[0] == L"переместить"){
                    if(слова.size()==4){
                        добавить_задачу([a = wstring_to_string(слова[1]),pos = sf::Vector2f(std::stoi(слова[2]),std::stoi(слова[3])),this]() -> bool {
                            спрайты[a].setPosition(pos);
                            return true;
                        });
                    }else{
                        ошибка_парсинга(L"Кол-во аргументов не cовпадает\nпереместить индентификатор X Y")
                    }
                }else if(слова[0] == L"музыка"){
                    if(слова.size()==2){
                        добавить_задачу([a = wstring_to_string(слова[1])]() -> bool {
                            включить_хит(a);
                            return true;
                        });
                    }else{
                        ошибка_парсинга(L"Кол-во аргументов не cовпадает\nмузыка название")
                    }
                }else if(слова[0] == L"заголовок"){
                    if(слова.size()>1){
                        стринги строкаи = получить_строку(слова,1);
                        добавить_задачу([a = &кадры_функции,b = строкаи]() -> bool {
                            float s{(float)sin((*a / 180.f) * PI)};
                            float m{(float)min<double>(sin((*a / 180.f) * PI),1.f)};
                            квадрат({0,360 - 50 * s},{1280,100 * s},{255,255,255,50});
                            пишем(b,{640,354},1,{255,255,255,(unsigned char)(255 * m)},42);
                            return *a>=180;
                        });
                    }else{
                        ошибка_парсинга(L"Кол-во аргументов не cовпадает\nзаголовок строка...")
                    }
                }else if(слова[0] == L"одновременно"){
                    if(слова.size()==2){
                        добавить_задачу([b = std::stoi(слова[1]),this]() -> bool {
                            одновременно_функции.clear();
                            for(int i = 0;i<b;i++){
                                одновременно_функции.push_back(функции[ид_функции+i+1]);
                            }
                            return true;
                        });
                    }else{
                        ошибка_парсинга(L"Кол-во аргументов не cовпадает\nодновременно N")
                    }
                }else if(слова[0] == L"убрать"){
                    if(слова.size()==2){
                        std::string id = wstring_to_string(слова[1]);
                        добавить_задачу([id = id,this]() -> bool {
                            спрайты.erase(id);
                            return true;
                        });
                    }else{
                        ошибка_парсинга(L"Кол-во аргументов не cовпадает\nубрать индентификатор")
                    }
                }else if(слова[0] == L"написать"){
                    if(слова.size()>=4){
                        std::wstring иди = получить_строку(слова,3);
                        добавить_задачу([
                            стр = иди,
                            сас = (unsigned)0,
                            ы = std::wstring(),
                            поз = sf::Vector2f(std::stoi(слова[1]),std::stoi(слова[2])),
                            this
                        ]() mutable -> bool {
                            if(стр.length()!=ы.length()){ы+=стр[сас];
                            сас++;
                            включить_звук(1);}
                            пишем(ы,поз);
                            return стр.length()==ы.length() && кадры_функции>=120+стр.length();
                        });
                    }else{
                        ошибка_парсинга(L"Кол-во аргументов не cовпадает\nубрать индентификатор")
                    }
                }else{
                    ошибка_парсинга(L"Неизвестная задача!");
                }
                строчка++;
            }
        }catch(std::exception &e){
            ошибка_парсинга(L"Неизвестная ошибка");
        }
        file.close();
        кадры=0;
        кадры_функции=0;
        ид_функции=0;
        спрайты.clear();
        одновременно_функции.clear();
    }
    bool кадр(){
        window.clear(фон);
        for(auto &ит : спрайты){
            window.draw(ит.second);
        }
        if(ид_функции >= функции.size())return true;
        выполнять_задачу();
        кадры_функции++;
        кадры++;
        return false;
    }
};