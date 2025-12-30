#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

// Saves data to <path>/<fileName>. 
bool ExportData(const char *path, const char *fileName, void *data, int size);

#endif