// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include "SDL_image.h"
#include "Random.h"
#include "Game.h"
#include "Actors/Actor.h"
#include "Actors/Pacman.h"
#include "Actors/Item.h"
#include "Actors/Bomb.h"
#include "Actors/Explosion.h"
#include "Actors/Wall.h"
#include "Components/DrawComponents/DrawComponent.h"
#include "Components/DrawComponents/DrawSpriteComponent.h"
#include "Actors/Box.h"
#include "Actors/Floor.h"
#include "AudioSystem.h"
#include "Font.h"
#include "Components/DrawComponents/DrawTextComponent.h"



Game::Game(int windowWidth, int windowHeight)
        :mWindow(nullptr)
        ,mRenderer(nullptr)
        ,mTicksCount(0)
        ,mIsRunning(true)
        ,mUpdatingActors(false)
        ,mWindowWidth(windowWidth)
        ,mWindowHeight(windowHeight)
        ,mRespawnTimer(RESPAWN_TIME)

{
}

bool Game::Initialize()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    auto Width = DM.w;
    auto Height = DM.h;
    mWindow = SDL_CreateWindow("P4: Super Pacman Bros", (Width - mWindowWidth) / 2, (Height - mWindowHeight)/2, mWindowWidth, mWindowHeight, 0);
    if (!mWindow)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!mRenderer)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }

    Random::Init();

    mTicksCount = SDL_GetTicks();

    // Init all game actors

    InitializeActors();
    return true;
}

void Game::InitializeActors()
{
    if(mGameState == State::Menu){
        beg = false;
        UnloadActors();
        //mMenuFont = new Font();
        //mMenuFont->Load("../Assets/Fonts/Zelda.ttf");
        auto *background = new Actor(this);
        background->SetPosition(Vector2(256.0f, 256.0f));
        new DrawSpriteComponent(background, "../Assets/Sprites/Background/Background.png", 512, 512);

        new DrawSpriteComponent(background, "../Assets/Sprites/Background/lettering.png", 512, 512);
        new DrawSpriteComponent(background, "../Assets/Sprites/Background/title.png", 512, 512);
        new DrawSpriteComponent(background, "../Assets/Sprites/Background/drawing.png", 512, 512);



    }

    if(mGameState ==State::Intro){
            beg = true;
            UnloadActors();
            auto* background = new Actor(this);
            background->SetPosition(Vector2(256.0f, 256.0f));


            LoadLevel("../Assets/Levels/Level.txt",15,15);
            mAudio = new AudioSystem();
            mAudio->PlaySound("MusicLoop.ogg",true);


    }

}

void Game::SetGameState(State gameState)
{
    //mAudio->StopAllSounds();
    mFadeState = FadeState::FadeOut;
    mGameState = gameState;


}


void Game::LoadLevel(const std::string& levelPath,const int width, const int height)
{
    const float STARTX = 32.0f;
    const float STARTY = 32.0f;
    const float SPACING = 32.0f;

    std::ifstream  levelP;
    levelP.open(levelPath);
    if(!levelP.is_open()){
        SDL_Log("Erro ao abrir a imagem");
        this->Quit();
        return;
    }
    std::string aux;
    for (int i = 0; i < height; ++i) {
        std::getline(levelP,aux);

        for (int j = 0; j < width; ++j) {
            Vector2 pos;
            pos.x = STARTX + SPACING * j;
            pos.y = STARTY + SPACING * i;

                if(aux[j] == '-'){


                    auto* wall = new Wall(this,std::string(1,aux[j]),ColliderLayer::Wall,1);
                    wall->SetPosition(pos);

                }

                else if(aux[j] == 'M'){

                    mPacman = new Pacman(this,1,125);
                    mPacman->SetPosition(pos);
                    auto* wall = new Wall(this,"%",ColliderLayer::Node,1);
                    wall->SetPosition(pos);
                    mBombPositions.emplace_back(pos);
                }
                else if(aux[j] == '%'){
                    auto* path = new Floor(this,std::string(1,aux[j]),ColliderLayer::Node,1);
                    path->SetPosition(pos);
                    mBombPositions.emplace_back(pos);

                }
                else if(aux[j] == 'A'){
                    mPlayer2 =  new Pacman(this,2,125);
                    mPlayer2->SetPosition(pos);
                    auto* wall = new Wall(this,"%",ColliderLayer::Node,1);
                    wall->SetPosition(pos);
                    mBombPositions.emplace_back(pos);

                }
                else if(aux[j] == 'C'){
                    auto* box = new Box(this,std::string(1,aux[j]),ColliderLayer::Box);
                    auto* path = new Wall(this,"%",ColliderLayer::Node,1);
                    path->SetPosition(pos);
                    box->SetPosition(pos);
                    mBombPositions.emplace_back(pos);
                }

            }
        }
        mPacman->Start();
        mPlayer2->Start();
    
        levelP.close();
}


void Game::UnloadActors()
{
    while (!mActors.empty())
    {
        delete mActors.back();
    }


}


void Game::RunLoop()
{
    while (mIsRunning)
    {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::ProcessInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                Quit();
                break;
        }
    }

    const Uint8* state = SDL_GetKeyboardState(nullptr);

    for (auto actor : mActors)
    {
        actor->ProcessInput(state);
    }

    if (state[SDL_SCANCODE_SPACE])
    {
            if(!beg)
                SetGameState(State::Intro);

    }

}

void Game::UpdateGame()
{
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
    if (deltaTime > 0.05f)
    {
        deltaTime = 0.05f;
    }

    mTicksCount = SDL_GetTicks();

    if (mGameState == State::Intro)
    {
        UnloadActors();
        InitializeActors();
    }

    // Update all actors and pending actors
    UpdateActors(deltaTime);

    // Update camera position
    UpdateCamera();

    // Update game state
    UpdateState(deltaTime);
}

void Game::UpdateCamera()
{

}




void Game::UpdateActors(float deltaTime)
{
    mUpdatingActors = true;
    for (auto actor : mActors)
    {
        actor->Update(deltaTime);
    }
    mUpdatingActors = false;

    for (auto pending : mPendingActors)
    {
        mActors.emplace_back(pending);
    }
    mPendingActors.clear();

    std::vector<Actor*> deadActors;
    for (auto actor : mActors)
    {
        if (actor->GetState() == ActorState::Destroy)
        {
            deadActors.emplace_back(actor);
        }
    }

    for (auto actor : deadActors)
    {
        delete actor;
    }
}

void Game::UpdateState(float deltaTime)
{


        if ((mPacman->IsDead() && mPacman->mDyingTimer <= 0) || (mPlayer2->IsDead() && mPlayer2->mDyingTimer <= 0)) {

            mGameState = State::Menu;
            mRespawnTimer = RESPAWN_TIME;

            InitializeActors();
        }


    // Count number of pellets in game
    int pellets_count = 0;

    // If there are no more pellets, player won
    // For now, just pause the game
    if(pellets_count == 0)
    {
        //mGameState = State::Won;

    }
}

void Game::AddActor(Actor* actor)
{
    if (mUpdatingActors)
    {
        mPendingActors.emplace_back(actor);
    }
    else
    {
        mActors.emplace_back(actor);
    }
}

void Game::RemoveActor(Actor* actor)
{
    auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
    if (iter != mPendingActors.end())
    {
        // Swap to end of vector and pop off (avoid erase copies)
        std::iter_swap(iter, mPendingActors.end() - 1);
        mPendingActors.pop_back();
    }

    iter = std::find(mActors.begin(), mActors.end(), actor);
    if (iter != mActors.end())
    {
        // Swap to end of vector and pop off (avoid erase copies)
        std::iter_swap(iter, mActors.end() - 1);
        mActors.pop_back();
    }
}

void Game::AddDrawable(class DrawComponent *drawable)
{
    mDrawables.emplace_back(drawable);

    std::sort(mDrawables.begin(), mDrawables.end(),[](DrawComponent* a, DrawComponent* b) {
        return a->GetDrawOrder() < b->GetDrawOrder();
    });
}

void Game::RemoveDrawable(class DrawComponent *drawable)
{
    auto iter = std::find(mDrawables.begin(), mDrawables.end(), drawable);
    mDrawables.erase(iter);
}



void Game::AddItem(Item* item)
{
    mItems.emplace_back(item);
}

void Game::RemoveItem(Item* item)
{
    auto iter = std::find(mItems.begin(), mItems.end(), item);
    mItems.erase(iter);
}

void Game::AddWall(Wall* wall)
{
    mWalls.emplace_back(wall);
}

void Game::RemoveWall(Wall* item)
{
    auto iter = std::find(mWalls.begin(), mWalls.end(), item);
    mWalls.erase(iter);
}

void Game::AddFloor(Floor* floor)
{
    mFloors.emplace_back(floor);
}

void Game::RemoveFloor(Floor* floor)
{
    auto iter = std::find(mFloors.begin(), mFloors.end(), floor);
    mFloors.erase(iter);
}

void Game::AddBox(Box* box)
{
    mBoxes.emplace_back(box);
}


void Game::RemoveBox(Box* box)
{
    auto iter = std::find(mBoxes.begin(), mBoxes.end(), box);
    mBoxes.erase(iter);
}

void Game::AddBomb(Bomb* bomb) {
    mBombs.emplace_back(bomb);
}

void Game::RemoveBomb(Bomb* bomb) {
    auto iter = std::find(mBombs.begin(), mBombs.end(), bomb);

    mBombs.erase(iter);
}




void Game::GenerateOutput()
{
    // Set draw color to black
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);

    // Clear back buffer
    SDL_RenderClear(mRenderer);



    for (auto drawable : mDrawables)
    {
        if (drawable->IsVisible())
        {
            drawable->Draw(mRenderer);
        }
    }

    // Swap front buffer and back buffer
    SDL_RenderPresent(mRenderer);
}



SDL_Texture* Game::LoadTexture(const std::string& texturePath) {
    // Load from file
    SDL_Surface* surf = IMG_Load(texturePath.c_str());
    if (!surf)
    {
        SDL_Log("Failed to load texture file %s", texturePath.c_str());
        return nullptr;
    }

    // Create texture from surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer, surf);
    SDL_FreeSurface(surf);
    if (!texture)
    {
        SDL_Log("Failed to convert surface to texture for %s", texturePath.c_str());
        return nullptr;
    }

    return texture;
}

void Game::Shutdown()
{
    while (!mActors.empty())
    {
        delete mActors.back();
    }

    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}
