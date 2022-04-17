#ifndef GAME_PROCESS_HPP
#define GAME_PROCESS_HPP

#include "core.hpp"
#include "systems/systems.hpp"

#include <filesystem>
#include <iostream>

#include "xml/pugixml.hpp"
#include <random>

constexpr const auto tileid = "tileset";
constexpr const auto spriteid = "spritesheet";
constexpr const auto batid = "batsprite";
class GameScene : public sdl::BasicScene
{
public:
    ~GameScene()
    {
    }
    GameScene()
    {
        auto &signal = registry.set<collision_signal>();
        auto &sink = registry.set<collision_sink>(signal);
        sink.connect<&EnemyCharging>();
        sink.connect<&OnHit>();

        textureCache.load(tileid, sdl::ResourceLoader::Sprite("resources/sprites/castle-tileset.png"));
        textureCache.load(spriteid, sdl::ResourceLoader::Sprite("resources/sprites/spritesheet.png"));
        textureCache.load(batid, sdl::ResourceLoader::Sprite("resources/sprites/Bat_Sprite.png"));

        fontCache.load("font23", sdl::ResourceLoader::Font("resources/fonts/dpcomic"
                                                           ".ttf",
                                                           23));
        fontCache.load("font35", sdl::ResourceLoader::Font("resources/fonts/dpcomic"
                                                           ".ttf",
                                                           35));

        scoreTable.Open("resources/score.txt");

        spriteSheet.Load("resources/tiled_files/sprite.tsx", textureCache.resource(spriteid));
        batSheet.Load("resources/tiled_files/bats.tsx", textureCache.resource(batid));
        tileset.Load("resources/tiled_files/Arena.tsx", textureCache.resource(tileid));
        CameraCreate();
        GridCreate();
        PlayerCreate();

          EnemyCreate(Enemy::spawns[0]);
          EnemyCreate(Enemy::spawns[1]);
          EnemyCreate(Enemy::spawns[2]);
          EnemyCreate(Enemy::spawns[3]);
          EnemyCreate(Enemy::spawns[4]);
          EnemyCreate(Enemy::spawns[5]);
          Enemy::currentSpawn = 6;

        CreateLabels();
    }

    void FixedUpdate() override
    {
        UpdateView();
        CameraFollow();
        CollisionDetection();
        HealthUpdate();
    }
    void Update(const float dt) override
    {
        CollisionTileDetection(dt);
        AnimationUpdate(dt);
        MovementUpdate(dt);
        EnemyWalking(dt);
        PlayerMovement(dt);
        PlayerAttack(dt);
        ParticleUpdate(dt);
        GravitationUpdate(dt);
    }
    void InputUpdate() override
    {
        CameraUpdateDebug();
        OpenGame();
        DebugMode();
    }

    void Render() override
    {
        GridRender();
        SpriteRender();
        PositionDebug();
        RectDebug();
        LabelsRender();
    }
};

#endif // GAME_PROCESS_HPP
