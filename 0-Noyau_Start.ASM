global _start
extern OS_Start

%define GRUB_SIGNATURE     0x1BADB002
%define GRUB_ALIGNEMENT    0x00000001
%define GRUB_INFO_MEMOIRE  0x00000002
%define GRUB_VIDEO         0x00000004
%define GRUB_INFO_SEGMENT  0x00010000

%define GRUB_MON_FLAG GRUB_ALIGNEMENT + GRUB_INFO_MEMOIRE 
%define GRUB_CHECKSUM       -(GRUB_SIGNATURE + GRUB_MON_FLAG )


_start:
	jmp Debut
;-------------------------------------------------------------------------------
        align 4
        dd GRUB_SIGNATURE
        dd GRUB_MON_FLAG
        dd GRUB_CHECKSUM  

Debut:
    push ebx      ; puisque une demande d'info mémoire a été demandée, l'adrese de la structure 
                  ; est envoyée dans EBX.
                  ; on empile EBS afin de passer en parametre l'adresse de la structure 
                  ; à la fonction OS_Start

    call OS_Start
    cli 
    hlt 






