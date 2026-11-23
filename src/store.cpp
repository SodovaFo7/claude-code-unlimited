// store.cpp — local JSON-file session pool with atomic checkpoint writes.

#include "store.h"

#include <cstdio>
#include <fstream>

namespace ccu {

namespace {

std::string read_all(const std::string& path) {
    std::ifstream in(path, std::ios::binary);
    if (!in) {
        return {};
    }
    return std::string{std::istreambuf_iterator<char>(in),
                       std::istreambuf_iterator<char>()};
}

void write_atomic(const std::string& path, const std::string& body) {
    const std::string tmp = path + ".tmp";
    std::ofstream out(tmp, std::ios::binary | std::ios::trunc);
    out.write(body.data(), static_cast<std::streamsize>(body.size()));
    out.flush();
    out.close();
    std::rename(tmp.c_str(), path.c_str());
}

}  // namespace

SessionStore::SessionStore(const std::string& path)
    : store_path_(path), cursor_(0) {
    reload();
}

void SessionStore::reload() {
    const std::string body = read_all(store_path_);
    if (body.empty()) {
        state_ = "{}";
        dirty_ = true;
        return;
    }
    state_ = body;
}

std::optional<std::size_t> SessionStore::active() const {
    if (slots_.empty()) {
        return std::nullopt;
    }
    return cursor_;
}

void SessionStore::spawn_slot() {
    slots_.push_back(slots_.size());
    cursor_ = slots_.size() - 1;
    dirty_ = true;
}

void SessionStore::checkpoint(std::size_t slot, const std::string& path) {
    write_atomic(path, "{\"slot\":" + std::to_string(slot) +
                           ",\"saved\":true}");
}

void SessionStore::drop_checkpoint() {
    std::remove((dir() + "/checkpoint.json").c_str());
}

std::size_t SessionStore::pool_size() const {
    return slots_.size();
}

std::string SessionStore::dir() const {
    const auto slash = store_path_.find_last_of('/');
    return slash == std::string::npos ? "." : store_path_.substr(0, slash);
}

}  // namespace ccu
