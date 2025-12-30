#include "file_manager.h"
#include <fstream>
#include "raylib.h"

bool ExportData(const char *path, const char *fileName, void *data, int size)
{
    if (!DirectoryExists(path))
        MakeDirectory(path);

    const char *currentPath = TextFormat("%s/%s", path, fileName);

    std::ofstream{currentPath};

    if (!SaveFileData(currentPath, data, size))
        TraceLog(LOG_WARNING, "Could not save chunk.");
    return false;
}