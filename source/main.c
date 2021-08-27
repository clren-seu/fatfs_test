#include <stdio.h>

#include "ff.h"
#include "diskio.h"

static FATFS fatfs;
extern char buf[1024 *1024 * 512];

PARTITION VolToPart[FF_VOLUMES] = {
	{0, 1},    /* "0:" ==> 1st partition in PD#0 */
	{0, 2},    /* "1:" ==> 2nd partition in PD#0 */
	{1, 0}	   /* "2:" ==> PD#1 as removable drive */
};


int main(int argc, char *argv[])
{
    FIL fil;            /* File object */
    FRESULT res;        /* API result code */
    UINT bw;            /* Bytes written */
    BYTE work[FF_MAX_SS]; /* Work area (larger is better for processing time) */

	
	LBA_t plist[] = {50, 50, 0};  /* Divide the drive into two partitions */
				 /* {0x10000000, 100}; 256M sectors for 1st partition and left all for 2nd partition */
				 /* {20, 20, 20, 0}; 20% for 3 partitions each and remaing space is left not allocated */

	res = f_fdisk(0, plist, work);                    /* Divide physical drive 0 */
	if (FR_OK != res) {
		printf("f_fdisk error: %d\n", res);
		return -1;
	}
    /* Format the default drive with default parameters */
   /* res = f_mkfs("", 0, work, sizeof(work));
	if (RES_OK != res) {
		printf("f_mkfs res: %d\n", res);
		return -1;
	}*/

	res = f_mkfs("0:", 0, work, sizeof(work)); /* Create FAT volume on the logical drive 0 */
	if (FR_OK != res) {
		printf("f_mkfs 0 error: %d\n", res);
		return -1;
	}
    res = f_mkfs("1:", 0, work, sizeof(work)); /* Create FAT volume on the logical drive 1 */
	if (FR_OK != res) {
		printf("f_mkfs 1 error: %d\n", res);
		return -1;
	}

    /* Give a work area to the default drive */
    if (f_mount(&fatfs, "0:", 0) != 0) {
		printf("f_mount error\n");
	}

    /* Create a file as new */
    res = f_open(&fil, "hello.txt", FA_CREATE_NEW | FA_WRITE | FA_READ);
    if (RES_OK != res) {
		printf("f_open res: %d\n", res);
		return -1;
	}

    /* Write a message */
    f_write(&fil, "Hello, World!\r\n", 15, &bw);

	f_lseek(&fil, 0);

	f_read(&fil, buf, 15, &bw);
	printf("%s, %d\n", buf, bw);

    /* Close the file */
    f_close(&fil);

    /* Unregister work area */
    f_mount(0, "", 0);
/*
	FILE *fp;
	fp = fopen("fs.tx", "w");
	for (int i = 0; i < sizeof(buf); i++) {
		fprintf(fp, "%08x: ", i);
		for (int j = 0; j < 16; j++) {
			fprintf(fp, "%02x ", buf[i]);
		}
		fprintf(fp, "\n");
	}

	fclose(fp);*/
	return 0;
}
