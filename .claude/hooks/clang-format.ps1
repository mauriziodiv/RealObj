$json = [Console]::In.ReadToEnd() | ConvertFrom-Json
$f = $json.tool_input.file_path
if ($f -and ($f.EndsWith('.cpp') -or $f.EndsWith('.h'))) {
    & 'C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\Llvm\x64\bin\clang-format.exe' -i $f 2>$null
}
