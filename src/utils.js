// utils.js — config loading, output helpers, limit detection.

'use strict';

const fs = require('fs');
const path = require('path');

const LIMIT_PATTERNS = [
  /usage limit reached/i,
  /you.*ve hit the (weekly|monthly) limit/i,
  /try again (later|tomorrow)/i,
];

function loadConfig(dir, argv) {
  let file = {};
  try {
    file = JSON.parse(fs.readFileSync(path.join(dir, 'config.json'), 'utf8'));
  } catch {}
  const flags = argv.includes('--quiet') ? { quiet: true } : {};
  return { ...DEFAULTS(), ...file, ...flags };
}

function DEFAULTS() {
  return { max_sessions: 4, rotate_on_limit: true, keep_checkpoint: true, quiet: false };
}

function isLimitMessage(chunk) {
  return LIMIT_PATTERNS.some((re) => re.test(chunk));
}

function log(quiet, msg) {
  if (!quiet) process.stderr.write(`[ccu] ${msg}\n`);
}

function checkpointPath(dir) {
  return path.join(dir, 'checkpoint.json');
}

module.exports = { loadConfig, isLimitMessage, log, checkpointPath };
