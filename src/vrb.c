/* Self header */
#include "../include/vrb.h"

/* C library */
#include <assert.h>
#include <stdint.h>

/* Os libraries */
#include <windows.h>

/**
 * @see https://stackoverflow.com/questions/1016888/windows-ring-buffer-without-copying
 * @param vrb
 * @param size
 * @param name
 * @return
 */
vrb_p vrb_init_opt(vrb_p vrb, size_t size, const char *name, int options) {
	(void) name;
	(void) options;

	/* Ensure size doesn't exceed implementation limit */
	if (size > UINT32_MAX / 2) {
		errno = -EINVAL;
		return NULL;
	}

	/* Ensure size if a multiple of the allocation granularity */
	SYSTEM_INFO info;
	GetSystemInfo(&info);
	if (size % info.dwAllocationGranularity > 0) {
		errno = -EINVAL;
		return NULL;
	}

	/* If vrb is null, allocate space for the new structure */
	uint8_t is_allocated = 0;
	if (vrb == NULL) {
		vrb_p vrb = malloc(sizeof(struct vrb));
		if (vrb == NULL) {
			errno = -ENOMEM;
			return NULL;
		}
		is_allocated = 1;
	}

	/* Step 1 */
	HANDLE hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, (uint32_t) (size * 2), "");
	if (hMapFile == NULL) {
		if (is_allocated) free(vrb);
		errno = -ENOMEM;
		return NULL;
	}

	/* Step 2 */
	LPVOID addr0 = VirtualAlloc(NULL, (uint32_t) (size * 2), MEM_RESERVE, PAGE_READWRITE);
	if (addr0 == NULL) {
		if (is_allocated) free(vrb);
		CloseHandle(hMapFile);
		errno = -ENOMEM;
		return NULL;
	}

	/* Step 3 */
	LPVOID addr1 = MapViewOfFileEx(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, (uint32_t) (size), (LPVOID) (addr0));
	if (addr1 == NULL) {
		if (is_allocated) free(vrb);
		CloseHandle(hMapFile);
		VirtualFree(addr0, 0, MEM_RELEASE);
		errno = -ENOMEM;
		return NULL;
	}

	/* Step 4 */
	LPVOID addr2 = MapViewOfFileEx(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, (uint32_t) (size), (LPVOID) ((char *) addr0 + size));
	if (addr2 == NULL) {
		if (is_allocated) free(vrb);
		CloseHandle(hMapFile);
		VirtualFree(addr0, 0, MEM_RELEASE);
		UnmapViewOfFile(addr1);
		errno = -ENOMEM;
		return NULL;
	}

	/* Return pointer on success */
	return vrb;
}
