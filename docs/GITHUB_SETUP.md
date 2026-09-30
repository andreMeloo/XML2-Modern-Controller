# GitHub publication

Official repository: https://github.com/andreMeloo/XML2-Modern-Controller
Default branch: main. Release: v0.5.0-beta.2 (prerelease).

Run the build and all five suites in README. Audit both Package.ps1 outputs,
verify final gameplay before publication, and attach these three artifacts:

- XML2-Modern-Controller-v0.5.0-beta.2.zip
- XML2-Modern-Controller-v0.5.0-beta.2-source.zip
- SHA256SUMS.txt

Use docs/RELEASE_NOTES_v0.5.0-beta.2.md for the release body. The binary ZIP contains
only DINPUT.dll, true-analog.ini, README.md and LICENSE. The source ZIP contains
only project-owned source/docs/art, not generated/game files or investigation data.

Generate hashes only after final packaging:

```powershell
$releaseFiles = @('build/modern-controller/DINPUT.dll',
  'dist/XML2-Modern-Controller-v0.5.0-beta.2.zip',
  'dist/XML2-Modern-Controller-v0.5.0-beta.2-source.zip')
$lines = foreach ($file in $releaseFiles) {
  '{0}  {1}' -f (Get-FileHash -LiteralPath $file -Algorithm SHA256).Hash.ToLowerInvariant(),
    [IO.Path]::GetFileName($file)
}
$lines | Set-Content -LiteralPath dist/SHA256SUMS.txt -Encoding ascii
```

Verify the published download against these checksums. Checksums are a separate
release artifact and are not included in the source ZIP. Existing beta.1 and
historical True Analog releases remain unchanged.
