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
