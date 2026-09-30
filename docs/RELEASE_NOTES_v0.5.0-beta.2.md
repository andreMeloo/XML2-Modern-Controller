# XML2 Modern Controller v0.5.0-beta.2

This beta improves lifecycle management of the Direct3D 8 state blocks used to
render controller glyphs. Each submission captures a fresh state block, draws,
restores the game state and deletes the block. A block is no longer retained
across frames or focus changes. Creation, restoration and deletion errors are
checked and logged; deletion is attempted even after draw/restoration errors.

The reported minimize/return failure after glyph display was addressed on the
tested setup. This is not a universal fix for all builds, drivers or focus issues.
Glyphs remain enabled. No wrapper, renderer conversion, EXE patch, new controller
feature, translation or proprietary game file is included.

## Update and rollback

With the game closed, back up your existing Modern Controller DINPUT.dll and
replace only that DLL. Keep true-analog.ini and custom bindings. Roll back with
the game closed by restoring the backed-up DLL.

## Scope

One PC executable and mainly Player 1 are validated. Existing beta limitations
remain, including Advanced's intentional textual fallback and incomplete physical
PlayStation/P2-P4 validation. See README and the validation note.


## Validation

Five automated suites passed, including ten added state-block error/lifecycle
scenarios. Two experimental gameplay sessions and an independent session with
the final versioned DLL passed with glyphs enabled: glyph display/disappearance,
minimize/return, controller menus, subtitles and accents. No new perceptible
performance issue was reported; no frame-time benchmark is claimed.
