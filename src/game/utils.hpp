#ifndef __UTILS__
#define __UTILS__

#include <string>

std::string utils_getDataPath();
void utils_createFolder(const char *path);
int utils_emptyFolder(const char *path);
std::string utils_readFile(const char *filePath);
bool utils_isRegularFile(const char *path);
int utils_getFileContent(const char *path, std::string *fileContent);

float utils_lerp(const float start, const float end, const float t);

#endif
