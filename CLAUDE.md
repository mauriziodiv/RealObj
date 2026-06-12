# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project

RealObj is a Windows C++ static library for loading and parsing OBJ mesh files.

## Build

Primary: open `RealObj.slnx` in Visual Studio 2022 and press **F7**.

CLI (MSBuild):
```
msbuild RealObj.slnx /p:Configuration=Debug /p:Platform=x64
msbuild RealObj.slnx /p:Configuration=Release /p:Platform=x64
msbuild RealObj.slnx /t:Clean /p:Configuration=Debug /p:Platform=x64
```

Supported configurations: `Debug|Win32`, `Release|Win32`, `Debug|x64`, `Release|x64`.

## Code Style

- Classes and types: PascalCase — `MeshLoader`, `ObjVertex`
- Methods and functions: lowercase — `load()`, `parse()`, `getVertices()`
- Language standard: C++20
- Platform: Windows only — uses `WIN32_LEAN_AND_MEAN`, requires Windows 10+ SDK
- New headers must use `#pragma once`
- Formatting: `.clang-format` is present — Microsoft style, 4-space indent, 120-column limit, left-aligned pointers and references (`int* p`, `int& r`)

## Precompiled Headers

All translation units must include `pch.h` first. Add new system or third-party includes to `pch.h`, not to individual `.cpp` files. Modifying `pch.h` triggers a full rebuild.

## Dependencies

No external dependencies — pure C++ standard library only.
