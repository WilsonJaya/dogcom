#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "configparse.h"
#include "auth.h"

#define VERSION "1.1.1"

void print_help(int exval);

int main(int argc, char *argv[]) {
    if (argc == 1) {
        print_help(1);
    }

    char *file_path;

    while (1) {
        static const struct option long_options[] = {
            { "mode", required_argument, 0, 'm' },
            { "conf", required_argument, 0, 'c' },
            { "log", required_argument, 0, 'l' },
            { "verbose", no_argument, 0, 'v' },
            { "help", no_argument, 0, 'h' },
            { 0, 0, 0, 0 }
        };

        int c;
        int option_index = 0;
        c = getopt_long(argc, argv, "m:c:l:vh", long_options, &option_index);
        
        if (c == -1) {
            break;
        }
        switch (c) {
            case 'm':
                if (strcmp(optarg, "dhcp") == 0) {
                    mode = strdup(optarg);
                } else if (strcmp(optarg, "pppoe") == 0) {
                    mode = strdup(optarg);
                } else {
                    printf("unknown mode\n");
                    exit(1);
                }
                break;
            case 'c':
                if (mode != NULL) {
                    file_path = optarg;
                };
                break;
            case 'l':
                if (mode != NULL) {
                    log_path = optarg;
                    logging_flag = 1;
                }
                break;
            case 'v':
                verbose_flag = 1;
                break;
            case 'h':
                print_help(0);
                break;
            case '?':
                print_help(1);
                break;
            default:
                break;
        }
    }

    if (mode != NULL && file_path != NULL) {
        if (!config_parse(file_path, mode)) {
            dogcom(5, mode);
        } else {
            return 1;
        }
    } else {
        printf("Need more options!\n\n");
        return 1;
    }
    return 0;
}

void print_help(int exval) {
    printf("\nDrcom-generic implementation in C.\n");
    printf("Version: %s\n\n", VERSION);

    printf("Usage:\n");
    printf("\tdogcom -m <dhcp/pppoe> -c <FILEPATH> [options <argument>]...\n\n");

    printf("Options:\n");
    printf("\t--mode <dhcp/pppoe>, -m <dhcp/pppoe>  set your dogcom mode \n");
    printf("\t--conf <FILEPATH>, -c <FILEPATH>      import configuration file\n");
    printf("\t--log <LOGPATH>, -l <LOGPATH>         specify log file\n");
    printf("\t--verbose, -v                         set verbose flag\n");
    printf("\t--help, -h                            display this help\n\n");
    exit(exval);
}