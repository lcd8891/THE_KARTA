#pragma once
#include "translate.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <vector>

#define TO_WSTRING(STR) std::wstring(STR.begin(),STR.end())

std::vector<sf::Texture> текстуры;
std::vector<sf::SoundBuffer> звуки;

unsigned посчитать_строки(std::ifstream &_филе){
    unsigned колво = 0;
    std::string str;
    while(getline(_филе,str)){
        if(str.empty())break;
        колво++;
    }
    _филе.clear();
    _филе.seekg(0);
    возврат колво;
}

ничего загрузить_основные_ресы(float &_процент){
    std::ifstream tex_file("./res/textures.txt");
    std::ifstream snd_file("./res/sounds.txt");
    if(!tex_file.is_open() || !snd_file.is_open()){
        обосратся ошибочка(L"Короч чёто данные о ресах сломались");
    }
    unsigned всего(посчитать_строки(tex_file) + посчитать_строки(snd_file)),счёт;
    sf::Texture tmp_tex;
    std::string line;
    while(getline(tex_file,line)){
        if(line.empty())continue;
        if(!tmp_tex.loadFromFile("./res/textures/"+line+".png")){
            обосратся ошибочка(L"файл текстуры "+TO_WSTRING(line)+L".png пропал безвестей или немножко изковеркан");
        }
        текстуры.push_back(tmp_tex);
        счёт++;
        _процент =  (float)счёт/(float)всего;
    }
    sf::SoundBuffer tmp_snd;
    while(getline(snd_file,line)){
        if(line.empty())continue;
        if(!tmp_snd.loadFromFile("./res/sounds/"+line+".wav")){
            обосратся ошибочка(L"файл текстуры "+TO_WSTRING(line)+L" пропал безвестей или немножко изковеркан");
        }
        звуки.push_back(tmp_snd);
        счёт++;
        _процент =  (float)счёт/(float)всего;
    }
    tex_file.close();snd_file.close();
    _процент=1; 
} 