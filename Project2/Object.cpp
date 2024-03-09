#pragma once
#include "Object.h"

void Object::LoadImg(std::string path, SDL_Renderer* des) {

    SDL_Texture* newText = NULL;
    SDL_Surface* newSurface = IMG_Load(path.c_str());
    SDL_SetColorKey(newSurface ,SDL_TRUE, SDL_MapRGB(newSurface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
    newText = SDL_CreateTextureFromSurface(des, newSurface);

    SDL_FreeSurface(newSurface);
    SDL_QueryTexture(newText, NULL, NULL, &rect_.w, &rect_.h);
    mTexture = newText;
    
}

void Object::Render(int x, int y, SDL_Renderer* des, const SDL_Rect* clip /* NULL */)
{

    SDL_Rect renderquad = {x, y, rect_.w, rect_.h };
    SDL_RenderCopy(des, mTexture, clip, &renderquad);

}

Object::Object()
{
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = 0;
    rect_.h = 0;
    mTexture=NULL;
}
Object::~Object()
{
    Free();
}
void Object::Free()
{
    if (mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        rect_.w = 0;
        rect_.h = 0;
    }
    
}
