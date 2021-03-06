#include <stdint.h>
#include "instruction/base.hpp"
#include "emulator/exception.hpp"

#define instr16(f) ((instrfunc_t)&Instr16::f)

Instr16::Instr16(Emulator *e, InstrData *id) : Instruction(e, id, false) {
	int i;

	// 0x00 : add_rm8_r8
	set_funcflag(0x01, instr16(add_rm16_r16), CHK_MODRM);
	// 0x02 : add_r8_rm8
	set_funcflag(0x03, instr16(add_r16_rm16), CHK_MODRM);
	// 0x04 : add_al_imm8
	set_funcflag(0x05, instr16(add_ax_imm16), CHK_IMM16);
	set_funcflag(0x06, instr16(push_es), 0);
	set_funcflag(0x07, instr16(pop_es), 0);
	// 0x08 : or_rm8_r8
	set_funcflag(0x09, instr16(or_rm16_r16), CHK_MODRM);
	// 0x0a : or_r8_rm8
	set_funcflag(0x0b, instr16(or_r16_rm16), CHK_MODRM);
	// 0x0c : or_al_imm8
	set_funcflag(0x0d, instr16(or_ax_imm16), CHK_IMM16);

	set_funcflag(0x16, instr16(push_ss), 0);
	set_funcflag(0x17, instr16(pop_ss), 0);

	set_funcflag(0x1e, instr16(push_ds), 0);
	set_funcflag(0x1f, instr16(pop_ds), 0);
	// 0x20 : and_rm8_r8
	set_funcflag(0x21, instr16(and_rm16_r16), CHK_MODRM);
	// 0x22 : and_r8_rm8
	set_funcflag(0x23, instr16(and_r16_rm16), CHK_MODRM);
	// 0x24 : and_al_imm8
	set_funcflag(0x25, instr16(and_ax_imm16), CHK_IMM16);

	// 0x28 : sub_rm8_r8
	set_funcflag(0x29, instr16(sub_rm16_r16), CHK_MODRM);
	// 0x2a : sub_r8_rm8
	set_funcflag(0x2b, instr16(sub_r16_rm16), CHK_MODRM);
	// 0x2c : sub_al_imm8
	set_funcflag(0x2d, instr16(sub_ax_imm16), CHK_IMM16);

	// 0x30 : xor_rm8_r8
	set_funcflag(0x31, instr16(xor_rm16_r16), CHK_MODRM);
	// 0x16 : xor_r8_rm8
	set_funcflag(0x33, instr16(xor_r16_rm16), CHK_MODRM);
	// 0x34 : xor_al_imm8
	set_funcflag(0x35, instr16(xor_ax_imm16), CHK_IMM16);

	// 0x38 : cmp_rm8_r8
	set_funcflag(0x39, instr16(cmp_rm16_r16), CHK_MODRM);
	// 0x3a : cmp_r8_rm8
	set_funcflag(0x3b, instr16(cmp_r16_rm16), CHK_MODRM);
	// 0x3c : cmp_al_imm8
	set_funcflag(0x3d, instr16(cmp_ax_imm16), CHK_IMM16);

	for (i=0; i<8; i++)	set_funcflag(0x40+i, instr16(inc_r16) ,0);
	for (i=0; i<8; i++)	set_funcflag(0x48+i, instr16(dec_r16) ,0);
	for (i=0; i<8; i++)	set_funcflag(0x50+i, instr16(push_r16) ,0);
	for (i=0; i<8; i++)	set_funcflag(0x58+i, instr16(pop_r16) ,0);

	set_funcflag(0x60, instr16(pusha), 0);
	set_funcflag(0x61, instr16(popa), 0);

	set_funcflag(0x68, instr16(push_imm16), CHK_IMM16);
	set_funcflag(0x69, instr16(imul_r16_rm16_imm16), CHK_MODRM|CHK_IMM16);
	set_funcflag(0x6a, instr16(push_imm8), CHK_IMM8);
	set_funcflag(0x6b, instr16(imul_r16_rm16_imm8), CHK_MODRM|CHK_IMM8);

	// 0x70-0x7f : jcc

	// 0x84 : test_rm8_r8
	set_funcflag(0x85, instr16(test_rm16_r16), CHK_MODRM);
	// 0x86 : xchg_r8_rm8
	set_funcflag(0x87, instr16(xchg_r16_rm16), CHK_MODRM);
	// 0x88 : mov_rm8_r8
	set_funcflag(0x89, instr16(mov_rm16_r16), CHK_MODRM);
	// 0x8a : mov_r8_rm8
	set_funcflag(0x8b, instr16(mov_r16_rm16), CHK_MODRM);
	set_funcflag(0x8c, instr16(mov_rm16_sreg), CHK_MODRM);
	set_funcflag(0x8d, instr16(lea_r16_m16), CHK_MODRM);
	// 0x8e : mov_sreg_rm16

	// 0x90 : nop
	for (i=1; i<8; i++)	set_funcflag(0x90+i, instr16(xchg_r16_ax) ,CHK_IMM16);
	set_funcflag(0x98, instr16(cbw), 0);
	set_funcflag(0x99, instr16(cwd), 0);
	set_funcflag(0x9a, instr16(callf_ptr16_16), CHK_PTR16 | CHK_IMM16);

	set_funcflag(0x9c, instr16(pushf), 0);
	set_funcflag(0x9d, instr16(popf), 0);

	// 0xa0 : mov_al_moffs8
	set_funcflag(0xa1, instr16(mov_ax_moffs16), CHK_MOFFS);
	// 0xa2 : mov_moffs8_al
	set_funcflag(0xa3, instr16(mov_moffs16_ax), CHK_MOFFS);

	set_funcflag(0xa6, instr16(cmps_m8_m8), 0);
	set_funcflag(0xa7, instr16(cmps_m16_m16), 0);
	// 0xa8 : test_al_imm8
	set_funcflag(0xa9, instr16(test_ax_imm16), CHK_IMM16);

	// 0xb0-0xb7 : mov_r8_imm
	for (i=0; i<8; i++)	set_funcflag(0xb8+i, instr16(mov_r16_imm16) ,CHK_IMM16);

	set_funcflag(0xc3, instr16(ret), 0);

	set_funcflag(0xc7, instr16(mov_rm16_imm16), CHK_MODRM | CHK_IMM16);

	set_funcflag(0xc9, instr16(leave), 0);

	// 0xcb : retf
	// 0xcc : int3
	// 0xcd : int_imm8

	// 0xcf : iret

	// 0xe4 : in_al_imm8
	set_funcflag(0xe5, instr16(in_ax_imm8), CHK_IMM8);
	// 0xe6 : out_imm8_al
	set_funcflag(0xe7, instr16(out_imm8_ax), CHK_IMM8);
	set_funcflag(0xe8, instr16(call_rel16), CHK_IMM16);
	set_funcflag(0xe9, instr16(jmp_rel16), CHK_IMM16);
	set_funcflag(0xea, instr16(jmpf_ptr16_16), CHK_PTR16 | CHK_IMM16);
	// 0xeb : jmp
	// 0xec : in_al_dx
	set_funcflag(0xed, instr16(in_ax_dx), 0);
	// 0xee : out_dx_al
	set_funcflag(0xef, instr16(out_dx_ax), 0);

	set_funcflag(0x0f80, instr16(jo_rel16), CHK_IMM16);
	set_funcflag(0x0f81, instr16(jno_rel16), CHK_IMM16);
	set_funcflag(0x0f82, instr16(jb_rel16), CHK_IMM16);
	set_funcflag(0x0f83, instr16(jnb_rel16), CHK_IMM16);
	set_funcflag(0x0f84, instr16(jz_rel16), CHK_IMM16);
	set_funcflag(0x0f85, instr16(jnz_rel16), CHK_IMM16);
	set_funcflag(0x0f86, instr16(jbe_rel16), CHK_IMM16);
	set_funcflag(0x0f87, instr16(ja_rel16), CHK_IMM16);
	set_funcflag(0x0f88, instr16(js_rel16), CHK_IMM16);
	set_funcflag(0x0f89, instr16(jns_rel16), CHK_IMM16);
	set_funcflag(0x0f8a, instr16(jp_rel16), CHK_IMM16);
	set_funcflag(0x0f8b, instr16(jnp_rel16), CHK_IMM16);
	set_funcflag(0x0f8c, instr16(jl_rel16), CHK_IMM16);
	set_funcflag(0x0f8d, instr16(jnl_rel16), CHK_IMM16);
	set_funcflag(0x0f8e, instr16(jle_rel16), CHK_IMM16);
	set_funcflag(0x0f8f, instr16(jnle_rel16), CHK_IMM16);

	set_funcflag(0x0faf, instr16(imul_r16_rm16), CHK_MODRM);

	set_funcflag(0x0fb6, instr16(movzx_r16_rm8), CHK_MODRM);
	set_funcflag(0x0fb7, instr16(movzx_r16_rm16), CHK_MODRM);

	set_funcflag(0x0fbe, instr16(movsx_r16_rm8), CHK_MODRM);
	set_funcflag(0x0fbf, instr16(movsx_r16_rm16), CHK_MODRM);

	// 0x80 : code_80
	set_funcflag(0x81, instr16(code_81), CHK_MODRM | CHK_IMM16);
	// 0x82 : code_82
	set_funcflag(0x83, instr16(code_83), CHK_MODRM | CHK_IMM8);
	// 0xc0 : code_c0
	set_funcflag(0xc1, instr16(code_c1), CHK_MODRM | CHK_IMM8);
	set_funcflag(0xd3, instr16(code_d3), CHK_MODRM);
	set_funcflag(0xf7, instr16(code_f7), CHK_MODRM);
	set_funcflag(0xff, instr16(code_ff), CHK_MODRM);
	set_funcflag(0x0f00, instr16(code_0f00), CHK_MODRM);
	set_funcflag(0x0f01, instr16(code_0f01), CHK_MODRM);
}

void Instr16::add_rm16_r16(void){
	uint16_t rm16, r16;

	rm16 = get_rm16();
	r16 = get_r16();
	set_rm16(rm16+r16);
	EFLAGS_UPDATE_ADD(rm16, r16);
}

void Instr16::add_r16_rm16(void){
	uint16_t r16, rm16;

	r16 = get_r16();
	rm16 = get_rm16();
	set_r16(r16+rm16);
	EFLAGS_UPDATE_ADD(r16, rm16);
}

void Instr16::add_ax_imm16(void){
	uint16_t ax;

	ax = GET_GPREG(AX);
	SET_GPREG(AX, ax+IMM16);
	EFLAGS_UPDATE_ADD(ax, IMM16);
}

void Instr16::push_es(void){
	PUSH16(EMU->get_segment(ES));
}

void Instr16::pop_es(void){
	EMU->set_segment(ES, POP16());
}

void Instr16::or_rm16_r16(void){
	uint16_t rm16, r16;

	rm16 = get_rm16();
	r16 = get_r16();
	set_rm16(rm16|r16);
	EFLAGS_UPDATE_OR(rm16, r16);
}

void Instr16::or_r16_rm16(void){
	uint16_t r16, rm16;

	r16 = get_r16();
	rm16 = get_rm16();
	set_r16(r16|rm16);
	EFLAGS_UPDATE_OR(r16, rm16);
}

void Instr16::or_ax_imm16(void){
	uint16_t ax;

	ax = GET_GPREG(AX);
	SET_GPREG(AX, ax|IMM16);
	EFLAGS_UPDATE_OR(ax, IMM16);
}

void Instr16::push_ss(void){
	PUSH16(EMU->get_segment(SS));
}

void Instr16::pop_ss(void){
	EMU->set_segment(SS, POP16());
}

void Instr16::push_ds(void){
	PUSH16(EMU->get_segment(DS));
}

void Instr16::pop_ds(void){
	EMU->set_segment(DS, POP16());
}

void Instr16::and_rm16_r16(void){
	uint16_t rm16, r16;

	rm16 = get_rm16();
	r16 = get_r16();
	set_rm16(rm16&r16);
	EFLAGS_UPDATE_AND(rm16, r16);
}

void Instr16::and_r16_rm16(void){
	uint16_t r16, rm16;

	r16 = get_r16();
	rm16 = get_rm16();
	set_r16(r16&rm16);
	EFLAGS_UPDATE_AND(r16, rm16);
}

void Instr16::and_ax_imm16(void){
	uint16_t ax;

	ax = GET_GPREG(AX);
	SET_GPREG(AX, ax&IMM16);
	EFLAGS_UPDATE_AND(ax, IMM16);
}

void Instr16::sub_rm16_r16(void){
	uint16_t rm16, r16;

	rm16 = get_rm16();
	r16 = get_r16();
	set_rm16(rm16-r16);
	EFLAGS_UPDATE_SUB(rm16, r16);
}

void Instr16::sub_r16_rm16(void){
	uint16_t r16, rm16;

	r16 = get_r16();
	rm16 = get_rm16();
	set_r16(r16-rm16);
	EFLAGS_UPDATE_SUB(r16, rm16);
}

void Instr16::sub_ax_imm16(void){
	uint16_t ax;

	ax = GET_GPREG(AX);
	SET_GPREG(AX, ax-IMM16);
	EFLAGS_UPDATE_SUB(ax, IMM16);
}

void Instr16::xor_rm16_r16(void){
	uint16_t rm16, r16;

	rm16 = get_rm16();
	r16 = get_r16();
	set_rm16(rm16^r16);
}

void Instr16::xor_r16_rm16(void){
	uint16_t r16, rm16;

	r16 = get_r16();
	rm16 = get_rm16();
	set_r16(r16^rm16);
}

void Instr16::xor_ax_imm16(void){
	uint16_t ax;

	ax = GET_GPREG(AX);
	SET_GPREG(AX, ax^IMM16);
}

void Instr16::cmp_rm16_r16(void){
	uint16_t rm16, r16;

	rm16 = get_rm16();
	r16 = get_r16();
	EFLAGS_UPDATE_SUB(rm16, r16);
}

void Instr16::cmp_r16_rm16(void){
	uint16_t r16, rm16;

	r16 = get_r16();
	rm16 = get_rm16();
	EFLAGS_UPDATE_SUB(r16, rm16);
}

void Instr16::cmp_ax_imm16(void){
	uint16_t ax;

	ax = GET_GPREG(AX);
	EFLAGS_UPDATE_SUB(ax, IMM16);
}

void Instr16::inc_r16(void){
	uint8_t reg;
	uint16_t r16;

	reg = OPCODE & ((1<<3)-1);
	r16 = GET_GPREG(static_cast<reg16_t>(reg));
	SET_GPREG(static_cast<reg16_t>(reg), r16+1);
	EFLAGS_UPDATE_ADD(r16, 1);
}

void Instr16::dec_r16(void){
	uint8_t reg;
	uint16_t r16;

	reg = OPCODE & ((1<<3)-1);
	r16 = GET_GPREG(static_cast<reg16_t>(reg));
	SET_GPREG(static_cast<reg16_t>(reg), r16-1);
	EFLAGS_UPDATE_SUB(r16, 1);
}

void Instr16::push_r16(void){
	uint8_t reg;

	reg = OPCODE & ((1<<3)-1);
	PUSH16(GET_GPREG(static_cast<reg16_t>(reg)));
}

void Instr16::pop_r16(void){
	uint8_t reg;

	reg = OPCODE & ((1<<3)-1);
	SET_GPREG(static_cast<reg16_t>(reg), POP16());
}

void Instr16::pusha(void){
	uint16_t sp;
	
	sp = GET_GPREG(SP);

	PUSH16(GET_GPREG(AX));
	PUSH16(GET_GPREG(CX));
	PUSH16(GET_GPREG(DX));
	PUSH16(GET_GPREG(BX));
	PUSH16(sp);
	PUSH16(GET_GPREG(BP));
	PUSH16(GET_GPREG(SI));
	PUSH16(GET_GPREG(DI));
}

void Instr16::popa(void){
	uint16_t sp;

	SET_GPREG(DI, POP16());
	SET_GPREG(SI, POP16());
	SET_GPREG(BP, POP16());
	sp = POP16();
	SET_GPREG(BX, POP16());
	SET_GPREG(DX, POP16());
	SET_GPREG(CX, POP16());
	SET_GPREG(AX, POP16());

	SET_GPREG(SP, sp);
}

void Instr16::push_imm16(void){
	PUSH16(IMM16);
}

void Instr16::imul_r16_rm16_imm16(void){
	int16_t rm16_s;

	rm16_s = get_rm16();
	set_r16(rm16_s*IMM16);
	EFLAGS_UPDATE_IMUL(rm16_s, IMM16);
}

void Instr16::push_imm8(void){
	PUSH16(IMM8);
}

void Instr16::imul_r16_rm16_imm8(void){
	int16_t rm16_s;

	rm16_s = get_rm16();
	set_r16(rm16_s*IMM8);
	EFLAGS_UPDATE_IMUL(rm16_s, IMM8);
}

void Instr16::test_rm16_r16(void){
	uint16_t rm16, r16;

	rm16 = get_rm16();
	r16 = get_r16();
	EFLAGS_UPDATE_AND(rm16, r16);
}

void Instr16::xchg_r16_rm16(void){
	uint16_t r16, rm16;

	r16 = get_r16();
	rm16 = get_rm16();
	set_r16(rm16);
	set_rm16(r16);
}

void Instr16::mov_rm16_r16(void){
	uint16_t r16;

	r16 = get_r16();
	set_rm16(r16);
}

void Instr16::mov_r16_rm16(void){
	uint16_t rm16;

	rm16 = get_rm16();
	set_r16(rm16);
}

void Instr16::mov_rm16_sreg(void){
	uint16_t sreg;

	sreg = get_sreg();
	set_rm16(sreg);
}

void Instr16::lea_r16_m16(void){
	uint16_t m16;

	m16 = get_m();
	set_r16(m16);
}

void Instr16::xchg_r16_ax(void){
	uint16_t r16, ax;

	r16 = get_r16();
	ax = GET_GPREG(AX);
	set_r16(ax);
	SET_GPREG(AX, r16);
}

void Instr16::cbw(void){
	int8_t al_s;

	al_s = GET_GPREG(AL);
	SET_GPREG(AX, al_s);
}

void Instr16::cwd(void){
	uint16_t ax;

	ax = GET_GPREG(AX);
	SET_GPREG(DX, ax&(1<<15) ? -1 : 0);
}

void Instr16::callf_ptr16_16(void){
	EmuInstr::callf(PTR16, IMM16);
}

void Instr16::pushf(void){
	PUSH16(EMU->get_flags());
}

void Instr16::popf(void){
	EMU->set_flags(POP16());
}

void Instr16::mov_ax_moffs16(void){
	SET_GPREG(AX, get_moffs16());
}

void Instr16::mov_moffs16_ax(void){
	set_moffs16(GET_GPREG(AX));
}

void Instr16::cmps_m8_m8(void){
	uint8_t m8_s, m8_d;

repeat:
	m8_s = EMU->get_data8(select_segment(), GET_GPREG(SI));
	m8_d = EMU->get_data8(ES, GET_GPREG(DI));
	EFLAGS_UPDATE_SUB(m8_s, m8_d);

	UPDATE_GPREG(SI, EFLAGS_DF ? -1 : 1);
	UPDATE_GPREG(DI, EFLAGS_DF ? -1 : 1);
	
	if(PRE_REPEAT){
		UPDATE_GPREG(CX, -1);
		switch(PRE_REPEAT){
			case REPZ:
				if(!GET_GPREG(CX) || !EFLAGS_ZF)
					break;
				goto repeat;
			case REPNZ:
				if(!GET_GPREG(CX) || EFLAGS_ZF)
					break;
				goto repeat;
			default:
				break;
		}
	}
}

void Instr16::cmps_m16_m16(void){
	uint16_t m16_s, m16_d;

repeat:
	m16_s = EMU->get_data16(select_segment(), GET_GPREG(SI));
	m16_d = EMU->get_data16(ES, GET_GPREG(DI));
	EFLAGS_UPDATE_SUB(m16_s, m16_d);

	UPDATE_GPREG(SI, EFLAGS_DF ? -1 : 1);
	UPDATE_GPREG(DI, EFLAGS_DF ? -1 : 1);

	if(PRE_REPEAT){
		UPDATE_GPREG(CX, -1);
		switch(PRE_REPEAT){
			case REPZ:
				if(!GET_GPREG(CX) || !EFLAGS_ZF)
					break;
				goto repeat;
			case REPNZ:
				if(!GET_GPREG(CX) || EFLAGS_ZF)
					break;
				goto repeat;
			default:
				break;
		}
	}
}

void Instr16::test_ax_imm16(void){
	uint16_t ax;

	ax = GET_GPREG(AX);
	EFLAGS_UPDATE_AND(ax, IMM16);
}

void Instr16::mov_r16_imm16(void){
	uint8_t reg;

	reg = OPCODE & ((1<<3)-1);
	SET_GPREG(static_cast<reg16_t>(reg), IMM16);
}

void Instr16::ret(void){
	SET_IP(POP16());
}

void Instr16::mov_rm16_imm16(void){
	set_rm16(IMM16);
}

void Instr16::leave(void){
	uint16_t ebp;

	ebp = GET_GPREG(EBP);
	SET_GPREG(ESP, ebp);
	SET_GPREG(EBP, POP16());
}

void Instr16::in_ax_imm8(void){
	SET_GPREG(AX, EMU->in_io16(IMM8));
}

void Instr16::out_imm8_ax(void){
	uint16_t ax;

	ax = GET_GPREG(AX);
	EMU->out_io16(IMM8, ax);
}

void Instr16::call_rel16(void){
	PUSH16(GET_IP());
	UPDATE_IP(IMM16);
}

void Instr16::jmp_rel16(void){
	UPDATE_IP(IMM16);
}

void Instr16::jmpf_ptr16_16(void){
	EmuInstr::jmpf(PTR16, IMM16);
}

void Instr16::in_ax_dx(void){
	uint16_t dx;

	dx = GET_GPREG(DX);
	SET_GPREG(AX, EMU->in_io16(dx));
}

void Instr16::out_dx_ax(void){
	uint16_t dx, ax;

	dx = GET_GPREG(DX);
	ax = GET_GPREG(AX);
	EMU->out_io16(dx, ax);
}

#define JCC_REL16(cc, is_flag) \
void Instr16::j ## cc ## _rel16(void){ \
	if(is_flag) \
		UPDATE_EIP(IMM16); \
}

JCC_REL16(o, EFLAGS_OF)
JCC_REL16(no, !EFLAGS_OF)
JCC_REL16(b, EFLAGS_CF)
JCC_REL16(nb, !EFLAGS_CF)
JCC_REL16(z, EFLAGS_ZF)
JCC_REL16(nz, !EFLAGS_ZF)
JCC_REL16(be, EFLAGS_CF || EFLAGS_ZF)
JCC_REL16(a, !(EFLAGS_CF || EFLAGS_ZF))
JCC_REL16(s, EFLAGS_SF)
JCC_REL16(ns, !EFLAGS_SF)
JCC_REL16(p, EFLAGS_PF)
JCC_REL16(np, !EFLAGS_PF)
JCC_REL16(l, EFLAGS_SF != EFLAGS_OF)
JCC_REL16(nl, EFLAGS_SF == EFLAGS_OF)
JCC_REL16(le, EFLAGS_ZF || (EFLAGS_SF != EFLAGS_OF))
JCC_REL16(nle, !EFLAGS_ZF && (EFLAGS_SF == EFLAGS_OF))

void Instr16::imul_r16_rm16(void){
	int16_t r16_s, rm16_s;

	r16_s = get_r16();
	rm16_s = get_rm16();
	set_r16(r16_s*rm16_s);
	EFLAGS_UPDATE_IMUL(r16_s, rm16_s);
}

void Instr16::movzx_r16_rm8(void){
	uint8_t rm8;

	rm8 = get_rm8();
	set_r16(rm8);
}

void Instr16::movzx_r16_rm16(void){
	uint16_t rm16;

	rm16 = get_rm16();
	set_r16(rm16);
}

void Instr16::movsx_r16_rm8(void){
	int8_t rm8_s;

	rm8_s = get_rm8();
	set_r16(rm8_s);
}

void Instr16::movsx_r16_rm16(void){
	int16_t rm16_s;

	rm16_s = get_rm16();
	set_r16(rm16_s);
}

/******************************************************************/

void Instr16::code_81(void){
	switch(REG){
		case 0:	add_rm16_imm16();	break;
		case 1:	or_rm16_imm16();	break;
		case 2:	adc_rm16_imm16();	break;
		case 3:	sbb_rm16_imm16();	break;
		case 4:	and_rm16_imm16();	break;
		case 5:	sub_rm16_imm16();	break;
		case 6:	xor_rm16_imm16();	break;
		case 7:	cmp_rm16_imm16();	break;
		default:
			ERROR("not implemented: 0x81 /%d\n", REG);
	}
}

void Instr16::code_83(void){
	switch(REG){
		case 0:	add_rm16_imm8();	break;
		case 1:	or_rm16_imm8();		break;
		case 2:	adc_rm16_imm8();	break;
		case 3:	sbb_rm16_imm8();	break;
		case 4:	and_rm16_imm8();	break;
		case 5:	sub_rm16_imm8();	break;
		case 6:	xor_rm16_imm8();	break;
		case 7:	cmp_rm16_imm8();	break;
		default:
			ERROR("not implemented: 0x83 /%d\n", REG);
	}
}

void Instr16::code_c1(void){
	switch(REG){
		case 4: shl_rm16_imm8();        break;
		case 5: shr_rm16_imm8();        break;
		case 6: sal_rm16_imm8();        break;	// ?
		case 7: sar_rm16_imm8();        break;
		default:
			ERROR("not implemented: 0xc1 /%d\n", REG);
	}
}

void Instr16::code_d3(void){
	switch(REG){
		case 4: shl_rm16_cl();        break;
		case 5: shr_rm16_cl();        break;
		case 6: sal_rm16_cl();        break;	// ?
		case 7: sar_rm16_cl();        break;
		default:
			ERROR("not implemented: 0xd3 /%d\n", REG);
	}
}

void Instr16::code_f7(void){
	switch(REG){
		case 0:	test_rm16_imm16();	break;
		case 2:	not_rm16();		break;
		case 3:	neg_rm16();		break;
		case 4:	mul_dx_ax_rm16();	break;
		case 5:	imul_dx_ax_rm16();	break;
		case 6:	div_dx_ax_rm16();	break;
		case 7:	idiv_dx_ax_rm16();	break;
		default:
			ERROR("not implemented: 0xf7 /%d\n", REG);
	}
}

void Instr16::code_ff(void){
	switch(REG){
		case 0:	inc_rm16();		break;
		case 1:	dec_rm16();		break;
		case 2:	call_rm16();		break;
		case 3:	callf_m16_16();		break;
		case 4:	jmp_rm16();		break;
		case 5:	jmpf_m16_16();		break;
		case 6:	push_rm16();		break;
		default:
			ERROR("not implemented: 0xff /%d\n", REG);
	}
}

void Instr16::code_0f00(void){
	switch(REG){
		case 3: ltr_rm16();		break;
		default:
			ERROR("not implemented: 0x0f00 /%d\n", REG);
	}
}

void Instr16::code_0f01(void){
	switch(REG){
		case 2: lgdt_m24();		break;
		case 3: lidt_m24();		break;
		default:
			ERROR("not implemented: 0x0f01 /%d\n", REG);
	}
}

/******************************************************************/

void Instr16::add_rm16_imm16(void){
	uint16_t rm16;

	rm16 = get_rm16();
	set_rm16(rm16+IMM16);
	EFLAGS_UPDATE_ADD(rm16, IMM16);
}

void Instr16::or_rm16_imm16(void){
	uint16_t rm16;

	rm16 = get_rm16();
	set_rm16(rm16|IMM16);
	EFLAGS_UPDATE_OR(rm16, IMM16);
}

void Instr16::adc_rm16_imm16(void){
	uint16_t rm16;
	uint8_t cf;

	rm16 = get_rm16();
	cf = EFLAGS_CF;
	set_rm16(rm16+IMM16+cf);
	EFLAGS_UPDATE_ADD(rm16, IMM16+cf);
}

void Instr16::sbb_rm16_imm16(void){
	uint16_t rm16;
	uint8_t cf;

	rm16 = get_rm16();
	cf = EFLAGS_CF;
	set_rm16(rm16-IMM16-cf);
	EFLAGS_UPDATE_SUB(rm16, IMM16+cf);
}

void Instr16::and_rm16_imm16(void){
	uint16_t rm16;

	rm16 = get_rm16();
	set_rm16(rm16&IMM16);
	EFLAGS_UPDATE_AND(rm16, IMM16);
}

void Instr16::sub_rm16_imm16(void){
	uint16_t rm16;

	rm16 = get_rm16();
	set_rm16(rm16-IMM16);
	EFLAGS_UPDATE_SUB(rm16, IMM16);
}

void Instr16::xor_rm16_imm16(void){
	uint16_t rm16;

	rm16 = get_rm16();
	set_rm16(rm16^IMM16);
}

void Instr16::cmp_rm16_imm16(void){
	uint16_t rm16;

	rm16 = get_rm16();
	EFLAGS_UPDATE_SUB(rm16, IMM16);
}

/******************************************************************/

void Instr16::add_rm16_imm8(void){
	uint16_t rm16;

	rm16 = get_rm16();
	set_rm16(rm16+IMM8);
	EFLAGS_UPDATE_ADD(rm16, IMM8);
}

void Instr16::or_rm16_imm8(void){
	uint16_t rm16;

	rm16 = get_rm16();
	set_rm16(rm16|IMM8);
	EFLAGS_UPDATE_OR(rm16, IMM8);
}

void Instr16::adc_rm16_imm8(void){
	uint16_t rm16;
	uint8_t cf;

	rm16 = get_rm16();
	cf = EFLAGS_CF;
	set_rm16(rm16+IMM8+cf);
	EFLAGS_UPDATE_ADD(rm16, IMM8+cf);
}

void Instr16::sbb_rm16_imm8(void){
	uint16_t rm16;
	uint8_t cf;

	rm16 = get_rm16();
	cf = EFLAGS_CF;
	set_rm16(rm16-IMM8-cf);
	EFLAGS_UPDATE_SUB(rm16, IMM8+cf);
}

void Instr16::and_rm16_imm8(void){
	uint16_t rm16;

	rm16 = get_rm16();
	set_rm16(rm16&IMM8);
	EFLAGS_UPDATE_AND(rm16, IMM8);
}

void Instr16::sub_rm16_imm8(void){
	uint16_t rm16;

	rm16 = get_rm16();
	set_rm16(rm16-IMM8);
	EFLAGS_UPDATE_SUB(rm16, IMM8);
}

void Instr16::xor_rm16_imm8(void){
	uint16_t rm16;

	rm16 = get_rm16();
	set_rm16(rm16^IMM8);
}

void Instr16::cmp_rm16_imm8(void){
	uint16_t rm16;

	rm16 = get_rm16();
	EFLAGS_UPDATE_SUB(rm16, IMM8);
}

/******************************************************************/

void Instr16::shl_rm16_imm8(void){
	uint16_t rm16;

	rm16 = get_rm16();
	set_rm16(rm16<<IMM8);
	EFLAGS_UPDATE_SHL(rm16, IMM8);
}

void Instr16::shr_rm16_imm8(void){
	uint16_t rm16;

	rm16 = get_rm16();
	set_rm16(rm16>>IMM8);
	EFLAGS_UPDATE_SHR(rm16, IMM8);
}

void Instr16::sal_rm16_imm8(void){
	int16_t rm16_s;

	rm16_s = get_rm16();
	set_rm16(rm16_s<<IMM8);
//	EFLAGS_UPDATE_SAL(rm16_s, IMM8);
}

void Instr16::sar_rm16_imm8(void){
	int16_t rm16_s;

	rm16_s = get_rm16();
	set_rm16(rm16_s>>IMM8);
//	EFLAGS_UPDATE_SAR(rm16_s, IMM8);
}

/******************************************************************/

void Instr16::shl_rm16_cl(void){
	uint16_t rm16;
	uint8_t cl;

	rm16 = get_rm16();
	cl = GET_GPREG(CL);
	set_rm16(rm16<<cl);
	EFLAGS_UPDATE_SHL(rm16, cl);
}

void Instr16::shr_rm16_cl(void){
	uint16_t rm16;
	uint8_t cl;

	rm16 = get_rm16();
	cl = GET_GPREG(CL);
	set_rm16(rm16>>cl);
	EFLAGS_UPDATE_SHR(rm16, cl);
}

void Instr16::sal_rm16_cl(void){
	int16_t rm16_s;
	uint8_t cl;

	rm16_s = get_rm16();
	cl = GET_GPREG(CL);
	set_rm16(rm16_s<<cl);
//	EFLAGS_UPDATE_SAL(rm16_s, cl);
}

void Instr16::sar_rm16_cl(void){
	int16_t rm16_s;
	uint8_t cl;

	rm16_s = get_rm16();
	cl = GET_GPREG(CL);
	set_rm16(rm16_s>>cl);
//	EFLAGS_UPDATE_SAR(rm16_s, cl);
}

/******************************************************************/

void Instr16::test_rm16_imm16(void){
	uint16_t rm16, imm16;

	rm16 = get_rm16();
	imm16 = EMU->get_code16(0);
	UPDATE_EIP(2);
	EFLAGS_UPDATE_AND(rm16, imm16);
}

void Instr16::not_rm16(void){
	uint16_t rm16;

	rm16 = get_rm16();
	set_rm16(~rm16);
}

void Instr16::neg_rm16(void){
	int16_t rm16_s;

	rm16_s = get_rm16();
	set_rm16(-rm16_s);
	EFLAGS_UPDATE_SUB((uint16_t)0, rm16_s);
}

void Instr16::mul_dx_ax_rm16(void){
	uint16_t rm16, ax;
	uint32_t val;

	rm16 = get_rm16();
	ax = GET_GPREG(AX);
	val = ax*rm16;

	SET_GPREG(AX, val&((1<<16)-1));
	SET_GPREG(DX, (val>>16)&((1<<16)-1));

	EFLAGS_UPDATE_MUL(ax, rm16);
}

void Instr16::imul_dx_ax_rm16(void){
	int16_t rm16_s, ax_s;
	int32_t val_s;

	rm16_s = get_rm16();
	ax_s = GET_GPREG(AX);
	val_s = ax_s*rm16_s;

	SET_GPREG(AX, val_s&((1<<16)-1));
	SET_GPREG(DX, (val_s>>16)&((1<<16)-1));

	EFLAGS_UPDATE_IMUL(ax_s, rm16_s);
}

void Instr16::div_dx_ax_rm16(void){
	uint16_t rm16;
	uint32_t val;

	rm16 = get_rm16();
	EXCEPTION(EXP_DE, !rm16);
	val = (GET_GPREG(DX)<<16)|GET_GPREG(AX);

	SET_GPREG(AX, val/rm16);
	SET_GPREG(DX, val%rm16);
}

void Instr16::idiv_dx_ax_rm16(void){
	int16_t rm16_s;
	int32_t val_s;

	rm16_s = get_rm16();
	EXCEPTION(EXP_DE, !rm16_s);
	val_s = (GET_GPREG(DX)<<16)|GET_GPREG(AX);

	SET_GPREG(AX, val_s/rm16_s);
	SET_GPREG(DX, val_s%rm16_s);
}

/******************************************************************/

void Instr16::inc_rm16(void){
	uint16_t rm16;

	rm16 = get_rm16();
	set_rm16(rm16+1);
	EFLAGS_UPDATE_ADD(rm16, 1);
}

void Instr16::dec_rm16(void){
	uint16_t rm16;

	rm16 = get_rm16();
	set_rm16(rm16-1);
	EFLAGS_UPDATE_SUB(rm16, 1);
}

void Instr16::call_rm16(void){
	uint16_t rm16;

	rm16 = get_rm16();

	PUSH16(GET_IP());
	SET_IP(rm16);
}

void Instr16::callf_m16_16(void){
	uint16_t m32, cs, ip;

	m32 = get_m();
	ip  = READ_MEM16(m32);
	cs  = READ_MEM16(m32+2);

	EmuInstr::callf(cs, ip);
}

void Instr16::jmp_rm16(void){
	uint16_t rm16;

	rm16 = get_rm16();
	SET_IP(rm16);
}

void Instr16::jmpf_m16_16(void){
	uint16_t m32, sel, ip;

	m32 = get_m();
	ip  = READ_MEM16(m32);
	sel  = READ_MEM16(m32+2);

	EmuInstr::jmpf(sel, ip);
}

void Instr16::push_rm16(void){
	uint16_t rm16;

	rm16 = get_rm16();
	PUSH16(rm16);
}

/******************************************************************/

void Instr16::lgdt_m24(void){
	uint16_t m48, base, limit;

	EXCEPTION(EXP_GP, !chk_ring(0));

	m48 = get_m();
	limit = READ_MEM16(m48);
	base  = READ_MEM32(m48+2)&((1<<24)-1);

	set_gdtr(base, limit);
}

void Instr16::lidt_m24(void){
	uint16_t m48, base, limit;

	EXCEPTION(EXP_GP, !chk_ring(0));

	m48 = get_m();
	limit = READ_MEM16(m48);
	base  = READ_MEM32(m48+2)&((1<<24)-1);

	set_idtr(base, limit);
}

