#ifndef _LIBAGVIO_H
#define _LIBAGVIO_H


#define DLL_EXPORT __attribute__((visibility("default")))


DLL_EXPORT void config_ini(char *path);
DLL_EXPORT int Read_Config_Value(char* path, char *key, char *value);
DLL_EXPORT int Write_Config_Value(char* path, char *key, char *value);
#endif
