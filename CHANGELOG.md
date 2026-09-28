# Changelog

## 0.5.0-beta.1

XML2 Modern Controller's first local public-beta candidate; no remote publication.

- True 360-degree movement, analog magnitude and radial deadzone.
- Hot-plug/reconnect and conservative device classification.
- Original Xbox/PlayStation glyphs, Generic-to-Xbox presentation and dynamic prompts.
- Advanced controller Accept/Back, native directions and mouse-selected binding edits.
- Intentional local text fallback and safe unsupported-build refusal.
- Consistent identity/version, quiet defaults, deterministic binary/source packaging
  and standalone clean-build/install validation.

Known limitations: one validated PC EXE; gameplay principally tested in P1;
P2-P4 and physical PlayStation hardware are unvalidated. Advanced uses text labels.
PreserveMagnitude=0 is unsupported. Final validation is recorded in docs/BETA-VALIDATION.md.

## 0.1.0

Added 360-degree left-stick movement, radial deadzone, partial-speed support,
runtime-only movement hook, build fingerprinting, unique signature validation,
optional input logging, and a reversible DirectInput 7 proxy.

Known limits: gameplay validated on one PC executable and controller index 0;
other builds fail closed, and other controller indices are experimental.
