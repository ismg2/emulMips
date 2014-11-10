#include "fonction_mips.h"


int(*choix_fonction(int a))(map_reg *,mem,union_RIJ)
{
	return listeFonctions[a];
}

int addi(map_reg * mrg,mem memoire,union_RIJ union_struct)
{
	uint32_t registre_rs;
	uint32_t registre_rt;

	registre_rs = renvoi_reg_num(mrg,union_struct.i.rs);
	DEBUG_MSG("rs = %u",registre_rs);
	registre_rt = registre_rs + union_struct.i.immediate;
	DEBUG_MSG("immediate : %d",union_struct.i.immediate);
	DEBUG_MSG("rt : %u",registre_rt);
	modif_reg_num(union_struct.i.rt,mrg,registre_rt);
	return 1;
}