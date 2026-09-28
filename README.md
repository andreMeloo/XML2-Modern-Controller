# XML2 Modern Controller

**v0.5.0-beta.1** — controller improvements for X-Men Legends II on PC.
Runtime hooks are reversible; `XMen2.exe` is never edited. Keyboard, mouse and
controller remain available together. LastInputSource changes prompt presentation only.

## Features

- True 360° analog movement, partial-stick speed and radial deadzone.
- Controller hot-plug and automatic reconnect.
- Dynamic keyboard/controller prompts with original Xbox and PlayStation glyph artwork.
- Generic controllers use Xbox presentation by default.
- Advanced controller navigation with South/A Accept and East/B Back.
- Console-style controller defaults that preserve existing custom bindings.

## Installation

1. Start with a working PC installation. Close the game.
2. Check that no other mod owns `DINPUT.dll`; do not overwrite another proxy.
3. Extract this package's `DINPUT.dll` and `true-analog.ini` beside `XMen2.exe`.
4. Open the game normally. No build tools or source checkout are required.

Windows 10 or later is targeted; the x86 DLL uses Windows DirectInput and the
Universal C Runtime. Only the PC build below has been validated.

## Uninstallation

Close the game and remove this mod's `DINPUT.dll`, `true-analog.ini` and optional
`true-analog.log`. The executable and game assets are unchanged.

## Configuration

Edit `true-analog.ini` before launching. The legacy filename is intentionally retained.

| Section / option | Default | Purpose |
| --- | --- | --- |
| Controller / TrueAnalogMovement | 1 | Enable the P1 movement correction |
| Controller / Deadzone | 0.15 | Radial deadzone, valid range 0–0.5 |
| Controller / PreserveMagnitude | 1 | Partial-stick speed; keep 1 in this beta (0 safely disables the hook) |
| Controller / ControllerIndex | 0 | Preferred DirectInput controller; other indices remain experimental |
| General / HotPlug | 1 | Late connection and reconnect |
| General / DynamicPrompts | 1 | Switch prompt presentation with real input |
| General / ControllerGlyphs | 1 | Use images where the text path supports them |
| General / TutorialControllerText | 1 | Use native controller tutorial text in controller context |
| General / AdvancedController | 1 | Enable contextual Accept/Back in Advanced |
| Player1 / ControllerType | Auto | Auto, Xbox, PlayStation or Generic; physical button interpretation |
| Player1 / GlyphStyle | Auto | Auto, Xbox or PlayStation; presentation only |
| Player1 / Preset | ConsoleDefault | Console defaults for an unconfigured pad; None disables preset publication |

Detailed traces are off by default. Older Controller settings remain supported;
optional Player1 overrides take precedence. Advanced bindings are selected with
the mouse; the original keyboard/controller capture remains intact. Use Esc to
cancel editing. There is no exclusive input-device selection.

## Compatibility

Validated `XMen2.exe` SHA-256:
`146CD9C316EDB57A267CD73753A7CE9AF647E52AAB750D449C6B278FB4A1669B`.

SUPPORTED means the hash, unique signatures and instruction/layout guards allow
runtime hooks. UNKNOWN/INCOMPATIBLE means no unsafe game patch is applied;
Windows DirectInput forwarding remains available. Other PC versions are not
claimed supported. See `docs/COMPATIBILITY.md` in the source package.

## Known limitations

- Gameplay is validated principally for P1. P2–P4 are experimental/unvalidated.
- Physical PlayStation hardware and native Sony HID mapping are not validated.
  Glyph presentation can be tested with an override; that is not hardware validation.
- Generic uses Xbox-compatible DirectInput indices; arbitrary HID layouts may differ.
- Advanced intentionally uses local text labels rather than inline glyphs.
  Entering it does not globally disable dialogue/gameplay glyphs.
- Binding selection/edit entry remains via mouse; keyboard and controller retain
  original capture behavior. There is no controller list editor.
- Combined DirectInput trigger axes keep the original game's limitation.
- Another DINPUT proxy cannot simply be installed alongside this DLL.

## Troubleshooting

`true-analog.log` is created beside the DLL. It records version, compatibility and
hook status; diagnostic traces are disabled. If the game fails to start, uninstall
the two mod files and verify the original game. Report Windows version, controller
model/connection, EXE hash, relevant log lines and reproduction steps. Do not send
game binaries, extracted assets, saves or personal paths.

## Build from source

On Windows, use PowerShell 7+, Zig **0.16.0**, resvg **0.47.0**, and Python with
Pillow. The tested asset toolchain is Python **3.12.14** / Pillow **12.3.0**.

```powershell
./build-controller.ps1 -ZigPath ./tools/zig.exe -PythonPath ./tools/python.exe -ResvgPath ./tools/resvg.exe
./tests/Test-Controller.ps1 -ZigPath ./tools/zig.exe
./tests/Test-Prompts.ps1 -ZigPath ./tools/zig.exe
./tests/Test-Advanced.ps1 -ZigPath ./tools/zig.exe
./tests/Test-UnknownBuild.ps1 -ZigPath ./tools/zig.exe
./tests/Test-Release.ps1 -ZigPath ./tools/zig.exe
./scripts/Package.ps1
./scripts/Package.ps1 -Source
```

Tool paths are examples; pass your installed executables. `VERSION` controls the
modern runtime/package version. Build regenerates the embedded atlas from the
approved SVGs and produces `build/modern-controller/DINPUT.dll` plus metadata.
No game, Dev/Vanilla installation or parent project is needed to build/package.
See `docs/BETA-VALIDATION.md` for evidence and `docs/SCREENSHOTS.md` for future images.

## Credits

Reverse-engineering reference: [SomeoneIsWorking/xmen2 at cf0def5](https://github.com/SomeoneIsWorking/xmen2/tree/cf0def5efd076e18f6333db67916bfdee336729b), MIT licensed.
This is an independent implementation; no upstream source or game assets were copied.
XML2 True Analog v0.1.0 remains a historical local artifact; its ZIP is not overwritten.

## License

MIT covers this project's original code, documentation and glyph artwork.
No license to the game or its proprietary assets is included. See `LICENSE`.
