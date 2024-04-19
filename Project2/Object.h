
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
    void Render(int x, int y, SDL_Renderer* des, const SDL_Rect* clip/* NULL */, double angle =0.0 , SDL_Point* Center=NULL,SDL_Rect* renderQuad =NULL);
    void Free();

};


#endif 



