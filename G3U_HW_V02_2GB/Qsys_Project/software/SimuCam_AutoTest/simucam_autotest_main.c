/*
 *  Main File for the SimuCam AutoTest application
 *
 */

#include "simucam_definitions.h"
#include "utils/initialization_simucam.h"
#include "test/de4/ddr2_mem_test.h"

/* Declaring file for JTAG debug */
#if DEBUG_ON
FILE* fp;
#endif

int main()
{
	/* Debug device initialization - JTAG USB */
#if DEBUG_ON
	fp = fopen(JTAG_UART_0_NAME, "r+");
#endif

#if DEBUG_ON
	fprintf(fp, "\nMain entry point.\n");
#endif

	/* Initialization of core HW */
	if (bInitSimucamCoreHW()) {
#if DEBUG_ON
		fprintf(fp, "\n");
		fprintf(fp, "SimuCam Release: %s\n", SIMUCAM_RELEASE);
		fprintf(fp, "SimuCam HW Version: %s.%s\n", SIMUCAM_RELEASE, SIMUCAM_HW_VERSION);
		fprintf(fp, "SimuCam FW Version: %s.%s.%s\n", SIMUCAM_RELEASE, SIMUCAM_HW_VERSION, SIMUCAM_FW_VERSION);
		fprintf(fp, "\n");
#endif
	} else {
#if DEBUG_ON
		fprintf(fp, "\n");
		fprintf(fp, "CRITICAL HW FAILURE: Hardware TimeStamp or System ID does not match the expected! SimuCam will be halted.\n");
		fprintf(fp, "CRITICAL HW FAILURE: Expected HW release: %s.%s\n", SIMUCAM_RELEASE, SIMUCAM_HW_VERSION);
		fprintf(fp, "CRITICAL HW FAILURE: SimuCam will be halted.\n");
		fprintf(fp, "\n");
#endif
		while (1) {
		}
	}

	char strUserInput[20];
	int iComponentSelect = 0;

	/* main infinite loop */
	while (1){

		printf("------------------------------------------------------------------------------------------------\n");
		printf("----------------------------------- SimuCam HW Testing Suite -----------------------------------\n");
		printf("------------------------------------------------------------------------------------------------\n");
		printf("\n");

		printf("  1) DE4 DDR2 Memories\n");

		printf("\n");
		printf("------------------------------------------------------------------------------------------------\n");
		printf("\n");

		printf("Select a component to test:");
		scanf("%s", strUserInput);
		printf("\n");

		/* Do not use 0 as possible input, it is the error value of the conversion function */
		iComponentSelect = atoi((const char *)strUserInput);
		switch (iComponentSelect) {

			case 0: /* Error */
				printf("The input [%s] is not a number or a parsing error occurred!\n", strUserInput);
				break;

			case 1: /* DE4 DDR2 Memories */
				vDe4Ddr2MemTestMenu();
				break;

			default: /* Invalid Option */
				printf("The selected component [%i] does not exist, enter a valid component!\n", iComponentSelect);

		}

		printf("\n");
		printf("Input any key to continue...");
		scanf("%s", strUserInput);
		printf("\n");

	}

	/* Correct Program Flow never gets here. */

	return 0;
}
