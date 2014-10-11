#include<strings.h>
#include<string.h>

#include"mem.h"
#include"common/bits.h"
#include"common/notify.h"
#include"common/types.h"

/////////////////////////////
////     Code fourni     ////
/////////////////////////////


/*
 * Creates a virtual memory and performs the necessary memory allocations
 * @param size  the number of segments that composes this virtual memory
 * @return the new allocated virtual memory or NULL in case of failure
 */

mem init_mem( uint32_t nseg ) {
    mem vm = calloc( nseg, sizeof( *vm ) );
    if ( NULL == vm ) {
        WARNING_MSG( "Unable to allocate host memory for vmem" );
        return NULL;
    }
    else {
        int i;
        vm->seg = calloc( nseg, sizeof( *(vm->seg) ) );
        if ( NULL == vm->seg ) {
            WARNING_MSG( "Unable to allocate host memory for vmem segment" );
            free( vm );
            return NULL;
        }
        // each segment is initialised to a null value
        // Note that though this is unnecessary since a calloc is used
        // this permits future evolution of the default initialisation values
        for ( i= 0; i< nseg; i++ ) {
            vm->seg[i].name      = NULL;
            vm->seg[i].content	 = NULL;
            vm->seg[i].start._64 = 0x0;
            vm->seg[i].size._64  = 0x0;
            vm->seg[i].attr      = 0x0;
        }
        vm->nseg = nseg;
    }
    return vm;
}

/**
 * Destroys a virtual memory by making all the necessary free operations
 * @param a virtual memory
 */

void del_mem (mem memoire, int nbre_seg){
    if (memoire != NULL) {
        if (memoire->seg != NULL) {
            int i;
            for ( i= 0; i< memoire->nseg; i++ ) {
                if (memoire->seg[i].content != NULL) {
                    free(memoire->seg[i].content);
                }
                if (memoire->seg[i].name != NULL) {
                    free(memoire->seg[i].name);
                }
            }
            free(memoire->seg);
        }
        free(memoire);
    }
    return;
}
/**
 * allocates an available segment in the virtual memory to the section named 'name'.
 * @param name the name of the segment (e.g., ".text", ".data"...)
 * @param attribute an integer value corresponding to the access and execution permissions of the segment (@see mem.h)
 * @return 0 in case of success, a non null value otherwise
 */

int attach_scn_to_mem( mem vm, char *name, uint32_t attr ) {

    if ( NULL != vm ) {
        uint i;

        for ( i= 0; i< vm->nseg; i++ ) {
            if ( NULL == vm->seg[i].name ) {
                vm->seg[i].attr = attr;
                vm->seg[i].name = strdup( name );
                return 0;
            }
        }

        WARNING_MSG( "All vmem segments already allocated" );
        return 1;
    }
    else {
        WARNING_MSG( "Virtual memory not initialized" );
        return 1;
    }
}

/**
 * Sets a segment with all the information about a section read from a ELF file
 * @param vm the virtual memory in which the segment to fill in can be found
 * @param name the name of the segment to look for (e.g., ".text", ".data"...)
 * @param size the size of the section content (in bytes)
 * @param start the virtual address in the virtual memory at which the beginning of the segment is located
 * @param content the real address at which the bytes of the section is located
 * @return 0 if succeed, a non null value otherwise
 */

int fill_mem_scn( mem vm, char *name, vsize sz, vaddr start, byte *content ) {

    if ( NULL != vm ) {
        uint i;

        for ( i= 0; i< vm->nseg; i++ ) {
            if ( 0 == strncasecmp( vm->seg[i].name, name, strlen(name) ) ) {
                switch( SCN_WIDTH( vm->seg[i].attr ) ) {
                case 32 :
                    vm->seg[i].size._32 = sz._32;
                    vm->seg[i].start._32 = start._32;
                    vm->seg[i].content = calloc( 1, sz._32 );
                    if ( NULL == vm->seg[i].content ) {
                        WARNING_MSG( "Unable to allocate host memory for vmem segment %s content", name );
                        vm->seg[i].size._32 = 0;
                        vm->seg[i].start._32 = 0;
                        return 1;
                    }
                    if ( NULL != content ) {
                        memcpy( vm->seg[i].content, content, sz._32 );
                    }
                    return 0;
                    break;
                case 64 :
                    vm->seg[i].size._64 = sz._64;
                    vm->seg[i].start._64 = start._64;
                    vm->seg[i].content = calloc( 1, sz._64 );
                    if ( NULL == vm->seg[i].content ) {
                        WARNING_MSG( "Unable to allocate host memory for vmem segment %s content", name );
                        vm->seg[i].size._64 = 0;
                        vm->seg[i].start._64 = 0;
                        return 1;
                    }
                    if ( NULL != content ) {
                        memcpy( vm->seg[i].content, content, sz._64 );
                    }
                    return 0;
                    break;
                default :
                    WARNING_MSG( "Wrong width" );
                    return 1;
                }
                return 0;
            }
        }

        WARNING_MSG( "Segment %s not attached yet", name );
        return 1;
    }
    else {
        WARNING_MSG( "Virtual memory not initialized" );
        return 1;
    }
}


/**
* prints the content of a virtual memory
* @param a virtual memory
*/

void print_mem( mem vm ) {
    if ( NULL != vm ) {
        uint i;
        uint n = 0;

        for ( i= 0; i< vm->nseg; i++ ) {
            if ( UNDEF != SCN_RIGHTS( vm->seg[i].attr ) ) {
                n++;
            }
        }

        printf( "Virtual memory map (%u segments)\n", n );

        for ( i= 0; i< vm->nseg; i++ ) {

            if ( UNDEF == SCN_RIGHTS( vm->seg[i].attr ) ) {
                continue;
            }

            printf( "%-8s\t", vm->seg[i].name );
            switch( SCN_RIGHTS( vm->seg[i].attr ) ) {
            case R__ :
                printf( "r--" );
                break;
            case RW_ :
                printf( "rw-" );
                break;
            case R_X :
                printf( "r-x" );
                break;
            default :
                printf( "???" );
            }
            printf( "\tVaddr: " );
            switch( SCN_WIDTH( vm->seg[i].attr ) ) {
            case 32 :
                printf( "0x%08x", vm->seg[i].start._32 );
                break;
            case 64 :
                printf( "0x%016lx", (long unsigned int)vm->seg[i].start._64 );
                break;
            default :
                printf( "?????????" );
                break;
            }
            printf( "\tSize: " );
            switch( SCN_WIDTH( vm->seg[i].attr ) ) {
            case 32 :
                printf( "%u", vm->seg[i].size._32 );
                break;
            case 64 :
                printf( "%lu", (long unsigned int)vm->seg[i].size._64 );
                break;
            default :
                printf( "?????????" );
                break;
            }
            printf( " bytes\n" );
            /*
            printf( " bytes\t(%s)\n", vm->seg[i].content==NULL?"empty":"filled" );
            */
        }
    }

    return;
}



/////////////////////////////
////      Code crée      ////
/////////////////////////////


/* Calcul l'adresse réelle à partir d'une adresse virtuelle*/
/*
vaddr32 conv_virtuel_reel (vaddr virtual_addr, mem *memoire) {
	vaddr32 raddr, faddr;
	seg seg_proche = calc_addr_proche (virtual_addr, 7, memoire);
	faddr=seg_proche.start._32;
	vaddr32 eloignement= virtual_addr._32 - faddr;
	raddr=seg_proche.start._32 + eloignement;
	return raddr;
}*/

// Calcul de l'adresse d'origine d'un segment la plus proche de l'adresse virtuelle donnée
/*
seg calc_addr_proche (vaddr virtual_addr, int nbre_seg, mem *memoire) {
	int i, j;
	vaddr32 m, q, n;
	vaddr k;
	seg p;
	m=virtual_addr._32 - memoire->seg->vaddr._32; // Calcul la distance entre l'adresse virtuelle demandée et l'origine de notre mémoire
	for (i=0; i<nbre_seg; i++) {
		p = memoire->(*(seg+i));
		k = p.start;
		q = k._32;
		n = (virtual_addr._32) - q;
		if ( n < 0 ) 
			return memoire->(seg+i-1);
		
		else if (n < m) {
			m=(virtual_addr._32) - q;
			j=i;
		}
		else 
			WARNING_MSG("Au secours");		
		
	}
	return memoire->(seg+j);
}


*/



























