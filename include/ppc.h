#ifndef CAPSTONE_PPC_H
#define CAPSTONE_PPC_H

/* Capstone Disassembly Engine */
/* By Nguyen Anh Quynh <aquynh@gmail.com>, 2013-2014 */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "platform.h"

#ifdef _MSC_VER
#pragma warning(disable:4201)
#endif

//> PPC branch codes for some branch instructions
typedef enum ppc_bc {
	PPC_BC_INVALID  = 0,
	PPC_BC_LT       = (0 << 5) | 12,
	PPC_BC_LE       = (1 << 5) |  4,
	PPC_BC_EQ       = (2 << 5) | 12,
	PPC_BC_GE       = (0 << 5) |  4,
	PPC_BC_GT       = (1 << 5) | 12,
	PPC_BC_NE       = (2 << 5) |  4,
	PPC_BC_UN       = (3 << 5) | 12,
	PPC_BC_NU       = (3 << 5) |  4,
	PPC_BC_LT_MINUS = (0 << 5) | 14,
	PPC_BC_LE_MINUS = (1 << 5) |  6,
	PPC_BC_EQ_MINUS = (2 << 5) | 14,
	PPC_BC_GE_MINUS = (0 << 5) |  6,
	PPC_BC_GT_MINUS = (1 << 5) | 14,
	PPC_BC_NE_MINUS = (2 << 5) |  6,
	PPC_BC_UN_MINUS = (3 << 5) | 14,
	PPC_BC_NU_MINUS = (3 << 5) |  6,
	PPC_BC_LT_PLUS  = (0 << 5) | 15,
	PPC_BC_LE_PLUS  = (1 << 5) |  7,
	PPC_BC_EQ_PLUS  = (2 << 5) | 15,
	PPC_BC_GE_PLUS  = (0 << 5) |  7,
	PPC_BC_GT_PLUS  = (1 << 5) | 15,
	PPC_BC_NE_PLUS  = (2 << 5) |  7,
	PPC_BC_UN_PLUS  = (3 << 5) | 15,
	PPC_BC_NU_PLUS  = (3 << 5) |  7
} ppc_bc;

//> PPC branch hint for some branch instructions
typedef enum ppc_bh {
	PPC_BH_NO = 0,	// no hint
	PPC_BH_PLUS,	// PLUS hint
	PPC_BH_MINUS,	// MINUS hint
} ppc_bh;

//> Operand type for instruction's operands
typedef enum ppc_op_type {
	PPC_OP_INVALID = 0,	// Uninitialized.
	PPC_OP_REG,	// Register operand.
	PPC_OP_IMM,	// Immediate operand.
	PPC_OP_MEM,	// Memory operand
} ppc_op_type;

// Instruction's operand referring to memory
// This is associated with PPC_OP_MEM operand type above
typedef struct ppc_op_mem {
	unsigned int base;	// base register
	int32_t disp;	// displacement/offset value
} ppc_op_mem;

// Instruction operand
typedef struct cs_ppc_op {
	ppc_op_type type;	// operand type
	union {
		unsigned int reg;	// register value for REG operand
		int32_t imm;		// immediate value for IMM operand
		ppc_op_mem mem;		// base/disp value for MEM operand
	};
} cs_ppc_op;

// Instruction structure
typedef struct cs_ppc {
	// branch code for branch instructions
	ppc_bc bc;

	// branch hint for branch instructions
	ppc_bh bh;

	// if update_cr0 = True, then this 'dot' insn updates CR0
	bool update_cr0;

	// Number of operands of this instruction, 
	// or 0 when instruction has no operand.
	uint8_t op_count;
	cs_ppc_op operands[8]; // operands for this instruction.
} cs_ppc;

//> PPC registers
typedef enum ppc_reg {
	PPC_REG_INVALID = 0,

	PPC_REG_CARRY,
	PPC_REG_CR0,
	PPC_REG_CR1,
	PPC_REG_CR2,
	PPC_REG_CR3,
	PPC_REG_CR4,
	PPC_REG_CR5,
	PPC_REG_CR6,
	PPC_REG_CR7,
	PPC_REG_CR8,
	PPC_REG_CR9,
	PPC_REG_CR10,
	PPC_REG_CR11,
	PPC_REG_CR12,
	PPC_REG_CR13,
	PPC_REG_CR14,
	PPC_REG_CR15,
	PPC_REG_CR16,
	PPC_REG_CR17,
	PPC_REG_CR18,
	PPC_REG_CR19,
	PPC_REG_CR20,
	PPC_REG_CR21,
	PPC_REG_CR22,
	PPC_REG_CR23,
	PPC_REG_CR24,
	PPC_REG_CR25,
	PPC_REG_CR26,
	PPC_REG_CR27,
	PPC_REG_CR28,
	PPC_REG_CR29,
	PPC_REG_CR30,
	PPC_REG_CR31,
	PPC_REG_CTR,
	PPC_REG_F0,
	PPC_REG_F1,
	PPC_REG_F2,
	PPC_REG_F3,
	PPC_REG_F4,
	PPC_REG_F5,
	PPC_REG_F6,
	PPC_REG_F7,
	PPC_REG_F8,
	PPC_REG_F9,
	PPC_REG_F10,
	PPC_REG_F11,
	PPC_REG_F12,
	PPC_REG_F13,
	PPC_REG_F14,
	PPC_REG_F15,
	PPC_REG_F16,
	PPC_REG_F17,
	PPC_REG_F18,
	PPC_REG_F19,
	PPC_REG_F20,
	PPC_REG_F21,
	PPC_REG_F22,
	PPC_REG_F23,
	PPC_REG_F24,
	PPC_REG_F25,
	PPC_REG_F26,
	PPC_REG_F27,
	PPC_REG_F28,
	PPC_REG_F29,
	PPC_REG_F30,
	PPC_REG_F31,
	PPC_REG_LR,
	PPC_REG_R0,
	PPC_REG_R1,
	PPC_REG_R2,
	PPC_REG_R3,
	PPC_REG_R4,
	PPC_REG_R5,
	PPC_REG_R6,
	PPC_REG_R7,
	PPC_REG_R8,
	PPC_REG_R9,
	PPC_REG_R10,
	PPC_REG_R11,
	PPC_REG_R12,
	PPC_REG_R13,
	PPC_REG_R14,
	PPC_REG_R15,
	PPC_REG_R16,
	PPC_REG_R17,
	PPC_REG_R18,
	PPC_REG_R19,
	PPC_REG_R20,
	PPC_REG_R21,
	PPC_REG_R22,
	PPC_REG_R23,
	PPC_REG_R24,
	PPC_REG_R25,
	PPC_REG_R26,
	PPC_REG_R27,
	PPC_REG_R28,
	PPC_REG_R29,
	PPC_REG_R30,
	PPC_REG_R31,
	PPC_REG_V0,
	PPC_REG_V1,
	PPC_REG_V2,
	PPC_REG_V3,
	PPC_REG_V4,
	PPC_REG_V5,
	PPC_REG_V6,
	PPC_REG_V7,
	PPC_REG_V8,
	PPC_REG_V9,
	PPC_REG_V10,
	PPC_REG_V11,
	PPC_REG_V12,
	PPC_REG_V13,
	PPC_REG_V14,
	PPC_REG_V15,
	PPC_REG_V16,
	PPC_REG_V17,
	PPC_REG_V18,
	PPC_REG_V19,
	PPC_REG_V20,
	PPC_REG_V21,
	PPC_REG_V22,
	PPC_REG_V23,
	PPC_REG_V24,
	PPC_REG_V25,
	PPC_REG_V26,
	PPC_REG_V27,
	PPC_REG_V28,
	PPC_REG_V29,
	PPC_REG_V30,
	PPC_REG_V31,
	PPC_REG_VRSAVE,

	// extra registers for mapping.c
	PPC_REG_RM,
	PPC_REG_CTR8,
	PPC_REG_LR8,
	PPC_REG_CR1EQ,

	PPC_REG_MAX,   // <-- mark the end of the list of registers
} ppc_reg;

//> PPC instruction
typedef enum ppc_insn {
	PPC_INS_INVALID = 0,

	PPC_INS_ADD,
	PPC_INS_ADDC,
	PPC_INS_ADDE,
	PPC_INS_ADDI,
	PPC_INS_ADDIC,
	PPC_INS_ADDIS,
	PPC_INS_ADDME,
	PPC_INS_ADDZE,
	PPC_INS_AND,
	PPC_INS_ANDC,
	PPC_INS_ANDIS,
	PPC_INS_ANDI,
	PPC_INS_B,
	PPC_INS_BA,
	PPC_INS_BCL,
	PPC_INS_BCTR,
	PPC_INS_BCTRL,
	PPC_INS_BDNZ,
	PPC_INS_BDNZA,
	PPC_INS_BDNZL,
	PPC_INS_BDNZLA,
	PPC_INS_BDNZLR,
	PPC_INS_BDNZLRL,
	PPC_INS_BDZ,
	PPC_INS_BDZA,
	PPC_INS_BDZL,
	PPC_INS_BDZLA,
	PPC_INS_BDZLR,
	PPC_INS_BDZLRL,
	PPC_INS_BL,
	PPC_INS_BLA,
	PPC_INS_BLR,
	PPC_INS_BLRL,
	PPC_INS_CMPD,
	PPC_INS_CMPDI,
	PPC_INS_CMPLD,
	PPC_INS_CMPLDI,
	PPC_INS_CMPLW,
	PPC_INS_CMPLWI,
	PPC_INS_CMPW,
	PPC_INS_CMPWI,
	PPC_INS_CNTLZD,
	PPC_INS_CNTLZW,
	PPC_INS_CREQV,
	PPC_INS_CRXOR,
	PPC_INS_CRAND,
	PPC_INS_CRANDC,
	PPC_INS_CRNAND,
	PPC_INS_CRNOR,
	PPC_INS_CROR,
	PPC_INS_CRORC,
	PPC_INS_DCBA,
	PPC_INS_DCBF,
	PPC_INS_DCBI,
	PPC_INS_DCBST,
	PPC_INS_DCBT,
	PPC_INS_DCBTST,
	PPC_INS_DCBZ,
	PPC_INS_DCBZL,
	PPC_INS_DIVD,
	PPC_INS_DIVDU,
	PPC_INS_DIVW,
	PPC_INS_DIVWU,
	PPC_INS_DSS,
	PPC_INS_DSSALL,
	PPC_INS_DST,
	PPC_INS_DSTST,
	PPC_INS_DSTSTT,
	PPC_INS_DSTT,
	PPC_INS_EIEIO,
	PPC_INS_EQV,
	PPC_INS_EXTSB,
	PPC_INS_EXTSH,
	PPC_INS_EXTSW,
	PPC_INS_FABS,
	PPC_INS_FADD,
	PPC_INS_FADDS,
	PPC_INS_FCFID,
	PPC_INS_FCFIDS,
	PPC_INS_FCFIDU,
	PPC_INS_FCFIDUS,
	PPC_INS_FCMPU,
	PPC_INS_FCPSGN,
	PPC_INS_FCTID,
	PPC_INS_FCTIDUZ,
	PPC_INS_FCTIDZ,
	PPC_INS_FCTIW,
	PPC_INS_FCTIWUZ,
	PPC_INS_FCTIWZ,
	PPC_INS_FDIV,
	PPC_INS_FDIVS,
	PPC_INS_FMADD,
	PPC_INS_FMADDS,
	PPC_INS_FMR,
	PPC_INS_FMSUB,
	PPC_INS_FMSUBS,
	PPC_INS_FMUL,
	PPC_INS_FMULS,
	PPC_INS_FNABS,
	PPC_INS_FNEG,
	PPC_INS_FNMADD,
	PPC_INS_FNMADDS,
	PPC_INS_FNMSUB,
	PPC_INS_FNMSUBS,
	PPC_INS_FRE,
	PPC_INS_FRES,
	PPC_INS_FRIM,
	PPC_INS_FRIN,
	PPC_INS_FRIP,
	PPC_INS_FRIZ,
	PPC_INS_FRSP,
	PPC_INS_FRSQRTE,
	PPC_INS_FRSQRTES,
	PPC_INS_FSEL,
	PPC_INS_FSQRT,
	PPC_INS_FSQRTS,
	PPC_INS_FSUB,
	PPC_INS_FSUBS,
	PPC_INS_ICBI,
	PPC_INS_ISEL,
	PPC_INS_ISYNC,
	PPC_INS_LA,
	PPC_INS_LBZ,
	PPC_INS_LBZU,
	PPC_INS_LBZUX,
	PPC_INS_LBZX,
	PPC_INS_LD,
	PPC_INS_LDARX,
	PPC_INS_LDBRX,
	PPC_INS_LDU,
	PPC_INS_LDUX,
	PPC_INS_LDX,
	PPC_INS_LFD,
	PPC_INS_LFDU,
	PPC_INS_LFDUX,
	PPC_INS_LFDX,
	PPC_INS_LFIWAX,
	PPC_INS_LFIWZX,
	PPC_INS_LFS,
	PPC_INS_LFSU,
	PPC_INS_LFSUX,
	PPC_INS_LFSX,
	PPC_INS_LHA,
	PPC_INS_LHAU,
	PPC_INS_LHAUX,
	PPC_INS_LHAX,
	PPC_INS_LHBRX,
	PPC_INS_LHZ,
	PPC_INS_LHZU,
	PPC_INS_LHZUX,
	PPC_INS_LHZX,
	PPC_INS_LI,
	PPC_INS_LIS,
	PPC_INS_LMW,
	PPC_INS_LVEBX,
	PPC_INS_LVEHX,
	PPC_INS_LVEWX,
	PPC_INS_LVSL,
	PPC_INS_LVSR,
	PPC_INS_LVX,
	PPC_INS_LVXL,
	PPC_INS_LWA,
	PPC_INS_LWARX,
	PPC_INS_LWAUX,
	PPC_INS_LWAX,
	PPC_INS_LWBRX,
	PPC_INS_LWZ,
	PPC_INS_LWZU,
	PPC_INS_LWZUX,
	PPC_INS_LWZX,
	PPC_INS_MCRF,
	PPC_INS_MFCR,
	PPC_INS_MFCTR,
	PPC_INS_MFFS,
	PPC_INS_MFLR,
	PPC_INS_MFMSR,
	PPC_INS_MFOCRF,
	PPC_INS_MFSPR,
	PPC_INS_MFTB,
	PPC_INS_MFVSCR,
	PPC_INS_MSYNC,
	PPC_INS_MTCRF,
	PPC_INS_MTCTR,
	PPC_INS_MTFSB0,
	PPC_INS_MTFSB1,
	PPC_INS_MTFSF,
	PPC_INS_MTLR,
	PPC_INS_MTMSR,
	PPC_INS_MTMSRD,
	PPC_INS_MTOCRF,
	PPC_INS_MTSPR,
	PPC_INS_MTVSCR,
	PPC_INS_MULHD,
	PPC_INS_MULHDU,
	PPC_INS_MULHW,
	PPC_INS_MULHWU,
	PPC_INS_MULLD,
	PPC_INS_MULLI,
	PPC_INS_MULLW,
	PPC_INS_NAND,
	PPC_INS_NEG,
	PPC_INS_NOP,
	PPC_INS_ORI,
	PPC_INS_NOR,
	PPC_INS_OR,
	PPC_INS_ORC,
	PPC_INS_ORIS,
	PPC_INS_POPCNTD,
	PPC_INS_POPCNTW,
	PPC_INS_RLDCL,
	PPC_INS_RLDCR,
	PPC_INS_RLDIC,
	PPC_INS_RLDICL,
	PPC_INS_RLDICR,
	PPC_INS_RLDIMI,
	PPC_INS_RLWIMI,
	PPC_INS_RLWINM,
	PPC_INS_RLWNM,
	PPC_INS_SC,
	PPC_INS_SLBIA,
	PPC_INS_SLBIE,
	PPC_INS_SLBMFEE,
	PPC_INS_SLBMTE,
	PPC_INS_SLD,
	PPC_INS_SLW,
	PPC_INS_SRAD,
	PPC_INS_SRADI,
	PPC_INS_SRAW,
	PPC_INS_SRAWI,
	PPC_INS_SRD,
	PPC_INS_SRW,
	PPC_INS_STB,
	PPC_INS_STBU,
	PPC_INS_STBUX,
	PPC_INS_STBX,
	PPC_INS_STD,
	PPC_INS_STDBRX,
	PPC_INS_STDCX,
	PPC_INS_STDU,
	PPC_INS_STDUX,
	PPC_INS_STDX,
	PPC_INS_STFD,
	PPC_INS_STFDU,
	PPC_INS_STFDUX,
	PPC_INS_STFDX,
	PPC_INS_STFIWX,
	PPC_INS_STFS,
	PPC_INS_STFSU,
	PPC_INS_STFSUX,
	PPC_INS_STFSX,
	PPC_INS_STH,
	PPC_INS_STHBRX,
	PPC_INS_STHU,
	PPC_INS_STHUX,
	PPC_INS_STHX,
	PPC_INS_STMW,
	PPC_INS_STVEBX,
	PPC_INS_STVEHX,
	PPC_INS_STVEWX,
	PPC_INS_STVX,
	PPC_INS_STVXL,
	PPC_INS_STW,
	PPC_INS_STWBRX,
	PPC_INS_STWCX,
	PPC_INS_STWU,
	PPC_INS_STWUX,
	PPC_INS_STWX,
	PPC_INS_SUBF,
	PPC_INS_SUBFC,
	PPC_INS_SUBFE,
	PPC_INS_SUBFIC,
	PPC_INS_SUBFME,
	PPC_INS_SUBFZE,
	PPC_INS_SYNC,
	PPC_INS_TD,
	PPC_INS_TDI,
	PPC_INS_TLBIE,
	PPC_INS_TLBIEL,
	PPC_INS_TLBSYNC,
	PPC_INS_TRAP,
	PPC_INS_TW,
	PPC_INS_TWI,
	PPC_INS_VADDCUW,
	PPC_INS_VADDFP,
	PPC_INS_VADDSBS,
	PPC_INS_VADDSHS,
	PPC_INS_VADDSWS,
	PPC_INS_VADDUBM,
	PPC_INS_VADDUBS,
	PPC_INS_VADDUHM,
	PPC_INS_VADDUHS,
	PPC_INS_VADDUWM,
	PPC_INS_VADDUWS,
	PPC_INS_VAND,
	PPC_INS_VANDC,
	PPC_INS_VAVGSB,
	PPC_INS_VAVGSH,
	PPC_INS_VAVGSW,
	PPC_INS_VAVGUB,
	PPC_INS_VAVGUH,
	PPC_INS_VAVGUW,
	PPC_INS_VCFSX,
	PPC_INS_VCFUX,
	PPC_INS_VCMPBFP,
	PPC_INS_VCMPEQFP,
	PPC_INS_VCMPEQUB,
	PPC_INS_VCMPEQUH,
	PPC_INS_VCMPEQUW,
	PPC_INS_VCMPGEFP,
	PPC_INS_VCMPGTFP,
	PPC_INS_VCMPGTSB,
	PPC_INS_VCMPGTSH,
	PPC_INS_VCMPGTSW,
	PPC_INS_VCMPGTUB,
	PPC_INS_VCMPGTUH,
	PPC_INS_VCMPGTUW,
	PPC_INS_VCTSXS,
	PPC_INS_VCTUXS,
	PPC_INS_VEXPTEFP,
	PPC_INS_VLOGEFP,
	PPC_INS_VMADDFP,
	PPC_INS_VMAXFP,
	PPC_INS_VMAXSB,
	PPC_INS_VMAXSH,
	PPC_INS_VMAXSW,
	PPC_INS_VMAXUB,
	PPC_INS_VMAXUH,
	PPC_INS_VMAXUW,
	PPC_INS_VMHADDSHS,
	PPC_INS_VMHRADDSHS,
	PPC_INS_VMINFP,
	PPC_INS_VMINSB,
	PPC_INS_VMINSH,
	PPC_INS_VMINSW,
	PPC_INS_VMINUB,
	PPC_INS_VMINUH,
	PPC_INS_VMINUW,
	PPC_INS_VMLADDUHM,
	PPC_INS_VMRGHB,
	PPC_INS_VMRGHH,
	PPC_INS_VMRGHW,
	PPC_INS_VMRGLB,
	PPC_INS_VMRGLH,
	PPC_INS_VMRGLW,
	PPC_INS_VMSUMMBM,
	PPC_INS_VMSUMSHM,
	PPC_INS_VMSUMSHS,
	PPC_INS_VMSUMUBM,
	PPC_INS_VMSUMUHM,
	PPC_INS_VMSUMUHS,
	PPC_INS_VMULESB,
	PPC_INS_VMULESH,
	PPC_INS_VMULEUB,
	PPC_INS_VMULEUH,
	PPC_INS_VMULOSB,
	PPC_INS_VMULOSH,
	PPC_INS_VMULOUB,
	PPC_INS_VMULOUH,
	PPC_INS_VNMSUBFP,
	PPC_INS_VNOR,
	PPC_INS_VOR,
	PPC_INS_VPERM,
	PPC_INS_VPKPX,
	PPC_INS_VPKSHSS,
	PPC_INS_VPKSHUS,
	PPC_INS_VPKSWSS,
	PPC_INS_VPKSWUS,
	PPC_INS_VPKUHUM,
	PPC_INS_VPKUHUS,
	PPC_INS_VPKUWUM,
	PPC_INS_VPKUWUS,
	PPC_INS_VREFP,
	PPC_INS_VRFIM,
	PPC_INS_VRFIN,
	PPC_INS_VRFIP,
	PPC_INS_VRFIZ,
	PPC_INS_VRLB,
	PPC_INS_VRLH,
	PPC_INS_VRLW,
	PPC_INS_VRSQRTEFP,
	PPC_INS_VSEL,
	PPC_INS_VSL,
	PPC_INS_VSLB,
	PPC_INS_VSLDOI,
	PPC_INS_VSLH,
	PPC_INS_VSLO,
	PPC_INS_VSLW,
	PPC_INS_VSPLTB,
	PPC_INS_VSPLTH,
	PPC_INS_VSPLTISB,
	PPC_INS_VSPLTISH,
	PPC_INS_VSPLTISW,
	PPC_INS_VSPLTW,
	PPC_INS_VSR,
	PPC_INS_VSRAB,
	PPC_INS_VSRAH,
	PPC_INS_VSRAW,
	PPC_INS_VSRB,
	PPC_INS_VSRH,
	PPC_INS_VSRO,
	PPC_INS_VSRW,
	PPC_INS_VSUBCUW,
	PPC_INS_VSUBFP,
	PPC_INS_VSUBSBS,
	PPC_INS_VSUBSHS,
	PPC_INS_VSUBSWS,
	PPC_INS_VSUBUBM,
	PPC_INS_VSUBUBS,
	PPC_INS_VSUBUHM,
	PPC_INS_VSUBUHS,
	PPC_INS_VSUBUWM,
	PPC_INS_VSUBUWS,
	PPC_INS_VSUM2SWS,
	PPC_INS_VSUM4SBS,
	PPC_INS_VSUM4SHS,
	PPC_INS_VSUM4UBS,
	PPC_INS_VSUMSWS,
	PPC_INS_VUPKHPX,
	PPC_INS_VUPKHSB,
	PPC_INS_VUPKHSH,
	PPC_INS_VUPKLPX,
	PPC_INS_VUPKLSB,
	PPC_INS_VUPKLSH,
	PPC_INS_VXOR,
	PPC_INS_WAIT,
	PPC_INS_XOR,
	PPC_INS_XORI,
	PPC_INS_XORIS,
	PPC_INS_BC,
	PPC_INS_BCA,
	PPC_INS_BCCTR,
	PPC_INS_BCCTRL,
	PPC_INS_BCLA,
	PPC_INS_BCLR,
	PPC_INS_BCLRL,

	PPC_INS_MAX,   // <-- mark the end of the list of instructions
} ppc_insn;

//> Group of PPC instructions
typedef enum ppc_insn_group {
	PPC_GRP_INVALID = 0,

	PPC_GRP_ALTIVEC,
	PPC_GRP_MODE32,
	PPC_GRP_MODE64,
	PPC_GRP_BOOKE,
	PPC_GRP_NOTBOOKE,

	PPC_GRP_JUMP,	// all jump instructions (conditional+direct+indirect jumps)

	PPC_GRP_MAX,   // <-- mark the end of the list of groups
} ppc_insn_group;

#ifdef __cplusplus
}
#endif

#endif
