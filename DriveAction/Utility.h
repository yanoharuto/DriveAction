#pragma once 
#include <Windows.h>

//関数のマクロ
//安全にインスタンスを開放 
#define SAFE_DELETE(p) {if(p){delete p; p=nullptr;}}

//エラーウィンドウ
#define ERROR_MSG(str){MessageBox(NULL,TEXT(str),TEXT("Error"),MB_OK|MB_ICONERROR);}