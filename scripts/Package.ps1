Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'
Add-Type -AssemblyName System.IO.Compression
Add-Type -AssemblyName System.IO.Compression.FileSystem -ErrorAction SilentlyContinue

$root = Split-Path -Parent $PSScriptRoot
$version = '0.1.0'
$name = "XML2-True-Analog-v$version"
$zipPath = Join-Path $root "dist/$name.zip"
$files = [ordered]@{
    'DINPUT.dll' = Join-Path $root 'build/DINPUT.dll'
    'true-analog.ini' = Join-Path $root 'config/true-analog.ini'
    'README.md' = Join-Path $root 'README.md'
    'LICENSE' = Join-Path $root 'LICENSE'
}
foreach ($path in $files.Values) {
    if (-not (Test-Path -LiteralPath $path -PathType Leaf)) { throw "Missing release file: $path" }
}
& (Join-Path $root 'scripts/Inspect-Proxy.ps1') -Path $files['DINPUT.dll'] | Out-Null
if (-not $?) { throw 'DLL inspection failed.' }
if ((Get-Content -LiteralPath $files['true-analog.ini'] -Raw) -notmatch
    '(?m)^TrueAnalogMovement=1\s*$') { throw 'Release INI must enable True Analog.' }
New-Item -ItemType Directory -Path (Split-Path $zipPath) -Force | Out-Null
$stream = [IO.File]::Open($zipPath, [IO.FileMode]::Create, [IO.FileAccess]::Write)
try {
    $archive = [IO.Compression.ZipArchive]::new($stream, [IO.Compression.ZipArchiveMode]::Create, $false)
    try {
        foreach ($entryName in $files.Keys) {
            $entry = $archive.CreateEntry("$name/$entryName", [IO.Compression.CompressionLevel]::Optimal)
            $entry.LastWriteTime = [DateTimeOffset]::new(2026, 9, 27, 0, 0, 0, [TimeSpan]::Zero)
            $source = [IO.File]::OpenRead($files[$entryName])
            $destination = $entry.Open()
            try { $source.CopyTo($destination) }
            finally { $destination.Dispose(); $source.Dispose() }
        }
    } finally { $archive.Dispose() }
} finally { $stream.Dispose() }
$check = [IO.Compression.ZipFile]::OpenRead($zipPath)
try {
    if ($check.Entries.Count -ne $files.Count) { throw 'Unexpected ZIP entry count.' }
    foreach ($entry in $check.Entries) {
        $baseName = [IO.Path]::GetFileName($entry.FullName)
        if ($entry.FullName -cne "$name/$baseName" -or -not $files.Contains($baseName)) {
            throw "Unexpected ZIP entry: $($entry.FullName)"
        }
        $sourceHash = (Get-FileHash -LiteralPath $files[$baseName] -Algorithm SHA256).Hash
        $sha = [Security.Cryptography.SHA256]::Create()
        $entryStream = $entry.Open()
        try { $entryHash = [BitConverter]::ToString($sha.ComputeHash($entryStream)).Replace('-','') }
        finally { $entryStream.Dispose(); $sha.Dispose() }
        if ($entryHash -ine $sourceHash) { throw "ZIP content differs: $baseName" }
    }
} finally { $check.Dispose() }
Write-Output "PASS: $zipPath"
Write-Output "SHA-256: $((Get-FileHash -LiteralPath $zipPath -Algorithm SHA256).Hash)"
