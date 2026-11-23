// rotator.js — checkpoint the current session and start a fresh one.

'use strict';

const { checkpointPath } = require('./utils');

class Rotator {
  constructor(store, config) {
    this.store = store;
    this.config = config;
    this.index = 0;
  }

  /** Detect the active session, checkpoint it, and hand back the next one. */
  rotate(done) {
    const active = this.store.active();
    this.store.checkpoint(active, checkpointPath(this.store.dir));

    const pool = this.store.pool();
    if (pool.length >= this.config.max_sessions) {
      // recycle the oldest slot instead of growing forever
      this.index = this.index % pool.length;
    } else {
      this.store.spawn();
      this.index = pool.length;
    }

    const next = this.store.at(this.index);
    done({ args: next.args, env: next.env() });
  }

  /** Manual rotation (used by `ccu rotate`). */
  manual() {
    return this.rotate(() => {});
  }
}

module.exports = { Rotator };
