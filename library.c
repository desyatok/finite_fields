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
    FieldMember *zero = (FieldMember *)malloc(sizeof(FieldMember));
    zero->field = field;
    zero->deg = field->poly_deg;
    zero->poly = (uint8_t *)malloc((zero->deg + 1) * sizeof(uint8_t));
    for (uint8_t i = 0; i <= zero->deg; ++i)
    {
        zero->poly[i] = 0;
    }
    return zero;
}

FieldMember *getIdentity(Field *field)
{
    FieldMember *identity = (FieldMember *)malloc(sizeof(FieldMember));
    identity->field = field;
    identity->deg = field->poly_deg;
    identity->poly = (uint8_t *)malloc((identity->deg + 1) * sizeof(uint8_t));
    for (uint8_t i = 0; i < identity->deg; ++i)
    {
        identity->poly[i] = 0;
    }
    identity->poly[identity->deg] = 1;
    return identity;
}
