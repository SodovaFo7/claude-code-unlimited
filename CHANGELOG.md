# Changelog

## [0.2.1] — 2026-11-23

### Fixed
- Truncation edge case in the limit detector when output chunks arrive split.

## [0.2.0] — 2026-11-23

### Added
- Manual rotation: `ccu rotate`.
- Pool inspection: `ccu status`.

### Changed
- Checkpoints are now written atomically.

## [0.1.0] — 2026-11-22

### Added
- Initial public release.
- Automatic limit detection and session rotation.
- Local JSON store with sane defaults.
