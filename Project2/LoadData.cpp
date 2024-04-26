#include "LoadData.h"



void LoadSFX()
{
    fall = Mix_LoadWAV("sound//fall.wav");
    walking = Mix_LoadWAV("sound//walking.wav");
    jumping = Mix_LoadWAV("sound//jumping.wav");
    landing = Mix_LoadWAV("sound//landing.wav");
    icebreaking = Mix_LoadWAV("sound//icebreaking.wav");
    tap = Mix_LoadWAV("sound//tap.wav");
    door_open = Mix_LoadWAV("sound//door_open.wav");
    bird = Mix_LoadWAV("sound//bird.mp3");
    cashing = Mix_LoadWAV("sound//cashing.wav");

    music_theme[0] = Mix_LoadMUS("sound//theme0.mp3");
    music_theme[1] = Mix_LoadMUS("sound//theme1.mp3");
    music_theme[2] = Mix_LoadMUS("sound//theme2.mp3");
    music_theme[3] = Mix_LoadMUS("sound//theme2.mp3");
    music_rick = Mix_LoadMUS("sound//rick.mp3");
    music_victory = Mix_LoadMUS("sound//victory.mp3");

}
void LoadMoney(std::ifstream& money)
{
    money.open("Data//money.txt");
    int mon;
    money >> mon;
    Achive_ = mon;
    money.close();
}

void SaveMoney(std::ofstream& money2)
{
    money2.open("Data//money.txt", std::ios::trunc);
    money2 << Achive_;
    money2.close();
}

void loadLeaderBoard(std::ifstream& board, std::pair< int, std::string>bo[11])
{

    board.open("Data//board.txt");
    if (!board.is_open()) {

        std::cout << "Unable to open file for writing.." << std::endl;
    }

    char a;
    for (int i = 1; i < 11; i++)
    {

        getline(board, bo[i].second);
        board >> bo[i].first;
        board.ignore();


    }

    board.close();

}


