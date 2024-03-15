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
    zero->deg = 0;
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
