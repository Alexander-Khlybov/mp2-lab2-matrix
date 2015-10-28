#include "utmatrix.h"

#include <gtest.h>

TEST(TVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TVector<int> v(5));
}

TEST(TVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TVector<int> v(-5));
}

TEST(TVector, throws_when_create_vector_with_negative_startindex)
{
  ASSERT_ANY_THROW(TVector<int> v(5, -2));
}

TEST(TVector, can_create_copied_vector)
{
  TVector<int> v(10);

  ASSERT_NO_THROW(TVector<int> v1(v));
}

TEST(TVector, copied_vector_is_equal_to_source_one)
{
    TVector<int> a(5);
    for (int i = 0; i < a.GetSize(); i++)
        a[i] = 0;
    a[3] = 7;
    TVector<int> b(a);
    EXPECT_EQ(a, b);
}

TEST(TVector, copied_vector_has_its_own_memory)
{
    TVector<int> a(5);
    for (int i = 0; i < a.GetSize(); i++)
        a[i] = 0;
    a[3] = 7;
    TVector<int> b(a);
    EXPECT_NE(&a[a.GetStartIndex()], &b[b.GetStartIndex()]);
}

TEST(TVector, can_get_size)
{
  TVector<int> v(4);

  EXPECT_EQ(4, v.GetSize());
}

TEST(TVector, can_get_start_index)
{
  TVector<int> v(4, 2);

  EXPECT_EQ(2, v.GetStartIndex());
}

TEST(TVector, can_get_element)
{
  TVector<int> a(4);
  for (int i = 0; i < a.GetSize(); i++)
      a[i] = 0;
  a[3] = 7;
  ASSERT_NO_THROW(a[0]);
}

TEST(TVector, can_set_element)
{
    TVector<int> a(4);
    for (int i = 0; i < a.GetSize(); i++)
        a[i] = 0;
    a[3] = 7;
    ASSERT_NO_THROW(a[0] = 1);
}

TEST(TVector, throws_when_set_element_with_negative_index)
{
    TVector<int> a(5);
    ASSERT_ANY_THROW(a[-1] = 1);
}

TEST(TVector, throws_when_set_element_with_too_large_index)
{
    TVector<int> a(5);
    ASSERT_ANY_THROW(a[7] = 1);
}

TEST(TVector, throws_when_set_element_with_index_less_than_StartIndex)
{
    TVector<int> a(5, 3);
    ASSERT_ANY_THROW(a[2] = 1);
}

TEST(TVector, can_assign_vector_to_itself)
{
    TVector<int> a(5);
    for (int i = 0; i < a.GetSize(); i++)
        a[i] = 0;
    a[3] = 7;
  ASSERT_NO_THROW(a = a);
}

TEST(TVector, can_assign_vectors_of_equal_size)
{
    TVector<int> a(5);
    for (int i = 0; i < a.GetSize(); i++)
        a[i] = 0;
    a[3] = 7;
    TVector<int> b(5);
    
    ASSERT_NO_THROW(a = b);
}

TEST(TVector, assign_operator_change_vector_size)
{
    TVector<int> a(5);
    for (int i = 0; i < a.GetSize(); i++)
        a[i] = 0;
    a[3] = 7;
    TVector<int> b(7);
    for (int i = 0; i < b.GetSize(); i++)
        b[i] = 0;
    int t = a.GetSize();
    a = b;
    EXPECT_NE(t, a.GetSize());
}

TEST(TVector, assign_operator_change_StartIndex)
{
    TVector<int> a(5, 1);
    for (int i = a.GetStartIndex(); i < a.GetSize(); i++)
        a[i] = 0;
    a[3] = 7;
    TVector<int> b(5, 2);
    for (int i = b.GetStartIndex(); i < b.GetSize(); i++)
        b[i] = 0;
    int t = a.GetStartIndex();
    a = b;
    EXPECT_NE(t, a.GetStartIndex());
}

TEST(TVector, can_assign_vectors_of_different_size)
{
    TVector<int> a(5);
    for (int i = 0; i < a.GetSize(); i++)
        a[i] = 0;
    a[3] = 7;
    TVector<int> b(7);
    for (int i = 0; i < b.GetSize(); i++)
        b[i] = 0;

    ASSERT_NO_THROW(a = b);
}

TEST(TVector, assign_operator_change_vector)
{
    TVector<int> a(5);
    for (int i = 0; i < a.GetSize(); i++)
        a[i] = 0;
    a[3] = 7;
    TVector<int> b(7);
    for (int i = 0; i < b.GetSize(); i++)
        b[i] = 0;
    b[3] = 7;
    TVector<int> c(a);
    a = b;
    EXPECT_NE(c, a);
}

TEST(TVector, assigned_vector_is_equal_to_source_one)
{
    TVector<int> a(5);
    for (int i = 0; i < a.GetSize(); i++)
        a[i] = 0;
    a[3] = 7;
    TVector<int> b(7);
    for (int i = 0; i < b.GetSize(); i++)
        b[i] = 0;
    a = b;
    EXPECT_EQ(a, b);
}

TEST(TVector, compare_equal_vectors_return_true)
{
    TVector<int> a(5);
    TVector<int> b(5);
    for (int i = 0; i < a.GetSize(); i++)
    {
        a[i] = 0;
        b[i] = 0;
    }
    a[3] = 7;
    b[3] = 7;

    EXPECT_EQ(a, b);
}

TEST(TVector, compare_vector_with_itself_return_true)
{
    TVector<int> a(5);
    for (int i = 0; i < a.GetSize(); i++)
        a[i] = 0;
    a[3] = 7;
    EXPECT_EQ(a, a);
}

TEST(TVector, vectors_with_different_size_are_not_equal)
{
    TVector<int> a(5);
    TVector<int> b(6);
    for (int i = 0; i < a.GetSize(); i++)
    {
        a[i] = 0;
        b[i] = 0;
    }
    b[5] = 0;
    EXPECT_NE(a, b);
}

TEST(TVector, can_add_scalar_to_vector)
{
    TVector<int> a(5);
    for (int i = 0; i < a.GetSize(); i++)
        a[i] = 0;
    a[3] = 7;
    ASSERT_NO_THROW(a + 3);
}

TEST(TVector, can_add_scalar_to_vector_EXP_EQ)
{
    TVector<int> a(5);
    for (int i = 0; i < a.GetSize(); i++)
        a[i] = 0;
    TVector<int> b(a);
    for (int i = 0; i < a.GetSize(); i++)
        a[i] += 3;
    EXPECT_EQ(a, b + 3);
}

TEST(TVector, can_substract_scalar_from_vector)
{
    TVector<int> a(5);
    for (int i = 0; i < a.GetSize(); i++)
        a[i] = 0;
    a[3] = 7;
    ASSERT_NO_THROW(a - 3);
}

TEST(TVector, can_subtract_scalar_from_vector_EXP_EQ)
{
    TVector<int> a(5);
    for (int i = 0; i < a.GetSize(); i++)
        a[i] = 0;
    TVector<int> b(a);
    for (int i = 0; i < a.GetSize(); i++)
        a[i] -= 3;
    EXPECT_EQ(a, b - 3);
}

TEST(TVector, can_multiply_scalar_by_vector)
{
    TVector<int> a(5);
    for (int i = 0; i < a.GetSize(); i++)
        a[i] = 1;
    a[3] = 7;
    ASSERT_NO_THROW(a * 3);
}

TEST(TVector, can_multiply_scalar_by_vector_EXP_EQ)
{
    TVector<int> a(5);
    for(int i = 0; i < a.GetSize(); i++)
        a[i] = 1;
    TVector<int> b(a);
    for (int i = 0; i < a.GetSize(); i++)
        a[i] *= 3;
    EXPECT_EQ(a, b * 3);
}

TEST(TVector, can_add_vectors_with_equal_size)
{
    TVector<int> a(5);
    TVector<int> b(5);
    for (int i = 0; i < a.GetSize(); i++)
    {
        a[i] = 0;
        b[i] = 1;
    }

  ASSERT_NO_THROW(a + b);
}

TEST(TVector, can_add_vectors_with_equal_size_EXP_EQ)
{
    TVector<int> a(5);
    for (int i = 0; i < a.GetSize(); i++)
        a[i] = 0;
    a[3] = 1;
    TVector<int> b(5);
    for (int i = 0; i < b.GetSize(); i++)
        b[i] = 0;
    b[2] = 1;
    TVector<int> ex(5);
    for (int i = 0; i < ex.GetSize(); i++)
        ex[i] = 0;
    ex[2] = 1;
    ex[3] = 1;
    EXPECT_EQ(ex, a + b);
}

TEST(TVector, cant_add_vectors_with_not_equal_size)
{
    TVector<int> a(5);
    for (int i = 0; i < a.GetSize(); i++)
        a[i] = 0;
    a[3] = 7;
    TVector<int> b(6);
    for (int i = 0; i < b.GetSize(); i++)
        b[i] = 0;
  ASSERT_ANY_THROW(a + b);
}

TEST(TVector, can_subtract_vectors_with_equal_size)
{
    TVector<int> a(5);
    TVector<int> b(5);
    for (int i = 0; i < a.GetSize(); i++)
    {
        a[i] = 0;
        b[i] = 1;
    }
    a[3] = 7;
    ASSERT_NO_THROW(a - b);
}

TEST(TVector, can_substract_vectors_with_equal_size_EXP_EQ)
{
    TVector<int> a(5);
    for (int i = 0; i < a.GetSize(); i++)
        a[i] = 0;
    a[3] = 1;
    TVector<int> b(5);
    for (int i = 0; i < b.GetSize(); i++)
        b[i] = 0;
    b[2] = 1;
    TVector<int> ex(5);
    for (int i = 0; i < ex.GetSize(); i++)
        ex[i] = 0;
    ex[2] = -1;
    ex[3] = 1;
    EXPECT_EQ(ex, a - b);
}

TEST(TVector, cant_subtract_vectors_with_not_equal_size)
{
    TVector<int> a(5);
    TVector<int> b(6);
    for (int i = 0; i < a.GetSize(); i++)
    {
        a[i] = 0;
        b[i] = 1;
    }
    b[5] = 7;
    ASSERT_ANY_THROW(a - b);
}

TEST(TVector, can_multiply_vectors_with_equal_size)
{
    TVector<int> a(5);
    TVector<int> b(5);
    for (int i = 0; i < a.GetSize(); i++)
    {
        a[i] = 0;
        b[i] = 1;
    }
    a[3] = 7;
    ASSERT_NO_THROW(a * b);
}

TEST(TVector, can_multiply_vectors_with_equal_size_EXP_EQ)
{
    TVector<int> a(5);
    for (int i = 0; i < a.GetSize(); i++)
        a[i] = 1;
    a[3] = 3;
    TVector<int> b(5);
    for (int i = 0; i < b.GetSize(); i++)
        b[i] = 1;
    b[2] = 2;
    int c = 8;
    EXPECT_EQ(8, a * b);
}

TEST(TVector, cant_multiply_vectors_with_not_equal_size)
{
    TVector<int> a(5);
    TVector<int> b(6);
    for (int i = 0; i < a.GetSize(); i++)
    {
        a[i] = 0;
        b[i] = 1;
    }
    b[5] = 7;
    ASSERT_ANY_THROW(a * b);
}