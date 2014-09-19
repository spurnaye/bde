// bslstl_ownerless.h                                                 -*-C++-*-
#ifndef INCLUDED_BSLSTL_OWNERLESS
#define INCLUDED_BSLSTL_OWNERLESS

#ifndef INCLUDED_BSLS_IDENT
#include <bsls_ident.h>
#endif
BSLS_IDENT("$Id$ $CSID$")

//@PURPOSE: Provide an ordering for shared and weak pointers.
//
//@CLASSES:
//  bsl::owner_less: ordering comparator for 'shared_ptr' and 'weak_ptr'
//
//@SEE_ALSO: bslstl_sharedptr
//
//@DESCRIPTION: This component provides the C+11 standard binary comparison
// functor, 'bsl::owner_less', that determines the order of two smart pointer
// objects by the relative order of the address of their 'bslma::SharedPtrRep'
// data.. Note that this class is an empty POD type.

// Prevent 'bslstl' headers from being included directly in 'BSL_OVERRIDES_STD'
// mode.  Doing so is unsupported, and is likely to cause compilation errors.
#if defined(BSL_OVERRIDES_STD) && !defined(BSL_STDHDRS_PROLOGUE_IN_EFFECT)
#error "include <bsl_memory.h> instead of <bslstl_ownerless.h> in \
BSL_OVERRIDES_STD mode"
#endif

#ifndef INCLUDED_BSLSCM_VERSION
#include <bslscm_version.h>
#endif

#ifndef INCLUDED_BSLSTL_SHAREDPTR
#include <bslstl_sharedptr.h>
#endif

namespace bsl {

template <class POINTER_TYPE>
struct owner_less;

template <class ELEMENT_TYPE>
struct owner_less<weak_ptr<ELEMENT_TYPE> >;

template <class ELEMENT_TYPE>
struct owner_less<weak_ptr<ELEMENT_TYPE> >;

                        // C++11 Compatibility

template <class ELEMENT_TYPE>
struct owner_less<shared_ptr<ELEMENT_TYPE> > {

    // STANDARD TYPEDEFS
    typedef bool result_type;
    typedef shared_ptr<ELEMENT_TYPE> first_argument_type;
    typedef shared_ptr<ELEMENT_TYPE> second_argument_type;

    //! owner_less() = default;
        // Create an 'owner_less' object.

    //! owner_less(const owner_less& original) = default;
        // Create an 'owner_less' object.  Note that as 'hash' is an empty
        // (stateless) type, this operation will have no observable effect.

    //! ~owner_less() = default;
        // Destroy this object.

    // MANIPULATORS
    //! owner_less& operator=(const owner_less& rhs) = default;
        // Assign to this object the value of the specified 'rhs' object, and
        // return a reference providing modifiable access to this object.  Note
        // that as 'owner_less' is an empty (stateless) type, this operation
        // will have no observable effect.

    // ACCESSORS
    bool operator()(const shared_ptr<ELEMENT_TYPE>& a,
                    const shared_ptr<ELEMENT_TYPE>& b) const;
    bool operator()(const shared_ptr<ELEMENT_TYPE>& a,
                    const weak_ptr<ELEMENT_TYPE>&   b) const;
    bool operator()(const weak_ptr<ELEMENT_TYPE>&   a,
                    const shared_ptr<ELEMENT_TYPE>& b) const;
        // Return 'true' if the address of the
        // 'BloombergLP::bslma::SharedPtrRep' object used by the specified 'a'
        // is ordered before the address of the
        // 'BloombergLP::bslma::SharedPtrRep' object used by the specified 'b'
        // under the total ordering supplied by
        // 'std::less<BloombergLP::bslma::SharedPtrRep *>', and 'false'
        // otherwise.
};

template <class ELEMENT_TYPE>
struct owner_less<weak_ptr<ELEMENT_TYPE> > {

    // STANDARD TYPEDEFS
    typedef bool result_type;
    typedef weak_ptr<ELEMENT_TYPE> first_argument_type;
    typedef weak_ptr<ELEMENT_TYPE> second_argument_type;

    //! owner_less() = default;
        // Create an 'owner_less' object.

    //! owner_less(const owner_less& original) = default;
        // Create an 'owner_less' object.  Note that as 'hash' is an empty
        // (stateless) type, this operation will have no observable effect.

    //! ~owner_less() = default;
        // Destroy this object.

    // MANIPULATORS
    //! owner_less& operator=(const owner_less& rhs) = default;
        // Assign to this object the value of the specified 'rhs' object, and
        // return a reference providing modifiable access to this object.  Note
        // that as 'owner_less' is an empty (stateless) type, this operation
        // will have no observable effect.

    // ACCESSORS
    bool operator()(const weak_ptr<ELEMENT_TYPE>&   a,
                    const weak_ptr<ELEMENT_TYPE>&   b) const;
    bool operator()(const shared_ptr<ELEMENT_TYPE>& a,
                    const weak_ptr<ELEMENT_TYPE>&   b) const;
    bool operator()(const weak_ptr<ELEMENT_TYPE>&   a,
                    const shared_ptr<ELEMENT_TYPE>& b) const;
        // Return 'true' if the address of the
        // 'BloombergLP::bslma::SharedPtrRep' object used by the specified 'a'
        // is ordered before the address of the
        // 'BloombergLP::bslma::SharedPtrRep' object used by the specified 'b'
        // under the total ordering supplied by
        // 'std::less<BloombergLP::bslma::SharedPtrRep *>', and 'false'
        // otherwise.
};


// ============================================================================
//                           INLINE DEFINITIONS
// ============================================================================

                // --------------------------------------------
                // struct owner_less<shared_ptr<ELEMENT_TYPE> >
                // --------------------------------------------

template <class ELEMENT_TYPE>
inline
bool owner_less<shared_ptr<ELEMENT_TYPE> >::operator()(
                                       const shared_ptr<ELEMENT_TYPE>& a,
                                       const shared_ptr<ELEMENT_TYPE>& b) const
{
    return a.owner_before(b);
}

template <class ELEMENT_TYPE>
inline
bool owner_less<shared_ptr<ELEMENT_TYPE> >::operator()(
                                       const shared_ptr<ELEMENT_TYPE>& a,
                                       const weak_ptr<ELEMENT_TYPE>&   b) const
{
    return a.owner_before(b);
}

template <class ELEMENT_TYPE>
inline
bool owner_less<shared_ptr<ELEMENT_TYPE> >::operator()(
                                       const weak_ptr<ELEMENT_TYPE>&   a,
                                       const shared_ptr<ELEMENT_TYPE>& b) const
{
    return a.owner_before(b);
}

                // ------------------------------------------
                // struct owner_less<weak_ptr<ELEMENT_TYPE> >
                // ------------------------------------------

template <class ELEMENT_TYPE>
inline
bool owner_less<weak_ptr<ELEMENT_TYPE> >::operator()(
                                        const weak_ptr<ELEMENT_TYPE>& a,
                                        const weak_ptr<ELEMENT_TYPE>& b) const
{
    return a.owner_before(b);
}

template <class ELEMENT_TYPE>
inline
bool owner_less<weak_ptr<ELEMENT_TYPE> >::operator()(
                                       const shared_ptr<ELEMENT_TYPE>& a,
                                       const weak_ptr<ELEMENT_TYPE>&   b) const
{
    return a.owner_before(b);
}

template <class ELEMENT_TYPE>
inline
bool owner_less<weak_ptr<ELEMENT_TYPE> >::operator()(
                                       const weak_ptr<ELEMENT_TYPE>&   a,
                                       const shared_ptr<ELEMENT_TYPE>& b) const
{
    return a.owner_before(b);
}


// ============================================================================
//                                TYPE TRAITS
// ============================================================================

// Type traits for 'equal_to'
//: o 'equal_to' is a stateless POD, trivially constructible, copyable, and
//:   moveable.

template<class POINTER_TYPE>
struct is_trivially_default_constructible<owner_less<POINTER_TYPE> >
: bsl::true_type
{};

template<class POINTER_TYPE>
struct is_trivially_copyable<owner_less<POINTER_TYPE> >
: bsl::true_type
{};

}  // close 'bsl' namespace

#endif

// ----------------------------------------------------------------------------
// Copyright (C) 2013 Bloomberg Finance L.P.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
// ----------------------------- END-OF-FILE ----------------------------------