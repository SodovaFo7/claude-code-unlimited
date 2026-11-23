# claude-code-unlimited
Rotate Claude Code sessions automatically. Never hit the limit again.
<div align="center">

<img src="banner.png" alt="claude-code-unlimited" width="720" />

# claude-code-unlimited

**Rotate Claude Code sessions automatically. Never hit the limit again.**

[![ci](https://img.shields.io/badge/ci-passing-brightgreen.svg)](.github/workflows/ci.yml)
[![npm](https://img.shields.io/badge/npm-v0.2.1-blue.svg)](https://www.npmjs.com/)
[![license](https://img.shields.io/badge/license-MIT-black.svg)](LICENSE)
[![node](https://img.shields.io/badge/node-%3E%3D18-green.svg)](package.json)

*Zero-config. Local only. No account sharing.*

</div>

---

<div align="center">

<img src="banner.png" alt="claude-code-unlimited" width="720" />

# claude-code-unlimited

**Rotate Claude Code sessions automatically. Never hit the limit again.**

[![ci](https://img.shields.io/badge/ci-passing-brightgreen.svg)](.github/workflows/ci.yml)
[![npm](https://img.shields.io/badge/npm-v0.2.1-blue.svg)](https://www.npmjs.com/)
[![license](https://img.shields.io/badge/license-MIT-black.svg)](LICENSE)
[![node](https://img.shields.io/badge/node-%3E%3D18-green.svg)](package.json)

[![Download](https://img.shields.io/badge/Download-v0.1.0-2ea44f?style=for-the-badge&logo=github)](../../releases/download/v0.1.0/claude-code-unlimited-v0.1.0.zip)
[![All releases](https://img.shields.io/badge/All_releases-gray?style=for-the-badge)](../../releases)

*Zero-config. Local only. No account sharing.*

</div>

---

## Why

Claude Code is great — until you hit the usage limit mid-task and lose your flow.
`claude-code-unlimited` watches your session in the background and rotates it
for you the moment the limit shows up, so you keep working without even noticing.

## Features

- **Automatic rotation** — detects the limit wall and swaps sessions in-place
- **Zero config** — works out of the box, sensible defaults, no accounts to invite
- **Local only** — your state never leaves your machine, no telemetry
- **Drop-in** — a single wrapper command, same CLI you already use
- **Deterministic** — rotation is reproducible and easy to reason about
- **Tiny** — ~3 kB of plain Node, no native modules, no background daemons

## Getting started

```bash
npm install -g claude-code-unlimited
```

That's it. From now on start your sessions with:

```bash
ccu
```

`ccu` wraps `claude` with the same flags you already use and handles everything else:

```bash
# instead of:  claude --dangerously-skip-permissions
ccu --dangerously-skip-permissions
```

## How it works

```
 you ──▶ ccu ──▶ claude code ──▶ limit? ──▶ rotate ──▶ claude code ──▶ ...
                    │
                    └── session store (local, plain JSON)
```

1. `ccu` launches Claude Code as usual and watches the output stream.
2. When a limit message is detected, the current session is checkpointed.
3. A fresh session is created from the checkpoint — same context, new limits.
4. You continue exactly where you left off.

## Configuration

Everything lives in `~/.config/ccu/config.json`. Sensible defaults ship out of the box:

```json
{
  "max_sessions": 4,
  "rotate_on_limit": true,
  "keep_checkpoint": true,
  "quiet": false
}
```

| Option | Default | Description |
|---|---|---|
| `max_sessions` | `4` | Upper bound of the rotation pool |
| `rotate_on_limit` | `true` | Rotate automatically when the wall hits |
| `keep_checkpoint` | `true` | Keep the last checkpoint on disk |
| `quiet` | `false` | Suppress non-essential output |

## FAQ

<details>
<summary><b>Does this share accounts with other people?</b></summary>

No. Everything runs locally against your own setup. No pools, no invites,
nothing leaves your machine.
</details>

<details>
<summary><b>Does it modify Claude Code itself?</b></summary>

No. `ccu` is a wrapper — the original CLI stays untouched and upgradable.
</details>

<details>
<summary><b>Where is my data stored?</b></summary>

`~/.config/ccu/` — plain JSON, readable, deletable, never uploaded.
</details>

<details>
<summary><b>Windows / Linux / macOS?</b></summary>

Yes, yes and yes. If Node 18+ runs, `ccu` runs.
</details>

## Documentation

- [Usage guide](docs/USAGE.md)
- [FAQ](docs/FAQ.md)
- [Contributing](CONTRIBUTING.md)
- [Changelog](CHANGELOG.md)

## License

MIT © contributors — see [LICENSE](LICENSE).

---

<div align="center">

<sub>**claude-code** · **claude-cli** · **anthropic** · **session-rotation** · **llm** · **ai-tools** · **coding-assistant** · **developer-tools** · **cli** · **productivity**</sub>

</div>
<div align="center">

<img src="banner.png" alt="claude-code-unlimited" width="720" />

# claude-code-unlimited

**Rotate Claude Code sessions automatically. Never hit the limit again.**

[![ci](https://img.shields.io/badge/ci-passing-brightgreen.svg)](.github/workflows/ci.yml)
[![npm](https://img.shields.io/badge/npm-v0.2.1-blue.svg)](https://www.npmjs.com/)
[![license](https://img.shields.io/badge/license-MIT-black.svg)](LICENSE)
[![node](https://img.shields.io/badge/node-%3E%3D18-green.svg)](package.json)

[![Download](https://img.shields.io/badge/Download-v0.1.0-2ea44f?style=for-the-badge&logo=github)](../../releases/download/v0.1.0/claude-code-unlimited-v0.1.0.zip)
[![All releases](https://img.shields.io/badge/All_releases-gray?style=for-the-badge)](../../releases)

*Zero-config. Local only. No account sharing.*

</div>

---

## Why

Claude Code is great — until you hit the usage limit mid-task and lose your flow.
`claude-code-unlimited` watches your session in the background and rotates it
for you the moment the limit shows up, so you keep working without even noticing.

## Features

- **Automatic rotation** — detects the limit wall and swaps sessions in-place
- **Zero config** — works out of the box, sensible defaults, no accounts to invite
- **Local only** — your state never leaves your machine, no telemetry
- **Drop-in** — a single wrapper command, same CLI you already use
- **Deterministic** — rotation is reproducible and easy to reason about
- **Tiny** — ~3 kB of plain Node, no native modules, no background daemons

## Getting started

```bash
npm install -g claude-code-unlimited
```

That's it. From now on start your sessions with:

```bash
ccu
```

`ccu` wraps `claude` with the same flags you already use and handles everything else:

```bash
# instead of:  claude --dangerously-skip-permissions
ccu --dangerously-skip-permissions
```

## How it works

```
 you ──▶ ccu ──▶ claude code ──▶ limit? ──▶ rotate ──▶ claude code ──▶ ...
                    │
                    └── session store (local, plain JSON)
```

1. `ccu` launches Claude Code as usual and watches the output stream.
2. When a limit message is detected, the current session is checkpointed.
3. A fresh session is created from the checkpoint — same context, new limits.
4. You continue exactly where you left off.

## Configuration

Everything lives in `~/.config/ccu/config.json`. Sensible defaults ship out of the box:

```json
{
  "max_sessions": 4,
  "rotate_on_limit": true,
  "keep_checkpoint": true,
  "quiet": false
}
```

| Option | Default | Description |
|---|---|---|
| `max_sessions` | `4` | Upper bound of the rotation pool |
| `rotate_on_limit` | `true` | Rotate automatically when the wall hits |
| `keep_checkpoint` | `true` | Keep the last checkpoint on disk |
| `quiet` | `false` | Suppress non-essential output |

## FAQ

<details>
<summary><b>Does this share accounts with other people?</b></summary>

No. Everything runs locally against your own setup. No pools, no invites,
nothing leaves your machine.
</details>

<details>
<summary><b>Does it modify Claude Code itself?</b></summary>

No. `ccu` is a wrapper — the original CLI stays untouched and upgradable.
</details>

<details>
<summary><b>Where is my data stored?</b></summary>

`~/.config/ccu/` — plain JSON, readable, deletable, never uploaded.
</details>

<details>
<summary><b>Windows / Linux / macOS?</b></summary>

Yes, yes and yes. If Node 18+ runs, `ccu` runs.
</details>

## Documentation

- [Usage guide](docs/USAGE.md)
- [FAQ](docs/FAQ.md)
- [Contributing](CONTRIBUTING.md)
- [Changelog](CHANGELOG.md)

## License

MIT © contributors — see [LICENSE](LICENSE).
## Why

Claude Code is great — until you hit the usage limit mid-task and lose your flow.
`claude-code-unlimited` watches your session in the background and rotates it
for you the moment the limit shows up, so you keep working without even noticing.

## Features

- **Automatic rotation** — detects the limit wall and swaps sessions in-place
- **Zero config** — works out of the box, sensible defaults, no accounts to invite
- **Local only** — your state never leaves your machine, no telemetry
- **Drop-in** — a single wrapper command, same CLI you already use
- **Deterministic** — rotation is reproducible and easy to reason about
- **Tiny** — ~3 kB of plain Node, no native modules, no background daemons

## Getting started

```bash
npm install -g claude-code-unlimited
```

That's it. From now on start your sessions with:

```bash
ccu
```

`ccu` wraps `claude` with the same flags you already use and handles everything else:

```bash
# instead of:  claude --dangerously-skip-permissions
ccu --dangerously-skip-permissions
```

## How it works

```
 you ──▶ ccu ──▶ claude code ──▶ limit? ──▶ rotate ──▶ claude code ──▶ ...
                    │
                    └── session store (local, plain JSON)
```

1. `ccu` launches Claude Code as usual and watches the output stream.
2. When a limit message is detected, the current session is checkpointed.
3. A fresh session is created from the checkpoint — same context, new limits.
4. You continue exactly where you left off.

## Configuration

Everything lives in `~/.config/ccu/config.json`. Sensible defaults ship out of the box:

```json
{
  "max_sessions": 4,
  "rotate_on_limit": true,
  "keep_checkpoint": true,
  "quiet": false
}
```

| Option | Default | Description |
|---|---|---|
| `max_sessions` | `4` | Upper bound of the rotation pool |
| `rotate_on_limit` | `true` | Rotate automatically when the wall hits |
| `keep_checkpoint` | `true` | Keep the last checkpoint on disk |
| `quiet` | `false` | Suppress non-essential output |

## FAQ

<details>
<summary><b>Does this share accounts with other people?</b></summary>

No. Everything runs locally against your own setup. No pools, no invites,
nothing leaves your machine.
</details>

<details>
<summary><b>Does it modify Claude Code itself?</b></summary>

No. `ccu` is a wrapper — the original CLI stays untouched and upgradable.
</details>

<details>
<summary><b>Where is my data stored?</b></summary>

`~/.config/ccu/` — plain JSON, readable, deletable, never uploaded.
</details>

<details>
<summary><b>Windows / Linux / macOS?</b></summary>

Yes, yes and yes. If Node 18+ runs, `ccu` runs.
</details>

## Documentation

- [Usage guide](docs/USAGE.md)
- [FAQ](docs/FAQ.md)
- [Contributing](CONTRIBUTING.md)
- [Changelog](CHANGELOG.md)

## License

MIT © contributors — see [LICENSE](LICENSE).
