#pragma once
#include <string>
// Перевод с бесовского на русский
using ничего = void;
using цифорка = int;
using да_нет = bool;
using строка = std::string;
using стринги = std::wstring;
using символ = char;
#define данные_какието struct
#define обосратся throw
#define главная main
#define возврат return
#define очко nullptr;

данные_какието ошибочка{
    стринги чё;
    ошибочка(стринги _текст):чё(_текст){}
};
