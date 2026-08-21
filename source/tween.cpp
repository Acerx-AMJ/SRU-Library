#include "SRU/error.hpp"
#include "SRU/tween.hpp"
#include "raymath.h"
#include <vector>

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
      int gen = tweens[ID.ID].generation;
      tweens[ID.ID] = tween;
      tweens[ID.ID].id = ID;
      tweens[ID.ID].generation = gen;
      return ID;
   }
}

// chain tweens
TweenID TweenID::chain(int *value, int target, float time, Formula formula) {
   TweenID tween = createTween(value, target, time, formula);
   tweens[tween.ID].started = false;
   tweens[tween.ID].root = (tweens[ID].root.isValid() ? tweens[ID].root : *this);
   tweens[ID].chained = tween;
   return tween;
}

TweenID TweenID::chain(float *value, float target, float time, Formula formula) {
   TweenID tween = createTween(value, target, time, formula);
   tweens[tween.ID].started = false;
   tweens[tween.ID].root = (tweens[ID].root.isValid() ? tweens[ID].root : *this);
   tweens[ID].chained = tween;
   return tween;
}

TweenID TweenID::chain(Vector2 *value, Vector2 target, float time, Formula formula) {
   TweenID tween = createTween(value, target, time, formula);
   tweens[tween.ID].started = false;
   tweens[tween.ID].root = (tweens[ID].root.isValid() ? tweens[ID].root : *this);
   tweens[ID].chained = tween;
   return tween;
}

TweenID TweenID::chain(Vector3 *value, Vector3 target, float time, Formula formula) {
   TweenID tween = createTween(value, target, time, formula);
   tweens[tween.ID].started = false;
   tweens[tween.ID].root = (tweens[ID].root.isValid() ? tweens[ID].root : *this);
   tweens[ID].chained = tween;
   return tween;
}

TweenID TweenID::chain(Vector4 *value, Vector4 target, float time, Formula formula) {
   TweenID tween = createTween(value, target, time, formula);
   tweens[tween.ID].started = false;
   tweens[tween.ID].root = (tweens[ID].root.isValid() ? tweens[ID].root : *this);
   tweens[ID].chained = tween;
   return tween;
}

TweenID TweenID::chain(Rectangle *value, Rectangle target, float time, Formula formula) {
   TweenID tween = createTween(value, target, time, formula);
   tweens[tween.ID].started = false;
   tweens[tween.ID].root = (tweens[ID].root.isValid() ? tweens[ID].root : *this);
   tweens[ID].chained = tween;
   return tween;
}

TweenID TweenID::chain(Color *value, Color target, float time, Formula formula) {
   TweenID tween = createTween(value, target, time, formula);
   tweens[tween.ID].started = false;
   tweens[tween.ID].root = (tweens[ID].root.isValid() ? tweens[ID].root : *this);
   tweens[ID].chained = tween;
   return tween;
}

// create parallel
TweenID TweenID::parallel(int *value, int target, float time, Formula formula) {
   TweenID tween = createTween(value, target, time, formula);
   tweens[tween.ID].started = false;
   tweens[tween.ID].root = (tweens[ID].root.isValid() ? tweens[ID].root : *this);
   tweens[ID].paralleled = tween;
   return tween;
}

TweenID TweenID::parallel(float *value, float target, float time, Formula formula) {
   TweenID tween = createTween(value, target, time, formula);
   tweens[tween.ID].started = false;
   tweens[tween.ID].root = (tweens[ID].root.isValid() ? tweens[ID].root : *this);
   tweens[ID].paralleled = tween;
   return tween;
}

TweenID TweenID::parallel(Vector2 *value, Vector2 target, float time, Formula formula) {
   TweenID tween = createTween(value, target, time, formula);
   tweens[tween.ID].started = false;
   tweens[tween.ID].root = (tweens[ID].root.isValid() ? tweens[ID].root : *this);
   tweens[ID].paralleled = tween;
   return tween;
}

TweenID TweenID::parallel(Vector3 *value, Vector3 target, float time, Formula formula) {
   TweenID tween = createTween(value, target, time, formula);
   tweens[tween.ID].started = false;
   tweens[tween.ID].root = (tweens[ID].root.isValid() ? tweens[ID].root : *this);
   tweens[ID].paralleled = tween;
   return tween;
}

TweenID TweenID::parallel(Vector4 *value, Vector4 target, float time, Formula formula) {
   TweenID tween = createTween(value, target, time, formula);
   tweens[tween.ID].started = false;
   tweens[tween.ID].root = (tweens[ID].root.isValid() ? tweens[ID].root : *this);
   tweens[ID].paralleled = tween;
   return tween;
}

TweenID TweenID::parallel(Rectangle *value, Rectangle target, float time, Formula formula) {
   TweenID tween = createTween(value, target, time, formula);
   tweens[tween.ID].started = false;
   tweens[tween.ID].root = (tweens[ID].root.isValid() ? tweens[ID].root : *this);
   tweens[ID].paralleled = tween;
   return tween;
}

TweenID TweenID::parallel(Color *value, Color target, float time, Formula formula) {
   TweenID tween = createTween(value, target, time, formula);
   tweens[tween.ID].started = false;
   tweens[tween.ID].root = (tweens[ID].root.isValid() ? tweens[ID].root : *this);
   tweens[ID].paralleled = tween;
   return tween;
}

// create tweens
TweenID createTween(int *value, int target, float time, Formula formula, TweenType type) {
   Tween tween {formula, 0, 0, 0, 0, TweenValue::integer, type, false, false, false, true, false, 0.0f, time, 0.0f};
   tween.ivalue = value;
   tween.istart = *value;
   tween.iend = target;
   return pushTween(tween);
}

TweenID createTween(float *value, float target, float time, Formula formula, TweenType type) {
   Tween tween {formula, 0, 0, 0, 0, TweenValue::floating, type, false, false, false, true, false, 0.0f, time, 0.0f};
   tween.fvalue = value;
   tween.fstart = *value;
   tween.fend = target;
   return pushTween(tween);
}

TweenID createTween(Vector2 *value, Vector2 target, float time, Formula formula, TweenType type) {
   Tween tween {formula, 0, 0, 0, 0, TweenValue::v2, type, false, false, false, true, false, 0.0f, time, 0.0f};
   tween.v2value = value;
   tween.v2start = *value;
   tween.v2end = target;
   return pushTween(tween);
}

TweenID createTween(Vector3 *value, Vector3 target, float time, Formula formula, TweenType type) {
   Tween tween {formula, 0, 0, 0, 0, TweenValue::v3, type, false, false, false, true, false, 0.0f, time, 0.0f};
   tween.v3value = value;
   tween.v3start = *value;
   tween.v3end = target;
   return pushTween(tween);
}

TweenID createTween(Vector4 *value, Vector4 target, float time, Formula formula, TweenType type) {
   Tween tween {formula, 0, 0, 0, 0, TweenValue::v4, type, false, false, false, true, false, 0.0f, time, 0.0f};
   tween.v4value = value;
   tween.v4start = *value;
   tween.v4end = target;
   return pushTween(tween);
}

TweenID createTween(Rectangle *value, Rectangle target, float time, Formula formula, TweenType type) {
   Tween tween {formula, 0, 0, 0, 0, TweenValue::r4, type, false, false, false, true, false, 0.0f, time, 0.0f};
   tween.r4value = value;
   tween.r4start = *value;
   tween.r4end = target;
   return pushTween(tween);
}

TweenID createTween(Color *value, Color target, float time, Formula formula, TweenType type) {
   Tween tween {formula, 0, 0, 0, 0, TweenValue::color, type, false, false, false, true, false, 0.0f, time, 0.0f};
   tween.cvalue = value;
   tween.cstart = *value;
   tween.cend = target;
   return pushTween(tween);
}

// private tween helpers
void updateTweenStartValues(TweenID ID) {
   if (!ID.isValid()) return;
   Tween &tween = ID.tween();

   switch (tween.value) {
   case TweenValue::integer:  tween.istart  = *tween.ivalue; break;
   case TweenValue::floating: tween.fstart  = *tween.fvalue; break;
   case TweenValue::v2:       tween.v2start = *tween.v2value; break;
   case TweenValue::v3:       tween.v3start = *tween.v3value; break;
   case TweenValue::v4:       tween.v4start = *tween.v4value; break;
   case TweenValue::r4:       tween.r4start = *tween.r4value; break;
   case TweenValue::color:    tween.cstart  = *tween.cvalue; break;
   default: break;
   }
}

void startTween(TweenID ID) {
   if (!ID.isValid()) return;
   Tween &tween = ID.tween();

   if (!tween.started && !tween.killed && !tween.finished) {
      tween.started = true;
      updateTweenStartValues(ID);
   }
}

void updateTween(TweenID ID, float DT) {
   if (!ID.isValid()) return;
   Tween &tween = ID.tween();
   startTween(tween.paralleled);
   updateTween(tween.paralleled, DT);

   if (tween.finished) {
      startTween(tween.chained);
      updateTween(tween.chained, DT);
   }

   if (!tween.started || tween.killed || tween.finished) return;
   tween.timer += DT;
   tween.progress = (tween.time == 0.0f ? 0.0f : Clamp(tween.timer / tween.time, 0.0f, 1.0f));

   float t = tween.formula(tween.progress);
   switch (tween.value) {
   case TweenValue::integer:  *tween.ivalue = Lerp(tween.istart, tween.iend, t); break;
   case TweenValue::floating: *tween.fvalue = Lerp(tween.fstart, tween.fend, t); break;
   case TweenValue::v2:       *tween.v2value = Vector2Lerp(tween.v2start, tween.v2end, t); break;
   case TweenValue::v3:       *tween.v3value = Vector3Lerp(tween.v3start, tween.v3end, t); break;
   case TweenValue::v4:       *tween.v4value = Vector4Lerp(tween.v4start, tween.v4end, t); break;
   case TweenValue::r4:       *tween.r4value = R4Lerp(tween.r4start, tween.r4end, t); break;
   case TweenValue::color:    *tween.cvalue = ColorLerp(tween.cstart, tween.cend, t); break;
   default: break;
   }

   if (tween.progress >= 1.0f) {
      tween.finished = true;
      startTween(tween.chained);
      updateTween(tween.chained, DT);
   }
}

bool isTweenFinished(TweenID ID) {
   if (!ID.isValid()) return true;
   Tween &tween = ID.tween();
   return tween.finished && isTweenFinished(tween.paralleled) && isTweenFinished(tween.chained);
}

void resetTween(TweenID ID) {
   if (!ID.isValid()) return;
   Tween &tween = ID.tween();

   resetTween(tween.chained);
   resetTween(tween.paralleled);
   tween.started = false;
   tween.finished = false;
   tween.timer = (tween.timer >= tween.time ? tween.timer - tween.time : 0.0f);
   tween.progress = 0.0f;
}

void killTween(TweenID ID) {
   if (!ID.isValid()) return;
   Tween &tween = ID.tween();

   killTween(tween.chained);
   killTween(tween.paralleled);
   tween.generation += 1;
   availableSpots.emplace_back(ID.ID, tween.generation);
   tween.id = 0;
   tween.killed = true;
}

void reverseTween(TweenID ID) {
   if (!ID.isValid()) return;
   Tween &tween = ID.tween();

   reverseTween(tween.chained);
   reverseTween(tween.paralleled);

   if (tween.started) {
      tween.progress = 1.0f - tween.progress;
      tween.timer = tween.progress * tween.time;
      tween.finished = (tween.progress >= 1.0f);
   }

   switch (tween.value) {
   case TweenValue::integer:  std::swap(tween.istart, tween.iend); break;
   case TweenValue::floating: std::swap(tween.fstart, tween.fend); break;
   case TweenValue::v2:       std::swap(tween.v2start, tween.v2end); break;
   case TweenValue::v3:       std::swap(tween.v3start, tween.v3end); break;
   case TweenValue::v4:       std::swap(tween.v4start, tween.v4end); break;
   case TweenValue::r4:       std::swap(tween.r4start, tween.r4end); break;
   case TweenValue::color:    std::swap(tween.cstart, tween.cend); break;
   default: break;
   }
}

// tweenid methods
void TweenID::stop() {
   root().stopped = true;
}

void TweenID::resume() {
   root().stopped = false;
}

void TweenID::toggleStopped() {
   Tween &r = root();
   r.stopped = !r.stopped;
}

void TweenID::restart() {
   Tween &r = root();
   if (r.killed) return;
   r.stopped = false;

   if (r.reversed) reverse();
   resetTween(r.id);
   startTween(r.id);
}

void TweenID::reverse() {
   Tween &r = root();
   if (r.killed) return;
   r.reversed = !r.reversed;
   reverseTween(r.id);
}

void TweenID::kill() {
   killTween(root().id);
}

bool TweenID::isStopped() {
   return !isValid() || root().stopped;
}

bool TweenID::isKilled() {
   return !isValid() || root().killed;
}

bool TweenID::isPlaying() {
   return !isFinished() && !isStopped() && !isKilled();
}

bool TweenID::isFinished() {
   return isTweenFinished(root().id);
}

bool TweenID::isReversed() {
   return isValid() && root().reversed;
}

bool TweenID::isValid() {
   return ID > 0 && ID < tweens.size() && generation == tweens[ID].generation;
}

bool TweenID::isRoot() {
   return isValid() && !tweens[ID].root.isValid();
}

Tween &TweenID::tween() {
   if (!isValid()) {
      SRULibWarning(TextFormat("srulib::TweenID::tween: tried to get tween from invalid ID %llu.\n", ID));
      return tweens[0];
   }
   return tweens[ID];
}

Tween &TweenID::root() {
   if (!isValid()) {
      SRULibWarning(TextFormat("srulib::TweenID::root: tried to get root from invalid ID %llu.\n", ID));
      return tweens[0];
   }
   Tween &tween = tweens[ID];
   return (!tween.root.isValid() ? tween : tweens[tween.root.ID]);
}

// update tweens
void updateTweens(float DT) {
   for (size_t ID = 1; ID < tweens.size(); ++ID) {
      Tween &tween = tweens[ID];

      // start updating from root tweens. since we cannot get the generation, we cannot go for
      // TweenID::tween/root. but we can just access the tween and then use that ID, that has
      // the right generation
      if (!tween.id.isValid() || tween.stopped || tween.killed || tween.root.isValid()) continue;
      updateTween(tween.id, DT);

      if (tween.type == TweenType::automatic && tween.id.isFinished()) {
         tween.id.kill();         
      }

      if (tween.type == TweenType::loop && tween.id.isFinished()) {
         tween.id.restart();
      }

      if (tween.type == TweenType::pingpong && tween.id.isFinished()) {
         tween.id.reverse();
      }
   }
}

void killAllTweens() {
   for (size_t ID = 1; ID < tweens.size(); ++ID) {
      Tween &tween = tweens[ID];
      if (tween.id.isValid() && !tween.killed && !tween.root.isValid()) {
         killTween(tween.id); // this is root
      }
   }
}

void killFinishedTweens() {
   for (size_t ID = 1; ID < tweens.size(); ++ID) {
      Tween &tween = tweens[ID];
      if (tween.id.isValid() && !tween.killed && tween.finished && !tween.root.isValid()) {
         killTween(tween.id); // this is root
      }
   }
}

size_t getTweenCount() {
   return tweens.size();
}

size_t getTweenFreeSpotCount() {
   return availableSpots.size();
}
