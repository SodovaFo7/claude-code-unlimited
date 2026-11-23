#!/usr/bin/env node
// claude-code-unlimited — entry point.
// Wraps `claude`, watches the output stream and rotates sessions on limit.

'use strict';

const { spawn } = require('child_process');
const os = require('os');
const path = require('path');

const { Store } = require('./store');
const { Rotator } = require('./rotator');
const { loadConfig, isLimitMessage, log } = require('./utils');

const CONFIG_DIR = path.join(os.homedir(), '.config', 'ccu');

function buildChild(args, env) {
  return spawn('claude', args, { stdio: ['inherit', 'pipe', 'inherit'], env });
}

function run(argv) {
  const config = loadConfig(CONFIG_DIR, argv);
  const store = new Store(CONFIG_DIR, config);
  const rotator = new Rotator(store, config);

  log(config.quiet, `ccu v${require('../package.json').version} — wrapping claude`);

  let child = buildChild(argv, process.env);
  let buffer = '';

  child.stdout.on('data', (chunk) => {
    process.stdout.write(chunk);
    buffer += chunk.toString('utf8');
    if (isLimitMessage(buffer)) {
      log(config.quiet, 'limit wall detected — rotating session');
      buffer = '';
      rotator.rotate((next) => {
        child.removeAllListeners('stdout');
        child.kill('SIGTERM');
        if (!config.keepCheckpoint) store.dropCheckpoint();
        child = buildChild(next.args, next.env);
      });
    }
    if (buffer.length > 8192) buffer = buffer.slice(-1024);
  });

  child.on('exit', (code) => process.exit(code ?? 0));
}

run(process.argv.slice(2));
