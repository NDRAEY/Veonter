#include "kernel/vfs.h"
#include <kernel/fs/fat32/fat32_to_vfs.h>
#include <kernel/fs/fat32/fat32.h>
#include <stdio.h>
#include <stdlib.h>

size_t fat32_filewrite(fs_object_t *fs, const void *data, size_t size, size_t count, NFILE *fp) {
    printf("TODO: FAT32 WRITE IS NOT TESTED!\n");
    
    fat_t* fat = fs->priv_data;
    
    printf("PATH: %s; OFF: %d; SIZE: %d; DATA AT: %x\n", fp->path, fp->position, size * count, data);

    fat32_write(fs, fat, fp->path, fp->position, size * count, data);

    return 0;
}

direntry_t* fat32_diropen(fs_object_t *obj, const char *path) {
    fat_t* fat = obj->priv_data;

    size_t cluster = fat32_search(obj, fat, path);

    if(cluster == 0) {
        return NULL;
    }

    return fat32_read_directory(obj, fat, cluster);
}

void fat32_dirclose(fs_object_t *obj, direntry_t *dir) {
    printf("FAT32 directory is closed\n");
}

NFILE* fat32_fileopen(fs_object_t *fs, const char* path) {
    fat_t* fat = fs->priv_data;

    size_t cluster = fat32_search(fs, fat, path);

    if(cluster == 0) {
        return NULL;
    }

    NFILE* file = calloc(1, sizeof(NFILE));

    file->path = path;
    file->size = fat32_get_file_size(fs, fat, path);
    file->priv_data = (void*)cluster;   // HINT: There's no pointer function, do not dereference it!!! It's only the data we want to store there.

    return file;
}

size_t fat32_fileread(fs_object_t *fs, void *data, size_t size, size_t count, NFILE *fp) {
    fat_t* fat = fs->priv_data;
    size_t clust = (size_t)fp->priv_data;

    return fat32_read_cluster_chain_advanced(fs, fat, clust, fp->position, size * count, false, data);
}

void fat32_fileclose(fs_object_t *fs, NFILE *fp) {
    // Nothing
}
