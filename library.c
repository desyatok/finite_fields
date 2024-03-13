#include <stdlib.h>

#include "library.h"

Field *getField(uint8_t mod, const uint8_t *poly, uint8_t poly_dim)
{
    Field *newField = (Field *)malloc(sizeof(Field));
    newField->mod = mod;
    newField->poly_dim = poly_dim;
    newField->irred_poly = (uint8_t *)malloc(poly_dim * sizeof(uint8_t));
    for (size_t i = 0; i < poly_dim; ++i)
    {
        newField->irred_poly[i] = poly[i];
    }
    return newField;
}

FieldMember *getZero(Field *field)
{
    FieldMember *zero = (FieldMember *)malloc(sizeof(FieldMember));
    zero->field = field;
    zero->dim = field->poly_dim;
    zero->poly = (uint8_t *)malloc(zero->dim * sizeof(uint8_t));
    for (uint8_t i = 0; i < zero->dim; ++i)
    {
        zero->poly[i] = 0;
    }
    return zero;
}

FieldMember *getIdentity(Field *field)
{
    FieldMember *identity = (FieldMember *)malloc(sizeof(FieldMember));
    identity->field = field;
    identity->dim = field->poly_dim;
    identity->poly = (uint8_t *)malloc(identity->dim * sizeof(uint8_t));
    for (uint8_t i = 0; i < identity->dim - 1; ++i)
    {
        identity->poly[i] = 0;
    }
    identity->poly[identity->dim - 1] = 1;
    return identity;
}
