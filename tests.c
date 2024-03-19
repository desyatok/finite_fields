#include <stdio.h>
#include <stdlib.h>
#include "minunit.h"
#include "library.h"

void testAddition(uint8_t *irred_poly, uint8_t irred_poly_deg, uint8_t field_mod,
                  uint8_t *poly1, uint8_t poly1_deg,
                  uint8_t *poly2, uint8_t poly2_deg,
                  uint8_t *res_poly, uint8_t res_poly_deg)
{
    Field *field = getField(field_mod,irred_poly,irred_poly_deg);
    FieldMember *mem1 = fieldMemberInit(field,poly1,poly1_deg);
    FieldMember *mem2 = fieldMemberInit(field,poly2,poly2_deg);
    FieldMember *sum = ffAdd(mem1, mem2);
    FieldMember *res = fieldMemberInit(field,res_poly,res_poly_deg);

    mu_check(fieldMembersAreEqual(sum, res));

    freeFieldMember(mem1,0);
    freeFieldMember(mem2,0);
    freeFieldMember(sum, 0);
    freeFieldMember(res,1);
}

void testSubtraction(uint8_t *irred_poly, uint8_t irred_poly_deg, uint8_t field_mod,
                     uint8_t *poly1, uint8_t poly1_deg,
                     uint8_t *poly2, uint8_t poly2_deg,
                     uint8_t *res_poly, uint8_t res_poly_deg)
{
    Field *field = getField(field_mod,irred_poly,irred_poly_deg);
    FieldMember *mem1 = fieldMemberInit(field,poly1,poly1_deg);
    FieldMember *mem2 = fieldMemberInit(field,poly2,poly2_deg);
    FieldMember *dif = ffSub(mem1, mem2);
    FieldMember *res = fieldMemberInit(field,res_poly,res_poly_deg);

    mu_check(fieldMembersAreEqual(dif, res));

    freeFieldMember(mem1,0);
    freeFieldMember(mem2,0);
    freeFieldMember(dif, 0);
    freeFieldMember(res,1);
}

void testMultiplication(uint8_t *irred_poly, uint8_t irred_poly_deg, uint8_t field_mod,
                     uint8_t *poly1, uint8_t poly1_deg,
                     uint8_t *poly2, uint8_t poly2_deg,
                     uint8_t *res_poly, uint8_t res_poly_deg)
{
    Field *field = getField(field_mod,irred_poly,irred_poly_deg);
    FieldMember *mem1 = fieldMemberInit(field,poly1,poly1_deg);
    FieldMember *mem2 = fieldMemberInit(field,poly2,poly2_deg);
    FieldMember *mul = ffMul(mem1, mem2);
    FieldMember *res = fieldMemberInit(field,res_poly,res_poly_deg);

    mu_check(fieldMembersAreEqual(mul, res));

    freeFieldMember(mem1,0);
    freeFieldMember(mem2,0);
    freeFieldMember(mul, 0);
    freeFieldMember(res,1);
}

void testDivision(uint8_t *irred_poly, uint8_t irred_poly_deg, uint8_t field_mod,
                        uint8_t *poly1, uint8_t poly1_deg,
                        uint8_t *poly2, uint8_t poly2_deg)
{
    Field *field = getField(field_mod,irred_poly,irred_poly_deg);
    FieldMember *mem1 = fieldMemberInit(field,poly1,poly1_deg);
    FieldMember *mem2 = fieldMemberInit(field,poly2,poly2_deg);
    FieldMember *div = ffDiv(mem1, mem2);
    FieldMember *new_mem1 = ffMul(div,mem2);

    mu_check(fieldMembersAreEqual(mem1, new_mem1));

    freeFieldMember(mem1,0);
    freeFieldMember(mem2,0);
    freeFieldMember(div, 0);
    freeFieldMember(new_mem1,1);
}

MU_TEST(test_ff_to_uint8)
{
    uint8_t poly[] = {1,0,1,1,1,0,0,0,1};
    Field *field = getField(2, poly,8);
    FieldMember *mem = getZero(field);
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
    Field *field = getField(2,poly,16);
    FieldMember *mem = getZero(field);
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
    Field *field = getField(2,poly,32);
    FieldMember *mem = getZero(field);
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
    FieldMember *mem = uint8_to_ff(elem);
    mu_check(ff_to_uint8(mem) == elem);
    freeFieldMember(mem, 1);
}

MU_TEST(test_uint16_to_ff)
{
    uint16_t elem = 4325;
    FieldMember *mem = uint16_to_ff(elem);
    mu_check(ff_to_uint16(mem) == elem);
    freeFieldMember(mem, 1);
}

MU_TEST(test_uint32_to_ff)
{
    uint32_t elem = 5345346;
    FieldMember *mem = uint32_to_ff(elem);
    mu_check(ff_to_uint32(mem) == elem);
    freeFieldMember(mem, 1);
}

MU_TEST(test_fieldMemberInit)
{
    uint8_t irred_poly[] = {1,1,0,0,1};
    Field *field = getField(3,irred_poly,4);
    uint8_t poly[] = {1,3,2,12};
    uint8_t poly_deg = 3;
    FieldMember *test_mem = fieldMemberInit(field,poly,poly_deg);
    FieldMember *mem = getZero(field);
    for (uint8_t i = 0; i <= field->poly_deg; ++i)
    {
        mem->poly[i] = mem->poly[i] = i <= poly_deg ? poly[i] % field->mod : 0;
        if (mem->poly[i] != 0) mem->deg = i;
    }
    mu_check(fieldMembersAreEqual(test_mem,mem));
    freeFieldMember(test_mem,0);
    freeFieldMember(mem,1);
}

MU_TEST(test_operations1)
{
    uint8_t irred_poly[] = {2,1,0,2,1,0,0,0,1};
    uint8_t irred_poly_deg = 8;
    uint8_t field_mod = 3;
    uint8_t poly1[] = {1,1,1,1,4};
    uint8_t poly1_deg = 4;
    uint8_t poly2[] = {2,2,0,1,0,5};
    uint8_t poly2_deg = 5;

    uint8_t sum[] = {0,0,1,2,1,2};
    uint8_t sum_deg = 5;
    testAddition(irred_poly, irred_poly_deg, field_mod,
                 poly1, poly1_deg,
                 poly2, poly2_deg,
                 sum,sum_deg);

    uint8_t dif[] = {2,2,1,0,1,1};
    uint8_t dif_deg = 5;
    testSubtraction(irred_poly, irred_poly_deg, field_mod,
                 poly1, poly1_deg,
                 poly2, poly2_deg,
                 dif,dif_deg);

    uint8_t mul[] = {1,1,2,1,2};
    uint8_t mul_deg = 4;
    testMultiplication(irred_poly, irred_poly_deg, field_mod,
                    poly1, poly1_deg,
                    poly2, poly2_deg,
                    mul,mul_deg);

    testDivision(irred_poly, irred_poly_deg, field_mod,
                       poly1, poly1_deg,
                       poly2, poly2_deg);
}

MU_TEST(test_operations2)
{
    uint8_t irred_poly[] = {2, 1, 0, 2, 1, 0, 0, 0, 1};
    uint8_t irred_poly_deg = 8;
    uint8_t field_mod = 3;
    uint8_t poly1[] = {1, 6, 3, 4, 4, 6, 2, 1};
    uint8_t poly1_deg = 7;
    uint8_t poly2[] = {2, 1, 0, 2, 0, 4};
    uint8_t poly2_deg = 5;

    uint8_t sum[] = {0,1,0,0,1,1,2,1};
    uint8_t sum_deg = 7;
    testAddition(irred_poly, irred_poly_deg, field_mod,
                 poly1, poly1_deg,
                 poly2, poly2_deg,
                 sum,sum_deg);

    uint8_t dif[] = {2, 2, 0, 2, 1, 2, 2, 1};
    uint8_t dif_deg = 7;
    testSubtraction(irred_poly, irred_poly_deg, field_mod,
                    poly1, poly1_deg,
                    poly2, poly2_deg,
                    dif,dif_deg);

    uint8_t mul[] = {0, 2, 0, 2, 0, 1, 0, 2}; // 1 2 2 2 2 0 0 2 0 1 0 1 2
    uint8_t mul_deg = 7;
    testMultiplication(irred_poly, irred_poly_deg, field_mod,
                       poly1, poly1_deg,
                       poly2, poly2_deg,
                       mul,mul_deg);

    testDivision(irred_poly, irred_poly_deg, field_mod,
                 poly1, poly1_deg,
                 poly2, poly2_deg);
}

MU_TEST(test_operations3)
{
    uint8_t irred_poly[] = {5,1,0,3,1,0,0,0,1};
    uint8_t irred_poly_deg = 8;
    uint8_t field_mod = 7;
    uint8_t poly1[] = {7,4,6,5,5,3,1,1};
    uint8_t poly1_deg = 7;
    uint8_t poly2[] = {4,4,5,6,1,3};
    uint8_t poly2_deg = 5;

    uint8_t sum[] = {4,1,4,4,6,6,1,1};
    uint8_t sum_deg = 7;
    testAddition(irred_poly, irred_poly_deg, field_mod,
                 poly1, poly1_deg,
                 poly2, poly2_deg,
                 sum,sum_deg);

    uint8_t dif[] = {4,0,6,1,3,0,6,6};
    uint8_t dif_deg = 7;
    testSubtraction(irred_poly, irred_poly_deg, field_mod,
                    poly2, poly2_deg,
                    poly1, poly1_deg,
                    dif,dif_deg);

    uint8_t mul[] = {4,2,1,1,0,3,5};
    uint8_t mul_deg = 6;
    testMultiplication(irred_poly, irred_poly_deg, field_mod,
                       poly1, poly1_deg,
                       poly2, poly2_deg,
                       mul,mul_deg);

    testDivision(irred_poly, irred_poly_deg, field_mod,
                 poly1, poly1_deg,
                 poly2, poly2_deg);
}

MU_TEST_SUITE(test_suite)
{

    MU_RUN_TEST(test_ff_to_uint8);
    MU_RUN_TEST(test_ff_to_uint16);
    MU_RUN_TEST(test_ff_to_uint32);

    MU_RUN_TEST(test_uint8_to_ff);
    MU_RUN_TEST(test_uint16_to_ff);
    MU_RUN_TEST(test_uint32_to_ff);

    MU_RUN_TEST(test_fieldMemberInit);

    MU_RUN_TEST(test_operations1);
    MU_RUN_TEST(test_operations2);
    MU_RUN_TEST(test_operations3);

}

int main()
{
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return MU_EXIT_CODE;
}
