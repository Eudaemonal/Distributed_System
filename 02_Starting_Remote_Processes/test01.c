#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>


/* Usage: rstart [OPTION]... EXECUTABLE-FILE NODE-OPTION...
*
*  -H HOSTFILE list of host names
*  -h          this usage message
*  -n N        fork N node processes
*  -v          print version information
*
*
* Forks N copies (one copy if -n not given) of
* EXECUTABLE-FILE.  The NODE-OPTIONs are passed as arguments to the node
* processes.  The hosts on which node processes are started are given in
* HOSTFILE, which defaults to `hosts'.  If the file does not exist,
* `localhost' is used.
*/
#define LOCALHOST "localhost"


void printUseage(){
	printf("Usage: rstart [OPTION]... EXECUTABLE-FILE NODE-OPTION...\n");
	printf("-H HOSTFILE list of host names\n");
	printf("-h          this usage message\n");
	printf("-n N        fork N node processes\n");
	printf("-v          print version information\n");
}

void rstart(){
	return;
}




int main(int argc, char* argv[]){
	
	char *host_file = NULL;
	char *log_file = NULL;
	char *executable_file = NULL;
	int n_processes = 1;
	char **clnt_program_options = NULL;
	int n_clnt_program_option = 0;
	
	int c; // used to read output of `getopt`
	while ((c = getopt (argc, argv, "vhn:H:")) != -1) {
		switch (c) {
			case 'v':
				printf("Version 1.0.0\n");
				return 0;
			case 'h':
				printUseage();
				return 0;
			case 'n':
				n_processes = atoi(optarg);
				if (n_processes < 1) {
					printf("Wrong input for N\n");
					return 1;
				}
				break;
			case 'H':
				host_file = optarg;
				break;
			default:
				printUseage();

		}
	}
	
	if (argv[optind] == NULL) {
		printf("EXECUTABLE-FILE is missing\n");
		return 1;
	}
	executable_file = argv[optind];

	if (argv[optind + 1] != NULL) {
		int index = optind + 1;
		clnt_program_options = &argv[index];
		n_clnt_program_option = argc - index;
	}
	
	// use default host_file name
	if (host_file == NULL) {
		host_file = "hosts";
	}
	if (access(host_file, F_OK) == -1) {
		host_file = LOCALHOST;
	}
}
