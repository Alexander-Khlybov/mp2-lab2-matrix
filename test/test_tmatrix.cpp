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

TEST(TMatrix, DISABLED_copied_matrix_is_equal_to_source_one)
{
  ADD_FAILURE();
}

TEST(TMatrix, DISABLED_copied_matrix_has_its_own_memory)
{
  ADD_FAILURE();
}

TEST(TMatrix, DISABLED_can_get_size)
{
  ADD_FAILURE();
}

TEST(TMatrix, DISABLED_can_set_and_get_element)
{
  ADD_FAILURE();
}

TEST(TMatrix, DISABLED_throws_when_set_element_with_negative_index)
{
  ADD_FAILURE();
}

TEST(TMatrix, DISABLED_throws_when_set_element_with_too_large_index)
{
  ADD_FAILURE();
}

TEST(TMatrix, DISABLED_can_assign_matrix_to_itself)
{
  ADD_FAILURE();
}

TEST(TMatrix, DISABLED_can_assign_matrices_of_equal_size)
{
  ADD_FAILURE();
}

TEST(TMatrix, DISABLED_assign_operator_change_matrix_size)
{
  ADD_FAILURE();
}

TEST(TMatrix, DISABLED_can_assign_matrices_of_different_size)
{
  ADD_FAILURE();
}

TEST(TMatrix, DISABLED_compare_equal_matrices_return_true)
{
  ADD_FAILURE();
}

TEST(TMatrix, DISABLED_compare_matrix_with_itself_return_true)
{
  ADD_FAILURE();
}

TEST(TMatrix, DISABLED_matrices_with_different_size_are_not_equal)
{
  ADD_FAILURE();
}

TEST(TMatrix, DISABLED_can_add_matrices_with_equal_size)
{
  ADD_FAILURE();
}

TEST(TMatrix, DISABLED_cant_add_matrices_with_not_equal_size)
{
  ADD_FAILURE();
}

TEST(TMatrix, DISABLED_can_subtract_matrices_with_equal_size)
{
  ADD_FAILURE();
}

TEST(TMatrix, DISABLED_cant_subtract_matrixes_with_not_equal_size)
{
  ADD_FAILURE();
}

