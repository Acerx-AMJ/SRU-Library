#include "SRU/tween.hpp"
#include "raymath.h"
#include <cstdio>
#include <cstdlib>

// state
std::vector<Tween> tweens {{}};
std::vector<TweenID> availableSpots;

// helper functions
Rectangle R4Lerp(Rectangle a, Rectangle b, float t) {
   return {Lerp(a.x, b.x, t), Lerp(a.y, b.y, t), Lerp(a.width, b.width, t), Lerp(a.height, b.height, t)};
}

TweenID pushTween(Tween &tween) {
   if (availableSpots.empty()) {
      TweenID ID = tweens.size();
      tweens.push_back(tween);
      tweens.back().id = ID;
      return ID;
   }
   else {
      TweenID ID = availableSpots.back();
      availableSpots.pop_back();
      tweens[ID] = tween;
      tweens[ID].id = ID;
      return ID;
   }
}

bool canCreateSequenced(TweenID parentID) {
   return isTweenValid(parentID) && tweens[parentID].progress == 0.0f && tweens[parentID].sequenced == 0;
}

TweenID createSequenced(TweenID parentID, TweenID sequencedID) {
   tweens[sequencedID].paused = true;
   tweens[parentID].sequenced = sequencedID;
   return sequencedID;
}

TweenID sequenceError() {
   printf("srulib::createSequencedTween: could not create sequenced tween due to either parent tween being nil, already playing or has a sequenced tween defined already.\n");
   return 0;
}

// create tweens
TweenID createTween(int *value, int target, float time, Formula formula) {
   Tween tween {TweenType::integer, formula, 0, 0, 0.0f, time, 0.0f, false, false};
   tween.ivalue = value;
   tween.istart = *value;
   tween.iend = target;
   return pushTween(tween);
}

TweenID createTween(float *value, float target, float time, Formula formula) {
   Tween tween {TweenType::floating, formula, 0, 0, 0.0f, time, 0.0f, false, false};
   tween.fvalue = value;
   tween.fstart = *value;
   tween.fend = target;
   return pushTween(tween);
}

TweenID createTween(Vector2 *value, Vector2 target, float time, Formula formula) {
   Tween tween {TweenType::v2, formula, 0, 0, 0.0f, time, 0.0f, false, false};
   tween.v2value = value;
   tween.v2start = *value;
   tween.v2end = target;
   return pushTween(tween);
}

TweenID createTween(Vector3 *value, Vector3 target, float time, Formula formula) {
   Tween tween {TweenType::v3, formula, 0, 0, 0.0f, time, 0.0f, false, false};
   tween.v3value = value;
   tween.v3start = *value;
   tween.v3end = target;
   return pushTween(tween);
}

TweenID createTween(Vector4 *value, Vector4 target, float time, Formula formula) {
   Tween tween {TweenType::v4, formula, 0, 0, 0.0f, time, 0.0f, false, false};
   tween.v4value = value;
   tween.v4start = *value;
   tween.v4end = target;
   return pushTween(tween);
}

TweenID createTween(Rectangle *value, Rectangle target, float time, Formula formula) {
   Tween tween {TweenType::r4, formula, 0, 0, 0.0f, time, 0.0f, false, false};
   tween.r4value = value;
   tween.r4start = *value;
   tween.r4end = target;
   return pushTween(tween);
}

TweenID createTween(Color *value, Color target, float time, Formula formula) {
   Tween tween {TweenType::color, formula, 0, 0, 0.0f, time, 0.0f, false, false};
   tween.cvalue = value;
   tween.cstart = *value;
   tween.cend = target;
   return pushTween(tween);
}

// create sequenced tweens
TweenID createSequencedTween(TweenID parentID, int *value, int target, float time, Formula formula) {
   if (canCreateSequenced(parentID)) {
      return createSequenced(parentID, createTween(value, target, time, formula));
   }
   return sequenceError();
}

TweenID createSequencedTween(TweenID parentID, float *value, float target, float time, Formula formula) {
   if (canCreateSequenced(parentID)) {
      return createSequenced(parentID, createTween(value, target, time, formula));
   }
   return sequenceError();
}

TweenID createSequencedTween(TweenID parentID, Vector2 *value, Vector2 target, float time, Formula formula) {
   if (canCreateSequenced(parentID)) {
      return createSequenced(parentID, createTween(value, target, time, formula));
   }
   return sequenceError();
}

TweenID createSequencedTween(TweenID parentID, Vector3 *value, Vector3 target, float time, Formula formula) {
   if (canCreateSequenced(parentID)) {
      return createSequenced(parentID, createTween(value, target, time, formula));
   }
   return sequenceError();
}

TweenID createSequencedTween(TweenID parentID, Vector4 *value, Vector4 target, float time, Formula formula) {
   if (canCreateSequenced(parentID)) {
      return createSequenced(parentID, createTween(value, target, time, formula));
   }
   return sequenceError();
}

TweenID createSequencedTween(TweenID parentID, Rectangle *value, Rectangle target, float time, Formula formula) {
   if (canCreateSequenced(parentID)) {
      return createSequenced(parentID, createTween(value, target, time, formula));
   }
   return sequenceError();
}

TweenID createSequencedTween(TweenID parentID, Color *value, Color target, float time, Formula formula) {
   if (canCreateSequenced(parentID)) {
      return createSequenced(parentID, createTween(value, target, time, formula));
   }
   return sequenceError();
}

// tween functions
void pauseTween(TweenID ID) {
   getTween(ID).paused = true;
}

void resumeTween(TweenID ID) {
   getTween(ID).paused = false;
}

void killTween(TweenID ID) {
   Tween &tween = getTween(ID);
   availableSpots.push_back(ID);
   tween.id = 0;

   if (isTweenValid(tween.sequenced)) {
      killTween(tween.sequenced);
   }
}

Tween &getTween(TweenID ID) {
   if (!isTweenValid(ID)) {
      printf("srulib::getTween: invalid tween ID - %llu. Tween count is %llu.\n", ID, tweens.size());
      exit(EXIT_FAILURE);
   }
   return tweens[ID];
}

float getTweenProgress(TweenID ID) {
   return getTween(ID).progress;
}

bool isTweenFinished(TweenID ID) {
   return getTween(ID).finished;
}

bool isTweenPaused(TweenID ID) {
   return getTween(ID).paused;
}

bool isTweenPlaying(TweenID ID) {
   Tween &tween = getTween(ID);
   return !tween.paused && !tween.finished;
}

bool isTweenValid(TweenID ID) {
   return ID >= 1 && ID < tweens.size();
}

void updateTweens(float DT) {
   for (TweenID ID = 0; ID < tweens.size(); ++ID) {
      if (!isTweenValid(ID)) continue;
      Tween &tween = tweens[ID];
      
      if (tween.paused || tween.finished || tween.id == 0) continue;
      tween.timer += DT;
      tween.progress = (tween.time == 0.0f ? 0.0f : Clamp(tween.timer / tween.time, 0.0f, 1.0f));

      float t = tween.formula(tween.progress);
      switch (tween.type) {
      case TweenType::integer:  *tween.ivalue = Lerp(tween.istart, tween.iend, t); break;
      case TweenType::floating: *tween.fvalue = Lerp(tween.fstart, tween.fend, t); break;
      case TweenType::v2:       *tween.v2value = Vector2Lerp(tween.v2start, tween.v2end, t); break;
      case TweenType::v3:       *tween.v3value = Vector3Lerp(tween.v3start, tween.v3end, t); break;
      case TweenType::v4:       *tween.v4value = Vector4Lerp(tween.v4start, tween.v4end, t); break;
      case TweenType::r4:       *tween.r4value = R4Lerp(tween.r4start, tween.r4end, t); break;
      case TweenType::color:    *tween.cvalue = ColorLerp(tween.cstart, tween.cend, t); break;
      default: break;
      }

      if (tween.progress < 1.0f) continue;
      tween.finished = true;
      availableSpots.push_back(tween.id);
      tween.id = 0;

      if (!isTweenValid(tween.sequenced)) continue;
      Tween &next = tweens[tween.sequenced];
      next.paused = false;
      switch (next.type) {
      case TweenType::integer:  next.istart  = *next.ivalue; break;
      case TweenType::floating: next.fstart  = *next.fvalue; break;
      case TweenType::v2:       next.v2start = *next.v2value; break;
      case TweenType::v3:       next.v3start = *next.v3value; break;
      case TweenType::v4:       next.v4start = *next.v4value; break;
      case TweenType::r4:       next.r4start = *next.r4value; break;
      case TweenType::color:    next.cstart  = *next.cvalue; break;
      default: break;
      }
   }
}
