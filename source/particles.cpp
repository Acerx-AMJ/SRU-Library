#include "SRU/error.hpp"
#include "SRU/particles.hpp"
#include "SRU/random.hpp"
#include "SRU/render.hpp"
#include "SRU/util.hpp"
#include <algorithm>
#include <cstdio>

static std::unordered_map<std::string, ParticleCluster> particleClusters;
static ParticleCluster fallbackCluster;

void pushParticleCluster(const std::string &name, ParticleConfig config) {
   std::vector<Particle> vector;
   vector.reserve(config.count);
   particleClusters[name] = {config, vector};
}

void removeParticleCluster(const std::string &name) {
   particleClusters.erase(name);
}

bool particleClusterExists(const std::string &name) {
   return particleClusters.find(name) != particleClusters.end();
}

ParticleCluster &getParticleCluster(const std::string &name) {
   if (auto it = particleClusters.find(name); it != particleClusters.end()) {
      return it->second;
   }
   SRULibWarning(TextFormat("srulib::getParticleCluster: Particle cluster '%s' does not exist.\n", name.c_str()));
   return fallbackCluster;
}

size_t getParticleClusterCount() {
   return particleClusters.size();
}

std::unordered_map<std::string, ParticleCluster> &getParticleClusterContainer() {
   return particleClusters;
}

bool isParticleClusterEmpty(const std::string &name) {
   if (auto it = particleClusters.find(name); it != particleClusters.end()) {
      return it->second.cluster.empty();
   }
   SRULibWarning(TextFormat("srulib::isParticleClusterEmpty: Particle cluster '%s' does not exist.\n", name.c_str()));
   return true;
}

size_t getParticleCount(const std::string &name) {
   if (auto it = particleClusters.find(name); it != particleClusters.end()) {
      return it->second.cluster.size();
   }
   SRULibWarning(TextFormat("srulib::getParticleCount: Particle cluster '%s' does not exist.\n", name.c_str()));
   return 0;
}

size_t getTotalParticleCount() {
   size_t total = 0;
   for (auto &[_, cluster]: particleClusters) {
      total += cluster.cluster.size();
   }
   return total;
}

void updateParticles(float DT) {
   for (auto &[_, cluster]: particleClusters) {
      updateParticleCluster(cluster, DT);
   }
}

void updateParticleCluster(const std::string &name, float DT) {
   if (auto it = particleClusters.find(name); it != particleClusters.end()) {
      updateParticleCluster(it->second, DT);
      return;
   }
   SRULibWarning(TextFormat("srulib::updateParticleCluster: Particle cluster '%s' does not exist.\n", name.c_str()));
}

void updateParticleCluster(ParticleCluster &cluster, float DT) {
   for (Particle &particle: cluster.cluster) {
      particle.age += DT;
      particle.position += particle.velocity * DT;
      particle.velocity += particle.acceleration * DT;
      particle.velocity *= (1.0f - particle.friction * DT);
      particle.size += V2(particle.scale * DT);
      particle.rotation += particle.rotationVelocity * DT;
   }

   cluster.cluster.erase(std::remove_if(cluster.cluster.begin(), cluster.cluster.end(), [](const Particle &p) -> bool {
      return p.age >= p.lifetime;
   }), cluster.cluster.end());
}

void drawParticles() {
   for (const auto &[_, cluster]: particleClusters) {
      drawParticleCluster(cluster);
   }
}

void drawParticleCluster(const std::string &name) {
   if (const auto it = particleClusters.find(name); it != particleClusters.end()) {
      drawParticleCluster(it->second);
      return;
   }
   SRULibWarning(TextFormat("srulib::drawParticleCluster: Particle cluster '%s' does not exist.\n", name.c_str()));
}

void drawParticleCluster(const ParticleCluster &cluster) {
   for (const Particle &particle: cluster.cluster) {
      if (particle.texture && (particle.splitWidth != 0 || particle.splitHeight != 0)) {
         float unitX = (float)particle.texture->width / particle.splitWidth;
         float unitY = (float)particle.texture->height / particle.splitHeight;
         Rectangle source = {particle.splitX * unitX, particle.splitY * unitY, unitX, unitY};
         drawTexture(*particle.texture, particle.position, particle.size, CENTER, Fade(WHITE, 1.0f - particle.age / particle.lifetime), source, particle.rotation);
      }
      else if (particle.texture) {
         drawTexture(*particle.texture, particle.position, particle.size, CENTER, Fade(WHITE, 1.0f - particle.age / particle.lifetime), FULL_SOURCE, particle.rotation);
      }
   }
}

void drawResponsiveParticles(Rectangle area, int type) {
   for (const auto &[_, cluster]: particleClusters) {
      drawResponsiveParticleCluster(cluster, area, type);
   }
}

void drawResponsiveParticleCluster(const std::string &name, Rectangle area, int type) {
   if (const auto it = particleClusters.find(name); it != particleClusters.end()) {
      drawResponsiveParticleCluster(it->second, area, type);
      return;
   }
   SRULibWarning(TextFormat("srulib::drawResponsiveParticleCluster: Particle cluster '%s' does not exist.\n", name.c_str()));
}

void drawResponsiveParticleCluster(const ParticleCluster &cluster, Rectangle area, int type) {
   for (const Particle &particle: cluster.cluster) {
      if (particle.texture && (particle.splitWidth != 0 || particle.splitHeight != 0)) {
         float unitX = (float)particle.texture->width / particle.splitWidth;
         float unitY = (float)particle.texture->height / particle.splitHeight;
         Rectangle source = {particle.splitX * unitX, particle.splitY * unitY, unitX, unitY};
         drawTextureResponsive(*particle.texture, particle.position, particle.size, CENTER, Fade(WHITE, 1.0f - particle.age / particle.lifetime), source, area, type, particle.rotation);
      }
      else if (particle.texture) {
         drawTextureResponsive(*particle.texture, particle.position, particle.size, CENTER, Fade(WHITE, 1.0f - particle.age / particle.lifetime), FULL_SOURCE, area, type, particle.rotation);
      }
   }
}

void clearParticles() {
   for (auto &[_, cluster]: particleClusters) {
      clearParticleCluster(cluster);
   }
}

void clearParticleCluster(const std::string &name) {
   if (auto it = particleClusters.find(name); it != particleClusters.end()) {
      clearParticleCluster(it->second);
      return;
   }
   SRULibWarning(TextFormat("srulib::clearParticleCluster: Particle cluster '%s' does not exist.\n", name.c_str()));
}

void clearParticleCluster(ParticleCluster &cluster) {
   cluster.cluster.clear();
}

void spawnParticles(const std::string &name, size_t count, Texture *texture, Vector2 position, bool useConfigPosition) {
   if (auto it = particleClusters.find(name); it != particleClusters.end()) {
      spawnParticles(it->second, count, texture, position, useConfigPosition);
      return;
   }
   SRULibWarning(TextFormat("srulib::spawnParticles: Particle cluster '%s' does not exist.\n", name.c_str()));
}

void spawnParticles(ParticleCluster &cluster, size_t count, Texture *texture, Vector2 position, bool useConfigPosition) {
   Texture *particleTexture = (texture && !IsTextureValid(*texture) ? cluster.config.texture : texture);
   size_t particleCount = (count == 0 ? cluster.config.count : count);

   const Particle &min = cluster.config.minimum;
   const Particle &max = cluster.config.maximum;

   bool shouldSplit = (min.splitWidth != 0 && min.splitHeight != 0 && max.splitWidth != 0 && max.splitHeight != 0);
   int splitWidth = 0;
   int splitHeight = 0;
   
   if (shouldSplit) {
      splitWidth = randomInt(min.splitWidth, max.splitWidth);
      splitHeight = randomInt(min.splitHeight, max.splitHeight);
      particleCount = splitWidth * splitHeight;
   }

   for (size_t i = 0; i < particleCount; ++i) {
      cluster.cluster.emplace_back(
         particleTexture,
         (useConfigPosition ? randomV2(min.position, max.position) : position),
         randomV2(min.velocity, max.velocity),
         randomV2(min.acceleration, max.acceleration),
         cluster.config.cubic ? randomV2Value(min.size.x, max.size.y) : randomV2(min.size, max.size),
         randomFloat(min.scale, max.scale),
         randomFloat(min.rotation, max.rotation),
         randomFloat(min.rotationVelocity, max.rotationVelocity),
         randomFloat(min.friction, max.friction),
         randomFloat(min.lifetime, max.lifetime),
         (shouldSplit ? i % splitWidth : 0),
         (shouldSplit ? i / splitWidth : 0),
         splitWidth,
         splitHeight
      );
   }
}
