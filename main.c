/*
	Given an HFS ID and the volume mount point that the FS is mounted on, return a full path 
	and file name that is identified by the HFS ID.

	Matt Stofko <matt@mjslabs.com>
*/

/*
COPYRIGHT & LICENSE

Copyright 2006 Matt Stofko

This program is free software; you can redistribute it and/or
modify it under the terms of either:

* the GNU General Public License as published by the Free
Software Foundation; either version 1, or (at your option) any
later version, or

* the Artistic License version 2.0.

*/

#include <stdio.h>
#include <Carbon/Carbon.h>

int main (int argc, const char *argv[]) {
	SInt32 fileID;
	FSRef ref, volRef;
	FSCatalogInfo volCatInfo;
	OSErr result;
	unsigned char pathName[255];

	// Exit if anything more or less than two arguments are passed in
	if (argc != 3) {
		printf("Usage: %s <HFS ID> <volume mount point>\n", argv[0]);
		return 0;
	}

	result = FSPathMakeRef(argv[2], &volRef, NULL);
	if (result != noErr) {
		printf("Error %d\n", result);
		return 10;
	}
	result = FSGetCatalogInfo(&volRef, kFSCatInfoVolume, &volCatInfo, NULL, NULL, NULL);
	if (result != noErr) {
		printf("Error %d\n", result);
		return 10;
	}

	fileID = atoi(argv[1]);
	result = FSResolveFileIDRef(volCatInfo.volume, fileID, &ref);
	if (result != noErr) {
		printf("Error %d\n", result);
		return 10;
	}
	result = FSRefMakePath(&ref, pathName, sizeof(pathName));
	if (result != noErr) {
		printf("Error %d\n", result);
		return 10;
	}

	printf("%s\n", pathName);
	return 0;
}