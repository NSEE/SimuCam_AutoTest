/**
 * @file   sync.h
 * @Author Cassio Berni (ccberni@hotmail.com)
 * @date   Novembro, 2018
 * @brief  Header File para controle do sync ip via Nios-Avalon
 */

#ifndef SYNC_H_
#define SYNC_H_

#include "../../simucam_definitions.h"

//! [constants definition]
// address
#define SYNC_BASE_ADDR                  SYNC_BASE
#define SYNC_SYNC_IRQ                   11
#define SYNC_PRE_SYNC_IRQ               12

// bit states
#define SYNC_BIT_ON                     TRUE
#define SYNC_BIT_OFF                    FALSE

#define SYNC_DEFAULT_SUBUNIT_OST        25e6

//! [constants definition]


//! [public module structs definition]

/* Sync Status Register Struct */
typedef struct SyncStatus {
	bool bIntExtN; /* Internal/External_n */
	alt_u32 ucState; /* State */
	alt_u32 ucErrorCode; /* Error code */
	alt_u32 ucCycleNumber; /* Cycle number */
} TSyncStatus;

/* Sync Interrupt Enable Register Struct */
typedef struct SyncIrqEn {
	bool bErrorIrqEn; /* Error interrupt enable bit */
	bool bBlankPulseIrqEn; /* Blank pulse interrupt enable bit */
	bool bMasterPulseIrqEn; /* Master pulse interrupt enable bit */
	bool bNormalPulseIrqEn; /* Normal pulse interrupt enable bit */
	bool bLastPulseIrqEn; /* Last pulse interrupt enable bit */
} TSyncIrqEn;

/* Sync Interrupt Flag Clear Register Struct */
typedef struct SyncIrqFlagClr {
	bool bErrorIrqFlagClr; /* Error interrupt flag clear bit */
	bool bBlankPulseIrqFlagClr; /* Blank pulse interrupt flag clear bit */
	bool bMasterPulseIrqFlagClr; /* Master pulse interrupt flag clear bit */
	bool bNormalPulseIrqFlagClr; /* Normal pulse interrupt flag clear bit */
	bool bLastPulseIrqFlagClr; /* Last pulse interrupt flag clear bit */
} TSyncIrqFlagClr;

/* Sync Interrupt Flag Register Struct */
typedef struct SyncIrqFlag {
	bool bErrorIrqFlag; /* Error interrupt flag bit */
	bool bBlankPulseIrqFlag; /* Blank pulse interrupt flag bit */
	bool bMasterPulseIrqFlag; /* Master pulse interrupt flag bit */
	bool bNormalPulseIrqFlag; /* Normal pulse interrupt flag bit */
	bool bLastPulseIrqFlag; /* Last pulse interrupt flag bit */
} TSyncIrqFlag;

/* Pre-Sync Interrupt Enable Register Struct */
typedef struct PreSyncIrqEn {
	bool bPreBlankPulseIrqEn; /* Pre-Blank pulse interrupt enable bit */
	bool bPreMasterPulseIrqEn; /* Pre-Master pulse interrupt enable bit */
	bool bPreNormalPulseIrqEn; /* Pre-Normal pulse interrupt enable bit */
	bool bPreLastPulseIrqEn; /* Pre-Last pulse interrupt enable bit */
} TPreSyncIrqEn;

/* Pre-Sync Interrupt Flag Clear Register Struct */
typedef struct PreSyncIrqFlagClr {
	bool bPreBlankPulseIrqFlagClr; /* Pre-Blank pulse interrupt flag clear bit */
	bool bPreMasterPulseIrqFlagClr; /* Pre-Master pulse interrupt flag clear bit */
	bool bPreNormalPulseIrqFlagClr; /* Pre-Normal pulse interrupt flag clear bit */
	bool bPreLastPulseIrqFlagClr; /* Pre-Last pulse interrupt flag clear bit */
} TPreSyncIrqFlagClr;

/* Pre-Sync Interrupt Flag Register Struct */
typedef struct PreSyncIrqFlag {
	bool bPreBlankPulseIrqFlag; /* Pre-Blank pulse interrupt flag bit */
	bool bPreMasterPulseIrqFlag; /* Pre-Master pulse interrupt flag bit */
	bool bPreNormalPulseIrqFlag; /* Pre-Normal pulse interrupt flag bit */
	bool bPreLastPulseIrqFlag; /* Pre-Last pulse interrupt flag bit */
} TPreSyncIrqFlag;

/* Sync Master Blank Time Config Register Struct */
typedef struct SyncConfig {
	alt_u32 uliMasterBlankTime; /* MBT value */
	alt_u32 uliBlankTime; /* BT value */
	alt_u32 uliLastBlankTime; /* LBT value */
	alt_u32 uliPreBlankTime; /* Pre-Blank value */
	alt_u32 uliPeriod; /* Period value */
	alt_u32 uliLastPeriod; /* Last Period value */
	alt_u32 uliMasterDetectionTime; /* Master Detection Time value */
	alt_u32 uliOneShotTime; /* OST value */
} TSyncConfig;

/* Sync General Config Register Struct */
typedef struct SyncGeneralConfig {
	bool bSignalPolarity; /* Signal polarity */
	alt_u32 ucNumberOfCycles; /* Number of cycles */
} TSyncGeneralConfig;

/* Sync Error Injection Register Struct */
typedef struct SyncErrorInjection {
	alt_u32 uliErrorInjection; /* Reserved */
} TSyncErrorInjection;

/* Sync Control Register Struct */
typedef struct SyncControl {
	bool bIntExtN; /* Internal/External(n) bit */
	bool bStart; /* Start bit */
	bool bReset; /* Reset bit */
	bool bOneShot; /* One Shot bit */
	bool bErrInj; /* Err_inj bit */
	bool bHoldBlankPulse; /* Hold Blank Pulse */
	bool bHoldReleasePulse; /* Hold Release Pulse */
	bool bOutEn; /* Sync_out out enable bit */
	bool bChannel1En; /* Channel 1 out enable bit */
	bool bChannel2En; /* Channel 2 out enable bit */
	bool bChannel3En; /* Channel 3 out enable bit */
	bool bChannel4En; /* Channel 4 out enable bit */
	bool bChannel5En; /* Channel 5 out enable bit */
	bool bChannel6En; /* Channel 6 out enable bit */
	bool bChannel7En; /* Channel 7 out enable bit */
	bool bChannel8En; /* Channel 8 out enable bit */
} TSyncControl;

/* Sync Test Control Register Struct */
typedef struct SyncTestControl {
	bool bSyncInOverrideEn; /* Sync_in override enable */
	bool bSyncInOverrideValue; /* Sync_in override value */
	bool bSyncOutOverrideEn; /* Sync_out override enable */
	bool bSyncOutOverrideValue; /* Sync_out override value */
} TSyncTestControl;

/* Sync Test Status Register Struct */
typedef struct SyncTestStatus {
	bool SyncInValue; /* Sync_in value */
	bool SyncOutValue; /* Sync_out value */
} TSyncTestStatus;

/* Sync IRQ Number Register Struct */
typedef struct SyncIRQNumber {
	alt_u32 uliSyncIrqNumber; /* Sync IRQ number */
	alt_u32 uliPreSyncIrqNumber; /* Pre-Sync IRQ number */
} TSyncIRQNumber;

/* General Struct for Registers Access */
typedef struct SyncModule {
	TSyncStatus xSyncStatus;
	TSyncIrqEn xSyncIrqEn;
	TSyncIrqFlagClr xSyncIrqFlagClr;
	TSyncIrqFlag xSyncIrqFlag;
	TPreSyncIrqEn xPreSyncIrqEn;
	TPreSyncIrqFlagClr xPreSyncIrqFlagClr;
	TPreSyncIrqFlag xPreSyncIrqFlag;
	TSyncConfig xSyncConfig;
	TSyncGeneralConfig xSyncGeneralConfig;
	TSyncErrorInjection xSyncErrorInjection;
	TSyncControl xSyncControl;
	TSyncTestControl xSyncTestControl;
	TSyncTestStatus xSyncTestStatus;
	TSyncIRQNumber xSyncIRQNumber;
} TSyncModule;
//! [public module structs definition]

//! [public function prototypes]
void vSyncInitIrq(void);
void vSyncHandleSyncIrq(void* pvContext);

void vSyncPreInitIrq(void);
void vSyncPreHandleIrq(void* pvContext);

bool bSyncStatusExtnIrq(void);
alt_u8 ucSyncStatusState(void);
alt_u8 ucSyncStatusErrorCode(void);
alt_u8 ucSyncStatusCycleNumber(void);

bool bSyncIrqEnableError(bool bValue);
bool bSyncIrqEnableBlankPulse(bool bValue);
bool bSyncIrqEnableMasterPulse(bool bValue);
bool bSyncIrqEnableNormalPulse(bool bValue);
bool bSyncIrqEnableLastPulse(bool bValue);

bool bSyncIrqFlagClrError(bool bValue);
bool bSyncIrqFlagClrBlankPulse(bool bValue);
bool bSyncIrqFlagClrMasterPulse(bool bValue);
bool bSyncIrqFlagClrNormalPulse(bool bValue);
bool bSyncIrqFlagClrLastPulse(bool bValue);

bool bSyncIrqFlagError(void);
bool bSyncIrqFlagBlankPulse(void);
bool bSyncIrqFlagMasterPulse(void);
bool bSyncIrqFlagNormalPulse(void);
bool bSyncIrqFlagLastPulse(void);

bool bSyncPreIrqEnableBlankPulse(bool bValue);
bool bSyncPreIrqEnableMasterPulse(bool bValue);
bool bSyncPreIrqEnableNormalPulse(bool bValue);
bool bSyncPreIrqEnableLastPulse(bool bValue);

bool bSyncPreIrqFlagClrBlankPulse(bool bValue);
bool bSyncPreIrqFlagClrMasterPulse(bool bValue);
bool bSyncPreIrqFlagClrNormalPulse(bool bValue);
bool bSyncPreIrqFlagClrLastPulse(bool bValue);

bool bSyncPreIrqFlagBlankPulse(void);
bool bSyncPreIrqFlagMasterPulse(void);
bool bSyncPreIrqFlagNormalPulse(void);
bool bSyncPreIrqFlagLastPulse(void);

bool bSyncSetMbt(alt_u32 uliValue);
bool bSyncSetBt(alt_u32 uliValue);
bool bSyncSetPreBt(alt_u32 uliValue);
bool bSyncSetPer(alt_u32 uliValue);
bool bSyncSetOst(alt_u32 uliValue);
bool bSyncSetPolarity(bool bValue);
bool bSyncSetNCycles(alt_u8 ucValue);

alt_u32 uliSyncGetMbt(void);
alt_u32 uliSyncGetBt(void);
alt_u32 uliSyncGetPer(void);
alt_u32 uliSyncGetOst(void);

bool bSyncErrInj(alt_u32 uliValue);

bool bSyncCtrIntern(bool bValue);
bool bSyncCtrStart(void);
bool bSyncCtrReset(void);
bool bSyncCtrOneShot(void);
bool bSyncCtrErrInj(void);
bool bSyncCtrHoldBlankPulse(bool bValue);
bool bSyncCtrHoldReleasePulse(bool bValue);
bool bSyncCtrSyncOutEnable(bool bValue);
bool bSyncCtrCh1OutEnable(bool bValue);
bool bSyncCtrCh2OutEnable(bool bValue);
bool bSyncCtrCh3OutEnable(bool bValue);
bool bSyncCtrCh4OutEnable(bool bValue);
bool bSyncCtrCh5OutEnable(bool bValue);
bool bSyncCtrCh6OutEnable(bool bValue);
bool bSyncCtrCh7OutEnable(bool bValue);
bool bSyncCtrCh8OutEnable(bool bValue);

bool bSyncTestConnection(void);
bool bSyncConfigOstSubunits(alt_u32 uliOstValue);
//! [public function prototypes]

//! [private function prototypes]
alt_u32 uliPerCalcPeriodMs(alt_u16 usiPeriodMs);
alt_u16 usiRegCalcTimeMs(alt_u32 uliSyncReg);
//! [private function prototypes]

//! [data memory public global variables - use extern]
//! [data memory public global variables - use extern]

//! [flags]
//! [flags]

//! [program memory public global variables - use extern]
//! [program memory public global variables - use extern]

//! [macros]
//! [macros]

#endif /* SYNC_H_ */
