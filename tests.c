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
    uint8_t poly[] = {1,1,0,1,0,0,0,0,
                      0,0,0,0,1,0,0,0, 1};
    field = getField(2,poly,16);
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
}

MU_TEST(test_ff_to_uint32)
{
    uint8_t poly[] = {1,1,1,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,1,0,
                      0,0,0,0,0,0,0,0,1};
    field = getField(2,poly,32);
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
}

MU_TEST(test_uint8_to_ff)
{
    uint8_t elem = 123;
    mem = uint8_to_ff(elem);
    mu_check(ff_to_uint8(mem) == elem);
    freeFieldMember(mem, 1);
}

MU_TEST(test_uint16_to_ff)
{
    uint16_t elem = 4325;
    mem = uint16_to_ff(elem);
    mu_check(ff_to_uint16(mem) == elem);
    freeFieldMember(mem, 1);
}

MU_TEST(test_uint32_to_ff)
{
    uint32_t elem = 5345346;
    mem = uint32_to_ff(elem);
    mu_check(ff_to_uint32(mem) == elem);
    freeFieldMember(mem, 1);
}

MU_TEST(test_fieldMemberInit)
{
    uint8_t irred_poly[] = {1,1,0,0,1};
    field = getField(3,irred_poly,4);
    uint8_t poly[] = {1,3,2,12};
    uint8_t poly_deg = 3;
    FieldMember *test_mem = fieldMemberInit(field,poly,poly_deg);
    mem = getZero(field);
    for (uint8_t i = 0; i <= field->poly_deg; ++i)
    {
        mem->poly[i] = mem->poly[i] = i <= poly_deg ? poly[i] % field->mod : 0;
    }
    mu_check(fieldMembersAreEqual(test_mem,mem));
    freeFieldMember(test_mem,0);
    freeFieldMember(mem,1);
}

MU_TEST_SUITE(test_suite)
{
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);

    MU_RUN_TEST(test_ff_to_uint8);
    MU_RUN_TEST(test_ff_to_uint16);
    MU_RUN_TEST(test_ff_to_uint32);

    MU_RUN_TEST(test_uint8_to_ff);
    MU_RUN_TEST(test_uint16_to_ff);
    MU_RUN_TEST(test_uint32_to_ff);

    MU_RUN_TEST(test_fieldMemberInit);
}

int main()
{
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return MU_EXIT_CODE;
}
