#pragma once
#include "header.hpp"
#include "translate.hpp"
#include <fstream>
#include <sstream>
#include <codecvt>

std::string wstring_to_string(const std::wstring& wstr) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(wstr);
}

#define ЧИТАТЬ getline(file,str)
#define РАЗМЕР 536

ничего добавить_кнопку(std::string id,sf::Vector2f _pos,sf::Vector2f _size);
class Карта{
    private:
    данные_какието Место{
        sf::Vector2f позиция;
        std::wstring город;
        std::wstring достопремечательность;
        std::wstring описание;
    };
    std::map<std::string,sf::Vector2f> коорды;
    
    public:
    sf::Texture картинка_1,картинка_2;
    std::map<std::string,Место> места;
    ничего загрузить(){
        std::wifstream file("./res/map.txt");
        file.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));
        std::wstring str;
        while(ЧИТАТЬ){
            str.erase(0, str.find_first_not_of(L" \t\r\n"));
            str.erase(str.find_last_not_of(L" \t\r\n") + 1);
            if(str.empty())continue;
            if(str.back()==':'){
                std::string ид = wstring_to_string(str.substr(0, str.length() - 1));
                Место временный;
                try{
                    if(ЧИТАТЬ){
                        str.erase(0, str.find_first_not_of(L" \t\r\n"));
                        str.erase(str.find_last_not_of(L" \t\r\n") + 1);
                        временный.позиция.x = (std::stof(str) / 100.f) * РАЗМЕР;
                    }
                    if(ЧИТАТЬ){
                    str.erase(0, str.find_first_not_of(L" \t\r\n"));
                    str.erase(str.find_last_not_of(L" \t\r\n") + 1);
                        временный.позиция.y = (std::stof(str) / 100.f) * РАЗМЕР;
                    }
                }catch(const std::exception &e){
                    обосратся ошибочка(L"Ошибка прогрузки карты!");
                }
                if(ЧИТАТЬ){
                    str.erase(0, str.find_first_not_of(L" \t\r\n"));
                    str.erase(str.find_last_not_of(L" \t\r\n") + 1);
                    временный.город = str;
                }
                if(ЧИТАТЬ){
                    str.erase(0, str.find_first_not_of(L" \t\r\n"));
                    str.erase(str.find_last_not_of(L" \t\r\n") + 1);
                    временный.достопремечательность = str;
                }
                if(ЧИТАТЬ){
                    str.erase(0, str.find_first_not_of(L" \t\r\n"));
                    str.erase(str.find_last_not_of(L" \t\r\n") + 1);
                    временный.описание = str;
                }
                места[ид] = временный;
            }
        }
        file.close();
    }
    sf::Vector2f загрузить_место(std::string id, стринги &_описание, стринги &что,sf::Vector2f &точка,стринги &назва){
        if(!картинка_1.loadFromFile("./res/map/"+id+"1.png")){
            картинка_1 = текстуры[4];
        }
        if(!картинка_2.loadFromFile("./res/map/"+id+"2.png")){
            картинка_2 = текстуры[4];
        }
        sf::Vector2f pos = коорды[id];
        sf::Vector2f tmp;
        tmp.x = 250 - pos.x;
        tmp.y = 360 - pos.y;
        _описание = места[id].описание;
        что = места[id].достопремечательность;
        назва = места[id].город;
        точка = коорды[id];
        return tmp;
    }
    ничего рисовать_пины(){
        for(auto &итератор : коорды){
            sf::Vector2f tmp = итератор.second;
            спрайт(3,tmp,true);
            стринги город = места[итератор.first].город;
            пишем(город,tmp + sf::Vector2f(10,20));
        }
    }
    ничего прогрузить_кнопки(){
        коорды.clear();
        for(auto &итератор : места){
            Место место = итератор.second;
            sf::Vector2f позиция = {372.f+место.позиция.x,55.f+место.позиция.y};
            std::string str;
            добавить_кнопку(итератор.first,позиция,{30,50});
            коорды[итератор.first] = позиция;
        }
    }
};