// store.h — local JSON-file session pool with atomic checkpoint writes.

#pragma once

#include <optional>
#include <string>
#include <vector>

namespace ccu {

class SessionStore {
public:
    explicit SessionStore(const std::string& path);

    void reload();
    std::optional<std::size_t> active() const;
    void spawn_slot();
    void checkpoint(std::size_t slot, const std::string& path);
    void drop_checkpoint();
    std::size_t pool_size() const;
    std::string dir() const;

private:
    std::string store_path_;
    std::string state_;
    std::vector<std::size_t> slots_;
    std::size_t cursor_;
    bool dirty_{false};
};

}  // namespace ccu
