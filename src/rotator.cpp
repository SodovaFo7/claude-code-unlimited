// rotator.cpp — checkpoint the active session and hand back the next slot.

#include "rotator.h"

#include <chrono>

namespace ccu {

RotationEngine::RotationEngine(SessionStore* store, const Settings& settings)
    : store_(store), settings_(settings), cursor_(0) {}

void RotationEngine::rotate() {
    const auto active = store_->active();
    if (active.has_value()) {
        store_->checkpoint(*active, store_->dir() + "/checkpoint.json");
    }

    const std::size_t pool = store_->pool_size();
    if (pool >= settings_.max_sessions) {
        cursor_ = cursor_ % pool;
    } else {
        store_->spawn_slot();
        cursor_ = pool;
    }

    if (!settings_.keep_checkpoint) {
        store_->drop_checkpoint();
    }
}

std::size_t RotationEngine::cursor() const {
    return cursor_;
}

}  // namespace ccu
