//
// Created by davih on 12.04.2020.
//

#include <windows.h>
#include<iostream>
int main(){
    char buffer[100];
   std::cout << GetModuleFileName( nullptr, buffer, 100 );
}