# Contributing

Issues and pull requests are welcome.

## Setup

```bash
git clone https://github.com/ /claude-code-unlimited
cd claude-code-unlimited
npm install
npm test
```

## Ground rules

- Plain Node, no native modules, no bundlers.
- Keep the public surface small: `ccu`, `ccu rotate`, `ccu status`, `ccu reset`.
- No telemetry. Local data stays local.
- Match the existing code style — small modules, explicit exports.

## Pull requests

1. Fork and branch from `main`.
2. One logical change per PR.
3. `npm test` green before you push.
