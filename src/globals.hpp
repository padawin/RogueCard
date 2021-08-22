#ifndef __GLOBALS__
#define __GLOBALS__

#define WORLD_MAP_GENERATION_SCRIPT "world_generator.py"
#define LEVEL_GENERATION_SCRIPT "level_generator.py"
#define LEVEL_CHANGE_SCRIPT "level_change.py"
#define LEVEL_END_SCRIPT "level_end.py"
#define GET_PERK_DATA_SCRIPT "get_perk_data.py"

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
