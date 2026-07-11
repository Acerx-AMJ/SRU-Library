#pragma once
#include "raylib.h"
#include <vector>

using ParticleID = size_t;

struct Particle {
   Particle() = default;
   Particle(Vector2 position, Vector2 velocity, Vector2 acceleration, Vector2 size, float scale, float rotation, float rotationVelocity, float friction, float lifetime);
   Particle(Texture *texture, Vector2 position, Vector2 velocity, Vector2 acceleration, Vector2 size, float scale, float rotation, float rotationVelocity, float friction, float lifetime);
   Particle(Texture *texture, Vector2 position, Vector2 velocity, Vector2 acceleration, Vector2 size, float scale, float rotation, float rotationVelocity, float friction, float lifetime, int splitX, int splitY, int splitWidth, int splitHeight);

   Texture2D *texture = nullptr;
   Vector2 position, velocity, acceleration;
   Vector2 size;
   float scale = 1.0f;
   float rotation = 0.0f;
   float rotationVelocity = 0.0f;
   float friction = 0.0f;
   float lifetime = 0.0f;
   float age = 0.0f;
   int splitX = 0;
   int splitY = 0;
   int splitWidth = 0;
   int splitHeight = 0;
};

struct ParticleConfig {
   Texture2D *texture = nullptr;
   Particle minimum, maximum;
   size_t count = 0;
   bool cubic = false;
};

ParticleID pushParticleConfig(ParticleConfig config);
ParticleConfig &getParticleConfig(ParticleID ID);
std::vector<ParticleConfig> &getParticleConfigContainer();
std::vector<std::vector<Particle>> &getParticleClusters();
std::vector<Particle> &getParticleCluster(ParticleID ID);

void updateParticles(float DT);
void updateParticleCluster(ParticleID ID, float DT);

void drawParticles();
void drawParticleCluster(ParticleID ID);
void drawResponsiveParticles();
void drawResponsiveParticleCluster(ParticleID ID);
void drawResponsiveCubicParticles();
void drawResponsiveCubicParticleCluster(ParticleID ID);

void clearParticles();
void clearParticleCluster(ParticleID ID);

void spawnParticles(ParticleID ID);
void spawnParticles(Vector2 position, ParticleID ID);
void spawnParticles(size_t count, ParticleID ID);
void spawnParticles(size_t count, Vector2 position, ParticleID ID);
void spawnParticles(Texture *texture, ParticleID ID);
void spawnParticles(Texture *texture, Vector2 position, ParticleID ID);
void spawnParticles(Texture *texture, size_t count, ParticleID ID);
void spawnParticles(Texture *texture, size_t count, Vector2 position, ParticleID ID);

void spawnSplitParticles(ParticleID ID);
void spawnSplitParticles(Vector2 position, ParticleID ID);
void spawnSplitParticles(int splitWidth, int splitHeight, ParticleID ID);
void spawnSplitParticles(int splitWidth, int splitHeight, Vector2 position, ParticleID ID);
void spawnSplitParticles(Texture *texture, ParticleID ID);
void spawnSplitParticles(Texture *texture, Vector2 position, ParticleID ID);
void spawnSplitParticles(Texture *texture, int splitWidth, int splitHeight, ParticleID ID);
void spawnSplitParticles(Texture *texture, int splitWidth, int splitHeight, Vector2 position, ParticleID ID);
