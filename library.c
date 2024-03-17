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
    zero->deg = UINT8_MAX;
    zero->poly = (uint8_t *)malloc((field->poly_deg + 1) * sizeof(uint8_t));
    for (uint8_t i = 0; i <= field->poly_deg; ++i)
    {
        zero->poly[i] = 0;
    }
    return zero;
}

FieldMember *getIdentity(Field *field)
{
    if (field == NULL) return NULL;
    FieldMember *identity = (FieldMember *)malloc(sizeof(FieldMember));
    identity->field = field;
    identity->deg = 0;
    identity->poly = (uint8_t *)malloc((field->poly_deg + 1) * sizeof(uint8_t));
    for (uint8_t i = 1; i <= field->poly_deg; ++i)
    {
        identity->poly[i] = 0;
    }
    identity->poly[0] = 1;
    return identity;
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
        if (mem->poly[i] != 0) mem->deg = i;
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
        if (mem->poly[i] != 0) mem->deg = i;
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
        if (mem->poly[i] != 0) mem->deg = i;
    }
    return mem;
}

FieldMember *fieldMemberInit(Field *field, const uint8_t *poly, uint8_t poly_deg)
{
    if (field == NULL || poly == NULL || field->poly_deg <= poly_deg) return NULL;
    FieldMember *member = getZero(field);
    for (uint8_t i = 0; i <= field->poly_deg; ++i)
    {
        member->poly[i] = i <= poly_deg ? poly[i] % field->mod : 0;
        if (member->poly[i] != 0) member->deg = i;
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
        || !fieldsAreEqual(left->field, right->field)
        || left->deg != right->deg) return 0;
    for (uint8_t i = 0; i <= left->field->poly_deg; ++i)
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
        if (result->poly[i] != 0) result->deg = i;
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
        if (result->poly[i] != 0) result->deg = i;
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
    copy->deg = elem->deg;
    for (uint8_t i = 0; i <= copy->deg; ++i)
    {
        copy->poly[i] = elem->poly[i];
    }
    return copy;
}
