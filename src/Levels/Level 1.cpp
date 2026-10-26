#include "CPU.hh"
#include "ball.hh"
#include "player.hh"
#include "collision_event_manager.hh"
#include "input_event_manager.hh"
#include <AEEngine.h>
#include <imgui/imgui.h>
#include "Level 1.h"

int mode = 0;

Player* player = nullptr;
Ball* ball = nullptr;
CPU* cpu = nullptr;

InputEventManager* inputManager = nullptr;
CollisionEventManager* collisionManager = nullptr;

bool ShowFrameworkMenu();

void Level_1_Load()
{
}

void Level_1_Init()
{
    player = new Player(-350, 0);
    ball = new Ball(0, 0);
    cpu = new CPU(350, 0, ball);

    inputManager = new InputEventManager();
    inputManager->registerEventHandler(player->getInputHandler());

    collisionManager = new CollisionEventManager(ball, player, cpu);
    collisionManager->registerEventHandler(ball->getCollisionHandler());
    collisionManager->registerEventHandler(cpu->getCollisionHandler());
}

void Level_1_Update()
{
    // core keyboard shortcuts and GUI, do not delete this code!
    KeyboardInput();
    bool guiActive = ShowFrameworkMenu();

    // Detect keyboard input and dispatch events
    if (inputManager != nullptr)
    {
        inputManager->update();
    }

    if (collisionManager != nullptr)
    {
        collisionManager->update();
    }
    // Update player position
    if (player != nullptr)
    {
        player->Update();
    }
    // Update ball position
    if (ball != nullptr)
    {
        ball->Update();
    }
    // Update cpu position
    if (cpu != nullptr)
    {
        cpu->Update();
    }
}

void Level_1_Render()
{
    // clear frame buffer, do not delete this code
    AEGfxSetClearColor(AEGfxColor(0, 0, 0));
    AEGfxClearBuffer();

    // Draw player paddle
    if (player != nullptr)
    {
        player->Draw();
    }
    // Draw ball
    if (ball != nullptr)
    {
        ball->Draw();
    }
    // Draw cpu
    if (cpu != nullptr)
    {
        cpu->Draw();
    }
}

void Level_1_Free()
{
    delete inputManager;
    inputManager = nullptr;

    delete collisionManager;
    collisionManager = nullptr;

    delete player;
    player = nullptr;

    delete ball;
    ball = nullptr;

    delete cpu;
    cpu = nullptr;
}

void Level_1_Unload()
{
}

void KeyboardInput()
{
    if (AEInputKeyTriggered('R'))
        AESetGameStateNext(AE_GS_RESTART);
    if (AEInputKeyTriggered('Q') && AEInputKeyPressed(AE_KEY_CTRL))
        AESetGameStateNext(AE_GS_QUIT);
}

bool ShowFrameworkMenu()
{
    bool isGuiActive = false;
    mode = 0;

    // show File options 
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Mode")) {

            if (ImGui::MenuItem("Restart", "1"))
                mode = 1;

            ImGui::EndMenu();
        }

        auto mSize = ImGui::GetWindowHeight();
        AEVec2 mouseVP = AEGetMouseData().position + AEVec2((float)AEGetSysWindowWidth() / 2.0f, (float)AEGetSysWindowHeight() / 2.0f);
        auto inMenu = mouseVP.y >= (AEGetSysWindowHeight() - mSize);
        isGuiActive = ImGui::IsAnyItemActive() || ImGui::IsAnyItemHovered() || inMenu;

        ImGui::EndMainMenuBar();
    }

    if (mode == 1) {
        AESetGameStateNext(AE_GS_RESTART);
    }

    return isGuiActive;
}

