/* Register modes */
#define NOWLIN_MODE	0b00000000
#define AGND_MODE	0b00000001
#define ONESHOT_MODE	0b00000001
#define LOCKOUT_MODE	0b00000101
#define DAC_MODE	0b00000110
#define GMODE		0b00001000

/* Channel Addresses */
#define CH0	0b00000000
#define CH1	0b00010000
#define CH2	0b00100000
#define CH3	0b00110000
#define CH4	0b01000000
#define CH5	0b01010000
#define CH6	0b01100000
#define CH7	0b01110000
#define CH8	0b10000000
#define CH9	0b10010000
#define CH10	0b10100000
#define CH11	0b10110000
#define CH12	0b11000000
#define CH13	0b11010000
#define	CH14	0b11100000
#define CH15	0b11110000
#define COMMON	0b00000000

/* Bit widths */
#define DATA_BITS	8
#define MODE_BITS	4
#define ADDR_BITS	4
