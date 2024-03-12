#ifndef FINITE_FIELDS_LIBRARY_H
#define FINITE_FIELDS_LIBRARY_H

#include <inttypes.h>
#include <stdlib.h>

typedef struct
{
    size_t mod;
    size_t poly_dim;
    uint8_t *poly;
} Field;

typedef struct
{
    Field *field;
    size_t dim;
    uint8_t *member;
} FieldMember;

Field *getField(size_t mod, const uint8_t *poly, size_t poly_dim);

FieldMember *getZero(Field *field);

FieldMember *getIdentity(Field *field);

FieldMember *ffAdd(const FieldMember *left, const FieldMember *right);

FieldMember *ffSub(const FieldMember *left, const FieldMember *right);

FieldMember *ffMul(const FieldMember *left, const FieldMember *right);

FieldMember *ffDiv(const FieldMember *left, const FieldMember *right);

FieldMember *ffInv(const FieldMember *elem); // обратное

FieldMember *ffNeg(const FieldMember *elem); // противоположное

FieldMember *uint8_to_ff(uint8_t elem);

FieldMember *uint16_to_ff(uint16_t elem);

FieldMember *uint32_to_ff(uint32_t elem);

uint8_t ff_to_uint8(const FieldMember *elem);

uint16_t ff_to_uint16(const FieldMember *elem);

uint32_t ff_to_uint32(const FieldMember *elem);

#endif //FINITE_FIELDS_LIBRARY_H
