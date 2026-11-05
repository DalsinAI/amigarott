/* The Amiga port's own helpers (amiga/).
 * Copyright (c) 2026 AmiCradle Team. GPL 2 or later, like Rise of the Triad. */
#ifndef AMIGA_PORT_H
#define AMIGA_PORT_H

void amiga_screens_snapshot(void);
void amiga_screens_close_leftovers(void);
void amiga_message(const char *title, const char *text);

#endif
