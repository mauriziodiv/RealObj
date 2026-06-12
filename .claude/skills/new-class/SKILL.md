---
name: new-class
description: Scaffold a new C++ class pair (header + .cpp) following RealObj conventions. Invoke as /new-class <ClassName>.
---

Create a new C++ class named $ARGUMENTS.

## Header (`RealObj/$ARGUMENTS.h`)

```cpp
#pragma once

class $ARGUMENTS
{
public:
    $ARGUMENTS();
    ~$ARGUMENTS();
};
```

## Implementation (`RealObj/$ARGUMENTS.cpp`)

```cpp
#include "pch.h"
#include "$ARGUMENTS.h"

$ARGUMENTS::$ARGUMENTS()
{
}

$ARGUMENTS::~$ARGUMENTS()
{
}
```

## After creating both files

Remind the user to add them to `RealObj.vcxproj`:
- `.h` → `<ClInclude Include="$ARGUMENTS.h" />` in the headers ItemGroup
- `.cpp` → `<ClCompile Include="$ARGUMENTS.cpp" />` in the sources ItemGroup

Or suggest opening the project in Visual Studio and using **Add > New Item** instead to have the IDE handle the vcxproj edits automatically.
