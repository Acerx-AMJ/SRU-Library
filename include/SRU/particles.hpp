#pragma once
#include "SRU/constants.hpp"
#include <string>
#include <unordered_map>
#include <vector>

struct Particle {
   Particle() = default;
   Particle(Vector2 position, Vector2 velocity, Vector2 acceleration, Vector2 size, float scale, float rotation, float rotationVelocity, float friction, float lifetime)
      : position(position), velocity(velocity), acceleration(acceleration), size(size), scale(scale), rotation(rotation), rotationVelocity(rotationVelocity), friction(friction), lifetime(lifetime) {}
   Particle(Texture *texture, Vector2 position, Vector2 velocity, Vector2 acceleration, Vector2 size, float scale, float rotation, float rotationVelocity, float friction, float lifetime)
      : texture(texture), position(position), velocity(velocity), acceleration(acceleration), size(size), scale(scale), rotation(rotation), rotationVelocity(rotationVelocity), friction(friction), lifetime(lifetime) {}
   Particle(Texture *texture, Vector2 position, Vector2 velocity, Vector2 acceleration, Vector2 size, float scale, float rotation, float rotationVelocity, float friction, float lifetime, int splitX, int splitY, int splitWidth, int splitHeight)
      : texture(texture), position(position), velocity(velocity), acceleration(acceleration), size(size), scale(scale), rotation(rotation), rotationVelocity(rotationVelocity), friction(friction), lifetime(lifetime), splitX(splitX), splitY(splitY), splitWidth(splitWidth), splitHeight(splitHeight) {}

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

struct ParticleCluster {
   ParticleConfig config;
   std::vector<Particle> cluster;
};

void pushParticleCluster(const std::string &name, ParticleConfig config);
void removeParticleCluster(const std::string &name);
bool particleClusterExists(const std::string &name);
ParticleCluster &getParticleCluster(const std::string &name);
size_t getParticleClusterCount();
std::unordered_map<std::string, ParticleCluster> &getParticleClusterContainer();

bool isParticleClusterEmpty(const std::string &name);
size_t getParticleCount(const std::string &name);
size_t getTotalParticleCount();

void updateParticles(float DT);
void updateParticleCluster(const std::string &name, float DT);
void updateParticleCluster(ParticleCluster &cluster, float DT);

void drawParticles();
void drawParticleCluster(const std::string &name);
void drawParticleCluster(const ParticleCluster &cluster);
void drawResponsiveParticles(Rectangle area = WINDOW_AREA, int type = RATIO);
void drawResponsiveParticleCluster(const std::string &name, Rectangle area = WINDOW_AREA, int type = RATIO);
void drawResponsiveParticleCluster(const ParticleCluster &cluster, Rectangle area = WINDOW_AREA, int type = RATIO);

void clearParticles();
void clearParticleCluster(const std::string &name);
void clearParticleCluster(ParticleCluster &cluster);

void spawnParticles(const std::string &name, size_t count = 0, Texture *texture = nullptr, Vector2 position = {}, bool useConfigPosition = true);
void spawnParticles(ParticleCluster &cluster, size_t count = 0, Texture *texture = nullptr, Vector2 position = {}, bool useConfigPosition = true);
