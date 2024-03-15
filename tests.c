#include <stdio.h>
#include <stdlib.h>
#include "minunit.h"
#include "library.h"

static Field *field;
static FieldMember *mem;

void test_setup(void)
{

}

void test_teardown(void)
{

}

MU_TEST(test_ff_to_uint8)
{
    uint8_t poly[] = {1,0,1,1,1,0,0,0,1};
    field = getField(2, poly,8);
    mem = getZero(field);
    mem->poly[7] = 1;
    mem->poly[6] = 1;
    mem->poly[5] = 1;
    mu_check(ff_to_uint8(mem) == 224);
    freeFieldMember(mem, 1);
}

MU_TEST(test_ff_to_uint16)
{
    const size_t DIM = 17;
    uint8_t *poly = malloc( DIM * sizeof(uint8_t));
    for (int i = 0; i < DIM; ++i)
    {
        poly[i] = 0;
    }
    poly[16] = 1;
    poly[12] = 1;
    poly[3] = 1;
    poly[1] = 1;
    poly[0] = 1;
    field = getField(2, poly,DIM - 1);

    mem = getZero(field);
    mem->poly[0] = 1;
    mem->poly[1] = 1;
    mem->poly[3] = 1;
    mem->poly[4] = 1;
    mem->poly[5] = 1;
    mem->poly[7] = 1;
    mem->poly[8] = 1;
    mem->poly[10] = 1;
    mem->poly[12] = 1;
    mu_check(ff_to_uint16(mem) == 5563);
    freeFieldMember(mem, 1);
    free(poly);
}
//10111110101111001010011110
MU_TEST(test_ff_to_uint32)
{
    const size_t DIM = 33;
    uint8_t *poly = malloc( DIM * sizeof(uint8_t));
    for (int i = 0; i < DIM; ++i)
    {
        poly[i] = 0;
    }
    poly[32] = 1;
    poly[22] = 1;
    poly[2] = 1;
    poly[1] = 1;
    poly[0] = 1;
    field = getField(2, poly,DIM - 1);
    mem = getZero(field);
    mem->poly[1] = 1;
    mem->poly[2] = 1;
    mem->poly[3] = 1;
    mem->poly[4] = 1;
    mem->poly[7] = 1;
    mem->poly[9] = 1;
    mem->poly[12] = 1;
    mem->poly[13] = 1;
    mem->poly[14] = 1;
    mem->poly[15] = 1;
    mem->poly[17] = 1;
    mem->poly[19] = 1;
    mem->poly[20] = 1;
    mem->poly[21] = 1;
    mem->poly[22] = 1;
    mem->poly[23] = 1;
    mem->poly[25] = 1;
    mu_check(ff_to_uint32(mem) == 50000542);
    freeFieldMember(mem, 1);
    free(poly);
}

MU_TEST_SUITE(test_suite)
{
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);

    MU_RUN_TEST(test_ff_to_uint8);
    MU_RUN_TEST(test_ff_to_uint16);
    MU_RUN_TEST(test_ff_to_uint32);
}

int main()
{
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return MU_EXIT_CODE;
}