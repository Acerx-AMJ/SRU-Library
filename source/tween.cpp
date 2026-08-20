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
      tweens[ID] = tween;
      tweens[ID].id = ID;
      return ID;
   }
}

// chain tweens
TweenID TweenID::chain(int *value, int target, float time, Formula formula) {
   TweenID tween = createTween(value, target, time, formula);
   tweens[tween].started = false;
   tweens[tween].root = (tweens[ID].root.valid() ? tweens[ID].root : *this);
   tweens[ID].chained = tween;
   return tween;
}

TweenID TweenID::chain(float *value, float target, float time, Formula formula) {
   TweenID tween = createTween(value, target, time, formula);
   tweens[tween].started = false;
   tweens[tween].root = (tweens[ID].root.valid() ? tweens[ID].root : *this);
   tweens[ID].chained = tween;
   return tween;
}

TweenID TweenID::chain(Vector2 *value, Vector2 target, float time, Formula formula) {
   TweenID tween = createTween(value, target, time, formula);
   tweens[tween].started = false;
   tweens[tween].root = (tweens[ID].root.valid() ? tweens[ID].root : *this);
   tweens[ID].chained = tween;
   return tween;
}

TweenID TweenID::chain(Vector3 *value, Vector3 target, float time, Formula formula) {
   TweenID tween = createTween(value, target, time, formula);
   tweens[tween].started = false;
   tweens[tween].root = (tweens[ID].root.valid() ? tweens[ID].root : *this);
   tweens[ID].chained = tween;
   return tween;
}

TweenID TweenID::chain(Vector4 *value, Vector4 target, float time, Formula formula) {
   TweenID tween = createTween(value, target, time, formula);
   tweens[tween].started = false;
   tweens[tween].root = (tweens[ID].root.valid() ? tweens[ID].root : *this);
   tweens[ID].chained = tween;
   return tween;
}

TweenID TweenID::chain(Rectangle *value, Rectangle target, float time, Formula formula) {
   TweenID tween = createTween(value, target, time, formula);
   tweens[tween].started = false;
   tweens[tween].root = (tweens[ID].root.valid() ? tweens[ID].root : *this);
   tweens[ID].chained = tween;
   return tween;
}

TweenID TweenID::chain(Color *value, Color target, float time, Formula formula) {
   TweenID tween = createTween(value, target, time, formula);
   tweens[tween].started = false;
   tweens[tween].root = (tweens[ID].root.valid() ? tweens[ID].root : *this);
   tweens[ID].chained = tween;
   return tween;
}

// create parallel
TweenID TweenID::parallel(int *value, int target, float time, Formula formula) {
   TweenID tween = createTween(value, target, time, formula);
   tweens[tween].started = false;
   tweens[tween].root = (tweens[ID].root.valid() ? tweens[ID].root : *this);
   tweens[ID].paralleled = tween;
   return tween;
}

TweenID TweenID::parallel(float *value, float target, float time, Formula formula) {
   TweenID tween = createTween(value, target, time, formula);
   tweens[tween].started = false;
   tweens[tween].root = (tweens[ID].root.valid() ? tweens[ID].root : *this);
   tweens[ID].paralleled = tween;
   return tween;
}

TweenID TweenID::parallel(Vector2 *value, Vector2 target, float time, Formula formula) {
   TweenID tween = createTween(value, target, time, formula);
   tweens[tween].started = false;
   tweens[tween].root = (tweens[ID].root.valid() ? tweens[ID].root : *this);
   tweens[ID].paralleled = tween;
   return tween;
}

TweenID TweenID::parallel(Vector3 *value, Vector3 target, float time, Formula formula) {
   TweenID tween = createTween(value, target, time, formula);
   tweens[tween].started = false;
   tweens[tween].root = (tweens[ID].root.valid() ? tweens[ID].root : *this);
   tweens[ID].paralleled = tween;
   return tween;
}

TweenID TweenID::parallel(Vector4 *value, Vector4 target, float time, Formula formula) {
   TweenID tween = createTween(value, target, time, formula);
   tweens[tween].started = false;
   tweens[tween].root = (tweens[ID].root.valid() ? tweens[ID].root : *this);
   tweens[ID].paralleled = tween;
   return tween;
}

TweenID TweenID::parallel(Rectangle *value, Rectangle target, float time, Formula formula) {
   TweenID tween = createTween(value, target, time, formula);
   tweens[tween].started = false;
   tweens[tween].root = (tweens[ID].root.valid() ? tweens[ID].root : *this);
   tweens[ID].paralleled = tween;
   return tween;
}

TweenID TweenID::parallel(Color *value, Color target, float time, Formula formula) {
   TweenID tween = createTween(value, target, time, formula);
   tweens[tween].started = false;
   tweens[tween].root = (tweens[ID].root.valid() ? tweens[ID].root : *this);
   tweens[ID].paralleled = tween;
   return tween;
}

// create tweens
TweenID createTween(int *value, int target, float time, Formula formula, TweenType type) {
   Tween tween {formula, 0, 0, 0, 0, TweenValue::integer, type, false, false, true, false, 0.0f, time, 0.0f};
   tween.ivalue = value;
   tween.istart = *value;
   tween.iend = target;
   return pushTween(tween);
}

TweenID createTween(float *value, float target, float time, Formula formula, TweenType type) {
   Tween tween {formula, 0, 0, 0, 0, TweenValue::floating, type, false, false, true, false, 0.0f, time, 0.0f};
   tween.fvalue = value;
   tween.fstart = *value;
   tween.fend = target;
   return pushTween(tween);
}

TweenID createTween(Vector2 *value, Vector2 target, float time, Formula formula, TweenType type) {
   Tween tween {formula, 0, 0, 0, 0, TweenValue::v2, type, false, false, true, false, 0.0f, time, 0.0f};
   tween.v2value = value;
   tween.v2start = *value;
   tween.v2end = target;
   return pushTween(tween);
}

TweenID createTween(Vector3 *value, Vector3 target, float time, Formula formula, TweenType type) {
   Tween tween {formula, 0, 0, 0, 0, TweenValue::v3, type, false, false, true, false, 0.0f, time, 0.0f};
   tween.v3value = value;
   tween.v3start = *value;
   tween.v3end = target;
   return pushTween(tween);
}

TweenID createTween(Vector4 *value, Vector4 target, float time, Formula formula, TweenType type) {
   Tween tween {formula, 0, 0, 0, 0, TweenValue::v4, type, false, false, true, false, 0.0f, time, 0.0f};
   tween.v4value = value;
   tween.v4start = *value;
   tween.v4end = target;
   return pushTween(tween);
}

TweenID createTween(Rectangle *value, Rectangle target, float time, Formula formula, TweenType type) {
   Tween tween {formula, 0, 0, 0, 0, TweenValue::r4, type, false, false, true, false, 0.0f, time, 0.0f};
   tween.r4value = value;
   tween.r4start = *value;
   tween.r4end = target;
   return pushTween(tween);
}

TweenID createTween(Color *value, Color target, float time, Formula formula, TweenType type) {
   Tween tween {formula, 0, 0, 0, 0, TweenValue::color, type, false, false, true, false, 0.0f, time, 0.0f};
   tween.cvalue = value;
   tween.cstart = *value;
   tween.cend = target;
   return pushTween(tween);
}

// private tween helpers
void updateTweenStartValues(TweenID ID) {
   if (!ID.valid()) return;
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
   if (!ID.valid()) return;
   Tween &tween = ID.tween();

   if (!tween.started && !tween.killed && !tween.finished) {
      tween.started = true;
      updateTweenStartValues(ID);
   }
}

void updateTween(TweenID ID, float DT) {
   if (!ID.valid()) return;
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
   if (!ID.valid()) return true;
   Tween &tween = ID.tween();
   return tween.finished && isTweenFinished(tween.paralleled) && isTweenFinished(tween.chained);
}

void resetTween(TweenID ID) {
   if (!ID.valid()) return;
   Tween &tween = ID.tween();

   resetTween(tween.chained);
   resetTween(tween.paralleled);
   tween.started = false;
   tween.finished = false;
   tween.timer = (tween.timer >= tween.time ? tween.timer - tween.time : 0.0f);
   tween.progress = 0.0f;
}

void killTween(TweenID ID) {
   if (!ID.valid()) return;
   Tween &tween = ID.tween();

   killTween(tween.chained);
   killTween(tween.paralleled);
   availableSpots.push_back(ID);
   tween.id = 0;
   tween.killed = true;
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
   resetTween(r.id);
   startTween(r.id);
}

void TweenID::kill() {
   killTween(root().id);
}

bool TweenID::stopped() {
   return root().stopped;
}

bool TweenID::killed() {
   return root().killed;
}

bool TweenID::playing() {
   return !finished() && !stopped() && !killed();
}

bool TweenID::finished() {
   return isTweenFinished(root().id);
}

bool TweenID::valid() {
   return ID > 0 && ID < tweens.size();
}

bool TweenID::isRoot() {
   return valid() && !tweens[ID].root.valid();
}

Tween &TweenID::tween() {
   if (!valid()) {
      SRULibWarning(TextFormat("srulib::TweenID::tween: tried to get tween from invalid ID %llu.\n", ID));
      return tweens[0];
   }
   return tweens[ID];
}

Tween &TweenID::root() {
   if (!valid()) {
      SRULibWarning(TextFormat("srulib::TweenID::root: tried to get root from invalid ID %llu.\n", ID));
      return tweens[0];
   }
   Tween &tween = tweens[ID];
   return (!tween.root.valid() ? tween : tweens[tween.root]);
}

// update tweens
void updateTweens(float DT) {
   for (TweenID ID = 1; ID < tweens.size(); ++ID) {
      Tween &tween = ID.tween();

      // start updating from root tweens
      if (!tween.id.valid() || tween.stopped || tween.killed || tween.root.valid()) continue;
      updateTween(ID, DT);

      // automatic cleanup
      if (tween.type == TweenType::automatic && ID.finished()) {
         ID.kill();         
      }

      // looping tween
      if (tween.type == TweenType::loop && ID.finished()) {
         ID.restart();
      }
   }
}

void killAllTweens() {
   for (TweenID ID = 1; ID < tweens.size(); ++ID) {
      Tween &tween = ID.tween();
      if (tween.id.valid() && !tween.killed && !tween.root.valid()) ID.kill();
   }
}

size_t getTweenCount() {
   return tweens.size();
}

size_t getTweenFreeSpotCount() {
   return availableSpots.size();
}
