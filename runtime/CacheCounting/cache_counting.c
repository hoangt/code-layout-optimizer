#include "papi/papiStdEventDefs.h"
#include "papi/papi.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


const int MAX_EVENT_SIZE=4;

int eventsize;
int *events;
long long counters[MAX_EVENT_SIZE];
long long sumcounters[MAX_EVENT_SIZE];

int inst_events[4]={PAPI_L1_ICM, PAPI_L2_ICM, PAPI_L2_ICA, PAPI_L1_ICA};
//int data_events[eventsize]={PAPI_L1_DCM, PAPI_L2_DCM, PAPI_L2_DCA};
//int accesses_events[eventsize]={PAPI_TOT_INS,PAPI_L2_ICA,PAPI_L2_DCA};
char inst_eventnames[4][6]={"L1_ICM", "L2_ICM","L2_ICA","L1_ICA"};
//char * data_eventnames[eventsize]={"L1_DCM", "L2_DCM","L2_DCA";
//char * accesses_eventnames[eventsize]={"TOT_INST","L2_ICA","L2_DCA"};

char * ccFileName;


void print_counters(void){
		FILE * ccFile = fopen("cachecount_ro.out","r");
		int i=0;
		for(;i<eventsize;++i){
				counters[i]=0;
				if(ccFile==NULL)
						sumcounters[i]=0;
				else{
						fscanf(ccFile,"%*s\t%lld\n",&sumcounters[i]);
				}
		}
		PAPI_read_counters(counters,eventsize);
		if(ccFile!=NULL)
				fclose(ccFile);

		ccFile = fopen("cachecount_ro.out","w");
		for(i=0;i<eventsize;++i){
				//printf("%lld %lld\n",counters[i], sumcounters[i]);
				long long me = counters[i];
				me += sumcounters[i];
				fprintf(ccFile,"%s\t%lld\n",inst_eventnames[i],me);
		}
		fclose(ccFile);
}

void init_cache_counters(uint8_t avail_counters){
		eventsize=avail_counters;
		atexit(print_counters);
		int retval = PAPI_library_init( PAPI_VER_CURRENT );
		if ( retval != PAPI_VER_CURRENT ) {
				fprintf(stderr,"failed.\n");
				exit(0);
		}
		PAPI_start_counters(inst_events,eventsize);
}