#include <stdio.h>
#include "wrapper.h"

#define DATASIZE 10

int main(int argc, char *argv[])
{
  unsigned char *data;
  int histogram[256] = {0, };
  int i, fsize;
  int datafd, histfd;
  struct stat file_stat;

  if (argc != 3){
    fprintf(stderr, "format: %s data.dat histo.dat\n", argv[0]);
    exit(-1);
  }
  datafd = Open(argv[1], O_RDONLY);
  
  // fsize <- get size of file 'datafd'
  if (fstat(datafd, &file_stat) < 0) {
	  perror("fstat error");
	  exit(-1);
  }
  fsize = file_stat.st_size;
  
  // allocate space for data
  data = (unsigned char *)malloc(fsize);
  if (data == NULL) {
	  perror("malloc error");
	  exit(-1);
  }

  // read data in file datafd and store them into data
  if (read(datafd, data, fsize) != fsize) {
	  perror("read error");
	  exit(-1);
  }
  close(datafd);

  histfd = Creat(argv[2], 0666); 
  
  // compute histogram of datafs into array histogram[]
  for (i = 0; i < fsize; i++) {
	 histogram[data[i]]++;
  } 

  write(histfd, histogram, sizeof(histogram));
  close(histfd);
  free(data);
  return 0;
}
  
