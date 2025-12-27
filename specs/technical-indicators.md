# Technical Indicators Specification

## Overview

TA-Lib implements over 200 technical analysis indicators organized into 10 functional groups. The indicator system uses a sophisticated code generation approach where indicator definitions are specified in an Interface Definition Language (IDL) and then automatically generate C source code, headers, and bindings for multiple languages.

## Architecture

### Three-Layer Architecture

1. **Abstract Layer** (`src/ta_abstract/`): Defines the interface and metadata for all indicators
2. **Implementation Layer** (`src/ta_func/`): Contains the actual indicator calculation code
3. **Code Generation Layer** (`src/tools/gen_code/`): Generates boilerplate code from abstract definitions

### Abstract Layer (IDL System)

The abstract layer serves as the single source of truth for indicator definitions. Each indicator is registered in one of 26 table files (`table_a.c` through `table_z.c`) organized alphabetically.

#### Indicator Registration

Indicators are registered using the `DEF_FUNCTION` macro in table files:

```c
DEF_FUNCTION( ACCBANDS,                    /* name */
              TA_GroupId_OverlapStudies,   /* groupId */
              "Acceleration Bands",        /* hint */
              "Accbands",                  /* CamelCase name */
              TA_FUNC_FLG_OVERLAP          /* flags */
             );
```

#### Input/Output Parameter Definitions

Each indicator defines:
- **Input Parameters**: Required and optional inputs (price data, integers, reals)
- **Output Parameters**: Result arrays with metadata (line, upper limit, lower limit, etc.)
- **Optional Input Parameters**: Configuration parameters with ranges and defaults

Example from `table_a.c`:

```c
static const TA_InputParameterInfo    *TA_ACCBANDS_Inputs[]    =
{
  &TA_DEF_UI_Input_Price_HLC,
  NULL
};

static const TA_OutputParameterInfo   *TA_ACCBANDS_Outputs[]   =
{
  &TA_DEF_UI_Output_Real_ACCBANDS_Upper,
  &TA_DEF_UI_Output_Real_ACCBANDS_Middle,
  &TA_DEF_UI_Output_Real_ACCBANDS_Lower,
  NULL
};
```

### Implementation Layer

Each indicator has a dedicated source file in `src/ta_func/` following the naming pattern `ta_<INDICATOR>.c`. The implementation files contain:

1. **Lookback Function**: Calculates the number of input bars needed before the first valid output
2. **Main Function**: Performs the actual indicator calculation
3. **Generated Code Sections**: Auto-generated boilerplate (marked with `GENCODE SECTION` comments)

#### Function Signature Pattern

All indicators follow a consistent signature pattern:

```c
TA_LIB_API int TA_SMA_Lookback( int optInTimePeriod );

TA_LIB_API TA_RetCode TA_SMA( int    startIdx,
                               int    endIdx,
                               const double *inReal,
                               int    optInTimePeriod,
                               int   *outBegIdx,
                               int   *outNBElement,
                               double *outReal );
```

Parameters:
- `startIdx`, `endIdx`: Input array bounds
- `inReal` (or price arrays): Input data
- `optIn*`: Optional input parameters
- `outBegIdx`: Index of first valid output
- `outNBElement`: Number of output elements
- `outReal`: Output array

#### Code Generation Sections

Each indicator file contains three generated sections:

1. **Section 1**: Function declarations and includes (platform-specific)
2. **Section 2**: Lookback calculation
3. **Section 3**: Main calculation logic

The manual code (between sections) contains the actual algorithm implementation.

### Code Generation System

The `gen_code` tool (`src/tools/gen_code/gen_code.c`) reads the abstract layer definitions and generates:

- Function prototypes in `include/ta_func.h`
- Implementation boilerplate in indicator source files
- SWIG interface files for language bindings
- Java bindings
- Rust bindings
- XML function descriptions (`ta_func_api.xml`)
- Documentation and test code

The generator uses the abstract layer's metadata to:
- Generate type-safe function signatures
- Create parameter validation code
- Generate language-specific bindings
- Maintain consistency across all generated artifacts

## Indicator Categories

Indicators are organized into 10 functional groups defined in `src/ta_abstract/ta_def_ui.h`:

1. **Math Operators** (`TA_GroupId_MathOperators`)
   - Basic arithmetic operations (ADD, SUB, MULT, DIV, etc.)

2. **Math Transform** (`TA_GroupId_MathTransform`)
   - Trigonometric and logarithmic functions (ACOS, ASIN, LOG, EXP, etc.)

3. **Overlap Studies** (`TA_GroupId_OverlapStudies`)
   - Moving averages and bands (SMA, EMA, BBANDS, ACCBANDS, etc.)

4. **Volatility Indicators** (`TA_GroupId_VolatilityIndicators`)
   - Volatility measures (ATR, NATR, TRANGE, etc.)

5. **Momentum Indicators** (`TA_GroupId_MomentumIndicators`)
   - Momentum oscillators (RSI, STOCH, MACD, CCI, etc.)

6. **Cycle Indicators** (`TA_GroupId_CycleIndicators`)
   - Hilbert Transform-based indicators (HT_DCPERIOD, HT_SINE, etc.)

7. **Volume Indicators** (`TA_GroupId_VolumeIndicators`)
   - Volume-based analysis (AD, ADOSC, OBV, MFI, etc.)

8. **Pattern Recognition** (`TA_GroupId_PatternRecognition`)
   - Candlestick patterns (CDLDOJI, CDLHAMMER, CDLENGULFING, etc.)

9. **Statistic Functions** (`TA_GroupId_Statistic`)
   - Statistical calculations (VAR, STDDEV, BETA, CORREL, etc.)

10. **Price Transform** (`TA_GroupId_PriceTransform`)
    - Price transformations (AVGPRICE, MEDPRICE, TYPPRICE, etc.)

## Common Implementation Patterns

### Utility Functions

Shared utility functions are defined in `src/ta_func/ta_utility.h`:

- `TA_INT_SMA()`: Internal Simple Moving Average
- `TA_INT_EMA()`: Internal Exponential Moving Average
- `TA_INT_MACD()`: Internal MACD calculation
- `TA_INT_PO()`: Internal Price Oscillator
- `TA_INT_VAR()`: Internal variance calculation

These internal functions assume validated parameters and are used by multiple indicators.

### Memory Management

Indicators use stack-allocated arrays for temporary calculations when possible. The `ARRAY_LOCAL` macro is used for local arrays:

```c
ARRAY_LOCAL(tempBuffer, lookback);
```

### Lookback Calculation

Every indicator implements a `*_Lookback()` function that calculates the minimum number of input bars required before the first valid output. This is essential for:
- Buffer allocation
- Input validation
- Performance optimization

### Unstable Periods

Some indicators have an "unstable period" where initial values may not be reliable. These are tracked in `include/ta_defs.h` via the `TA_FUNC_UNST_*` enum.

## Input Types

The abstract layer supports various input parameter types:

- **Price Data**: OHLCV combinations (OHLCV, HLCV, OHLC, HLC, HL, OC)
- **Real Arrays**: Generic double arrays
- **Integer Parameters**: Configuration values with ranges
- **Enum Parameters**: Moving average types, compatibility modes, etc.

## Output Types

Output parameters can be marked with flags indicating their display characteristics:

- `TA_OUT_LINE`: Standard line output
- `TA_OUT_UPPER_LIMIT`: Upper band/limit
- `TA_OUT_LOWER_LIMIT`: Lower band/limit
- `TA_OUT_CANDLE`: Candlestick pattern result

## File Organization

### Source Files

- `src/ta_func/`: 164+ indicator implementation files (`ta_*.c`)
- `src/ta_func/ta_utility.h`: Shared utility functions
- `src/ta_abstract/tables/`: 26 table files defining indicator metadata
- `src/ta_abstract/ta_abstract.c`: Abstract layer implementation
- `src/ta_abstract/ta_func_api.c`: Function API registration

### Generated Files

- `include/ta_func.h`: Auto-generated function prototypes
- `ta_func_api.xml`: XML representation of all functions
- `swig/src/interface/ta_func.swg`: SWIG interface definitions

## Example: Simple Moving Average (SMA)

### Abstract Definition

Located in `src/ta_abstract/tables/table_s.c`:

```c
DEF_FUNCTION( SMA,
              TA_GroupId_OverlapStudies,
              "Simple Moving Average",
              "Sma",
              TA_FUNC_FLG_OVERLAP
             );
```

### Implementation

File: `src/ta_func/ta_SMA.c`

1. **Lookback**: Returns `optInTimePeriod - 1`
2. **Calculation**: Sums values over the period and divides by period length
3. **Output**: Single array of moving average values

### Function Signature

```c
TA_LIB_API int TA_SMA_Lookback( int optInTimePeriod );

TA_LIB_API TA_RetCode TA_SMA( int    startIdx,
                               int    endIdx,
                               const double *inReal,
                               int    optInTimePeriod,
                               int   *outBegIdx,
                               int   *outNBElement,
                               double *outReal );
```

## Adding New Indicators

To add a new indicator:

1. **Define in Table File**: Add `DEF_FUNCTION` entry to appropriate `table_*.c`
2. **Implement Calculation**: Create `ta_<NAME>.c` with lookback and main functions
3. **Run Code Generator**: Execute `gen_code` to update headers and bindings
4. **Test**: Use `ta_regtest` to verify correctness

The code generator handles:
- Function prototype generation
- Parameter validation
- Language binding creation
- Documentation updates

## References

- Abstract Layer: `src/ta_abstract/`
- Indicator Implementations: `src/ta_func/`
- Code Generator: `src/tools/gen_code/gen_code.c`
- Function Definitions: `include/ta_func.h` (generated)
- XML Metadata: `ta_func_api.xml` (generated)

