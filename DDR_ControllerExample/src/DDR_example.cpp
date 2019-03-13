/*****************************************************************************/
/**
 *
 * @file DDR_example.cpp
 *
 * (Description of what this file does)
 *
 * <pre>
 * MODIFICATION HISTORY:
 *
 * Ver    Who Date     Changes
 * ----- ---- -------- -----------------------------------------------
 * 1.0 	xx   12 Mar 2019  First release
 *
 * </pre>
 *
 ******************************************************************************/

/***************************** Include Files *********************************/

#include "xil_types.h"
#include "ddr_qos_ctrl.h"
#include "ddrc.h"
#include "DDR_example.hpp"
#include <c++/7.2.1/iostream>

/************************** Function Prototypes ******************************/

/************************** Variable Definitions *****************************/

int main(int argc, char **argv) {

	uint32_t * register8 = (uint32_t *) 0x800;
	enum error_code Status = ERROR;

	Status = read_ddr_register(register8);
	if (Status != SUCCESS) {
		std::cout << "Failed with error code " << Status << std::endl;
	}
	/*Print value of register*/
	std::cout << "Value of register is : " << std::hex  << *register8 << std::endl;

	return 0;
}

/****************************************************************************/
/**
 * @brief	 This function performs mode register reads via software. Mode
 * register reads (MRR) are applicable only to LPDDR2/LPDDR3/LPDDR4, and are used to read
 * configuration and status data from mode registers in the SDRAM.
 *
 * @param	register_address - pointer to the register (0x800 = register 8)
 *
 * @return	enum error_code- returns one of : SUCCESS, 	ERROR, 	ERROR_TIMOUT
 *
 * @note		None.
 *
 ****************************************************************************/
enum error_code read_ddr_register(uint32_t* register_address) {

	uint32_t ddr_reg_value = 0, value = 0;

	/*No outstanding MR transactions*/
	if ((DDRC_MRSTAT & DDRC_MRSTAT_MR_WR_BUSY_MASK) != 0) {

		/*TODO : Create timeout ...*/

	} else {

		/* Write MRCTRL0.mr_type = 1 (for read), and MRCTRL0.mr_rank = 0x1 or 0x2 (depending
		 on which rank you want to read)*/
		*(uint32_t *) DDRC_MRCTRL0 = 0x11;

		/* Write MRCTRL1[15:8] to the address of the mode register to be read. In this case 8*/
		*(uint32_t *) DDRC_MRCTRL1 = *register_address;

		/*#Write DDRC.MRCTRL0.mr_rank and mr_type to indicate read from rank 0, this time setting
		 #bit 31 = 1 to initiate the MRR.*/
		*(uint32_t *) DDRC_MRCTRL0 = 0x80000011;

		/*#Read DDRC.MRCTRL0 to look for bit 31 to have been cleared*/
		while ((*(uint32_t *) DDRC_MRCTRL0 & DDRC_MRCTRL0_MR_WR_MASK)
				== DDRC_MRCTRL0_MR_WR_MASK) {
			/*TODO: Create a timeout and return with ERROR_TIMOUT*/
		};

		/*Make sure MRR has completed*/
		while ((*(uint32_t *) DDRC_MRSTAT & DDRC_MRCTRL0_MR_WR_MASK) != 0x0) {
			/*TODO: Create a timeout and return with ERROR_TIMOUT*/
		}
		/*#Check DDR_QOS_CTRL.DDRC_MRR_STATUS to look for 0x3 or higher*/
		while ((*(uint32_t *) DDR_QOS_CTRL_DDRC_MRR_STATUS) < 0x3) {
			/*TODO: Create a timeout and return with ERROR_TIMOUT*/
		}
		/*Get the value of the register*/
		*register_address = *(uint32_t *) DDR_QOS_CTRL_DDRC_MRR_DATA0;

		/*Read DDR_QOS_CTRL.DDRC_MRR_DATA11 to reset the MRR read FIFO RD pointer.*/
		value = *(uint32_t *) DDR_QOS_CTRL_DDRC_MRR_DATA11;

	}

	return SUCCESS;
}
