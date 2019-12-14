#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define UNUSED(x) (void)(x)

#define FILENAME_RED   "rawdata/img-5400x3600x8-r.bin"
#define FILENAME_GREEN "rawdata/img-5400x3600x8-g.bin"
#define FILENAME_BLUE  "rawdata/img-5400x3600x8-b.bin"
#define FILENAME_OUT   "img.bmp"

#define X_RESOLUTION 5400
#define Y_RESOLUTION 3600
#define COLOR_DEPTH 8
#define PIXEL_BIT_SIZE COLOR_DEPTH * 3
#define PIXEL_ARRAY_SIZE (X_RESOLUTION * Y_RESOLUTION * PIXEL_BIT_SIZE) / 8

#pragma pack(push,1)
typedef struct{
    uint8_t signature[2];
    uint32_t filesize;
    uint32_t reserved;
    uint32_t fileoffset_to_pixelarray;
} bitmapfileheader;

typedef struct{
    uint32_t dibheadersize;
    uint32_t width;
    uint32_t height;
    uint16_t planes;
    uint16_t bitsperpixel;
    uint32_t compression;
    uint32_t imagesize_bytes;
    uint32_t x_resolution_ppm;
    uint32_t y_resolution_ppm;
    uint32_t num_colors;
    uint32_t imp_colors;
} dibheader;

typedef struct{
	bitmapfileheader bmpfile_header;
	dibheader dib_header;
}bitmapheader;
#pragma pack(pop)

void open_files(FILE** file_red, FILE** file_green, FILE** file_blue, FILE** file_out) {
	// open rgb raw data files
	if( (*file_red = fopen(FILENAME_RED, "rb")) == NULL) {
		fprintf(stderr, "Cannot open " FILENAME_RED);
		perror(" ");
		exit(1);
	}
	
	if( (*file_green = fopen(FILENAME_GREEN, "rb")) == NULL) {
		fprintf(stderr, "Cannot open " FILENAME_GREEN);
		perror(" ");
		exit(1);
	}
	
	if( (*file_blue = fopen(FILENAME_BLUE, "rb")) == NULL) {
		fprintf(stderr, "Cannot open " FILENAME_BLUE);
		perror(" ");
		exit(1);
	}
	
	// open output file
	if( (*file_out = fopen(FILENAME_OUT, "wb")) == NULL) {
		fprintf(stderr, "Cannot open " FILENAME_OUT);
		perror(" ");
		exit(1);
	}
}

void write_header(FILE* file_out) {
	bitmapheader *bmpheader = (bitmapheader*)calloc(1,sizeof(bitmapheader));
	bmpheader->bmpfile_header.signature[0] = 'B';
	bmpheader->bmpfile_header.signature[1] = 'M';
	bmpheader->bmpfile_header.filesize = PIXEL_ARRAY_SIZE + sizeof(bitmapheader) ;
	bmpheader->bmpfile_header.fileoffset_to_pixelarray = sizeof(bitmapheader);
	bmpheader->dib_header.dibheadersize = sizeof(dibheader);
	bmpheader->dib_header.width = X_RESOLUTION;
	bmpheader->dib_header.height = Y_RESOLUTION;
	bmpheader->dib_header.planes = 1;
	bmpheader->dib_header.bitsperpixel = PIXEL_BIT_SIZE;
	bmpheader->dib_header.compression = 0;
	bmpheader->dib_header.imagesize_bytes = PIXEL_ARRAY_SIZE;
	bmpheader->dib_header.x_resolution_ppm = 0x130B;
	bmpheader->dib_header.y_resolution_ppm = 0x130B;
	bmpheader->dib_header.num_colors = 0;

	fwrite(bmpheader, 1, sizeof(bitmapheader), file_out);
	free(bmpheader);
}

void write_data(FILE* file_red, FILE* file_green, FILE* file_blue, FILE* file_out) {
	uint8_t *pixelbuffer = (uint8_t *)malloc(PIXEL_ARRAY_SIZE);
	size_t buffer_index = 0;
	
	while(buffer_index < PIXEL_ARRAY_SIZE)
	{
		pixelbuffer[buffer_index] = fgetc(file_blue);
		pixelbuffer[buffer_index+1] = fgetc(file_green);
		pixelbuffer[buffer_index+2] = fgetc(file_red);
		buffer_index += 3;
	}

	fwrite(pixelbuffer, 1,PIXEL_ARRAY_SIZE, file_out);
	free(pixelbuffer);
}

int main(int argc, char** argv) {
	UNUSED(argc);
	UNUSED(argv);
	FILE* file_red;
	FILE* file_green;
	FILE* file_blue;
	FILE* file_out;

	open_files(&file_red, &file_green, &file_blue, &file_out);
	
	write_header(file_out);
	
	write_data(file_red, file_green, file_blue, file_out);
	
	fclose(file_red);
	fclose(file_green);
	fclose(file_blue);
	fclose(file_out);
}