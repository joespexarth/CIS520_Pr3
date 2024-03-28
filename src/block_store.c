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
    blockStore->bitmap = bitmap_overlay(BITMAP_SIZE_BYTES * 8, (blockStore->data[127]));
    blockStore->bitmap = bitmap_overlay(BITMAP_SIZE_BYTES * 8, (blockStore->data[128]));

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
    if (!block_store_request(blockStore, 128))
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
    if(bs == NULL || (int)block_id < 0 || block_id > BLOCK_STORE_AVAIL_BLOCKS) return false;
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
    // Assert valid parameters
    if(bs == NULL) return SIZE_MAX;
    // Get the total number of bits set
    size_t n = bitmap_total_set(bs->bitmap);
    // Assert logical value
    if(n <= 0 || n > BLOCK_STORE_NUM_BLOCKS) return SIZE_MAX;
    // Return n - 1 as one block is used by the bitmap and not by the user, this method tells the user how many blocks they are using (Im assuming from test cases)
    return n;
}

size_t block_store_get_free_blocks(const block_store_t *const bs)
{
    // Assert valid parameters
    if(bs == NULL) return SIZE_MAX;
    // Get the total number of bits set
    size_t n = bitmap_total_set(bs->bitmap);
    // Assert logical value
    if(n <= 0 || n > BLOCK_STORE_NUM_BLOCKS) return SIZE_MAX;
    return (BITMAP_SIZE_BYTES * 8 ) - n;
}

size_t block_store_get_total_blocks()
{
    // Simply return the number of available user-addressable blocks
    return BLOCK_STORE_NUM_BLOCKS;
}

size_t block_store_read(const block_store_t *const bs, const size_t block_id, void *buffer)
{
    // Assert valid parameters
    if (bs == NULL || buffer == NULL || (int)block_id < 0 || block_id > BLOCK_STORE_AVAIL_BLOCKS - 1)  return 0;

    // Copy the data from the block store to the buffer
    memcpy(buffer, bs->data[block_id], BLOCK_SIZE_BYTES);

    // Return the number of bytes read
    return BLOCK_SIZE_BYTES;
}

size_t block_store_write(block_store_t *const bs, const size_t block_id, const void *buffer)
{
    // Assert valid parameters
    if (bs == NULL || buffer == NULL || (int)block_id < 0 || block_id > BLOCK_STORE_AVAIL_BLOCKS - 1)  return 0;

    // Copy the data from the block store to the buffer
    memcpy(bs->data[block_id], buffer, BLOCK_SIZE_BYTES);

    // Return the number of bytes read
    return BLOCK_SIZE_BYTES;
}

block_store_t *block_store_deserialize(const char *const filename)
{
    if(filename == NULL) return NULL;
    FILE *file = fopen(filename, "rb");
    if(file == NULL) {
        return NULL;
    }
    block_store_t *bs = (block_store_t*)malloc(sizeof(block_store_t));
    // Read the data from the file into the block store
    size_t num_read = fread(bs->data, 1, BLOCK_STORE_NUM_BLOCKS * BLOCK_SIZE_BYTES, file);
    fclose(file);

    if(num_read != BLOCK_STORE_NUM_BLOCKS * BLOCK_SIZE_BYTES) {
        free(bs); 
        return NULL;
    }

    bs->bitmap = bitmap_overlay(BITMAP_SIZE_BYTES * 8, bs->data[127]);
    bs->bitmap = bitmap_overlay(BITMAP_SIZE_BYTES * 8, bs->data[128]);

    return bs;
}

size_t block_store_serialize(const block_store_t *const bs, const char *const filename)
{
    // Assert valid parameters
    if(bs == NULL || filename == NULL) return 0;

    // Trys to open file write binary
    FILE *file = fopen(filename, "wb");

    // Assert file opened
    if(file != NULL){

        // Writes bs->data array to the file
        int num = fwrite(bs->data, 1, BLOCK_STORE_NUM_BLOCKS * BLOCK_SIZE_BYTES, file);

        // Closes file
        fclose(file);

        // Assert correct amount of elements have been written 
        if(num == -1){
            return 0;
        }
        return num;
    }
    return 0;
}