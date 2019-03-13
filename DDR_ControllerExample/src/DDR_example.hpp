/*****************************************************************************/
/**
*
* @file DDR_example.hpp
*
* @addtogroup a53_64_cache_apis Cortex A53 Cache Functions_ //modify!! doc..
*
*  (insert description of what this file does)
*
* @{
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date     Changes
* ----- ---- -------- -----------------------------------------------
* 5.00 	xx  12 Mar 2019 First release
* </pre>
*
******************************************************************************/
#ifndef SRC_DDR_EXAMPLE_HPP_
#define SRC_DDR_EXAMPLE_HPP_

#include "xil_types.h"

#ifdef __cplusplus
extern "C" {
#endif


enum error_code{
	SUCCESS,
	ERROR,
	ERROR_TIMOUT
};

/************************** Constant Definitions *****************************/

#define EXAMPLE_MASK  0xE000

/************************** Function Prototypes ******************************/
enum error_code read_ddr_register(uint32_t* register_address);

#ifdef __cplusplus
}
#endif

#endif /* SRC_DDR_EXAMPLE_HPP_ */
/**
* @} End of "addtogroup a53_64_cache_apis". //modify!!
*/



