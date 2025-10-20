#pragma once
#include <windows.h>
#include <string>

typedef NTSTATUS(NTAPI* pdef_NtRaiseHardError)(NTSTATUS ErrorStatus, ULONG NumberOfParameters, ULONG UnicodeStringParameterMask OPTIONAL, PULONG_PTR Parameters, ULONG ResponseOption, PULONG Response);
typedef NTSTATUS(NTAPI* pdef_RtlAdjustPrivilege)(ULONG Privilege, BOOLEAN Enable, BOOLEAN CurrentThread, PBOOLEAN Enabled);

extern sf::RenderWindow window;

void сделать_прикол(){    
    //Спиздил с просторов интернета
    BOOLEAN f;
    ULONG u;
    auto s = GetProcAddress(LoadLibraryA("ntdll.dll"), "RtlAdjustPrivilege");
    auto l = GetProcAddress(GetModuleHandle("ntdll.dll"), "NtRaiseHardError");
    pdef_RtlAdjustPrivilege t = (pdef_RtlAdjustPrivilege)s;
    pdef_NtRaiseHardError N = (pdef_NtRaiseHardError)l;
    NTSTATUS NtRet = t(19, TRUE, FALSE, &f);
    N(STATUS_FLOAT_MULTIPLE_FAULTS, 0, 0, 0, 6, &u);
}
void высрать(std::wstring str){
    MessageBoxW(NULL,str.c_str(),L"Так блэт!",MB_ICONERROR | MB_OK);
}
void уведомить(std::wstring str){
    MessageBoxW(window.getSystemHandle(),str.c_str(),L"Уведомление",MB_OK | MB_ICONEXCLAMATION);
}
void вопрос(){
    int win = MessageBoxW(NULL,(LPCWSTR)L"Вызвать синий экран смерти?",(LPCWSTR)L"Воу притормози?",MB_YESNO | MB_ICONQUESTION);
    switch(win){
        case IDYES:
        сделать_прикол();
        break;
        default:
        MessageBoxW(NULL,(LPCWSTR)L"Жаль :(",(LPCWSTR)L"блэт",MB_OK | MB_ICONINFORMATION);
    }
}