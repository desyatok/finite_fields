#include <stdlib.h>

#include "library.h"

Field *getField(uint8_t mod, const uint8_t *poly, uint8_t poly_deg)
{
    Field *newField = (Field *)malloc(sizeof(Field));
    newField->mod = mod;
    newField->poly_deg = poly_deg;
    newField->irred_poly = (uint8_t *)malloc((poly_deg + 1) * sizeof(uint8_t));
    for (size_t i = 0; i <= poly_deg; ++i)
    {
        newField->irred_poly[i] = poly[i];
    }
    return newField;
}

void freeField(Field *field)
{
    if (field == NULL) return;
    free(field->irred_poly);
    free(field);
}

void freeFieldMember(FieldMember *mem, _Bool delete_field)
{
    if (mem == NULL) return;
    if (delete_field)
    {
        freeField(mem->field);
    }
    free(mem->poly);
    free(mem);
}

FieldMember *getZero(Field *field)
{
    if (field == NULL) return NULL;
    FieldMember *zero = (FieldMember *)malloc(sizeof(FieldMember));
    zero->field = field;
    zero->poly = (uint8_t *)malloc(field->poly_deg * sizeof(uint8_t));
    for (uint8_t i = 0; i < field->poly_deg; ++i) // memset
    {
        zero->poly[i] = 0;
    }
    return zero;
}

FieldMember *getIdentity(Field *field)
{

}

uint8_t ff_to_uint8(const FieldMember *elem)
{
    if (elem == NULL || elem->field->mod != 2 || elem->field->poly_deg != 8) return 0;
    uint8_t num = 0;
    for (uint8_t i = 0; i < elem->field->poly_deg; ++i)
    {
        num |= elem->poly[i] << i;
    }
    return num;
}

uint16_t ff_to_uint16(const FieldMember *elem)
{
    if (elem == NULL || elem->field->mod != 2 || elem->field->poly_deg != 16) return 0;
    uint16_t num = 0;
    for (uint8_t i = 0; i < elem->field->poly_deg; ++i)
    {
        num |= elem->poly[i] << i;
    }
    return num;
}

uint32_t ff_to_uint32(const FieldMember *elem)
{
    if (elem == NULL || elem->field->mod != 2 || elem->field->poly_deg != 32) return 0;
    uint32_t num = 0;
    for (uint8_t i = 0; i < elem->field->poly_deg; ++i)
    {
        num |= elem->poly[i] << i;
    }
    return num;
}

FieldMember *uint8_to_ff(uint8_t elem)
{
    uint8_t poly[] = {1,0,1,1,1,0,0,0,1};
    Field *field = getField(2,poly,8);
    FieldMember *mem = getZero(field);
    for (uint8_t i = 0; i < mem->field->poly_deg; ++i)
    {
        mem->poly[i] = elem % 2;
        elem /= 2;
    }
    return mem;
}

FieldMember *uint16_to_ff(uint16_t elem)
{
    uint8_t poly[] = {1,1,0,1,0,0,0,0,
                       0,0,0,0,1,0,0,0, 1};
    Field *field = getField(2,poly,16);
    FieldMember *mem = getZero(field);
    for (uint8_t i = 0; i < mem->field->poly_deg; ++i)
    {
        mem->poly[i] = elem % 2;
        elem /= 2;
    }
    return mem;
}

FieldMember *uint32_to_ff(uint32_t elem)
{
    uint8_t poly[] = {1,1,1,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,1,0,
                      0,0,0,0,0,0,0,0,1};
    Field *field = getField(2,poly,32);
    FieldMember *mem = getZero(field);
    for (uint8_t i = 0; i < mem->field->poly_deg; ++i)
    {
        mem->poly[i] = elem % 2;
        elem /= 2;
    }
    return mem;
}

FieldMember *fieldMemberInit(Field *field, const uint8_t *poly, uint8_t poly_deg)
{
    if (field == NULL || poly == NULL || field->poly_deg <= poly_deg) return NULL;
    FieldMember *member = getZero(field);
    for (uint8_t i = 0; i < field->poly_deg; ++i) // memset ?
    {
        member->poly[i] = i <= poly_deg ? poly[i] % field->mod : 0;
    }
    return member;
}

_Bool fieldsAreEqual(const Field *left, const Field *right)
{
    if (left == NULL || right == NULL || left->mod != right->mod || left->poly_deg != right->poly_deg) return 0;
    for (uint8_t i = 0; i <= left->poly_deg; ++i)
    {
        if (left->irred_poly[i] != right->irred_poly[i]) return 0;
    }
    return 1;
}

_Bool fieldMembersAreEqual(const FieldMember *left, const FieldMember *right)
{
    if (left == NULL || right == NULL
        || !fieldsAreEqual(left->field, right->field)) return 0;
    for (uint8_t i = 0; i < left->field->poly_deg; ++i)
    {
        if (left->poly[i] != right->poly[i]) return 0;
    }
    return 1;
}

FieldMember *ffAdd(const FieldMember *left, const FieldMember *right)
{
    if (left == NULL || right == NULL || !fieldsAreEqual(left->field, right->field)) return NULL;
    FieldMember *result = getZero(left->field);
    for (uint8_t i = 0; i < left->field->poly_deg; ++i)
    {
        result->poly[i] = (left->poly[i] + right->poly[i]) % left->field->mod;
    }
    return result;
}

FieldMember *ffNeg(const FieldMember *elem)
{
    if (elem == NULL || elem->field == NULL) return NULL;
    FieldMember *result = getZero(elem->field);
    for (uint8_t i = 0; i < elem->field->poly_deg; ++i)
    {
        result->poly[i] = (elem->field->mod - elem->poly[i]) % elem->field->mod;
    }
    return result;
}

FieldMember *ffSub(const FieldMember *left, const FieldMember *right)
{
    FieldMember *neg_right = ffNeg(right);
    FieldMember *result = ffAdd(left, neg_right);
    freeFieldMember(neg_right, 0);
    return result;
}

FieldMember *fieldMemberCopy(FieldMember *elem)
{
    if (elem == NULL || elem->field == NULL) return NULL;
    FieldMember *copy = getZero(elem->field);
    for (uint8_t i = 0; i <= copy->field->poly_deg; ++i) // memcpy
    {
        copy->poly[i] = elem->poly[i];
    }
    return copy;
}

FieldMember *takeMod(const uint8_t *left, uint8_t left_deg, Field *field)
{
    uint8_t *res_poly = (uint8_t *)malloc((left_deg + 1) * sizeof(uint8_t));
    for (uint8_t i = 0; i <= left_deg; ++i) // memcpy
    {
        res_poly[i] = left[i];
    }
    uint8_t res_deg = left_deg;

    while (res_deg >= field->poly_deg)
    {
        uint8_t leading_coefficient = res_poly[res_deg] / field->irred_poly[field->poly_deg];
        for (uint8_t i = 0; i <= field->poly_deg; ++i)
        {
            uint8_t neg_sub = (field->mod - (leading_coefficient * field->irred_poly[i]) % field->mod)
                              % field->mod;
            res_poly[res_deg - field->poly_deg + i] = (res_poly[res_deg - field->poly_deg + i] + neg_sub)
                                                      % field->mod;
        }
        while (res_deg != UINT8_MAX && res_poly[res_deg] == 0)
        {
            res_deg--;
        }
    }
    FieldMember *result = fieldMemberInit(field,res_poly,res_deg);
    free(res_poly);
    return result;
}

FieldMember *ffMul(const FieldMember *left, const FieldMember *right)
{

}

FieldMember *fastPow(FieldMember* elem, uint64_t power)
{
    if (elem == NULL || elem->field == NULL) return NULL;
    FieldMember *result = getIdentity(elem->field);
    FieldMember *base = fieldMemberCopy(elem);
    while (power > 0)
    {
        if (power & 1)
        {
            FieldMember *tmp = result;
            result = ffMul(result,base);
            freeFieldMember(tmp,0);
        }
        FieldMember *tmp = base;
        base = ffMul(base,base);
        freeFieldMember(tmp,0);
        power >>= 1;
    }
    freeFieldMember(base,0);
    return result;
}

uint64_t fastPowIntegers(uint64_t base, uint8_t power)
{
    uint64_t result = 1;
    while (power > 0)
    {
        if (power & 1)
        {
            result *= base;
        }
        base *= base;
        power >>= 1;
    }
    return result;
}

FieldMember *ffInv(FieldMember *elem)
{
    uint64_t power = fastPowIntegers((uint64_t)elem->field->mod,elem->field->poly_deg) - 2;
    return fastPow(elem,power);
}

FieldMember *ffDiv(const FieldMember *left, FieldMember *right)
{
    FieldMember *right_inv = ffInv(right);
    FieldMember *result = ffMul(left,right_inv);
    freeFieldMember(right_inv,0);
    return result;
}
