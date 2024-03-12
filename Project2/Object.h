
#pragma once
#ifndef OBJECT_H_
#define OBJECT_H_


#include "CommonFunc.h"


class Object {
public:
    Object() ;
    ~Object() ;
    SDL_Rect rect_ ;
    SDL_Texture* mTexture;

    virtual void LoadImg(std::string path, SDL_Renderer* des);
    void Render(int x, int y, SDL_Renderer* des,const SDL_Rect*clip/* NULL */);
    void Free();

};


#endif 



