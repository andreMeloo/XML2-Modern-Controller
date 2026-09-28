# Beta validation: 0.5.0-beta.1

Scope is frozen at the accepted Advanced mouse-edit behavior from `bd22d0a`.
No new gameplay, renderer, exclusivity, binding-editor or art features are added.
Changes are identity/version, release defaults, diagnostic gating, documentation
and deterministic standalone packaging. Historical True Analog v0.1.0 ZIP is preserved.

## Evidence

- Previous validated core: P1 angles, circle, partial stick, radial deadzone,
  keyboard, mouse, camera, combat, character changes, menus and save/load.
- Previous Advanced round: directions, A/B, mouse/Esc, reconnect and diagonal
  were reported working. Dialogue images were explicitly confirmed; Advanced
  text fallback is intentional and local.
- Final beta technical tests pass: controller COM ABI/model/config, prompt model,
  render/tutorial ABI, Advanced ABI/commands, unsupported-build refusal and release
  identity/defaults/logger. The actual logger emitted zero writes for 10,000
  diagnostic events with trace off; support/refusal logging remained available.
- Clean source build and working-tree build produce identical stripped x86 DLLs:
  `340D47F3EEF8D28995CFA7D2F88A85B76F0D8BFADC452D90F65EFF85A2A633E6`.
  Approved decoded atlas hash remains
  `ae22bd3b54b7ed525c9f65739025a72a6696c2ddfb952a9129fa2be88b6ef014`.
  Removing debug symbols avoids path-dependent linker IDs; runtime behavior is unchanged.
- Binary ZIP round-trip/content audit passes with exactly four owned files;
  two package runs produced the same ZIP hash. Original v0.1.0 ZIP remains intact.
- Exact ZIP files installed in baseline-matching marked Dev. Direct launch with
  no log override confirmed beta version, supported hash, analog/Advanced/prompt
  hooks, Generic controller at startup, embedded atlas, and normal local support log.
- A fresh extraction of the source ZIP also rebuilt the identical DLL and binary
  ZIP without parent-project files. Historical tests are not relabeled as beta tests.
- Final beta session 1: user confirmed the complete connected-startup route:
  requested angles/circle, partial speed/deadzone, keyboard/mouse/controller,
  prompts, Advanced A/B and original mouse edit, combat/powers/camera, character
  changes, menus and save/load. Direct Dev process exited with code 0.
- Support log after this session: 36 lines / 3,469 bytes, with no enumeration or
  input trace spam. Advanced fallback and actual glyph submissions were observed.
- Standalone uninstall passed: removing the four ownership-verified package files
  and generated support log returned Dev to the complete SHA-256 baseline.
- Final beta session 2 passed by user confirmation: startup without a pad, late
  connection, disconnect/reconnect during Advanced navigation without stuck input,
  PlayStation Cross presentation override in dialogue and return to keyboard.
  The process exited with code 0. This validates presentation on the available
  Generic controller, not physical PlayStation hardware.
- Final local installation restores the exact public ZIP defaults (GlyphStyle=Auto,
  traces off). Game EXE/assets and Vanilla/source installations are not modified.
- Removed the obsolete generated DINPUT.pdb; build caches/historical artifacts
  are excluded from source packaging, rather than deleting useful parent history.

## Short final physical route

Session 1, controller connected before launch: confirm normal startup; test
0/30/45/60/90/135 degrees, a circle, partial stick and center/deadzone. Switch
keyboard/mouse/controller freely. Check dialogue keyboard -> glyph -> keyboard,
Advanced directions/A/B, mouse-selected capture/cancel, and glyphs after leaving.
Check attacks, powers, camera, character change, menus and save/load.

Session 2, controller disconnected before launch: start with keyboard, connect
and wait up to five seconds; enter Advanced, disconnect during navigation,
reconnect, and confirm no stuck input. Return to gameplay and check movement/buttons.

PlayStation presentation is checked with GlyphStyle override; physical Sony HID
and P2-P4 remain unvalidated. Default Generic presentation is Xbox.

## Standalone install/uninstall

Install only the four files from the binary ZIP in a clean marked Dev game,
with game files first matching the verified baseline. Start the game directly,
without a source checkout or Codex launcher dependency. The normal support log
is `true-analog.log` beside the DLL. Close the game, remove only mod-owned files
and its generated log, verify the baseline, then reinstall the exact ZIP.
Machine-specific setup/validation lives in the parent project's ignored work/config,
not in this portable source project.

## Performance and release limits

Signature scans run at initialization, not each frame. The approved atlas is
embedded and uploaded once at runtime; it is not regenerated there. Glyph lookup
uses cached cells/UVs. Device discovery remains on the existing notification/5-second
worker; refresh consumes its cached inventory on changes. The original Advanced
manager may enumerate on its own menu timer; no additional per-frame Windows
enumeration is introduced. Detailed lifecycle logging now requires ControllerTrace=1;
AdvancedTrace/PromptTrace and input sampling are off. No new performance benchmark
is claimed.

One EXE hash is supported. P1 is the main validated path. The final requested
physical regressions passed; native PlayStation hardware and P2-P4 remain beta
limitations. No remote, push, release, forum post or fabricated screenshot is
created. Real publication screenshots remain for the user to supply.
