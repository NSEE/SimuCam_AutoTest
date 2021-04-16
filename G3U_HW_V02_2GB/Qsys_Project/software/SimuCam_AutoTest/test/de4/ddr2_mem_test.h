/*
 * ddr2_mem_test.h
 *
 *  Created on: 15 de abr de 2021
 *      Author: rfranca
 */

#ifndef TEST_DE4_DDR2_MEM_TEST_H_
#define TEST_DE4_DDR2_MEM_TEST_H_

#include "../../simucam_definitions.h"
#include "../../api_drivers/ddr2/ddr2.h"
#include "../../driver/memory_filler/memory_filler.h"

//! [constants definition]
//! [constants definition]

//! [public module structs definition]
//! [public module structs definition]

//! [public function prototypes]

void vDe4Ddr2MemTestMenu( void );

bool bDe4Ddr2MemZeroFill( alt_u8 Ddr2MemID );

//! [public function prototypes]

//! [data memory public global variables - use extern]
//! [data memory public global variables - use extern]

//! [flags]
//! [flags]

//! [program memory public global variables - use extern]
//! [program memory public global variables - use extern]

//! [macros]
//! [macros]

#endif /* TEST_DE4_DDR2_MEM_TEST_H_ */
