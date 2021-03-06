/*
    MANGO Multimedia Development Platform
    Copyright (C) 2012-2019 Twilight Finland 3D Oy Ltd. All rights reserved.
*/
#pragma once

#include "vector.hpp"

namespace mango
{

    template <>
    struct Vector<u16, 32>
    {
        using VectorType = simd::u16x32;
        using ScalarType = u16;
        enum { VectorSize = 32 };

        union
        {
            VectorType m;
            DeAggregate<ScalarType> component[VectorSize];
        };

        ScalarType& operator [] (size_t index)
        {
            assert(index < VectorSize);
            return component[index].data;
        }

        ScalarType operator [] (size_t index) const
        {
            assert(index < VectorSize);
            return component[index].data;
        }

        const ScalarType* data() const
        {
            return reinterpret_cast<const ScalarType *>(component);
        }

        explicit Vector() {}
        ~Vector() {}

        Vector(u16 s)
            : m(simd::u16x32_set1(s))
        {
        }

        Vector(simd::u16x32 v)
            : m(v)
        {
        }

        Vector& operator = (simd::u16x32 v)
        {
            m = v;
            return *this;
        }

        Vector& operator = (u16 s)
        {
            m = simd::u16x32_set1(s);
            return *this;
        }

        operator simd::u16x32 () const
        {
            return m;
        }

#ifdef int512_is_hardware_vector
        operator simd::u16x32::vector () const
        {
            return m.data;
        }
#endif
    };

    static inline const Vector<u16, 32> operator + (Vector<u16, 32> v)
    {
        return v;
    }

    static inline Vector<u16, 32> operator - (Vector<u16, 32> v)
    {
        return simd::sub(simd::u16x32_zero(), v);
    }

    static inline Vector<u16, 32>& operator += (Vector<u16, 32>& a, Vector<u16, 32> b)
    {
        a = simd::add(a, b);
        return a;
    }

    static inline Vector<u16, 32>& operator -= (Vector<u16, 32>& a, Vector<u16, 32> b)
    {
        a = simd::sub(a, b);
        return a;
    }

    static inline Vector<u16, 32> operator + (Vector<u16, 32> a, Vector<u16, 32> b)
    {
        return simd::add(a, b);
    }

    static inline Vector<u16, 32> operator - (Vector<u16, 32> a, Vector<u16, 32> b)
    {
        return simd::sub(a, b);
    }

    static inline Vector<u16, 32> nand(Vector<u16, 32> a, Vector<u16, 32> b)
    {
        return simd::bitwise_nand(a, b);
    }

    static inline Vector<u16, 32> operator & (Vector<u16, 32> a, Vector<u16, 32> b)
    {
        return simd::bitwise_and(a, b);
    }

    static inline Vector<u16, 32> operator | (Vector<u16, 32> a, Vector<u16, 32> b)
    {
        return simd::bitwise_or(a, b);
    }

    static inline Vector<u16, 32> operator ^ (Vector<u16, 32> a, Vector<u16, 32> b)
    {
        return simd::bitwise_xor(a, b);
    }

    static inline Vector<u16, 32> adds(Vector<u16, 32> a, Vector<u16, 32> b)
    {
        return simd::adds(a, b);
    }

    static inline Vector<u16, 32> subs(Vector<u16, 32> a, Vector<u16, 32> b)
    {
        return simd::subs(a, b);
    }

    static inline Vector<u16, 32> min(Vector<u16, 32> a, Vector<u16, 32> b)
    {
        return simd::min(a, b);
    }

    static inline Vector<u16, 32> max(Vector<u16, 32> a, Vector<u16, 32> b)
    {
        return simd::max(a, b);
    }

    static inline mask16x32 operator > (Vector<u16, 32> a, Vector<u16, 32> b)
    {
        return simd::compare_gt(a, b);
    }

    static inline mask16x32 operator < (Vector<u16, 32> a, Vector<u16, 32> b)
    {
        return simd::compare_gt(b, a);
    }

    static inline mask16x32 operator == (Vector<u16, 32> a, Vector<u16, 32> b)
    {
        return simd::compare_eq(a, b);
    }

    static inline Vector<u16, 32> select(mask16x32 mask, Vector<u16, 32> a, Vector<u16, 32> b)
    {
        return simd::select(mask, a, b);
    }

    static inline Vector<u16, 32> operator << (Vector<u16, 32> a, int b)
    {
        return simd::sll(a, b);
    }

    static inline Vector<u16, 32> operator >> (Vector<u16, 32> a, int b)
    {
        return simd::srl(a, b);
    }

} // namespace mango
