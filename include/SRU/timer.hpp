#pragma once
#include <cmath>
#include <thread>

inline bool wait(float seconds) {
   std::this_thread::sleep_for(std::chrono::duration<float>(seconds));
   return true;
}

struct Timer {
   Timer() = default;
   Timer(float duration)
      : duration(duration) {}

   void update(float dt) {
      if (!paused) {
         timer += dt;
      }
   }

   void reset() {
      timer = 0.0f;
   }

   bool isDone() const {
      return timer >= duration;
   }

   float progress() const {
      return fminf(timer / duration, 1.0f);
   }

   float duration = 0.0f;
   float timer = 0.0f;
   bool paused = false;
};

struct BasicTimer {
   BasicTimer() = default;
   BasicTimer(float duration)
      : timer(duration) {}
   
   void update(float dt) {
      timer -= dt;
   }

   bool isDone() const {
      return timer <= 0.0f;
   }

   float timer = 0.0f;
};

struct Interval {
   Interval() = default;
   Interval(float duration)
      : duration(duration) {}
   
   bool tick(float dt) {
      if (paused) return false;
      
      timer += dt;
      if (timer >= duration) {
         timer -= duration;
         return true;
      }
      return false;
   }

   float duration = 0.0f;
   float timer = 0.0f;
   bool paused = false;
};
