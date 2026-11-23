# Usage

## Wrap a session

```bash
ccu
```

Any flags you normally pass to `claude` go through untouched:

```bash
ccu --dangerously-skip-permissions
ccu -p "explain this repo"
```

## Manual rotation

```bash
ccu rotate
```

Checkpoints the current session and moves to the next slot in the pool.

## Inspect the pool

```bash
ccu status
```

Prints the local session pool, the active slot, and the checkpoint age.

## Reset everything

```bash
ccu reset
```

Drops checkpoints and rebuilds the pool from scratch. Your `~/.config/ccu/config.json` is kept.

## Configuration

See the [README](../README.md#configuration) for the full list of options.
Everything lives in `~/.config/ccu/config.json`.
