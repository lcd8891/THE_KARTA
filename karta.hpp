#pragma once
#include "header.hpp"
#include "translate.hpp"
#include <fstream>
#include <sstream>
#include <codecvt>
#include <vector>

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
        std::wstring достопремечательность;
        std::wstring описание;
    };
    данные_какието Город{
        std::wstring назва;
        sf::Vector2f позиция;
        std::vector<Место> места;
    };
    std::map<std::string,sf::Vector2f> коорды;
    std::string конкретный_ид;
    std::map<std::string,Город> города;
    
    public:
    sf::Texture картинка_1,картинка_2;
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
                Город временный;
                unsigned колво_мест;
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
                    if(ЧИТАТЬ){
                        str.erase(0, str.find_first_not_of(L" \t\r\n"));
                        str.erase(str.find_last_not_of(L" \t\r\n") + 1);
                        колво_мест = std::stoi(str);
                    }
                }catch(const std::exception &e){
                    обосратся ошибочка(L"Ошибка прогрузки карты!");
                }
                if(ЧИТАТЬ){
                    str.erase(0, str.find_first_not_of(L" \t\r\n"));
                    str.erase(str.find_last_not_of(L" \t\r\n") + 1);
                    временный.назва = str;
                }
                for(unsigned i = 0;i<колво_мест;i++){
                    Место ест;
                    if(ЧИТАТЬ){
                        str.erase(0, str.find_first_not_of(L" \t\r\n"));
                        str.erase(str.find_last_not_of(L" \t\r\n") + 1);
                        ест.достопремечательность = str;
                    }
                    if(ЧИТАТЬ){
                        str.erase(0, str.find_first_not_of(L" \t\r\n"));
                        str.erase(str.find_last_not_of(L" \t\r\n") + 1);
                        ест.описание = str;
                    }
                    временный.места.push_back(ест);
                }
                города[ид] = временный;
            }
        }
        file.close();
    }
    sf::Vector2f загрузить_город(std::string id, unsigned &колво,sf::Vector2f &точка,стринги &назва){
        конкретный_ид = id;
        sf::Vector2f pos = коорды[id];
        sf::Vector2f tmp;
        tmp.x = 250 - pos.x;
        tmp.y = 360 - pos.y;
        точка = pos;
        назва = города[id].назва;
        колво = города[id].места.size()-1;
        return tmp;
    }
    ничего загрузить_место(unsigned id, стринги &_описание, стринги &что){
        if(!картинка_1.loadFromFile("./res/map/"+конкретный_ид+std::to_string(id)+"-1.png")){
            картинка_1 = текстуры[4];
        }
        if(!картинка_2.loadFromFile("./res/map/"+конкретный_ид+std::to_string(id)+"-2.png")){
            картинка_2 = текстуры[4];
        }
        _описание = города[конкретный_ид].места[id].описание;
        что = города[конкретный_ид].места[id].достопремечательность;
    }
    ничего рисовать_пины(){
        for(auto &итератор : коорды){
            sf::Vector2f tmp = итератор.second;
            спрайт(3,tmp,true);
            стринги город = города[итератор.first].назва;
            пишем(город,tmp + sf::Vector2f(10,20));
        }
    }
    ничего прогрузить_кнопки(){
        коорды.clear();
        for(auto &итератор : города){
            Город город = итератор.second;
            sf::Vector2f позиция = {372.f+город.позиция.x,55.f+город.позиция.y};
            std::string str;
            добавить_кнопку(итератор.first,позиция,{30,50});
            коорды[итератор.first] = позиция;
        }
    }
};