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
        if (mem->poly[i] != 0) mem->deg = i;
    }
    mu_check(fieldMembersAreEqual(test_mem,mem));
    freeFieldMember(test_mem,0);
    freeFieldMember(mem,1);
}

MU_TEST(test_ffAdd)
{
    uint8_t irred_poly[] = {2,1,0,2,1,0,0,0,1};
    field = getField(3,irred_poly,8);
    uint8_t poly1[] = {1,1,1,1,4,};
    uint8_t poly2[] = {2,2,0,1,0,5};
    FieldMember *mem1 = fieldMemberInit(field,poly1,4);
    FieldMember *mem2 = fieldMemberInit(field,poly2,5);
    FieldMember *added = ffAdd(mem1,mem2);

    uint8_t res_poly[] = {0,0,1,2,1,2};
    FieldMember *res = fieldMemberInit(field,res_poly,5);
    mu_check(fieldMembersAreEqual(added,res));

    freeFieldMember(mem1,0);
    freeFieldMember(mem2,0);
    freeFieldMember(added,0);
    freeFieldMember(res,1);
}

MU_TEST(test_ffNeg_and_ffSub)
{
    uint8_t irred_poly[] = {2,1,0,2,1,0,0,0,1};
    field = getField(3,irred_poly,8);
    uint8_t poly1[] = {1,6,3,4,4,6,2,1}; // 1 0 0 1 1 0 2 1 0
    uint8_t poly2[] = {2,1,0,2,0,4};            // 1 2 0 1 0 2 0 0 0
    FieldMember  *mem1 = fieldMemberInit(field,poly1,7);
    FieldMember *mem2 = fieldMemberInit(field,poly2,5);
    FieldMember *sub = ffSub(mem1,mem2);

    uint8_t res_poly[] = {2,2,0,2,1,2,2,1};
    FieldMember *res = fieldMemberInit(field,res_poly,7);
    mu_check(fieldMembersAreEqual(sub,res));

    freeFieldMember(mem1,0);
    freeFieldMember(mem2,0);
    freeFieldMember(sub,0);
    freeFieldMember(res,1);
}

MU_TEST(test_ffMul)
{
    uint8_t irred_poly[] = {5,1,0,3,1,0,0,0,1};
    field = getField(7,irred_poly,8);
    uint8_t poly1[] = {7,4,6,5,5,3,1,1};
    uint8_t poly2[] = {4,4,5,6,1,3};
    FieldMember *mem1 = fieldMemberInit(field,poly1,7);
    FieldMember *mem2 = fieldMemberInit(field,poly2,5);
    FieldMember *mul = ffMul(mem1,mem2);

    uint8_t res_poly[] = {4,2,1,1,0,3,5};
    FieldMember *res = fieldMemberInit(field,res_poly,6);
    mu_check(fieldMembersAreEqual(mul,res));

    freeFieldMember(mem1,0);
    freeFieldMember(mem2,0);
    freeFieldMember(mul,0);
    freeFieldMember(res,1);
}

MU_TEST(test_ffInv)
{
    uint8_t irred_poly[] = {2,1,0,2,1,0,0,0,1};
    field = getField(3,irred_poly,8);
    uint8_t poly[] = {1,1,0,2,2,0,1,1};
    mem = fieldMemberInit(field,poly,7);
    FieldMember *mem_inv = ffInv(mem);
    FieldMember *identity = getIdentity(mem->field);
    FieldMember *result = ffMul(mem,mem_inv);

    mu_check(fieldMembersAreEqual(result,identity));
    freeFieldMember(mem_inv,0);
    freeFieldMember(identity,0);
    freeFieldMember(result,0);
    freeFieldMember(mem,1);
}


MU_TEST(test_ffDiv)
{
    uint8_t irred_poly[] = {2,1,0,2,1,0,0,0,1};
    field = getField(3,irred_poly,8);
    uint8_t poly1[] = {1,1,0,2,2,0,1,1};
    uint8_t poly2[] = {1,0,2,2,1,1};
    FieldMember *mem1 = fieldMemberInit(field,poly1,7);
    FieldMember *mem2 = fieldMemberInit(field,poly2,5);
    FieldMember *div = ffDiv(mem1, mem2);

    FieldMember *new_mem1 = ffMul(div,mem2);
    mu_check(fieldMembersAreEqual(mem1, new_mem1));

    freeFieldMember(mem1,0);
    freeFieldMember(mem2,0);
    freeFieldMember(div, 0);
    freeFieldMember(new_mem1,1);
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

    MU_RUN_TEST(test_ffAdd);
    MU_RUN_TEST(test_ffNeg_and_ffSub);
    MU_RUN_TEST(test_ffMul);
    MU_RUN_TEST(test_ffInv);
    MU_RUN_TEST(test_ffDiv);
}

int main()
{
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return MU_EXIT_CODE;
}
