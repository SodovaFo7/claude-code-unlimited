// store.js — tiny local JSON store for sessions and checkpoints.

'use strict';

const fs = require('fs');
const path = require('path');

const DEFAULTS = { max_sessions: 4, rotate_on_limit: true, keep_checkpoint: true, quiet: false };

class Store {
  constructor(dir, config) {
    this.dir = dir;
    this.config = config;
    this.file = path.join(dir, 'state.json');
    fs.mkdirSync(dir, { recursive: true });
  }

  read() {
    try {
      return JSON.parse(fs.readFileSync(this.file, 'utf8'));
    } catch {
      return { sessions: [], active: 0 };
    }
  }

  write(state) {
    fs.writeFileSync(this.file, JSON.stringify(state, null, 2));
  }

  pool() {
    return this.read().sessions;
  }

  at(i) {
    return this.pool()[i] ?? null;
  }

  active() {
    const s = this.read();
    return this.at(s.active) ?? null;
  }

  spawn() {
    const s = this.read();
    s.sessions.push({ id: s.sessions.length, created: new Date().toISOString() });
    s.active = s.sessions.length - 1;
    this.write(s);
  }

  checkpoint(session, target) {
    if (!session) return;
    fs.writeFileSync(target, JSON.stringify({ ...session, at: Date.now() }));
  }

  dropCheckpoint() {
    try { fs.unlinkSync(path.join(this.dir, 'checkpoint.json')); } catch {}
  }
}

module.exports = { Store, DEFAULTS };
