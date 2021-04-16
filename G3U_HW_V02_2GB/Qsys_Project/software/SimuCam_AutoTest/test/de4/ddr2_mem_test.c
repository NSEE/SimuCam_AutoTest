/*
 * ddr2_mem_test.c
 *
 *  Created on: 15 de abr de 2021
 *      Author: rfranca
 */

#include "ddr2_mem_test.h"

//! [private function prototypes]
//! [private function prototypes]

//! [data memory public global variables]
//! [data memory public global variables]

//! [program memory public global variables]
//! [program memory public global variables]

//! [data memory private global variables]
//! [data memory private global variables]

//! [program memory private global variables]
//! [program memory private global variables]

//! [public functions]

void vDe4Ddr2MemTestMenu( void ) {

	char strUserInput[20];
	int iTestSelect = 0;

	printf("------------------------------------------------------------------------------------------------\n");
	printf("--------------------------------- DE4 DDR2 Memories Test Menu ----------------------------------\n");
	printf("------------------------------------------------------------------------------------------------\n");
	printf("\n");

	printf("1) Test DE4 DDR2 Memory 1\n");
	printf("2) Test DE4 DDR2 Memory 2\n");
	printf("3) Test both DE4 DDR2 Memories\n");

	printf("\n");
	printf("    Make sure there is a compatible DDR2 Memory in the slot to be tested\n");

	printf("\n");
	printf("------------------------------------------------------------------------------------------------\n");
	printf("\n");

	printf("Select a test: ");
	scanf("%s", strUserInput);
	printf("\n");

	iTestSelect = atoi((const char *)strUserInput);
	switch (iTestSelect) {

		case 0: /* Error */
			printf("The input [%s] is not a number or a parsing error occurred!\n", strUserInput);
			break;

		case 1: /* Test DE4 DDR2 Memory 1 */
			printf("Testing DE4 DDR2 Memory 1...\n");
			/* perform test */
			if (bDe4Ddr2MemZeroFill(eDdr2Memory1)) {
				/* test successful */
				printf("DE4 DDR2 Memory 1 test successful!\n");
			} else {
				/* test failure */
				printf("DE4 DDR2 Memory 1 test failure!\n");
			}
			break;

		case 2: /* Test DE4 DDR2 Memory 2 */
			printf("Testing DE4 DDR2 Memory 2...\n");
			/* perform test */
			if (bDe4Ddr2MemZeroFill(eDdr2Memory2)) {
				/* test successful */
				printf("DE4 DDR2 Memory 2 test successful!\n");
			} else {
				/* test failure */
				printf("DE4 DDR2 Memory 2 test failure!\n");
			}
			break;

		case 3: /* Test both DE4 DDR2 Memories */
			printf("Testing both DE4 DDR2 Memories...\n");
			/* perform tests */
			if (bDe4Ddr2MemZeroFill(eDdr2Memory1)) {
				/* test successful */
				printf("DE4 DDR2 Memory 1 test successful!\n");
			} else {
				/* test failure */
				printf("DE4 DDR2 Memory 1 test failure!\n");
			}
			if (bDe4Ddr2MemZeroFill(eDdr2Memory2)) {
				/* test successful */
				printf("DE4 DDR2 Memory 2 test successful!\n");
			} else {
				/* test failure */
				printf("DE4 DDR2 Memory 2 test failure!\n");
			}
			break;

		default: /* Invalid Option */
			printf("The selected test [%i] does not exist, enter a valid test!\n", iTestSelect);

	}

}

//! [public functions]

bool bDe4Ddr2MemZeroFill( alt_u8 Ddr2MemID ) {
	bool bSuccess = FALSE;

	const alt_u32 uliMemData[8] = {
			0x00000000, 0x00000000, 0x00000000, 0x00000000,
			0x00000000, 0x00000000, 0x00000000, 0x00000000
	};

	/* Check if the DDR2 Memory ID is valid */
	if (Ddr2MemID <= eDdr2Memory2) {

		bMfilSetWrData(uliMemData);

		bMfilResetDma(TRUE);

		/* DDR2 Memory Zero Fill */

		if (bMfilDmaTransfer(Ddr2MemID, (alt_u32 *)0x00000000, DDR2_M1_MEMORY_SIZE)) {
			while ( ( TRUE == bMfilGetWrBusy() ) && ( FALSE == bMfilGetWrTimeoutErr() ) ) {
				usleep(100);
			}
			if ( FALSE == bMfilGetWrTimeoutErr() ) {
				bSuccess = TRUE;
			}
		}

		bMfilResetDma(TRUE);

	}

	return (bSuccess);
}

//! [private functions]
//! [private functions]

