---
name: build-check
description: Run MSBuild to verify the project compiles after changes. Use after editing C++ source files to catch errors without opening Visual Studio.
disable-model-invocation: false
---

Run the following command from the repo root to verify the project compiles:

```
msbuild RealObj.slnx /p:Configuration=Debug /p:Platform=x64 /v:minimal
```

Report:
- Whether the build succeeded or failed
- Any compiler errors or warnings, with file and line number
- A one-line summary (e.g., "Build succeeded — 0 errors, 2 warnings")

If the build fails, diagnose the errors and suggest fixes before reporting back.
