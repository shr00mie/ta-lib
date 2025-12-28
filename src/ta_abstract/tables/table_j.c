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

/*********************************************************************
 * This file contains only TA functions starting with the letter 'J' *
 *********************************************************************/
#include <stddef.h>
#include "ta_abstract.h"
#include "ta_def_ui.h"

/* Follow the 3 steps defined below for adding a new TA Function to this
 * file.
 */

/****************************************************************************
 * Step 1 - Define here the interface to your TA functions with
 *          the macro DEF_FUNCTION.
 *
 ****************************************************************************/

/* JMA BEGIN */
static const TA_IntegerRange TA_DEF_JMA_Phase =
{
   -100,            /* min */
   100,             /* max */
   0,               /* suggested start */
   0,               /* suggested end */
   1                /* suggested increment */
};

static const TA_IntegerRange TA_DEF_JMA_TimePeriod =
{
   1,               /* min */
   100000,          /* max */
   14,              /* suggested start */
   14,              /* suggested end */
   1                /* suggested increment */
};

static const TA_IntegerRange TA_DEF_JMA_VolPeriods =
{
   1,               /* min */
   100000,          /* max */
   65,              /* suggested start */
   65,              /* suggested end */
   1                /* suggested increment */
};

static const TA_OptInputParameterInfo TA_DEF_UI_JMA_TimePeriod =
{
   TA_OptInput_IntegerRange, /* type */
   "optInTimePeriod",        /* paramName */
   0,                        /* flags */
   "Time Period",            /* displayName */
   (const void *)&TA_DEF_JMA_TimePeriod, /* dataSet */
   14, /* defaultValue */
   "Period length for the moving average", /* hint */
   NULL /* CamelCase name */
};

static const TA_OptInputParameterInfo TA_DEF_UI_JMA_Phase =
{
   TA_OptInput_IntegerRange, /* type */
   "optInPhase",             /* paramName */
   0,                        /* flags */
   "Phase",                  /* displayName */
   (const void *)&TA_DEF_JMA_Phase, /* dataSet */
   0, /* defaultValue */
   "Phase parameter (typically 0-100). Controls the phase ratio", /* hint */
   NULL /* CamelCase name */
};

static const TA_OptInputParameterInfo TA_DEF_UI_JMA_VolPeriods =
{
   TA_OptInput_IntegerRange, /* type */
   "optInVolPeriods",         /* paramName */
   0,                         /* flags */
   "Volatility Periods",     /* displayName */
   (const void *)&TA_DEF_JMA_VolPeriods, /* dataSet */
   65, /* defaultValue */
   "Period for average volatility calculation", /* hint */
   NULL /* CamelCase name */
};

const TA_OutputParameterInfo TA_DEF_UI_Output_Real_JMA =
                               { TA_Output_Real, "outRealJMA", TA_OUT_LINE };

const TA_OutputParameterInfo TA_DEF_UI_Output_Real_JMA_Upper =
                               { TA_Output_Real, "outRealUpperBand", TA_OUT_UPPER_LIMIT };

const TA_OutputParameterInfo TA_DEF_UI_Output_Real_JMA_Lower =
                               { TA_Output_Real, "outRealLowerBand", TA_OUT_LOWER_LIMIT };

static const TA_InputParameterInfo    *TA_JMA_Inputs[]    =
{
  &TA_DEF_UI_Input_Real,
  NULL
};

static const TA_OutputParameterInfo   *TA_JMA_Outputs[]   =
{
  &TA_DEF_UI_Output_Real_JMA,
  &TA_DEF_UI_Output_Real_JMA_Upper,
  &TA_DEF_UI_Output_Real_JMA_Lower,
  NULL
};

static const TA_OptInputParameterInfo *TA_JMA_OptInputs[] =
{
  &TA_DEF_UI_JMA_TimePeriod,
  &TA_DEF_UI_JMA_Phase,
  &TA_DEF_UI_JMA_VolPeriods,
  NULL
};

DEF_FUNCTION( JMA,                        /* name */
              TA_GroupId_OverlapStudies,  /* groupId */
              "Jurik Moving Average",       /* hint */
              "Jma",                       /* CamelCase name */
              TA_FUNC_FLG_OVERLAP          /* flags */
             );
/* JMA END */

/****************************************************************************
 * Step 2 - Add your TA function to the table.
 *          Keep in alphabetical order. Must be NULL terminated.
 ****************************************************************************/
const TA_FuncDef *TA_DEF_TableJ[] =
{
   ADD_TO_TABLE(JMA),
   NULL
};


/* Do not modify the following line. */
const unsigned int TA_DEF_TableJSize =
              ((sizeof(TA_DEF_TableJ)/sizeof(TA_FuncDef *))-1);


/****************************************************************************
 * Step 3 - Make sure "gen_code" is executed for generating all other
 *          source files derived from this one.
 *          You can then re-compile the library as usual and you are done!
 ****************************************************************************/
