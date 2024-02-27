#include <stdio.h>
#include <stdint.h>
#include "bitmap.h"
#include "block_store.h"
#include <string.h>
// include more if you need

// You might find this handy.  I put it around unused parameters, but you should
// remove it before you submit. Just allows things to compile initially.
#define UNUSED(x) (void)(x)

// I'm not sure if I defined this correctly but based off my understanding it makes sense, lmk if you have any questions (-Joseph Spexarth)
typedef struct block_store {
    uint8_t data[BLOCK_STORE_NUM_BLOCKS][BLOCK_SIZE_BYTES];
    bitmap_t *bitmap; // Pointer to the bitmap
}block_store_t;

block_store_t *block_store_create()
{
    // Malloc space for new BS
    block_store_t * blockStore = (block_store_t*)malloc(BLOCK_STORE_NUM_BYTES);
    // Ensure proper memory initalization       
    if(blockStore == NULL)
    { 
        printf("Failed to malloc memory in BSC");
        return NULL; 
    }     
    // Initialize the new BS to zero
    memset(blockStore, 0, BLOCK_STORE_NUM_BYTES);                
    // Initialize the bitmap -> project says FBM starts in block 127
    blockStore->bitmap = bitmap_overlay(BITMAP_SIZE_BYTES * 8, (blockStore->data[127]) );
    // Ensure proper memory initalization
    if(blockStore->bitmap == NULL)
    {
        // Error handling if bitmap allocation fails
        printf("Failed to allocate bitmap");
        block_store_destroy(blockStore); // Free allocated memory
        return NULL;
    }
    
    
    // Mark the block used by the bitmap as allocated
    if (!block_store_request(blockStore, 127))
    {
    // Error handling if block allocation fails
    printf("Failed to allocate block for bitmap");
    block_store_destroy(blockStore); // Free allocated memory
    return NULL;
    }
    
    return blockStore;
}

void block_store_destroy(block_store_t *const bs)
{
    // Assure we arnt waisting our time
    if(bs == NULL) { return; }
    // Free Bitmap
    bitmap_destroy(bs->bitmap);
    // Free Block Store
    free(bs);
    return;
}

size_t block_store_allocate(block_store_t *const bs)
{
    if(bs == NULL) return SIZE_MAX;
    // Find the first zero
    size_t firstOpenBlockId = bitmap_ffz(bs->bitmap);

    if(firstOpenBlockId == SIZE_MAX) return SIZE_MAX;

    // Set the block as active
    if (!block_store_request(bs, firstOpenBlockId)) return SIZE_MAX;
    return firstOpenBlockId;
}

bool block_store_request(block_store_t *const bs, const size_t block_id)
{
    // Assert valid parameters
    if(bs == NULL || (int)block_id < 0 || block_id > BLOCK_STORE_AVAIL_BLOCKS -1 ) return false;
    // Assert the desired block is not already allocated
    if(bitmap_test(bs->bitmap, block_id)) return false;
    // Set the corrisponding bit in the bitmap to on
    bitmap_set(bs->bitmap, block_id);
    // Assert the bit was successfully set
    if(!bitmap_test(bs->bitmap, block_id)) return false;
    return true;
}

void block_store_release(block_store_t *const bs, const size_t block_id)
{
    // Assert valid parameters
    if(bs == NULL || (int)block_id < 0 || block_id > BLOCK_STORE_AVAIL_BLOCKS -1 ) return;
    // Free the desired block in the bitmap
    bitmap_reset(bs->bitmap, block_id);
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
    // Simply return the number of available user-addressable blocks
    return BLOCK_STORE_AVAIL_BLOCKS;
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