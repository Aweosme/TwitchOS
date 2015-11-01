#include <stdint.h>

/* A global descriptor table entry struct */
struct gdt_entry_struct
{
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_middle;
	uint8_t access;
	uint8_t granularity;
	uint8_t base_high;
} __attribute__((packed));
typedef struct gdt_entry_struct gdt_entry_t;

/* A global descriptor table pointer struct */
struct gdt_ptr_struct
{
	uint16_t limit;
	uint32_t base;
} __attribute__((packed));
typedef struct gdt_ptr_struct gdt_ptr_t;

gdt_entry_t gdt[5];
gdt_ptr_t   gdt_ptr;

/* Setup a descriptor in the Global Descriptor Table */
void gdt_set_entry(int32_t num, uint32_t base, uint32_t limit,
			uint8_t access, uint8_t gran)
{
	/* Setup the descriptor base address */
	gdt[num].base_low = (base & 0xFFFF);
	gdt[num].base_middle = (base >> 16) & 0xFF;
	gdt[num].base_high = (base >> 24) & 0xFF;

	/* Setup the descriptor limits */
	gdt[num].limit_low = (limit & 0xFFFF);
	gdt[num].granularity = ((limit >> 16) & 0x0F);

	/* Finally, set up the granularity and access flags */
	gdt[num].granularity |= (gran & 0xF0);
	gdt[num].access = access;
}

extern void gdt_flush();

void init_gdt()
{
	/* Setup the GDT pointer and limit */
	gdt_ptr.limit = (sizeof(gdt_entry_t) * 5) - 1;
	gdt_ptr.base = (uint32_t)&gdt;

	gdt_set_entry(0, 0, 0, 0, 0);				 // NULL segment
	gdt_set_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Kernel code segment
	gdt_set_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Kernel data segment
	gdt_set_entry(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User code segment
	gdt_set_entry(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User data segment

	/* Set new gdt */
	gdt_flush();
}
