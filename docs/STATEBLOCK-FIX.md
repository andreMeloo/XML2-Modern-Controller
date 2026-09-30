# Direct3D 8 glyph state-block lifecycle (beta.2)

## Change

The renderer previously created a D3DSBT_ALL block on its first glyph submission,
then reused it with CaptureStateBlock. It remained alive after glyphs disappeared
and across focus changes. The renderer does not hook or manage the game's Reset.

Beta.2 scopes the token to one pg_render_submit call. CreateStateBlock captures
current state, the unchanged glyph draw runs, ApplyStateBlock restores state,
and DeleteStateBlock releases the block before returning. Every successful
creation reaches restore and deletion even after a drawing error. HRESULTs are
checked and logged; deletion is still attempted after restoration failure.
If the API refuses deletion, release cannot be guaranteed: the error is logged
and rendering is disabled rather than repeatedly allocating more blocks.

No atlas, font metrics, glyph ID, hook address, device reset, binding, analog or
hot-plug change is part of this fix. The managed atlas remains managed by the
existing renderer. This narrowly changes state-block lifetime and error handling.

## Evidence and limits

On one tested Windows 10 PC build, minimizing worked before the first glyph;
after its display it failed even when the glyph disappeared. Two independent
sessions with ControllerGlyphs=0 passed. Two independent experimental sessions
with glyphs enabled and per-submission blocks also passed. The user confirmed
symbols, movement, commands, menus, subtitles/accents and focus changes, with no
new perceptible issues. Session logs confirm state restoration/deletion, no
reported block errors and normal exit. The final beta.2 clean release build also passed an independent human session:
glyphs displayed/disappeared, minimize/return, controller menus and subtitles/
accents remained correct, with no reported crashes or visible corruption. All
three sessions exited normally; original saves and settings were restored.

This implicates persistence/lifetime of the glyph state block. It does not
separately prove which captured resource or driver behavior caused the failure,
or promise a universal fix across builds/drivers. No crash reproduction with
the old DLL was repeated to obtain this result.

## Technical validation

All five existing suites passed on a clean x86 build. Added coverage uses the
actual submit function against a simulated D3D8 vtable: successful/repeated
submissions, early/no-match returns and create/set/draw/apply/delete errors.
Successful submissions restore the mocked complete state and retain no block;
delete is attempted even after restore failure. These tests are not GPU QA.
The atlas BGRA checksum is unchanged. Compared with the approved experimental
DLL, the final DLL's .text, .data, .tls and .reloc sections are identical; version
strings and build metadata differ.

## Performance

Create/delete adds allocation/release work per matching glyph submission in
place of reusing/capturing one block. Calls without matching glyph quads still
return before allocating. Human testing reported no new perceptible problems;
there is no measured frame-time benchmark or universal performance guarantee.
No pooling/optimization or other lifecycle change was introduced without testing.
