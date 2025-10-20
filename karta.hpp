#pragma once
#include "header.hpp"
#include "translate.hpp"
#include <fstream>

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
        std::ifstream file("./res/map.txt");
        std::string str;
        while(ЧИТАТЬ){
            if(str.empty())continue;
            if(str.back()==':'){
                std::string ид = str.substr(0, str.length() - 1);
                Место временный;
                try{
                    if(ЧИТАТЬ){
                        временный.позиция.x = (std::stof(str) / 100.f) * РАЗМЕР;
                    }
                    if(ЧИТАТЬ){
                        временный.позиция.y = (std::stof(str) / 100.f) * РАЗМЕР;
                    }
                }catch(const std::exception &e){
                    обосратся ошибочка(L"Ошибка прогрузки карты!");
                }
                if(ЧИТАТЬ){
                    временный.город = TO_WSTRING(str);
                }
                if(ЧИТАТЬ){
                    временный.достопремечательность = TO_WSTRING(str);
                }
                if(ЧИТАТЬ){
                    временный.описание = TO_WSTRING(str);
                }
                места[ид] = временный;
            }
        }
        file.close();
    }
    sf::Vector2f загрузить_место(std::string id){
        sf::Vector2f pos = коорды[id];
        sf::Vector2f tmp;
        tmp.x = 250 - pos.x;
        tmp.y = 360 - pos.y;
        return tmp;
    }
    ничего рисовать_пины(){
        for(auto &итератор : коорды){
            sf::Vector2f tmp = итератор.second;
            спрайт(3,tmp,true);
        }
    }
    ничего прогрузить_кнопки(){
        коорды.clear();
        for(auto &итератор : места){
            Место место = итератор.second;
            sf::Vector2f позиция = {372.f+место.позиция.x,55.f+место.позиция.y};
            std::string str;
            добавить_кнопку(итератор.first,позиция,{20,20});
            коорды[итератор.first] = позиция;
        }
    }
};