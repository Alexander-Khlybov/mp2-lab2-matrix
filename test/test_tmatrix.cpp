#include "utmatrix.h"

#include <gtest.h>

TEST(TMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TMatrix<int> m(5));
}

TEST(TMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TMatrix<int> m(-5));
}

TEST(TMatrix, can_create_copied_matrix)
{
  TMatrix<int> m(5);

  ASSERT_NO_THROW(TMatrix<int> m1(m));
}

TEST(TMatrix, copied_matrix_is_equal_to_source_one)
{
    TMatrix<int> a(5);
    a.FSV();
    a[2][4] = 7;
    TMatrix<int> b(a);
    EXPECT_EQ(a, b);
}

TEST(TMatrix, copied_matrix_has_its_own_memory)
{
    TMatrix<int> a(5);
    a.FSV();
    a[2][4] = 7;
    TMatrix<int> b(a);
    EXPECT_NE(&a[0], &b[0]);
}

TEST(TMatrix, can_get_size)
{
    TMatrix<int> a(5);
    EXPECT_EQ(5, a.GetSize());
}

TEST(TMatrix, can_set_and_get_element)
{
    TMatrix<int> a(5);
    a.FSV();
    a[2][4] = 7;
    EXPECT_EQ(7, a[2][4]);
}

TEST(TMatrix, throws_when_set_element_with_negative_first_index)
{
    TMatrix<int> a(5);
    ASSERT_ANY_THROW(a[-1][2] = 3);
}
TEST(TMatrix, throws_when_set_element_with_negative_second_index)
{
    TMatrix<int> a(5);
    ASSERT_ANY_THROW(a[2][-1] = 3);
}

TEST(TMatrix, throws_when_set_element_with_too_large_first_index)
{
    TMatrix<int> a(5);
    ASSERT_ANY_THROW(a[6][1] = 3);
}

TEST(TMatrix, throws_when_set_element_with_too_large_second_index)
{
    TMatrix<int> a(5);
    ASSERT_ANY_THROW(a[1][6] = 3);
}

TEST(TMatrix, can_assign_matrix_to_itself)
{
    TMatrix<int> a(5);
    ASSERT_NO_THROW(a = a);
}

TEST(TMatrix, can_assign_matrices_of_equal_size)
{
    TMatrix<int> a(5);
    TMatrix<int> b(5);
    ASSERT_NO_THROW(a = b);
}

TEST(TMatrix, assign_operator_change_matrix_size)
{
    TMatrix<int> a(5);
    TMatrix<int> b(7);
    int x = a.GetSize();
    a = b;
    int x2 = a.GetSize();
    EXPECT_NE(x, a.GetSize());
}

TEST(TMatrix, can_assign_matrices_of_different_size)
{
    TMatrix<int> a(5);
    TMatrix<int> b(7);
    ASSERT_NO_THROW(a = b);
}

TEST(TMatrix, compare_equal_matrices_return_true)
{
    TMatrix<int> a(5);
    a.FSV();
    a[3][3] = 1;
    TMatrix<int> b(5);
    b.FSV();
    b[3][3] = 1;
    EXPECT_EQ(1, a == b);
}

TEST(TMatrix, compare_matrix_with_itself_return_true)
{
    TMatrix<int> a(5);
    a.FSV();
    a[3][3] = 1;
    EXPECT_EQ(1, a == a);
}

TEST(TMatrix, matrices_with_different_size_are_not_equal)
{
    TMatrix<int> a(5);
    a.FSV();
    a[3][3] = 1;
    TMatrix<int> b(7);
    b.FSV();
    b[3][3] = 1;
    EXPECT_EQ(0, a == b);
}

TEST(TMatrix, can_add_matrices_with_equal_size)
{
    TMatrix<int> a(5);
    a.FSV();
    a[3][3] = 1;
    TMatrix<int> b(5);
    b.FSV();
    b[3][4] = 1;
    ASSERT_NO_THROW(a + b);
}

TEST(TMatrix, cant_add_matrices_with_not_equal_size)
{
    TMatrix<int> a(5);
    a.FSV();
    a[3][3] = 1;
    TMatrix<int> b(7);
    b.FSV();
    b[3][3] = 1;
    ASSERT_ANY_THROW(a + b);
}

TEST(TMatrix, can_subtract_matrices_with_equal_size)
{
    TMatrix<int> a(5);
    a.FSV();
    a[3][3] = 1;
    TMatrix<int> b(5);
    b.FSV();
    b[3][4] = 1;
    ASSERT_NO_THROW(a - b);
}

TEST(TMatrix, cant_subtract_matrixes_with_not_equal_size)
{
    TMatrix<int> a(5);
    a.FSV();
    a[3][3] = 1;
    TMatrix<int> b(7);
    b.FSV();
    b[3][3] = 1;
    ASSERT_ANY_THROW(a - b);
}