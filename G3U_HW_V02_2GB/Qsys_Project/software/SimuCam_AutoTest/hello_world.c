/*
 * "Hello World" example.
 *
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example
 * designs. It runs with or without the MicroC/OS-II RTOS and requires a STDOUT
 * device in your system's hardware.
 * The memory footprint of this hosted application is ~69 kbytes by default
 * using the standard reference design.
 *
 * For a reduced footprint version of this template, and an explanation of how
 * to reduce the memory footprint for a given application, see the
 * "small_hello_world" template.
 *
 */

#include "simucam_definitions.h"
#include "utils/initialization_simucam.h"

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
		fprintf(fp, "Main entry point.\n");
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

	while (1){}

//	/* Test of some critical IPCores HW interfaces in the Simucam */
//	if (!bTestSimucamCriticalHW()) {
//		if (T_simucam.T_conf.usiDebugLevels <= xCritical) {
//			fprintf(fp, "CRITICAL HW FAILURE: SimuCam will be halted.\n");
//			fprintf(fp, "\n");
//		}
//		while (1) {
//		}
//	}
//
//	/* Initialization and Test of basic HW */
//	vInitSimucamBasicHW();
//	bTestSimucamBasicHW();
//
//	/* Initialize SD Card */
//	bInitializeSDCard();
//
//	/* Load DEBUG Configurations from SD Card */
//	bLoadDefaultDebugConf();
//
//	/* Load RMAP Configurations from SD Card */
//	bLoadDefaultRmapConf();
//
//	/* Load ETH Configurations from SD Card */
//	bLoadDefaultEthConf();
//
//	/* Show loaded configurations from SD Card */
//#if DEBUG_ON
//	if (xConfDebug.usiDebugLevel <= xMajor) {
//		vShowDebugConfig();
//		vShowRmapConfig();
//		vShowEthConfig();
//	}
//#endif
//
//	/* Clear the RTOS timer */
//	OSTimeSet(0);
//
//#if DEBUG_ON
//	if (xConfDebug.usiDebugLevel <= xMajor) {
//		fprintf(fp, "\nSimucam Tasks initializing\n");
//	}
//#endif
//
//	/*
//	 * Create os data structures
//	 */
//	SimucamCreateOSQ();
//	DataCreateOSQ();
//
//	/*create the sub-units data structures*/
//	sub_unit_create_os_data_structs();
//
//	/* create the Simucam tasks */
//	SimucamCreateTasks();
//
//	/*
//	 * Start the OS
//	 */
//	OSStart();
//
//	while (1)
//		; /* Correct Program Flow never gets here. */

  return 0;
}
