// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include <SDL.h>
#include <vector>
#include "Math.h"
#include <string>



class Game
{
public:
    enum State
    {
        Intro,
        Started,
        Over,
        Won
    };



    Game(int windowWidth, int windowHeight);

    bool Initialize();
    void RunLoop();
    void Shutdown();
    void Quit() { mIsRunning = false; }

    // Actor functions
    void InitializeActors();
    void UpdateActors(float deltaTime);
    void AddActor(class Actor* actor);
    void RemoveActor(class Actor* actor);

    // Draw functions
    void AddDrawable(class DrawComponent* drawable);
    void RemoveDrawable(class DrawComponent* drawable);

    // Camera functions
    Vector2& GetCameraPos() { return mCameraPos; };
    void SetCameraPos(const Vector2& position) { mCameraPos = position; };

    // Window functions
    int GetWindowWidth() const { return mWindowWidth; }
    int GetWindowHeight() const { return mWindowHeight; }

    SDL_Texture* LoadTexture(const std::string& texturePath);

    // Game-specific
    std::vector<class Pacman*> GetPlayer() {
        std::vector<class Pacman*> pacmans;
        pacmans.push_back(mPacman);
        pacmans.push_back(mPlayer2);
        return pacmans;
    }

    void SetGameState(State gameState);
    bool GetGameState() { return mGameState; }

    std::vector<class Bomb*> mBombs;
    void AddBomb(Bomb* bomb);
    void RemoveBomb(Bomb* bomb);




    void AddItem(class Item* item);
    void RemoveItem(class Item* item);
    std::vector<class Item*>& GetItems() { return mItems; }

    void AddWall(class Wall* wall);
    void RemoveWall(class Wall* wall);
    std::vector<class Wall*>& GetWalls() { return mWalls; }

    void AddFloor(class Floor* floor);
    void RemoveFloor(class Floor* floor);
    std::vector<class Floor*>& GetFloor() { return mFloors; }

    std::vector<class Box*>& Getbox() { return mBoxes; }
    void AddBox(class Box* box);
    void RemoveBox(class Box* box);



private:
    const float RESPAWN_TIME = 1.1f;

    // Core game loop
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();

    // Auxiliary updates
    void UpdateCamera();
    void UpdateState(float deltaTime);

    // Load data
    void LoadLevel(const std::string& texturePath, const int width, const int height);
    void LoadPaths(const std::string& fileName);

    class AudioSystem* mAudio;
    // All the actors in the game
    std::vector<class Actor*> mActors;
    std::vector<class Actor*> mPendingActors;

    // All the draw components
    std::vector<class DrawComponent*> mDrawables;

    // SDL stuff
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;

    // Window properties
    int mWindowWidth;
    int mWindowHeight;

    // Track elapsed time since game start
    Uint32 mTicksCount;

    // Track if we're updating actors right now
    bool mIsRunning;
    bool mUpdatingActors;

    Vector2 mCameraPos;

    // Game-specific
    class Pacman *mPacman;
    class Pacman *mPlayer2;
    
    std::vector<class Item*> mItems;
    std::vector<class Wall*> mWalls;
    std::vector<class Floor*> mFloors;
    std::vector<class Ghost*> mGhosts;
    std::vector<class PathNode*> mPathNodes;
    std::vector<class Box*> mBoxes;



    class PathNode* mTunnelLeft = nullptr;
    class PathNode* mTunnelRight = nullptr;
    class PathNode* mGhostPen = nullptr;



    bool mShowGraph = false;
    bool mShowGhostPaths = true;
    bool mPrev1Input = false;
    bool mPrev2Input = false;
    int mGameState = State::Intro;

    float mRespawnTimer = 0.0f;

    void RestartGame();
};
