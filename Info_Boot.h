#ifndef EN_TETE_BOOT_H
#define	EN_TETE_BOOT_H
#define BOOT_INFO_MEMOIRE                    0x00000001
#define BOOT_INFO_PARTITION_BOOT             0x00000002
#define BOOT_LIGNE_COMMANDE                  0x00000004
#define BOOT_INFO_MODULE                     0x00000008
#define BOOT_INFO_EXE32                      0x00000010
#define BOOT_INFO_ELF32                      0X00000020
#define BOOT_INFO_MAP_MEMOIRE                0x00000040
#define BOOT_INFO_DISQUE                     0x00000080
#define BOOT_INFO_CONFIG                     0x00000100     
#define BOOT_INFO_BOOTLOADER                 0x00000200
#define BOOT_INFO_APM                        0x00000400
#define BOOT_INFO_VIDEO                      0x00000800

     
typedef struct 
{
       UINT32 Taille_Table;
       UINT32 Taille_Chaine;
       UINT32 Adresse;
       UINT32 zero;
}T_TABLE_SYMBOLES_EXE32;
     

typedef struct 
{
       UINT32 Nombre;
       UINT32 Taille;
       UINT32 Adresse;
       UINT32 Section;
}T_TABLE_SYMBOLE_ELF2;


typedef struct  {
         UINT32 Flags;
         UINT32 Adresse_Basse;
         UINT32 Adresse_Haute;
         UINT32 Partition_Boot;
         UINT32 Ligne_De_Commande;
         UINT32 Nombre_Modules;
         UINT32 Adresse_Modules;
         union {
            T_TABLE_SYMBOLES_EXE32 Symboles_Exe32;
            T_TABLE_SYMBOLE_ELF2   Symboles_Elf32;           
         }Symboles;
         UINT32 Taille_Map;
         UINT32 Adresse_Map;
         UINT32 Configuration_Disque;
         UINT32 Nom_BootLoader;
         UINT32 Table_APM;
         UINT32 Video_Information_Controle;
         UINT32 Video_Information_Mode;
         UINT16 Video_Mode;
         UINT16 Video_Segment;
         UINT16 Video_Offset;
         UINT16 Video_Taille;
        
 }T_BOOT_INFO ;



#endif	/* EN_TETE_BOOT_H */

