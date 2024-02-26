#include <stdio.h>
#include <stdint.h>
#include "bitmap.h"
#include "block_store.h"
// include more if you need

// You might find this handy.  I put it around unused parameters, but you should
// remove it before you submit. Just allows things to compile initially.
#define UNUSED(x) (void)(x)

block_store_t *block_store_create()
{
    // Malloc space for new BS
    block_store_t * newBlock = malloc(sizeof(block_store_t));       
    if(newBlock == NULL)
    { 
        printf("Failed to malloc memory in BSC");
        return NULL; 
    }
    // Initialize the new BS to zero
    memset(newBlock, 0, sizeof(block_store_t));                     
    // Initialize the bitmap
    newBlock->bitmap = bitmap_overlay(BITMAP_SIZE_BITS, BITMAP_START_BLOCK);
    if(newBlock->bitmap == NULL)
    {
        // Error handling if bitmap allocation fails
        printf("Failed to allocate bitmap");
        free(newBlock); // Free allocated memory
        return NULL;
    }
    // Mark the blocks used by the bitmap as allocated
    for (size_t i = 0; i < BITMAP_SIZE_BITS; i++)
    {
        if (!block_store_request(newBlock, BITMAP_START_BLOCK + i))
        {
            // Error handling if block allocation fails
            printf("Failed to allocate block for bitmap");
            bitmap_destroy(newBlock->bitmap); // Destroy bitmap overlay
            free(newBlock); // Free allocated memory
            return NULL;
        }
    }
    return newBlock;
}

void block_store_destroy(block_store_t *const bs)
{
    UNUSED(bs);
}
size_t block_store_allocate(block_store_t *const bs)
{
    UNUSED(bs);
    return 0;
}

bool block_store_request(block_store_t *const bs, const size_t block_id)
{
    UNUSED(bs);
    UNUSED(block_id);
    return false;
}

void block_store_release(block_store_t *const bs, const size_t block_id)
{
    UNUSED(bs);
    UNUSED(block_id);
}

size_t block_store_get_used_blocks(const block_store_t *const bs)
{
    UNUSED(bs);
    return 0;
}

size_t block_store_get_free_blocks(const block_store_t *const bs)
{
    UNUSED(bs);
    return 0;
}

size_t block_store_get_total_blocks()
{
    return 0;
}

size_t block_store_read(const block_store_t *const bs, const size_t block_id, void *buffer)
{
    UNUSED(bs);
    UNUSED(block_id);
    UNUSED(buffer);
    return 0;
}

size_t block_store_write(block_store_t *const bs, const size_t block_id, const void *buffer)
{
    UNUSED(bs);
    UNUSED(block_id);
    UNUSED(buffer);
    return 0;
}

block_store_t *block_store_deserialize(const char *const filename)
{
    UNUSED(filename);
    return NULL;
}

size_t block_store_serialize(const block_store_t *const bs, const char *const filename)
{
    UNUSED(bs);
    UNUSED(filename);
    return 0;
}