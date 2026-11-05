/* A Shell gives 4 KB of stack; the renderer and the menus keep big tables
 * in locals and SDL 2 wants more besides. libnix's startup sets this much
 * up.
 * Copyright (c) 2026 AmiCradle Team. GPL 2 or later, like Rise of the Triad. */
unsigned long __stack = 512 * 1024;
static const char version[] __attribute__((used)) = "$VER: Rott 2025.12.22 Amiga (05.11.2026)";
