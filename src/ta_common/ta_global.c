/* TA-LIB Copyright (c) 1999-2025, Mario Fortier
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or
 * without modification, are permitted provided that the following
 * conditions are met:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in
 *   the documentation and/or other materials provided with the
 *   distribution.
 *
 * - Neither name of author nor the names of its contributors
 *   may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* List of contributors:
 *
 *  Initial  Name/description
 *  -------------------------------------------------------------------
 *  MF       Mario Fortier
 *  AC       Angelo Ciceri
 *
 *
 * Change history:
 *
 *  MMDDYY BY   Description
 *  -------------------------------------------------------------------
 *  112400 MF   First version.
 *  041106 MF   Add prefix to theGlobals to avoid clash with other libs.
 *  040707 MF   Change global initialization to eliminate Mac OS X link error.
 */

/* Description:
 *   Provides initialization / shutdown functionality for all modules.
 */

/**** Headers ****/
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "ta_common.h"
#include "ta_magic_nb.h"
#include "ta_global.h"
#include "ta_func.h"

/**** External functions declarations. ****/
/* None */

/**** External variables declarations. ****/
/* None */

/**** Global variables definitions.    ****/

/* The entry point for all globals */
TA_LibcPriv ta_theGlobals = {0,{{0,0,0}},0,0,0,0,(TA_Compatibility)0,{0}};

TA_LibcPriv *TA_Globals = &ta_theGlobals;

/**** Local declarations.              ****/
/* None */

/**** Local functions declarations.    ****/
/* None */

/**** Local variables definitions.     ****/
/* None */

/**** Global functions definitions.   ****/
TA_RetCode TA_Initialize( void )
{
   /* Initialize the "global variable" used to manage the global
    * variables of all other modules...
    */
   memset( TA_Globals, 0, sizeof( TA_LibcPriv ) );
   TA_Globals->magicNb = TA_LIBC_PRIV_MAGIC_NB;

   /*** At this point, TA_Shutdown can be called to clean-up. ***/

   /* Set the default value to global variables */

   return TA_SUCCESS;
}

TA_RetCode TA_Shutdown( void )
{
   if( TA_Globals->magicNb != TA_LIBC_PRIV_MAGIC_NB )
      return TA_LIB_NOT_INITIALIZE;

   /* Initialize to all zero to make sure we invalidate that object. */
   memset( TA_Globals, 0, sizeof( TA_LibcPriv ) );

   return TA_SUCCESS;
}



/**** Local functions definitions.     ****/
/* None */


