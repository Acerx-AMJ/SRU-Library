#include "SRU/particles.hpp"
#include "SRU/random.hpp"
#include "SRU/render.hpp"
#include "SRU/util.hpp"
#include <algorithm>
#include <cstdio>

static std::vector<ParticleConfig> particleConfig;
static std::vector<std::vector<Particle>> particleClusters;

Particle::Particle(Vector2 position, Vector2 velocity, Vector2 acceleration, Vector2 size, float scale, float rotation, float rotationVelocity, float friction, float lifetime)
   : position(position), velocity(velocity), acceleration(acceleration), size(size), scale(scale), rotation(rotation), rotationVelocity(rotationVelocity), friction(friction), lifetime(lifetime) {}

Particle::Particle(Texture *texture, Vector2 position, Vector2 velocity, Vector2 acceleration, Vector2 size, float scale, float rotation, float rotationVelocity, float friction, float lifetime)
   : texture(texture), position(position), velocity(velocity), acceleration(acceleration), size(size), scale(scale), rotation(rotation), rotationVelocity(rotationVelocity), friction(friction), lifetime(lifetime) {}

Particle::Particle(Texture *texture, Vector2 position, Vector2 velocity, Vector2 acceleration, Vector2 size, float scale, float rotation, float rotationVelocity, float friction, float lifetime, int splitX, int splitY, int splitWidth, int splitHeight)
   : texture(texture), position(position), velocity(velocity), acceleration(acceleration), size(size), scale(scale), rotation(rotation), rotationVelocity(rotationVelocity), friction(friction), lifetime(lifetime), splitX(splitX), splitY(splitY), splitWidth(splitWidth), splitHeight(splitHeight) {}

ParticleID pushParticleConfig(ParticleConfig config) {
   particleConfig.push_back(config);
   particleClusters.push_back({});
   return particleConfig.size() - 1;
}

ParticleConfig &getParticleConfig(ParticleID ID) {
   if (ID >= particleConfig.size()) {
      printf("srulib::getParticleConfig: ID out of bounds. ID is %llu and particle config count is %llu.\n", ID, particleConfig.size());
      exit(EXIT_FAILURE);
   }
   return particleConfig[ID];
}

std::vector<ParticleConfig> &getParticleConfigContainer() {
   return particleConfig;
}

std::vector<std::vector<Particle>> &getParticleClusters() {
   return particleClusters;
}

std::vector<Particle> &getParticleCluster(ParticleID ID) {
   return particleClusters[ID];
}

void updateParticles(float DT) {
   for (size_t ID = 0; ID < particleClusters.size(); ++ID) {
      updateParticleCluster(DT, ID);
   }
}

void updateParticleCluster(ParticleID ID, float DT) {
   std::vector<Particle> &cluster = particleClusters[ID];
   for (Particle &particle: cluster) {
      particle.age += DT;
      particle.position += particle.velocity * DT;
      particle.velocity += particle.acceleration * DT;
      particle.velocity *= (1.0f - particle.friction * DT);
      particle.size += V2(particle.scale * DT);
      particle.rotation += particle.rotationVelocity * DT;
   }

   cluster.erase(std::remove_if(cluster.begin(), cluster.end(), [](const Particle &p) -> bool {
      return p.age >= p.lifetime;
   }), cluster.end());
}

void drawParticles() {
   for (size_t ID = 0; ID < particleClusters.size(); ++ID) {
      drawParticleCluster(ID);
   }
}

void drawParticleCluster(ParticleID ID) {
   for (Particle &particle: particleClusters[ID]) {
      if (particle.texture && (particle.splitWidth != 0 || particle.splitHeight != 0)) {
         float unitX = (float)particle.texture->width / particle.splitWidth;
         float unitY = (float)particle.texture->height / particle.splitHeight;
         Rectangle source = {particle.splitX * unitX, particle.splitY * unitY, unitX, unitY};
         drawTextureSourceCentered(*particle.texture, source, particle.position, particle.size, Fade(WHITE, 1.0f - particle.age / particle.lifetime), particle.rotation);
      }
      else if (particle.texture) {
         drawTextureCentered(*particle.texture, particle.position, particle.size, Fade(WHITE, 1.0f - particle.age / particle.lifetime), particle.rotation);
      }
   }
}

void drawResponsiveParticles() {
   for (size_t ID = 0; ID < particleClusters.size(); ++ID) {
      drawResponsiveParticleCluster(ID);
   }
}

void drawResponsiveParticleCluster(ParticleID ID) {
   for (Particle &particle: particleClusters[ID]) {
      if (particle.texture && (particle.splitWidth != 0 || particle.splitHeight != 0)) {
         float unitX = (float)particle.texture->width / particle.splitWidth;
         float unitY = (float)particle.texture->height / particle.splitHeight;
         Rectangle source = {particle.splitX * unitX, particle.splitY * unitY, unitX, unitY};
         drawTextureSourceCenteredResponsive(*particle.texture, source, particle.position, particle.size, Fade(WHITE, 1.0f - particle.age / particle.lifetime), particle.rotation);
      }
      else if (particle.texture) {
         drawTextureCenteredResponsive(*particle.texture, particle.position, particle.size, Fade(WHITE, 1.0f - particle.age / particle.lifetime), particle.rotation);
      }
   }
}

void drawResponsiveCubicParticles() {
   for (size_t ID = 0; ID < particleClusters.size(); ++ID) {
      drawResponsiveCubicParticleCluster(ID);
   }
}

void drawResponsiveCubicParticleCluster(ParticleID ID) {
   for (Particle &particle: particleClusters[ID]) {
      if (particle.texture && (particle.splitWidth != 0 || particle.splitHeight != 0)) {
         float unitX = (float)particle.texture->width / particle.splitWidth;
         float unitY = (float)particle.texture->height / particle.splitHeight;
         Rectangle source = {particle.splitX * unitX, particle.splitY * unitY, unitX, unitY};
         drawTextureSourceCenteredResponsiveCubic(*particle.texture, source, particle.position, particle.size, Fade(WHITE, 1.0f - particle.age / particle.lifetime), particle.rotation);
      }
      else if (particle.texture) {
         drawTextureCenteredResponsiveCubic(*particle.texture, particle.position, particle.size, Fade(WHITE, 1.0f - particle.age / particle.lifetime), particle.rotation);
      }
   }
}

void clearParticles() {
   for (size_t ID = 0; ID < particleClusters.size(); ++ID) {
      clearParticleCluster(ID);
   }
}

void clearParticleCluster(ParticleID ID) {
   particleClusters[ID].clear();
}

void spawnParticles(ParticleID ID) {
   ParticleConfig &config = particleConfig[ID];
   spawnParticles(config.texture, config.count, randomV2(config.minimum.position, config.maximum.position), ID);
}

void spawnParticles(Vector2 position, ParticleID ID) {
   ParticleConfig &config = particleConfig[ID];
   spawnParticles(config.texture, config.count, position, ID);
}

void spawnParticles(size_t count, ParticleID ID) {
   ParticleConfig &config = particleConfig[ID];
   spawnParticles(config.texture, count, randomV2(config.minimum.position, config.maximum.position), ID);
}

void spawnParticles(size_t count, Vector2 position, ParticleID ID) {
   ParticleConfig &config = particleConfig[ID];
   spawnParticles(config.texture, count, position, ID);
}

void spawnParticles(Texture *texture, ParticleID ID) {
   ParticleConfig &config = particleConfig[ID];
   spawnParticles(texture, config.count, randomV2(config.minimum.position, config.maximum.position), ID);
}

void spawnParticles(Texture *texture, Vector2 position, ParticleID ID) {
   spawnParticles(texture, particleConfig[ID].count, position, ID);
}

void spawnParticles(Texture *texture, size_t count, ParticleID ID) {
   ParticleConfig &config = particleConfig[ID];
   spawnParticles(texture, count, randomV2(config.minimum.position, config.maximum.position), ID);
}

void spawnParticles(Texture *texture, size_t count, Vector2 position, ParticleID ID) {
   std::vector<Particle> &cluster = particleClusters[ID];
   ParticleConfig &config = particleConfig[ID];

   for (size_t i = 0; i < count; ++i) {
      cluster.emplace_back(
         texture,
         position,
         randomV2(config.minimum.velocity, config.maximum.velocity),
         randomV2(config.minimum.acceleration, config.maximum.acceleration),
         config.cubic ? randomV2Value(config.minimum.size.x, config.maximum.size.y) : randomV2(config.minimum.size, config.maximum.size),
         randomFloat(config.minimum.scale, config.maximum.scale),
         randomFloat(config.minimum.rotation, config.maximum.rotation),
         randomFloat(config.minimum.rotationVelocity, config.maximum.rotationVelocity),
         randomFloat(config.minimum.friction, config.maximum.friction),
         randomFloat(config.minimum.lifetime, config.maximum.lifetime)
      );
   }
}

void spawnSplitParticles(ParticleID ID) {
   ParticleConfig &config = particleConfig[ID];
   spawnSplitParticles(config.texture, randomInt(config.minimum.splitWidth, config.maximum.splitWidth), randomInt(config.minimum.splitHeight, config.maximum.splitHeight), randomV2(config.minimum.position, config.maximum.position), ID);
}

void spawnSplitParticles(Vector2 position, ParticleID ID) {
   ParticleConfig &config = particleConfig[ID];
   spawnSplitParticles(config.texture, randomInt(config.minimum.splitWidth, config.maximum.splitWidth), randomInt(config.minimum.splitHeight, config.maximum.splitHeight), position, ID);
}

void spawnSplitParticles(int splitWidth, int splitHeight, ParticleID ID) {
   ParticleConfig &config = particleConfig[ID];
   spawnSplitParticles(config.texture, splitWidth, splitHeight, randomV2(config.minimum.position, config.maximum.position), ID);
}

void spawnSplitParticles(int splitWidth, int splitHeight, Vector2 position, ParticleID ID) {
   ParticleConfig &config = particleConfig[ID];
   spawnSplitParticles(config.texture, splitWidth, splitHeight, position, ID);
}

void spawnSplitParticles(Texture *texture, ParticleID ID) {
   ParticleConfig &config = particleConfig[ID];
   spawnSplitParticles(texture, randomInt(config.minimum.splitWidth, config.maximum.splitWidth), randomInt(config.minimum.splitHeight, config.maximum.splitHeight), randomV2(config.minimum.position, config.maximum.position), ID);
}

void spawnSplitParticles(Texture *texture, Vector2 position, ParticleID ID) {
   ParticleConfig &config = particleConfig[ID];
   spawnSplitParticles(texture, randomInt(config.minimum.splitWidth, config.maximum.splitWidth), randomInt(config.minimum.splitHeight, config.maximum.splitHeight), position, ID);
}

void spawnSplitParticles(Texture *texture, int splitWidth, int splitHeight, ParticleID ID) {
   ParticleConfig &config = particleConfig[ID];
   spawnSplitParticles(texture, splitWidth, splitHeight, randomV2(config.minimum.position, config.maximum.position), ID);
}

void spawnSplitParticles(Texture *texture, int splitWidth, int splitHeight, Vector2 position, ParticleID ID) {
   std::vector<Particle> &cluster = particleClusters[ID];
   ParticleConfig &config = particleConfig[ID];
   size_t N = splitWidth * splitHeight;

   for (size_t i = 0; i < N; ++i) {
      cluster.emplace_back(
         texture,
         position,
         randomV2(config.minimum.velocity, config.maximum.velocity),
         randomV2(config.minimum.acceleration, config.maximum.acceleration),
         config.cubic ? randomV2Value(config.minimum.size.x, config.maximum.size.y) : randomV2(config.minimum.size, config.maximum.size),
         randomFloat(config.minimum.scale, config.maximum.scale),
         randomFloat(config.minimum.rotation, config.maximum.rotation),
         randomFloat(config.minimum.rotationVelocity, config.maximum.rotationVelocity),
         randomFloat(config.minimum.friction, config.maximum.friction),
         randomFloat(config.minimum.lifetime, config.maximum.lifetime),
         i % splitWidth,
         i / splitWidth,
         splitWidth,
         splitHeight
      );
   }
}
