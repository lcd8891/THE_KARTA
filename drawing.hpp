#pragma once
#include <SFML/Graphics.hpp>
#include <stdexcept>
#include "resources.hpp"
#include "translate.hpp"

extern sf::RenderWindow window;

using Шрифт = sf::Font;
using Текст = sf::Text;

Шрифт некрасивый_шрифт, красивый_шрифт;
Текст некрасивый_текст, красивый_текст;
sf::Sprite spr;
sf::RectangleShape парралелепипед;

ничего загрузить_шрифт(){
    if(!красивый_шрифт.loadFromFile("./res/font.ttf")){
        обосратся ошибочка(L"красивый шрифт решил не загружатся");
    }
    некрасивый_текст.setFont(некрасивый_шрифт);
    красивый_текст.setFont(красивый_шрифт);
}

ничего пишем(стринги _строка, sf::Vector2f _позиция,символ _угол = 0 ,sf::Color _цвет = sf::Color::White, цифорка _размер = 32){
    красивый_текст.setOutlineThickness(2);
    красивый_текст.setOutlineColor({0,0,0,_цвет.a});
    красивый_текст.setString(_строка);
    красивый_текст.setCharacterSize(_размер);
    sf::FloatRect r  = красивый_текст.getGlobalBounds();
    float x;
    switch(_угол){
        case 1:
        x = r.width / 2;
        break;
        case 2:
        x = r.width;
        break;
        default:
        x = 0;
    }
    красивый_текст.setPosition({_позиция.x - x,_позиция.y});
    красивый_текст.setOrigin({0,_размер / 2.0f});
    красивый_текст.setFillColor(_цвет);
    window.draw(красивый_текст);
}
ничего пишем_некрасиво(стринги _строка, sf::Vector2f _позиция,символ _угол = 0 ,sf::Color _цвет = sf::Color::White, цифорка _размер = 32){
    некрасивый_текст.setString(_строка);
    некрасивый_текст.setCharacterSize(_размер);
    sf::FloatRect r = некрасивый_текст.getLocalBounds();
    float x;
    switch(_угол){
        case 1:
        x = r.width / 2;
        break;
        case 2:
        x = r.width;
        break;
        default:
        x = 0;
    }
    некрасивый_текст.setPosition({_позиция.x - x,_позиция.y});
    некрасивый_текст.setOrigin({0,_размер / 2.f});
    некрасивый_текст.setFillColor(sf::Color::White);
    window.draw(некрасивый_текст);
}
ничего спрайт(unsigned _ид, sf::Vector2f _позиция, да_нет _центрировать = false,sf::Color цвет = sf::Color::White){
    spr.setTexture(текстуры[_ид],true);
    if(_центрировать){
        sf::Vector2f size = {текстуры[_ид].getSize().x / 2.f, текстуры[_ид].getSize().y / 2.f};
        spr.setOrigin(size);
    }else{
        spr.setOrigin({0,0});
    }
    spr.setColor(цвет);
    spr.setPosition(_позиция);
    window.draw(spr);
}
ничего спрайт(sf::Texture &текстура, sf::Vector2f _позиция,sf::Color цвет = sf::Color::White, да_нет _центрировать = false){
    spr.setTexture(текстура,true);
    if(_центрировать){
        sf::Vector2f size = {текстура.getSize().x / 2.f, текстура.getSize().y / 2.f};
        spr.setOrigin(size);
    }else{
        spr.setOrigin({0,0});
    }
    spr.setColor(цвет);
    spr.setPosition(_позиция);
    window.draw(spr);
}
ничего прикольная_линия(sf::Vector2f с, sf::Vector2f по, sf::Color цвет_с,sf::Color цвет_по){
    sf::VertexArray line(sf::LineStrip, 2);
    line[0].position = с;
    line[0].color = цвет_с;
    line[1].position = по;
    line[1].color = цвет_по;
    window.draw(line);
}
ничего квадрат(sf::Vector2f _позиция,sf::Vector2f _размер,sf::Color _цвет = sf::Color::White){
    парралелепипед.setFillColor(_цвет);
    парралелепипед.setOutlineThickness(0);
    парралелепипед.setOutlineColor({0,0,0,0});
    парралелепипед.setSize(_размер);
    парралелепипед.setPosition(_позиция);
    window.draw(парралелепипед);
}
ничего квадрат_из_линий( sf::Vector2f _позиция,sf::Vector2f _размер,sf::Color _цвет = sf::Color::White){
    парралелепипед.setFillColor({0,0,0,0});
    парралелепипед.setOutlineThickness(2);
    парралелепипед.setOutlineColor(_цвет);
    парралелепипед.setSize(_размер);
    парралелепипед.setPosition(_позиция);
    window.draw(парралелепипед);
}