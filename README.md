# memriff

a lightweight windows memory hacking library for games.

## features
- attach to processes by name or pid
- read/write int, float, vector3, strings, byte arrays
- resolve multi-level pointer chains
- aob pattern scanning with wildcards
- dll injection and ejection

## usage

```cpp
#include "memriff.h"
using namespace memriff;

// attach to cs2
attach(L"cs2.exe");

// read health
uintptr_t client = module(L"client.dll");
uintptr_t local = get<uintptr_t>(client + 0x1874050);
int health = get<int>(local + 0x344);

// write infinite health
set<int>(local + 0x344, 999);

// resolve pointer chain
uintptr_t health_addr = follow(client + 0x1874050, {0x344});

// pattern scan
uintptr_t addr = scan(client, 0x2000000, "48 8B 0D ?? ?? ?? ??");

// inject dll
load(L"C:\\mydll.dll");

// cleanup
detach();