// rotator.h — checkpoint the active session and hand back the next slot.

#pragma once

#include "store.h"

namespace ccu {

class RotationEngine {
public:
    RotationEngine(SessionStore* store, const Settings& settings);

    void rotate();
    std::size_t cursor() const;

private:
    SessionStore* store_;
    Settings settings_;
    std::size_t cursor_;
};

}  // namespace ccu
