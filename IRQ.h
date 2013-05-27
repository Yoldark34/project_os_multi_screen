
#ifndef IRQ_H
#define	IRQ_H
#define NOMBRE_IRQ      15

#define INT_IRQ0         0x20
#define INT_IRQ1         0x21
#define INT_IRQ3         0x23
#define INT_IRQ4         0x24
#define INT_IRQ5         0x25
#define INT_IRQ6         0x26
#define INT_IRQ7         0x27
#define INT_IRQ8         0x70
#define INT_IRQ9         0x71
#define INT_IRQ10        0X72
#define INT_IRQ11        0x74
#define INT_IRQ12        0X75
#define INT_IRQ13        0X76
#define INT_IRQ14        0X77
#define INT_IRQ15        0X78

void Interruption_IRQ0();
void Interruption_IRQ1();
void Interruption_IRQ3();
void Interruption_IRQ4();
void Interruption_IRQ5();
void Interruption_IRQ6();
void Interruption_IRQ7();
void Interruption_IRQ8();
void Interruption_IRQ9();
void Interruption_IRQ10();
void Interruption_IRQ11();
void Interruption_IRQ12();
void Interruption_IRQ13();
void Interruption_IRQ14();
void Interruption_IRQ15();

void Interruption_IRQ_Defaut();



#endif	/* IRQ_H */

