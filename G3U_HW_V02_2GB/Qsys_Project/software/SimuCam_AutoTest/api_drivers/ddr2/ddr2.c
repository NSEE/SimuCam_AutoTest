/**
 * @file   ddr2.c
 * @Author Rodrigo França (rodrigo.franca@maua.br | rodmarfra@gmail.com)
 * @date   Maio, 2017
 * @brief  Source File para testes e acesso as memórias DDR2 da DE4
 *
 */

#include "ddr2.h"

typedef alt_u32 TMyData;

TMyData xSZData[256];

alt_u32 uliInitialState;
alt_u32 uliXorshift32(alt_u32 *puliState);

#if DEBUG_ON
char cDebugBuffer[256];
#endif

/**
 * @name    bDdr2EepromTest
 * @brief
 * @ingroup DDR2
 *
 * Realiza teste de leitura e escrita da EEPROM da memória escolhida.
 *
 * @param [in] MemoryId  ID da mémoria a ser testada
 *
 * @retval TRUE : Sucesso
 *
 */
bool bDdr2EepromTest(alt_u8 ucMemoryId) {

#if DEBUG_ON
	fprintf(fp, "===== DE4 DDR2 EEPROM Test =====\n");
#endif
	const alt_u8 cucDeviceAddr = DDR2_EEPROM_I2C_ADDRESS;
	bool bSuccess = FALSE;
	alt_u32 uliI2cSclBase;
	alt_u32 uliI2cSdaBase;
	int iI;

	switch (ucMemoryId) {
	case DDR2_M1_ID:
		uliI2cSclBase = DDR2_M1_EEPROM_I2C_SCL_BASE;
		uliI2cSdaBase = DDR2_M1_EEPROM_I2C_SDA_BASE;
		bSuccess = TRUE;
		break;
	case DDR2_M2_ID:
		uliI2cSclBase = DDR2_M2_EEPROM_I2C_SCL_BASE;
		uliI2cSdaBase = DDR2_M2_EEPROM_I2C_SDA_BASE;
		bSuccess = TRUE;
		break;
	default:
		bSuccess = FALSE;
#if DEBUG_ON
		fprintf(fp, "DR2 Memory ID not identified!! Aborting Test \n");
#endif
		return bSuccess;
	}

	alt_u8 ucControlAddr, ucValue;
#if DEBUG_ON
	fprintf(fp, "DDR2 EEPROM Read Test\n");
#endif
	usleep(20 * 1000);
	for (iI = 0; iI < 256 && bSuccess; iI++) {
		ucControlAddr = iI;
		bSuccess = I2C_Read(uliI2cSclBase, uliI2cSdaBase, cucDeviceAddr, ucControlAddr, &ucValue);
		if (bSuccess) {
#if DEBUG_ON
			fprintf(fp, "EEPROM[%03d]=%02Xh\n", ucControlAddr, ucValue);
#endif
		} else {
#if DEBUG_ON
			fprintf(fp, "Failed to read EEPROM\n");
#endif
		}
	}
	if (bSuccess) {
#if DEBUG_ON
		fprintf(fp, "DDR2 EEPROM Read Test Completed\n\n");
#endif
	} else {
#if DEBUG_ON
		fprintf(fp, "DDR2 EEPROM Read Test Failed\n\n");
#endif
	}

#if DEBUG_ON
	fprintf(fp, "DDR2 EEPROM Write Test\n");
#endif
	alt_u8 ucWriteData = 0x12, ucTestAddr = 128;
	alt_u8 ucReadData;
	usleep(20 * 1000);
	bSuccess = I2C_Write(uliI2cSclBase, uliI2cSdaBase, cucDeviceAddr, ucTestAddr, ucWriteData);
	if (!bSuccess) {
#if DEBUG_ON
		fprintf(fp, "Failed to write EEPROM\n");
#endif
	} else {
		bSuccess = I2C_Read(uliI2cSclBase, uliI2cSdaBase, cucDeviceAddr, ucTestAddr, &ucReadData);
		if (!bSuccess) {
#if DEBUG_ON
			fprintf(fp, "Failed to read EEPROM for verify\n");
#endif
		} else {
			if (ucReadData != ucWriteData) {
				bSuccess = FALSE;
#if DEBUG_ON
				fprintf(fp, "Verify EEPROM write fail, ReadData=%02Xh, WriteData=%02Xh\n", ucReadData, ucWriteData);
#endif
			}
		}
	}
	if (bSuccess) {
#if DEBUG_ON
		fprintf(fp, "DDR2 EEPROM Write Test Completed\n\n");
#endif
	} else {
#if DEBUG_ON
		fprintf(fp, "DDR2 EEPROM Write Test Failed\n\n");
#endif
	}
#if DEBUG_ON
	fprintf(fp, "\n");
#endif

	return bSuccess;
}

/**
 * @name    bDdr2EepromDump
 * @brief
 * @ingroup DDR2
 *
 * Realiza o dump das informações da EEPROM da memória escolhida, com os nomes das informações.
 *
 * @param [in] MemoryId  ID da mémoria a ser testada
 *
 * @retval TRUE : Sucesso
 *
 */
bool bDdr2EepromDump(alt_u8 ucMemoryId) {

#if DEBUG_ON
	fprintf(fp, "===== DE4 DDR2 EEPROM Dump =====\n");
#endif
	const alt_u8 cucDeviceAddr = DDR2_EEPROM_I2C_ADDRESS;
	bool bSuccess = FALSE;
	alt_u32 uliI2cSclBase;
	alt_u32 uliI2cSdaBase;
	int iI;

	switch (ucMemoryId) {
	case DDR2_M1_ID:
		uliI2cSclBase = DDR2_M1_EEPROM_I2C_SCL_BASE;
		uliI2cSdaBase = DDR2_M1_EEPROM_I2C_SDA_BASE;
		bSuccess = TRUE;
		break;
	case DDR2_M2_ID:
		uliI2cSclBase = DDR2_M2_EEPROM_I2C_SCL_BASE;
		uliI2cSdaBase = DDR2_M2_EEPROM_I2C_SDA_BASE;
		bSuccess = TRUE;
		break;
	default:
		bSuccess = FALSE;
#if DEBUG_ON
		fprintf(fp, "DR2 Memory ID not identified!! Aborting Dump \n");
#endif
		return bSuccess;
	}

	alt_u8 ucSZData[256];
	bSuccess = I2C_MultipleRead(uliI2cSclBase, uliI2cSdaBase, cucDeviceAddr, ucSZData, sizeof(ucSZData));
	if (bSuccess) {
		for (iI = 0; iI < 256 && bSuccess; iI++) {
			if (iI == 0) {
#if DEBUG_ON
				fprintf(fp, "(Number of SPD Bytes Used)\n" "EEPROM[%03d]=%02Xh ", iI, ucSZData[iI]);

#endif
			} else if (iI == 1) {
#if DEBUG_ON
				fprintf(fp, "(Total Number of Bytes in SPD Device, Log2(N))\n");

#endif
			} else if (iI == 2) {
#if DEBUG_ON
				fprintf(fp, "(Basic Memory Type[08h:DDR2])\n");

#endif
			} else if (iI == 3) {
#if DEBUG_ON
				fprintf(fp, "(Number of Row Addresses on Assembly)\n");

#endif
			} else if (iI == 4) {
#if DEBUG_ON
				fprintf(fp, "(Number of Column Addresses on Assembly)\n");

#endif
			} else if (iI == 5) {
#if DEBUG_ON
				fprintf(fp, "(DIMM Height and Module Rank Number[b2b1b0+1])\n");

#endif
			} else if (iI == 6) {
#if DEBUG_ON
				fprintf(fp, "(Module Data Width)\n");

#endif
			} else if (iI == 7) {
#if DEBUG_ON
				fprintf(fp, "(Module Data Width, Continued)\n");

#endif
			} else if (iI == 16) {
#if DEBUG_ON
				fprintf(fp, "(Burst Lengths Supported[bitmap: x x x x 8 4 x x])\n");

#endif
			} else if (iI == 13) {
#if DEBUG_ON
				fprintf(fp, "(Primary SDRAM width)\n");

#endif
			} else if (iI == 14) {
#if DEBUG_ON
				fprintf(fp, "(ECC SDRAM width)\n");

#endif
			} else if (iI == 17) {
#if DEBUG_ON
				fprintf(fp, "(Banks per SDRAM device)\n");

#endif
			} else if (iI == 18) {
#if DEBUG_ON
				fprintf(fp, "(CAS lantencies supported[bitmap: x x 5 4 3 2 x x])\n");

#endif
			} else if (iI == 20) {
#if DEBUG_ON
				fprintf(fp, "(DIMM Type: x x Mini-UDIMM Mini-RDIMM Micro-DIMM SO-DIMM UDIMMM RDIMM)\n");

#endif
			} else if (iI == 22) {
#if DEBUG_ON
				fprintf(fp, "(Memory Chip feature bitmap)\n");

#endif
			} else if (iI == 27) {
#if DEBUG_ON
				fprintf(fp, "(Minimun row precharge time[tRP;nsx4])\n");

#endif
			} else if (iI == 28) {
#if DEBUG_ON
				fprintf(fp, "(Minimun row active-row activce delay[tRRD;nsx4])\n");

#endif
			} else if (iI == 29) {
#if DEBUG_ON
				fprintf(fp, "(Minimun RAS to CAS delay[tRCD;nsx4])\n");

#endif
			} else if (iI == 30) {
#if DEBUG_ON
				fprintf(fp, "(Minimun acive to precharge time[tRAS;ns])\n");

#endif
			} else if (iI == 31) {
#if DEBUG_ON
				fprintf(fp, "(Size of each rank[bitmap:512MB,256MB,128MB,16GB,8GB,4GB,2GB,1GB)\n");

#endif
			} else if (iI == 36) {
#if DEBUG_ON
				fprintf(fp, "(Minimun write receovery time[tWR;nsx4])\n");

#endif
			} else if (iI == 37) {
#if DEBUG_ON
				fprintf(fp, "(Internal write to read command delay[tWTR;nsx4])\n");

#endif
			} else if (iI == 38) {
#if DEBUG_ON
				fprintf(fp, "(Internal read to precharge command delay[tRTP;nsx4])\n");

#endif
			} else if (iI == 41) {
#if DEBUG_ON
				fprintf(fp, "(Minimun activce to active/refresh time[tRC;ns])\n");

#endif
			} else if (iI == 42) {
#if DEBUG_ON
				fprintf(fp, "(Minimun refresh to active/refresh time[tRFC;ns])\n");

#endif
			} else if (iI == 62) {
#if DEBUG_ON
				fprintf(fp, "(SPD Revision)\n");

#endif
			} else if (iI == 63) {
#if DEBUG_ON
				fprintf(fp, "(Checksum)\n");

#endif
			} else if (iI == 64) {
#if DEBUG_ON
				fprintf(fp, "(64~71: Manufacturer JEDEC ID)\n");

#endif
			} else if (iI == 72) {
#if DEBUG_ON
				fprintf(fp, "(Module manufacturing location[Vendor-specific code])\n");

#endif
			} else if (iI == 73) {
#if DEBUG_ON
				fprintf(fp, "(73~90: Moduloe part number)\n");

#endif
			} else if (iI == 91) {
#if DEBUG_ON
				fprintf(fp, "(91~92: Moduloe revision code)\n");

#endif
			} else if (iI == 93) {
#if DEBUG_ON
				fprintf(fp, "(Manufacture Years since 2000[0-255])\n");

#endif
			} else if (iI == 94) {
#if DEBUG_ON
				fprintf(fp, "(Manufacture Weeks[1-52])\n");

#endif
			} else if (iI == 95) {
#if DEBUG_ON
				fprintf(fp, "(95~98[4-bytes]: Module serial number)\n");

#endif
			} else if (iI == 99) {
#if DEBUG_ON
				fprintf(fp, "(99~128: Manufacturer-specific data)\n");

#endif
			} else {
#if DEBUG_ON
				fprintf(fp, "\n");

#endif
			}
		}
	} else {
#if DEBUG_ON
		fprintf(fp, "Failed to dump EEPROM\n");

#endif
	}
#if DEBUG_ON
	fprintf(fp, "\n");

#endif

	return bSuccess;
}

bool bDdr2SwitchMemory(alt_u8 ucMemoryId) {

	bool bSuccess = FALSE;
	alt_u32 *puliDdr2MemAddr = (alt_u32 *) DDR2_EXT_ADDR_CONTROL_BASE;

	switch (ucMemoryId) {
	case DDR2_M1_ID:
		*(puliDdr2MemAddr) = (alt_u32) DDR2_M1_MEMORY_WINDOWED_OFFSET;
		bSuccess = TRUE;
		break;
	case DDR2_M2_ID:
		*(puliDdr2MemAddr) = (alt_u32) DDR2_M2_MEMORY_WINDOWED_OFFSET;
		bSuccess = TRUE;
		break;
	default:
		bSuccess = FALSE;
#if DEBUG_ON
		fprintf(fp, "DR2 Memory ID not identified!! Error switching memories!! \n");
#endif
	}

	return bSuccess;
}

/**
 * @name    bDdr2MemoryWriteTest
 * @brief
 * @ingroup DDR2
 *
 * Teste de escrita na memória, baseados em um vetor de dados aleatórios.
 *
 * @param [in] MemoryId  ID da mémoria a ser testada
 *
 * @retval TRUE : Sucesso
 *
 */
bool bDdr2MemoryWriteTest(alt_u8 ucMemoryId) {

#if DEBUG_ON
	fprintf(fp, "===== DE4 DDR2 Memory Write Test =====\n");

#endif
	bool bSuccess = FALSE;
	alt_u32 uliDdr2Base;
	alt_u32 uliByteLen;

	switch (ucMemoryId) {
	case DDR2_M1_ID:
		bDdr2SwitchMemory(ucMemoryId);
		uliDdr2Base = DDR2_EXT_ADDR_WINDOWED_BASE;
		uliByteLen = DDR2_M1_MEMORY_SIZE;
		bSuccess = TRUE;
		break;
	case DDR2_M2_ID:
		bDdr2SwitchMemory(ucMemoryId);
		uliDdr2Base = DDR2_EXT_ADDR_WINDOWED_BASE;
		uliByteLen = DDR2_M2_MEMORY_SIZE;
		bSuccess = TRUE;
		break;
	default:
		bSuccess = FALSE;
#if DEBUG_ON
		fprintf(fp, "DR2 Memory ID not identified!! Aborting Test \n");
#endif
		return bSuccess;
	}

#if DEBUG_ON
	fprintf(fp, "DDR2 Size: %ld MBytes\n", uliByteLen / 1024 / 1024);

#endif

	int iI, iNRemainedLen, iNAccessLen;
	TMyData *pxDes;

	int iNItemNum, iNPos;
	const int ciMyDataSize = sizeof(TMyData);
	int iNProgressIndex = 0;
	alt_u32 uliInitValue;
	alt_u32 uliSZProgress[10];
	int iTimeStart, iTimeElapsed = 0;

	for (iI = 0; iI < 10; iI++) {
		uliSZProgress[iI] = uliByteLen / 10 * (iI + 1);
	}
	uliInitValue = alt_nticks();
	iNItemNum = sizeof(xSZData) / sizeof(xSZData[0]);
	for (iI = 0; iI < iNItemNum; iI++) {
		if (iI == 0) {
			xSZData[iI] = uliInitValue;
		} else {
			xSZData[iI] = xSZData[iI - 1] * 13;
		}
	}
	xSZData[iNItemNum - 1] = 0xAAAAAAAA;
	xSZData[iNItemNum - 2] = 0x55555555;
	xSZData[iNItemNum - 3] = 0x00000000;
	xSZData[iNItemNum - 4] = 0xFFFFFFFF;

#if DEBUG_ON
	fprintf(fp, "Writing data...\n");

#endif
	iTimeStart = alt_nticks();
	pxDes = (TMyData *) uliDdr2Base;
	iNAccessLen = sizeof(xSZData);
	iNItemNum = iNAccessLen / ciMyDataSize;
	iNPos = 0;
	while (iNPos < uliByteLen) {
		iNRemainedLen = uliByteLen - iNPos;
		if (iNAccessLen > iNRemainedLen) {
			iNAccessLen = iNRemainedLen;
			iNItemNum = iNAccessLen / ciMyDataSize;
		}
		memcpy(pxDes, xSZData, iNAccessLen);
		pxDes += iNItemNum;
		iNPos += iNAccessLen;
		if (iNProgressIndex <= 9 && iNPos >= uliSZProgress[iNProgressIndex]) {
			iNProgressIndex++;
#if DEBUG_ON
			fprintf(fp, "%02d%% ", iNProgressIndex * 10);

#endif
		}
	}
	alt_dcache_flush_all();
#if DEBUG_ON
	fprintf(fp, "\n");

#endif

	iTimeElapsed = alt_nticks() - iTimeStart;
	if (bSuccess) {
#if DEBUG_ON
		fprintf(fp, "DDR2 write test pass, size=%lu bytes, %.3f sec\n", uliByteLen, (float) iTimeElapsed / (float) alt_ticks_per_second());

#endif
	} else {
#if DEBUG_ON
		fprintf(fp, "DDR2 write test fail\n");

#endif
	}
#if DEBUG_ON
	fprintf(fp, "\n");

#endif

	return bSuccess;
}

/**
 * @name    bDdr2MemoryReadTest
 * @brief
 * @ingroup DDR2
 *
 * Teste de escrita na memória, baseados em um vetor de dados aleatórios.
 *
 * @param [in] MemoryId  ID da mémoria a ser testada
 *
 * @retval TRUE : Sucesso
 *
 */
bool bDdr2MemoryReadTest(alt_u8 ucMemoryId) {

#if DEBUG_ON
	fprintf(fp, "===== DE4 DDR2 Memory Read Test =====\n");

#endif
	bool bSuccess = FALSE;
	alt_u32 uliDdr2Base;
	alt_u32 uliByteLen;

	switch (ucMemoryId) {
	case DDR2_M1_ID:
		bDdr2SwitchMemory(ucMemoryId);
		uliDdr2Base = DDR2_EXT_ADDR_WINDOWED_BASE;
		uliByteLen = DDR2_M1_MEMORY_SIZE;
		bSuccess = TRUE;
		break;
	case DDR2_M2_ID:
		bDdr2SwitchMemory(ucMemoryId);
		uliDdr2Base = DDR2_EXT_ADDR_WINDOWED_BASE;
		uliByteLen = DDR2_M2_MEMORY_SIZE;
		bSuccess = TRUE;
		break;
	default:
		bSuccess = FALSE;
#if DEBUG_ON
		fprintf(fp, "DR2 Memory ID not identified!! Aborting Test \n");
#endif
		return bSuccess;
	}

#if DEBUG_ON
	fprintf(fp, "DDR2 Size: %lu MBytes\n", uliByteLen / 1024 / 1024);

#endif

	int iI, iNRemainedLen, iNAccessLen;
	TMyData *pxDes, *pxSrc;
	int iNItemNum, iNPos;
	iNItemNum = sizeof(xSZData) / sizeof(xSZData[0]);
	const int ciMyDataSize = sizeof(TMyData);
	iNAccessLen = iNItemNum * ciMyDataSize;
	int iNProgressIndex = 0;
	alt_u32 uliSZProgress[10];
	int iTimeStart, iTimeElapsed = 0;

	for (iI = 0; iI < 10; iI++) {
		uliSZProgress[iI] = uliByteLen / 10 * (iI + 1);
	}

	iNProgressIndex = 0;
#if DEBUG_ON
	fprintf(fp, "Reading/Verifying Data...\n");

#endif
	iTimeStart = alt_nticks();

	pxSrc = (TMyData *) uliDdr2Base;
	iNAccessLen = sizeof(xSZData);
	iNItemNum = iNAccessLen / ciMyDataSize;
	iNPos = 0;
	while (bSuccess && iNPos < uliByteLen) {
		iNRemainedLen = uliByteLen - iNPos;
		if (iNAccessLen > iNRemainedLen) {
			iNAccessLen = iNRemainedLen;
			iNItemNum = iNAccessLen / ciMyDataSize;
		}
		pxDes = xSZData;
		for (iI = 0; iI < iNItemNum && bSuccess; iI++) {
			if (*pxSrc++ != *pxDes++) {
#if DEBUG_ON
				fprintf(fp, "verify ng, read=%08Xh, expected=%08Xh, WordIndex=%Xh\n", (int) *(pxSrc - 1), (int) xSZData[iI], (iNPos / ciMyDataSize) + iI);

#endif
				bSuccess = FALSE;
			}
		}
		iNPos += iNAccessLen;
		if (iNProgressIndex <= 9 && iNPos >= uliSZProgress[iNProgressIndex]) {
			iNProgressIndex++;
#if DEBUG_ON
			fprintf(fp, "%02d%% ", iNProgressIndex * 10);

#endif
		}
	}
#if DEBUG_ON
	fprintf(fp, "\n");

#endif

	iTimeElapsed = alt_nticks() - iTimeStart;
	if (bSuccess) {
#if DEBUG_ON
		fprintf(fp, "DDR2 read test pass, size=%ld bytes, %.3f sec\n", uliByteLen, (float) iTimeElapsed / (float) alt_ticks_per_second());

#endif
	} else {
#if DEBUG_ON
		fprintf(fp, "DDR2 read test fail\n");

#endif
	}
#if DEBUG_ON
	fprintf(fp, "\n");

#endif

	return bSuccess;
}

/**
 * @name    bDdr2MemoryRandomWriteTest
 * @brief
 * @ingroup DDR2
 *
 * Teste de escrita na memória, baseados nos valores gerados por um RNG.
 *
 * @param [in] MemoryId  ID da mémoria a ser testada
 * @param [in] bVerbose  Controle o modo verbose da função
 * @param [in] bTime  Controla se a duração da função será medida
 *
 * @retval TRUE : Sucesso
 *
 */
bool bDdr2MemoryRandomWriteTest(alt_u8 ucMemoryId, bool bVerbose, bool bTime) {

#if DEBUG_ON
	fprintf(fp, "===== DE4 DDR2 Memory Random Write Test =====\n");

#endif
	bool bSuccess = FALSE;
	alt_u32 uliDdr2Base;
	alt_u32 uliByteLen;

	switch (ucMemoryId) {
	case DDR2_M1_ID:
		bDdr2SwitchMemory(ucMemoryId);
		uliDdr2Base = DDR2_EXT_ADDR_WINDOWED_BASE;
		uliByteLen = DDR2_M1_MEMORY_SIZE;
		bSuccess = TRUE;
		break;
	case DDR2_M2_ID:
		bDdr2SwitchMemory(ucMemoryId);
		uliDdr2Base = DDR2_EXT_ADDR_WINDOWED_BASE;
		uliByteLen = DDR2_M2_MEMORY_SIZE;
		bSuccess = TRUE;
		break;
	default:
		bSuccess = FALSE;
#if DEBUG_ON
		fprintf(fp, "DR2 Memory ID not identified!! Aborting Test \n");
#endif
		return bSuccess;
	}

#if DEBUG_ON
	fprintf(fp, "DDR2 Size: %ld MBytes\n", uliByteLen / 1024 / 1024);

#endif

	alt_u32 *puliDestination;
	alt_u32 uliCurrentState;
	alt_u32 uliMemoryEndAddress;
	alt_u32 uliNextMilestone;
	alt_u8 ucPercentage;

	uliInitialState = alt_nticks();
	uliCurrentState = uliInitialState;
	uliMemoryEndAddress = uliDdr2Base + uliByteLen;
	uliNextMilestone = uliDdr2Base + uliByteLen / 20;
	ucPercentage = 5;
#if DEBUG_ON
	fprintf(fp, "Writing to memory...\n");

#endif
	if (bVerbose == DDR2_VERBOSE) {
#if DEBUG_ON
		fprintf(fp, "00%%..");

#endif
	}
	int TimeStart, TimeElapsed = 0;

	TimeStart = alt_nticks();
	for (puliDestination = (alt_u32*) uliDdr2Base; (alt_u32) puliDestination < uliMemoryEndAddress; puliDestination++) {
		*puliDestination = uliXorshift32(&uliCurrentState);
		if ((bVerbose == DDR2_VERBOSE) & ((alt_u32) puliDestination > uliNextMilestone)) {
#if DEBUG_ON
			fprintf(fp, "..%02d%%..", ucPercentage);

#endif
			uliNextMilestone += uliByteLen / 20;
			ucPercentage += 5;
		}
	}
	alt_dcache_flush_all();
	if (bVerbose == DDR2_VERBOSE) {
#if DEBUG_ON
		fprintf(fp, "..100%%\n");

#endif
	}

	if (bSuccess) {
		if (bTime == TRUE) {
			TimeElapsed = alt_nticks() - TimeStart;
#if DEBUG_ON
			fprintf(fp, "DDR2 write test pass, size=%ld bytes, %.3f sec\n", uliByteLen, (float) TimeElapsed / (float) alt_ticks_per_second());

#endif
		} else {
#if DEBUG_ON
			fprintf(fp, "DDR2 write test pass, size=%ld bytes\n", uliByteLen);

#endif
		}
	} else {
#if DEBUG_ON
		fprintf(fp, "DDR2 write test fail\n");

#endif
	}
#if DEBUG_ON
	fprintf(fp, "\n");

#endif

	return bSuccess;
}

/**
 * @name    bDdr2MemoryRandomReadTest
 * @brief
 * @ingroup DDR2
 *
 * Teste de leitura da memória, baseados nos valores gerados por um RNG.
 *
 * @param [in] MemoryId  ID da mémoria a ser testada
 * @param [in] bVerbose  Controle o modo verbose da função
 * @param [in] bTime  Controla se a duração da função será medida
 *
 * @retval TRUE : Sucesso
 *
 */
bool bDdr2MemoryRandomReadTest(alt_u8 ucMemoryId, bool bVerbose, bool bTime) {

#if DEBUG_ON
	fprintf(fp, "===== DE4 DDR2 Memory Random Read Test =====\n");

#endif
	bool bSuccess = FALSE;
	alt_u32 uliDdr2Base;
	alt_u32 uliByteLen;

	switch (ucMemoryId) {
	case DDR2_M1_ID:
		bDdr2SwitchMemory(ucMemoryId);
		uliDdr2Base = DDR2_EXT_ADDR_WINDOWED_BASE;
		uliByteLen = DDR2_M1_MEMORY_SIZE;
		bSuccess = TRUE;
		break;
	case DDR2_M2_ID:
		bDdr2SwitchMemory(ucMemoryId);
		uliDdr2Base = DDR2_EXT_ADDR_WINDOWED_BASE;
		uliByteLen = DDR2_M2_MEMORY_SIZE;
		bSuccess = TRUE;
		break;
	default:
		bSuccess = FALSE;
#if DEBUG_ON
		fprintf(fp, "DR2 Memory ID not identified!! Aborting Test \n");

#endif
		return bSuccess;
	}

#if DEBUG_ON
	fprintf(fp, "DDR2 Size: %ld MBytes\n", uliByteLen / 1024 / 1024);

#endif

	alt_u32 *puliSource;
	alt_u32 uliCurrentState;
	alt_u32 uliMemoryEndAddress;
	alt_u32 uliNextMilestone;
	alt_u8 ucPercentage;

	uliCurrentState = uliInitialState;
	uliMemoryEndAddress = uliDdr2Base + uliByteLen;
	uliNextMilestone = uliDdr2Base + uliByteLen / 20;
	ucPercentage = 5;
#if DEBUG_ON
	fprintf(fp, "Reading from memory...\n");

#endif
	if (bVerbose == DDR2_VERBOSE) {
#if DEBUG_ON
		fprintf(fp, "00%%..");

#endif
	}

	int TimeStart, TimeElapsed = 0;

	TimeStart = alt_nticks();
	for (puliSource = (alt_u32*) uliDdr2Base; (alt_u32) puliSource < uliMemoryEndAddress; puliSource++) {
		if (uliXorshift32(&uliCurrentState) != *puliSource) {
			bSuccess = FALSE;
			if (bVerbose == DDR2_VERBOSE) {
#if DEBUG_ON
				fprintf(fp, "Failed to read adress 0x%08lX\n", (alt_u32) puliSource);

#endif
			}
		}
		if ((bVerbose == DDR2_VERBOSE) && ((alt_u32) puliSource > uliNextMilestone)) {
#if DEBUG_ON
			fprintf(fp, "..%02d%%..", ucPercentage);

#endif
			uliNextMilestone += uliByteLen / 20;
			ucPercentage += 5;
		}
	}
	if (bVerbose == DDR2_VERBOSE) {
#if DEBUG_ON
		fprintf(fp, "..100%%\n");

#endif
	}

	if (bSuccess) {
		if (bTime == TRUE) {
			TimeElapsed = alt_nticks() - TimeStart;
#if DEBUG_ON
			fprintf(fp, "DDR2 read test pass, size=%lu bytes, %.3f sec\n", uliByteLen, (float) TimeElapsed / (float) alt_ticks_per_second());

#endif
		} else {
#if DEBUG_ON
			fprintf(fp, "DDR2 read test pass, size=%lu bytes\n", uliByteLen);

#endif
		}
	} else {
#if DEBUG_ON
		fprintf(fp, "DDR2 read test fail\n");

#endif
	}
#if DEBUG_ON
	fprintf(fp, "\n");

#endif

	return bSuccess;
}

/**
 * @name    uliXorshift32
 * @brief
 * @ingroup DDR2
 *
 * Helper function para gerar valores aleatórios para teste de memória (RNG)
 *
 * @param [in] bDRIVE  Estado atual do RNG
 *
 * @retval Número aleatório resultate do RNG
 *
 */
alt_u32 uliXorshift32(alt_u32 *puliState) {

	alt_u32 uliX = *puliState;
	uliX ^= uliX << 13;
	uliX ^= uliX >> 17;
	uliX ^= uliX << 5;
	*puliState = uliX;

	return uliX;
}
