//////////////////////////////////////////////////////////////////////////////////
//
// Created by Sebastian Lee on 12.09.17
// Description:
// This file contains the address map to be used in the programmers view to access
// the ADC control and status registers as defined on the User Manual.
//
//////////////////////////////////////////////////////////////////////////////////

#define MCLK_PERIOD 10 //in SC_NS
#define ADC_PERIOD 100
#define RESOLUTION 12
//#define M_PI 3.14159
//Base address
#define ADC_BADR 0x4003800

//Set of registers by offset from base address

#define ADC_CR    ADC_BADR + 0x00
#define ADC_MR    ADC_BADR + 0x04
#define ADC_CHER  ADC_BADR + 0x10
#define ADC_CHDR  ADC_BADR + 0x14
#define ADC_CHSR  ADC_BADR + 0x18
#define ADC_CGR   ADC_BADR + 0x48
#define ADC_COR   ADC_BADR + 0x4C
#define ADC_CDR0  ADC_BADR + 0x50
#define ADC_CDR1  ADC_BADR + 0x54
#define ADC_CDR2  ADC_BADR + 0x58
#define ADC_CDR3  ADC_BADR + 0x5C
#define ADC_CDR4  ADC_BADR + 0x60
#define ADC_CDR5  ADC_BADR + 0x64
#define ADC_CDR6  ADC_BADR + 0x68
#define ADC_CDR7  ADC_BADR + 0x6C
#define ADC_CDR8  ADC_BADR + 0x70
#define ADC_CDR9  ADC_BADR + 0x74
#define ADC_CDR10 ADC_BADR + 0x78
#define ADC_CDR11 ADC_BADR + 0x7C
#define ADC_CDR12 ADC_BADR + 0x80
#define ADC_CDR13 ADC_BADR + 0x84
#define ADC_CDR14 ADC_BADR + 0x88
#define ADC_CDR15 ADC_BADR + 0x8C
#define ADC_WPMR  ADC_BADR + 0xE4

#define MAX_OFFSET 0xE4 //max offset defined from the last availabe address.. used to avoid access to unsed data set

