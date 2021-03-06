/*
 * test_module_simucam.c
 *
 *  Created on: 21/10/2018
 *      Author: TiagoLow
 */

#include "test_module_simucam.h"

bool bDdr2MemoryFastTest(void);
bool bDdr2MemoryZeroFill(void);

bool bTestSimucamCriticalHW(void) {
	bool bSuccess;

	bSuccess = bIdmaInitCh1Dma();
	if ( FALSE == bSuccess) {
#if DEBUG_ON
		fprintf(fp, "SimuCam Critical HW Test: CRITICAL! Could not initiate the DMA for DCOM Channel 1!\n");
#endif
		return (bSuccess);
	} else {
#if DEBUG_ON
		fprintf(fp, "SimuCam Critical HW Test: DMA for DCOM Channel 1 initiated.\n");
#endif
	}

	bSuccess = bIdmaInitCh2Dma();
	if ( FALSE == bSuccess) {
#if DEBUG_ON
		fprintf(fp, "SimuCam Critical HW Test: CRITICAL! Could not initiate the DMA for DCOM Channel 2!\n");
#endif
		return (bSuccess);
	} else {
#if DEBUG_ON
		fprintf(fp, "SimuCam Critical HW Test: DMA for DCOM Channel 2 initiated.\n");
#endif
	}

	bSuccess = bIdmaInitCh3Dma();
	if ( FALSE == bSuccess) {
#if DEBUG_ON
		fprintf(fp, "SimuCam Critical HW Test: CRITICAL! Could not initiate the DMA for DCOM Channel 3!\n");
#endif
		return (bSuccess);
	} else {
#if DEBUG_ON
		fprintf(fp, "SimuCam Critical HW Test: DMA for DCOM Channel 3 initiated.\n");
#endif
	}

	bSuccess = bIdmaInitCh4Dma();
	if ( FALSE == bSuccess) {
#if DEBUG_ON
		fprintf(fp, "SimuCam Critical HW Test: CRITICAL! Could not initiate the DMA for DCOM Channel 4!\n");
#endif
		return (bSuccess);
	} else {
#if DEBUG_ON
		fprintf(fp, "SimuCam Critical HW Test: DMA for DCOM Channel 4 initiated.\n");
#endif
	}

	bSuccess = bIdmaInitCh5Dma();
	if ( FALSE == bSuccess) {
#if DEBUG_ON
		fprintf(fp, "SimuCam Critical HW Test: CRITICAL! Could not initiate the DMA for DCOM Channel 5!\n");
#endif
		return (bSuccess);
	} else {
#if DEBUG_ON
		fprintf(fp, "SimuCam Critical HW Test: DMA for DCOM Channel 5 initiated.\n");
#endif
	}

	bSuccess = bIdmaInitCh6Dma();
	if ( FALSE == bSuccess) {
#if DEBUG_ON
		fprintf(fp, "SimuCam Critical HW Test: CRITICAL! Could not initiate the DMA for DCOM Channel 6!\n");
#endif
		return (bSuccess);
	} else {
#if DEBUG_ON
		fprintf(fp, "SimuCam Critical HW Test: DMA for DCOM Channel 6 initiated.\n");
#endif
	}

	bSuccess = bIdmaInitCh7Dma();
	if ( FALSE == bSuccess) {
#if DEBUG_ON
		fprintf(fp, "SimuCam Critical HW Test: CRITICAL! Could not initiate the DMA for DCOM Channel 7!\n");
#endif
		return (bSuccess);
	} else {
#if DEBUG_ON
		fprintf(fp, "SimuCam Critical HW Test: DMA for DCOM Channel 7 initiated.\n");
#endif
	}

	bSuccess = bIdmaInitCh8Dma();
	if ( FALSE == bSuccess) {
#if DEBUG_ON
		fprintf(fp, "SimuCam Critical HW Test: CRITICAL! Could not initiate the DMA for DCOM Channel 8!\n");
#endif
		return (bSuccess);
	} else {
#if DEBUG_ON
		fprintf(fp, "SimuCam Critical HW Test: DMA for DCOM Channel 8 initiated.\n");
#endif
	}

//	bDdr2MemoryFastTest();

	bSuccess = bDdr2MemoryZeroFill();
	if ( FALSE == bSuccess) {
		return (bSuccess);
	}

	return (TRUE);
}

bool bTestSimucamBasicHW(void) {
	bool bSuccess;

#if DEBUG_ON
	fprintf(fp, "SimuCam Basic HW Test:\n");
#endif

	/* Sync Connection Test */

	/* Enable Isolator Board */
	bEnableIsoDrivers();

	/* Test Sync Connections */
	bSuccess = bSyncTestConnection();

	/* Disable Isolator  Board */
	bDisableIsoDrivers();

	if ( FALSE == bSuccess) {
#if DEBUG_ON
		fprintf(fp, "  WARNING! Sync connection test failed! Problem with the internal Sync connections or no Sync cable in loopback \n");
#endif
//		return (bSuccess);
	} else {
#if DEBUG_ON
		fprintf(fp, "  Sync connection test successful.\n");
#endif
	}

	return (bSuccess);
}

bool bDdr2MemoryFastTest(void) {
	bool bSuccess = FALSE;
	bool bM1Success = FALSE;
	bool bM2Success = FALSE;
	volatile alt_u32 *vpuliDdrMemAddr = NULL;

	/* Write data into ddr2 memory 1 and ddr2 memory 2 to check if they are working*/

	/* Ddr2 Memory 1 */
#if DEBUG_ON
	fprintf(fp, "SimuCam Critical HW Test: Testing DDR2 Memory 1... ");
#endif
	usleep(1000000);
	bDdr2SwitchMemory(DDR2_M1_ID);
	bSuccess = TRUE;
	vRstcHoldSimucamReset(0); /* Hold SimuCam Reset Signal - Enable "Watchdog" (t = 1000 ms) */
	vpuliDdrMemAddr = (alt_u32 *) 0x00000000;
	*vpuliDdrMemAddr = (alt_u32) 0xAAAAAAAA;
	if (*vpuliDdrMemAddr != (alt_u32) 0xAAAAAAAA) {
		bSuccess = FALSE;
	}
	vpuliDdrMemAddr = (alt_u32 *) 0x0FFFFFFF;
	*vpuliDdrMemAddr = (alt_u32) 0x55555555;
	if (*vpuliDdrMemAddr != (alt_u32) 0x55555555) {
		bSuccess = FALSE;
	}
	vpuliDdrMemAddr = (alt_u32 *) 0x1FFFFFFF;
	*vpuliDdrMemAddr = (alt_u32) 0xAAAAAAAA;
	if (*vpuliDdrMemAddr != (alt_u32) 0xAAAAAAAA) {
		bSuccess = FALSE;
	}
	vpuliDdrMemAddr = (alt_u32 *) 0x2FFFFFFF;
	*vpuliDdrMemAddr = (alt_u32) 0x55555555;
	if (*vpuliDdrMemAddr != (alt_u32) 0x55555555) {
		bSuccess = FALSE;
	}
	vpuliDdrMemAddr = (alt_u32 *) 0x3FFFFFFF;
	*vpuliDdrMemAddr = (alt_u32) 0xAAAAAAAA;
	if (*vpuliDdrMemAddr != (alt_u32) 0xAAAAAAAA) {
		bSuccess = FALSE;
	}
	vpuliDdrMemAddr = (alt_u32 *) 0x4FFFFFFF;
	*vpuliDdrMemAddr = (alt_u32) 0x55555555;
	if (*vpuliDdrMemAddr != (alt_u32) 0x55555555) {
		bSuccess = FALSE;
	}
	vpuliDdrMemAddr = (alt_u32 *) 0x5FFFFFFF;
	*vpuliDdrMemAddr = (alt_u32) 0xAAAAAAAA;
	if (*vpuliDdrMemAddr != (alt_u32) 0xAAAAAAAA) {
		bSuccess = FALSE;
	}
	vpuliDdrMemAddr = (alt_u32 *) 0x6FFFFFFF;
	*vpuliDdrMemAddr = (alt_u32) 0x55555555;
	if (*vpuliDdrMemAddr != (alt_u32) 0x55555555) {
		bSuccess = FALSE;
	}
	vpuliDdrMemAddr = (alt_u32 *) 0x7FFFFFFF;
	*vpuliDdrMemAddr = (alt_u32) 0xAAAAAAAA;
	if (*vpuliDdrMemAddr != (alt_u32) 0xAAAAAAAA) {
		bSuccess = FALSE;
	}
	if (bSuccess) {
		bM1Success = TRUE;
		vRstcReleaseSimucamReset(0); /* Release SimuCam Reset Signal - Disable "Watchdog"*/
#if DEBUG_ON
		fprintf(fp, "DDR2 Memory 1 Passed!\n");
#endif
	} else {
#if DEBUG_ON
		fprintf(fp, "CRITICAL! DDR2 Memory 1 Failure!\n");
#endif
	}

	/* Ddr2 Memory 2 */
#if DEBUG_ON
	fprintf(fp, "SimuCam Critical HW Test: Testing DDR2 Memory 2... ");
#endif
	usleep(1000000);
	bDdr2SwitchMemory(DDR2_M2_ID);
	bSuccess = TRUE;
	vRstcHoldSimucamReset(0); /* Hold SimuCam Reset Signal - Enable "Watchdog" (t = 1000 ms) */
	vpuliDdrMemAddr = (alt_u32 *) 0x00000000;
	*vpuliDdrMemAddr = (alt_u32) 0xAAAAAAAA;
	if (*vpuliDdrMemAddr != (alt_u32) 0xAAAAAAAA) {
		bSuccess = FALSE;
	}
	vpuliDdrMemAddr = (alt_u32 *) 0x0FFFFFFF;
	*vpuliDdrMemAddr = (alt_u32) 0x55555555;
	if (*vpuliDdrMemAddr != (alt_u32) 0x55555555) {
		bSuccess = FALSE;
	}
	vpuliDdrMemAddr = (alt_u32 *) 0x1FFFFFFF;
	*vpuliDdrMemAddr = (alt_u32) 0xAAAAAAAA;
	if (*vpuliDdrMemAddr != (alt_u32) 0xAAAAAAAA) {
		bSuccess = FALSE;
	}
	vpuliDdrMemAddr = (alt_u32 *) 0x2FFFFFFF;
	*vpuliDdrMemAddr = (alt_u32) 0x55555555;
	if (*vpuliDdrMemAddr != (alt_u32) 0x55555555) {
		bSuccess = FALSE;
	}
	vpuliDdrMemAddr = (alt_u32 *) 0x3FFFFFFF;
	*vpuliDdrMemAddr = (alt_u32) 0xAAAAAAAA;
	if (*vpuliDdrMemAddr != (alt_u32) 0xAAAAAAAA) {
		bSuccess = FALSE;
	}
	vpuliDdrMemAddr = (alt_u32 *) 0x4FFFFFFF;
	*vpuliDdrMemAddr = (alt_u32) 0x55555555;
	if (*vpuliDdrMemAddr != (alt_u32) 0x55555555) {
		bSuccess = FALSE;
	}
	vpuliDdrMemAddr = (alt_u32 *) 0x5FFFFFFF;
	*vpuliDdrMemAddr = (alt_u32) 0xAAAAAAAA;
	if (*vpuliDdrMemAddr != (alt_u32) 0xAAAAAAAA) {
		bSuccess = FALSE;
	}
	vpuliDdrMemAddr = (alt_u32 *) 0x6FFFFFFF;
	*vpuliDdrMemAddr = (alt_u32) 0x55555555;
	if (*vpuliDdrMemAddr != (alt_u32) 0x55555555) {
		bSuccess = FALSE;
	}
	vpuliDdrMemAddr = (alt_u32 *) 0x7FFFFFFF;
	*vpuliDdrMemAddr = (alt_u32) 0xAAAAAAAA;
	if (*vpuliDdrMemAddr != (alt_u32) 0xAAAAAAAA) {
		bSuccess = FALSE;
	}
	if (bSuccess) {
		bM2Success = TRUE;
		vRstcReleaseSimucamReset(0); /* Release SimuCam Reset Signal - Disable "Watchdog"*/
#if DEBUG_ON
		fprintf(fp, "DDR2 Memory 2 Passed!\n\n");
#endif
	} else {
#if DEBUG_ON
		fprintf(fp, "CRITICAL! DDR2 Memory 2 Failure!\n\n");
#endif
	}

	bSuccess = FALSE;
	if ((bM1Success) && (bM2Success)) {
		bSuccess = TRUE;
	}

	return (bSuccess);
}

bool bDdr2MemoryZeroFill(void) {
	bool bM1Success = FALSE;
	bool bM2Success = FALSE;
	bool bSuccess = FALSE;

	const alt_u32 uliMemData[8] = {
			0x00000000, 0x00000000, 0x00000000, 0x00000000,
			0x00000000, 0x00000000, 0x00000000, 0x00000000
	};

	bMfilSetWrData(uliMemData);

	bMfilResetDma(TRUE);

	/* DDR2 Memory 1 Zero Fill */

	if (bMfilDmaTransfer(eDdr2Memory1, (alt_u32 *)0x00000000, DDR2_M1_MEMORY_SIZE)) {
		while ( ( TRUE == bMfilGetWrBusy() ) && ( FALSE == bMfilGetWrTimeoutErr() ) ) {
			usleep(100);
		}
		if ( FALSE == bMfilGetWrTimeoutErr() ) {
#if DEBUG_ON
			fprintf(fp, "  DDR2 Memory 1 Cleared!\n");
			bM1Success = TRUE;
#endif
		} else {
#if DEBUG_ON
			fprintf(fp, "  CRITICAL! DDR2 Memory 1 Failure!\n");
			return (bM1Success);
#endif
		}
	}

	bMfilResetDma(TRUE);

	/* DDR2 Memory 2 Zero Fill */

	if (bMfilDmaTransfer(eDdr2Memory2, (alt_u32 *)0x00000000, DDR2_M2_MEMORY_SIZE)) {
		while ( ( TRUE == bMfilGetWrBusy() ) && ( FALSE == bMfilGetWrTimeoutErr() ) ) {
			usleep(100);
		}
		if ( FALSE == bMfilGetWrTimeoutErr() ) {
#if DEBUG_ON
			fprintf(fp, "  DDR2 Memory 2 Cleared!\n");
			bM2Success = TRUE;
#endif
		} else {
#if DEBUG_ON
			fprintf(fp, "  CRITICAL! DDR2 Memory 2 Failure!\n");
			return (bM2Success);
#endif
		}
	}

	bMfilResetDma(TRUE);

	if ( ( TRUE == bM1Success ) && ( TRUE == bM2Success ) ) {
		bSuccess = TRUE;
	}

	return (bSuccess);
}

