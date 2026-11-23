# FAQ

## Does this share accounts with other people?

No. Everything runs locally against your own setup. No pools, no invites,
nothing leaves your machine.

## Does it modify Claude Code itself?

No. `ccu` is a wrapper — the original CLI stays untouched and upgradable.
When a new Claude Code version drops, you update it the usual way.

## Where is my data stored?

`~/.config/ccu/` — plain JSON, readable, deletable, never uploaded.

## What happens if the wrapper crashes?

Your session is checkpointed on every rotation. Worst case you re-run `ccu`
and it picks up the last checkpoint.

## Windows / Linux / macOS?

Yes, yes and yes. If Node 18+ runs, `ccu` runs.

## Does it work with other wrappers?

It composes fine with anything that spawns `claude` as a child process.

## Found a bug?

Open an [issue](https://github.com/) with your platform, Node version, and
the relevant log lines from stderr.
