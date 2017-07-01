#ifndef H_MPIIO_UTIL
#define H_MPIIO_UTIL
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>

#include <mpi.h>
#include "io_rdtsc.h"
#include "io_util.h"

extern char rstFilename[kMaxPathLen];
extern char mFilename[kMaxPathLen];
extern char rbFilename[kMaxPathLen];
extern char rbasciiFilename[kMaxPathLen];
extern char rbnmmFilename[kMaxPathLen];
extern char nmFilename[kMaxPathLen];

extern char* mfBuffer;
extern long long mfBufferCur ;
extern long long mfileCur ;
extern long long fieldSizeSum ;

extern int myrank, mysize;
extern int mySpecies, localsize, groupRank, numGroups;
extern MPI_Comm localcomm;

extern double io_time;
extern double overall_time;
extern double file_io_time;

void getfilename_(int *id, int *nid, int io_option);

#ifdef UPCASE
void SET_ASCII_TRUE ();
#elif  IBM
void set_ascii_true ();
#else
void set_ascii_true_();
#endif

#ifdef UPCASE
void SET_ASCII_NMM ();
#elif  IBM
void set_ascii_nmm ();
#else
void set_ascii_nmm_();
#endif

#ifdef UPCASE
void SET_ASCII_NM ();
#elif  IBM
void set_ascii_nm ();
#else
void set_ascii_nm_();
#endif

// define file structure to pass to IO thread
typedef struct file_s {
	pthread_t pthread;
	pthread_attr_t thread_attr;
	pthread_mutex_t mutex;
	pthread_mutexattr_t mutex_attr;
	pthread_cond_t	cond;

	MPI_File* pmfile; // pointer to file descriptor
//	long long* pmfileCur; // pointer to file current position
	char* pwriterBuffer; // pointer to write buffer
	long long llwriterBufferCur; // pointer to write buffer current position
} file_t;
// following for rbIO_nekcem.c
void init_file_struc();
void reset_file_struc();
void free_file_struc(file_t* file);
void run_io_thread(file_t* file);


#endif
