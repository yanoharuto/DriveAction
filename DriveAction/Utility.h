#pragma once 
#include <Windows.h>

//�֐��̃}�N��
//���S�ɃC���X�^���X���J�� 
#define SAFE_DELETE(p) {if(p){delete p; p=nullptr;}}

//�G���[�E�B���h�E
#define ERROR_MSG(str){MessageBox(NULL,TEXT(str),TEXT("Error"),MB_OK|MB_ICONERROR);}