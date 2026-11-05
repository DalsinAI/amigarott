Rise of the Triad for AmigaOS 3.x
=================================

A port of Taradino (https://github.com/fabiangreffrath/taradino, main at
commit 2b4ea3c6c18caf60959efee1f2534c2122607716, version 2025.12.22), the
SDL 2 source port of Apogee's Rise of the Triad (1994), for AmigaOS 3.2 on a
68040 or 68060 with an FPU and an RTG screen, on OpenGPU's SDL 2.

Status: runs in the AmiCradle lab with the shareware data: title, menus, a
new game, walking, turning, shooting, and quitting cleanly to the Workbench.
Sound effects are mixed but the lab is muted, so they were not heard; there
is no music (see Known limits).


What you need
-------------

- A 68040 or 68060 with an FPU (not an LC040 or EC040), AmigaOS 3.2, an RTG
  card (or the AmiCradle lab), and about 16 MB of free memory.
- GFOpenGPU 0.8 or later: LIBS:GFOpenGPU/SDL2.module and SDL2_mixer.module
  (installed by OpenUp).
- The game's data, which is not included (see Licences.txt):
  - "The HUNT Begins" (shareware, free to download as 1rott13.zip; the
    ROTTSW13.SHR inside it is a ZIP archive): HUNTBGIN.WAD, HUNTBGIN.RTL,
    HUNTBGIN.RTC and REMOTE1.RTS, for Rott-Shareware;
  - or the registered game ("Dark War", sold by Apogee, GOG and Steam):
    DARKWAR.WAD, DARKWAR.RTL, DARKWAR.RTC and REMOTE1.RTS (or the Site
    Licence / Extreme ROTT versions of the .RTC), for Rott.
  Copy them into the Rott drawer, beside the programs. Upper or lower case
  does not matter.


How to play
-----------

Run Install-Rott (or copy the Rott drawer where you want it), add the data,
then double-click Rott-Shareware (or Rott), or from a Shell:

    cd Rott
    Rott-Shareware [NOWAIT] [FULLSCREEN] [RESOLUTION 640x480] [NOSOUND]

- NOWAIT skips the intro and goes to the menu; FULLSCREEN opens a 640x480
  screen of its own rather than a window on the Workbench; RESOLUTION
  640x480 draws the game at 640x480 (twice the work for the 68040; the
  default is the game's own 320x200 shown in a 640x480 window). The game
  keeps FULLSCREEN and RESOLUTION in its settings: WINDOW goes back to the
  window, RESOLUTION 320x200 to the small picture. Taradino's other options
  are in ReadMe-taradino and Cheats.txt.
- Keys, as on the PC: cursor keys walk and turn, Ctrl fires, Alt strafes,
  Shift runs, Space opens doors and presses switches, Enter selects in the
  menus. Options > Controls changes them; the mouse works when the window
  has it (Ctrl+G grabs and frees it in a window).
- Esc opens the game's menu, which has Quit at the bottom (Y answers its
  question). Right Amiga+Q quits at once from anywhere.
- The settings and saved games are in the drawer's huntbgin (or darkwar)
  drawer; an update by Install-Rott keeps it.


Building
--------

GFOpenAmigaGCC 16.2.0-open6 (the os32-gcc16-open6 stove, with the GFOpenGPU
SDK 0.8 in it):

    make -f amiga/Makefile.amigaos -j4 dist STOVE=/path/to/os32-gcc16-open6

STOVE defaults to ~/AmiCradle/stoves/os32-gcc16-open6. Output:
build/amigaos/Rott and Rott-Shareware; 'dist' makes dist/Rott/ (both
programs, ReadMe, ReadMe-taradino, Cheats.txt, COPYING.txt, Licences.txt,
with GlowIcons), dist/Rott.info and dist/Install-Rott with its icon. The
icons are made from amiga/icons/icons.json and Install-Rott from
amiga/installer.json with amicradle's scripts/port_icons.py and
port_installer.py (see "about" in icons.json).


What was changed
----------------

- amiga/Makefile.amigaos: upstream's rott/*.c, built twice (SHAREWARE=1
  for Rott-Shareware), linked with the stove's libSDL2_mixer.a and
  libSDL2.a; version.h made from version.h.in.
- rott/rt_datadir.c, rott/m_misc.c: the data is looked for in PROGDIR:,
  then the current directory; the settings and saves go in
  PROGDIR:huntbgin (darkwar). M_StringJoin() leaves out a "/" after a
  volume name, a "/" or nothing (AmigaDOS reads "PROGDIR:/x" as the parent
  drawer); M_DirName() and M_BaseName() know "VOL:name". No XDG, Steam or
  GOG lookups, no getpwuid().
- rott/modexlib.c, rott/vgatext.c: OpenGPU's SDL 2 reports a 24-bit window,
  so the picture goes through a SDL_PIXELFORMAT_RGB888 streaming texture.
  A 640x480 window (not resizable); a full screen is SDL_WINDOW_FULLSCREEN,
  not _DESKTOP.
- rott/winrott.c, rott/rt_cfg.c: 320x200 and a window by default (upstream:
  640x480, full screen).
- rott/fx_mixer.c: sound mixed at 22050 Hz rather than 44100 (the effects
  are 11 kHz samples).
- rott/rt_in.c: Right Amiga+Q quits through ShutDown() (the settings are
  written).
- rott/rt_main.c: an atexit() handler shuts SDL down and closes the empty
  screens SDL2.module leaves behind (amiga/amiga_screens.c, from the other
  SDL 2 ports). QuitGame() stops the music rather than fading it and leaves
  out the DOS end text screen (both hung the quit in the lab; see Known
  limits).
- rott/rt_menu.c: the menu's Quit stops the music rather than fading it,
  as upstream does on Windows.
- rott/rt_sound.c: SD_WaitSound() (the quit sound) waits four seconds at
  most and reads the events while it waits.
- rott/rt_util.c: Error() shows its text in an Intuition requester
  (amiga/amiga_message.c), seen from the Workbench too, before ShutDown()
  (which exits).
- amiga/stack.c: 512 KB of stack and a $VER string.

Big-endian: Taradino already reads the WAD, the maps and the saves through
its byte-order helpers (byteordr.c, the SwapLE macros), as its README says
("support for 64-bit and big-endian systems"); the lab run loaded the
shareware WAD and the first level and drew them right with no change.

Frame pacing: the game counts 35 Hz tics from SDL_GetTicks() and waits in
WaitVBL() with SDL_Delay(), as upstream does.


Known limits
------------

- No music: Taradino plays the game's MIDI songs through SDL2_mixer, which
  needs a SoundFont (soundfont.sf2 in the drawer) and a MIDI player in
  SDL2_mixer.module; the lab printed "No Soundfont found!" and played none.
  A SoundFont was not tried (it would cost the 68040 a lot).
- The DOS end text screen (the ordering text shown on quitting) is left
  out: through OpenGPU's SDL 2 it stayed black and waited for a key.
- Quitting from the menu takes a few seconds (the quit sound, then SDL's
  shutdown).
- The frame rate on a real 68040 was not measured; the lab's CPU is faster.
- No network or modem play (as upstream). Demos may go out of step (as
  upstream says).
- The registered game (Rott) was only started without its data (it shows
  the "Required file not found" requester and quits); it was not played.


Licence
-------

The program is under the GNU GPL, version 2 or later (COPYING.txt);
vgatext.c is MIT and vgafont.h public domain. The game data is Apogee's and
is not included; see Licences.txt. The port's own files are GPL 2 or later,
Copyright (c) 2026 AmiCradle Team.
