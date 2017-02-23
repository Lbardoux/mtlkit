/**
 * @file mat.hpp
 * @brief Offers a single way to manipulate matrix over the program.
 * 
 * 
 * @author MTLCRBN
 * @version 1.0
 */
#ifndef MTLKIT_MAT_HPP_INCLUDED
#define MTLKIT_MAT_HPP_INCLUDED

#include <type_traits> // For compile time checks.
#include <cstdint>     // For fixed bytes sized types.
#include <algorithm>   // For common algorithm such as std::copy.
#include <iostream>    // For std::ostream.
#include <iterator>    // For std::ostream_iterator.
#include <array>       // To replace static C array.
#include <stdexcept>   // For std::runtime_error


/**
 * @class Matrix
 * @brief Defines a matrix <b>Rows</b>x<b>Cols</b> of type \b T.
 */
template<typename T, uint32_t Rows, uint32_t Cols>
class Matrix final
{
    public:
        /**
         * @brief Construct a matrix, filled with the default value of \b T if
         * no argument was provide.
         * @param[in] value The default value for every matrix value.
         */
        Matrix(const T& value = T()) noexcept
        {
            this->_buffer.fill(value);
        }
        //! @brief Destroy the current matrix.
        ~Matrix(void) noexcept
        {
            
        }
        /**
         * @brief Construct a new matrix by copying \b other.
         * @param[in] other The matrix to copy.
         */
        Matrix(const Matrix<T, Rows, Cols>& other) noexcept
        {
            this->copy(other);
        }
        /**
         * @brief Construct a new matrix by "moving" the buffered values.
         * @param[in,out] other The other Matrix to move.
         */
        Matrix(Matrix<T, Rows, Cols>&& other) noexcept
        {
            this->move(other);
        }
        /**
         * @brief Affects \b other to \b this by copy.
         * @param[in] other The matrix to copy.
         * @return A reference on this matrix.
         */
        Matrix<T, Rows, Cols>& operator=(const Matrix<T, Rows, Cols>& other) noexcept
        {
            return this->copy(other);
        }
        /**
         * @brief Affects \b other to \b this by move.
         * @param[in] other The matrix to moves.
         * @return A reference on this matrix.
         */
        Matrix<T, Rows, Cols>& operator=(Matrix<T, Rows, Cols>&& other) noexcept
        {
            return this->move(std::move(other));
        }
        /**
         * @brief Grants access to the number of columns of this Matrix.
         * @return The number of columns.
         */
        inline uint32_t cols(void) const noexcept
        {
            return Cols;
        }
        /**
         * @brief Grants access to the number of rows of this Matrix.
         * @return The number of rows.
         */
        inline uint32_t rows(void) const noexcept
        {
            return Rows;
        }
        /**
         * @brief Grants access to the number of elements stored on this matrix.
         * @return The number of elements, basicaly rows*cols.
         */
        inline uint32_t nbElements(void) const noexcept
        {
            return Rows*Cols;
        }
        /**
         * @brief Grants access to the size of the matrix.
         * @return The number elements stored on this matrix.
         */
        uint32_t size(void) const noexcept
        {
            return Rows;
        }
        
        Matrix<T, Cols, Rows> transpose(void) const noexcept
        {
            Matrix<T, Cols, Rows> result;
            
            // TODO
            
            return result;
        }
        /**
         * @brief Computes the determinant of this matrix if possible.
         * @return The result of this computation.
         * @pre The current matrix must be a square matrix.
         * @throw std::runtime_error If the matrix isn't square.
         */
        double determinant(void) const
        {
            return _determinant(std::integral_constant<bool, Rows == Cols>());
        }
        
        
        
        
    private:
        std::array<T, Rows*Cols> _buffer; //!< The internal storage for the matrix' values [rows*cols].
        
        // Checks some aspects of the templates.
        static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type.");
        static_assert(std::integral_constant<bool, Rows >= 2>::value, "You must precise at least 2 rows !");
        static_assert(std::integral_constant<bool, Cols >= 2>::value, "You must precise at least 2 cols !");
        
        /**
         * @brief Copies \b other elements.
         * @param[in] other The matrix with the same dimensions to copy.
         */
        Matrix<T, Rows, Cols>& copy(const Matrix<T, Rows, Cols>& other) noexcept
        {
            std::copy(other._buffer.cbegin(), other._buffer.cend(), this->_buffer.begin());
            return *this;
        }
        /**
         * @brief Moves \b other elements
         * @param[in,out] other The matrix to moves, which will be filled with default values.
         */
        Matrix<T, Rows, Cols>& move(Matrix<T, Rows, Cols>&& other) noexcept
        {
            this->copy(other);
            other.fill(T());
            return *this;
        }
        /**
         * @brief Computes the square matrix determinant.
         * @return The result of this computation.
         */
        double _determinant(std::true_type) const
        {
            // TODO
            return 0.0;
        }
        /**
         * @brief Undefined case of the determinant computation
         * @return Nothing
         * @throw std::runtime_error Because it's undefined.
         */
        double _determinant(std::false_type) const
        {
            throw std::runtime_error("determinant isn't defined for a non square matrix");
        }
};


#endif
