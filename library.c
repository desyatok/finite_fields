#include <stdlib.h>

#include "library.h"

Field* getField(uint8_t mod, const uint8_t *poly, uint8_t poly_deg)
{
    Field *newField = (Field *)malloc(sizeof(Field));
    newField->mod = mod;
    newField->poly_deg = poly_deg;
    newField->irred_poly = (uint8_t *)malloc(poly_deg * sizeof(uint8_t));
    for (size_t i = 0; i < poly_deg; ++i)
    {
        newField->irred_poly[i] = poly[i];
    }
    return newField;
}
