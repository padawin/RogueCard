#ifndef __GLOBALS__
#define __GLOBALS__

#if GCW
const bool FULL_SCREEN = true;
#else
const bool FULL_SCREEN = false;
#endif
const int SCREEN_WIDTH = 320;
const int SCREEN_HEIGHT = 240;
const char * const GAME_DATA_FOLDER = ".card-rogue/";

const char* const FONT_PATH = "fonts/VCR_OSD_MONO_1.001.ttf";

const int FONT_HEIGHT = 16;
const int ARROW_WIDTH = 16;
const int ARROW_HEIGHT = 16;

#endif
