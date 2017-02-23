/**
 * @file vec.hpp
 * @brief Defines vec2 , vec3, vec4 for common usage between glsl and mtlkit.
 * @author MTLCRBN
 * @version 1.0
 */
#ifndef MTLKIT_VEC_HPP_INCLUDED
#define MTLKIT_VEC_HPP_INCLUDED

#include <cmath>
#include <cstdint>
#include <stdexcept>
#include <type_traits>
#include <iostream>


/**
 * @struct Vecf
 * @brief A basic implementation to get vec2,3,4 inside the application.
 */
template<typename T, uint32_t N>
struct Vecf final
{
    public:
        Vecf(const Vecf<T, N>& other) = default;
        /**
         * @brief Construct a Vecf with variable arguments.
         * @param[in] args Every arguments being passed to the function.
         */
        template<typename... Args>
        Vecf(const Args&... args)
        {
            this->_construct(0, args...);
        }
        /**
         * @brief Convert this Vecf into a pointer to float, for a const Vecf.
         * You'll have to deal with memory issues.
         */
        operator const T*(void) const noexcept
        {
            return this->values;
        }
        /**
         * @brief Convert this Vecf into a pointer to float.
         * You'll have to deal with memory issues.
         */
        operator T*(void) noexcept
        {
            return this->values;
        }
        /**
         * @brief Returns the x coordinate value of this vec.
         * @return The x value as a float.
         */
        T x(void) const {return this->values[0];}
        /**
         * @brief Returns the y coordinate value of this vec.
         * @return The y value as a float.
         */
        T y(void) const {return this->values[1];}
        /**
         * @brief Returns the u texcoord value of this vec2.
         * @return The u value of this vec2 as a float.
         */
        T u(void) const {return this->x();}
        /**
         * @brief Returns the v texcoord value of this vec2.
         * @return The v value of this vec2 as a float.
         */
        T v(void) const {return this->z();}
        /**
         * @brief Returns the z coordinate value of this vecX with X >= 3
         * @return This z value as a float.
         */
        T z(void) const {return this->_request_z(std::integral_constant<bool, N >= 3>());}
        /**
         * @brief Returns the homogenic coordinate value of this vec4
         * @return This w value as a float.
         */
        T w(void) const {return this->_request_w(std::integral_constant<bool, N == 4>());}
        /**
         * @brief Returns the alpha value of this vec4
         * @return This a value as a float.
         */
        T a(void) const {return this->w();}
        /**
         * @brief Returns the r red value of this vec3|4
         * @return This r value as a float.
         */
        T r(void) const {return this->x();}
        /**
         * @brief Returns the g green value of this vec3|4
         * @return This g value as a float.
         */
        T g(void) const {return this->y();}
        /**
         * @brief Returns the b blue value of this vec3|4
         * @return This b value as a float.
         */
        T b(void) const {return this->z();}
        /**
         * @brief Sets the x coordinate value to \b value.
         * @param[in] value The new value to set up.
         */
        void x(T value) {this->values[0] = value;}
        /**
         * @brief Sets the y coordinate value to \b value.
         * @param[in] value The new value to set up.
         */
        void y(T value) {this->values[1] = value;}
        /**
         * @brief Sets the z coordinate value to \b value.
         * @param[in] value The new value to set up.
         * @pre this must represent a vec3 or vec4.
         */
        void z(T value) {this->_set_z(value, std::integral_constant<bool, N >= 3>());}
        /**
         * @brief Sets the u texcoord value to \b value.
         * @param[in] value The new value to set up.
         * @pre this must represent a vec2.
         */
        void u(T value) {this->x(value);}
        /**
         * @brief Sets the v texcoord value to \b value.
         * @param[in] value The new value to set up.
         * @pre this must represent a vec2.
         */
        void v(T value) {this->y(value);}
        /**
         * @brief Sets the alpha value to \b value.
         * @param[in] value The new value to set up.
         * @pre this must represent a vec4.
         */
        void a(T value) {this->w(value);}
        /**
         * @brief Sets the w homogenic coordinate value to \b value.
         * @param[in] value The new value to set up.
         * @pre this must represent a vec4.
         */
        void w(T value) {this->_set_w(value, std::integral_constant<bool, N == 4>());}
        /**
         * @brief Sets the red color value to \b value.
         * @param[in] value The new value to set up.
         * @pre this must represent a vec3 or a vec4.
         */
        void r(T value) {this->x(value);}
        /**
         * @brief Sets the green color value to \b value.
         * @param[in] value The new value to set up.
         * @pre this must represent a vec3 or a vec4.
         */
        void g(T value) {this->y(value);}
        /**
         * @brief Sets the blue color value to \b value.
         * @param[in] value The new value to set up.
         * @pre this must represent a vec3 or a vec4.
         */
        void b(T value) {this->z(value);}
        /**
         * @brief Affects \b other to \b this as a copy.
         * @param[in] other The same Vecf to copy.
         * @return A reference into \b this to chain calls.
         */
        Vecf<T, N>& operator=(const Vecf<T, N>& other) noexcept
        {
            this->copy(other);
            return *this;
        }
        /**
         * @brief Moves \b other to \b this as a copy.
         * @param[in] other The same Vecf to copy.
         * @return A reference into \b this to chain calls.
         */
        Vecf<T, N>& operator=(Vecf<T, N>&& other) noexcept
        {
            this->copy(other);
            return *this;
        }
        /**
         * @brief Affects \b other to \b this as a copy.
         * @param[in] other Another type of Vecf to copy.
         * @return A reference into \b this to chain calls.
         */
        template<uint32_t V>
        Vecf<T, N>& operator=(const Vecf<T, V>& other) noexcept
        {
            this->copy(other);
            return *this;
        }
        /**
         * @brief Moves \b other to \b this as a copy.
         * @param[in] other Another type of Vecf to copy.
         * @return A reference into \b this to chain calls.
         */
        template<uint32_t V>
        Vecf<T, N>& operator=(Vecf<T, V>&& other) noexcept
        {
            this->copy(other);
            return *this;
        }
        
    private:
        // Convert to std::array
        T values[N]; //!< The container for the datatype you wanna use.
        
        //! @brief Ensures that you don't overflow the possible values.
        static_assert(N >= 2 && N <= 4, "N of Vecf must be between 2 and 4 included");
        static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic datatype");
        
        /**
         * @brief Copy X elements from \b other to \b this, with X = min(#other, #this)
         * @param[in] other The Vecf to copy into this.
         * @return The number of copied elements.
         */
        template<uint32_t V>
        uint32_t copy(const Vecf<T, V>& other)
        {
            uint32_t max_iteration = std::min(V, N);
            uint32_t n             = 0;
            for(uint32_t i=0;i<max_iteration;++i)
            {
                this->values[i] = other.values[i];
                ++n;
            }
            return n;
        }
        //! @brief Construct by copying from a Vecf
        template<uint32_t V, typename... Args>
        void _construct(uint32_t n, const Vecf<T, V>& other, const Args&... args)
        {
            n += this->copy(other);
            this->_construct(n, args...);
        }
        //! @brief If you provides too few values.
        void _construct(uint32_t n)
        {
            if (n < N)
            {
                this->values[n] = T();
                this->_construct(n+1);
            }
        }
        //! @brief Terminal case.
        void _construct(void){}
        //! @brief Filling up the floats.
        template<typename Data, typename... Args>
        void _construct(uint32_t n, const Data& f, const Args&... args)
        {
            static_assert(std::is_arithmetic<Data>::value, "Arguments must be vec or numerics !");
            if (n < N)
            {
                this->values[n] = static_cast<T>(f);
                this->_construct(n+1, args...);
            }
        }
        T _request_z(std::true_type)  const {return this->values[2];}
        T _request_z(std::false_type) const {
            throw std::out_of_range("Request for z|b with vec2 is invalid !");
            return 0.0f;
        }
        T _request_w(std::true_type)  const {return this->values[3];}
        T _request_w(std::false_type) const {
            throw std::out_of_range("Request for w|a with vec2|3 is invalid !");
            return 0.0f;
        }
        void _set_w(T value, std::true_type)  {this->values[3] = value;}
        void _set_w(T value, std::false_type) {
            (void)value;
            throw std::out_of_range("Request for w|a with vec2|3 is invalid !");
        }
        void _set_z(T value, std::true_type)  {this->values[2] = value;}
        void _set_z(T value, std::false_type) {
            (void)value;
            throw std::out_of_range("Request for z|b with vec2 is invalid !");
        }
        
        template<typename TT, uint32_t V> friend Vecf<TT, V>   operator+ (const Vecf<TT, V>& v1, const Vecf<TT, V>& v2);
        template<typename TT, uint32_t V> friend Vecf<TT, V>   operator- (const Vecf<TT, V>& v1, const Vecf<TT, V>& v2);
        template<typename TT, uint32_t V> friend Vecf<TT, V>   operator* (const Vecf<TT, V>& v, float f);
        template<typename TT, uint32_t V> friend Vecf<TT, V>   operator* (float f, const Vecf<TT, V>& v);
        template<typename TT, uint32_t V> friend Vecf<TT, V>   operator/ (const Vecf<TT, V>& v, float f);
        template<typename TT, uint32_t V> friend Vecf<TT, V>&  operator+=(Vecf<TT, V>& self, const Vecf<TT, V>& other);
        template<typename TT, uint32_t V> friend Vecf<TT, V>&  operator-=(Vecf<TT, V>& self, const Vecf<TT, V>& other);
        template<typename TT, uint32_t V> friend Vecf<TT, V>&  operator*=(Vecf<TT, V>& self, float f);
        template<typename TT, uint32_t V> friend Vecf<TT, V>&  operator/=(Vecf<TT, V>& self, float f);
        template<typename TT, uint32_t V> friend bool          operator==(const Vecf<TT, V>& v1, const Vecf<TT, V>& v2);
        template<typename TT, uint32_t V> friend bool          operator!=(const Vecf<TT, V>& v1, const Vecf<TT, V>& v2);
        template<typename TT, uint32_t V> friend std::ostream& operator<<(std::ostream& os, const Vecf<TT, V>& v);
        friend struct Vecf<T, 2>;
        friend struct Vecf<T, 3>;
        friend struct Vecf<T, 4>;
};


/**
 * @brief Apply the + operator on 2 Vecf and write the result into
 * a new rvalue.
 * @param[in] v1 The first  Vecf to sum.
 * @param[in] v2 The second Vecf to sum.
 * @return A new Vecf which contains the sum of \b v1 and \b v2.
 */
template<typename T, uint32_t N>
Vecf<T, N> operator+(const Vecf<T, N>& v1, const Vecf<T, N>& v2)
{
    Vecf<T, N> result;
    for(uint32_t i=0;i<N;++i)
    {
        result.values[i] = v1.values[i] + v2.values[i];
    }
    return result;
}
/**
 * @brief Apply the - operator on 2 Vecf and write the result into
 * a new rvalue.
 * @param[in] v1 The first  Vecf to soustract.
 * @param[in] v2 The second Vecf to soustract.
 * @return A new Vecf which contains the difference of \b v1 and \b v2.
 */
template<typename T, uint32_t N>
Vecf<T, N> operator-(const Vecf<T, N>& v1, const Vecf<T, N>& v2)
{
    Vecf<T, N> result;
    for(uint32_t i=0;i<N;++i)
    {
        result.values[i] = v1.values[i] - v2.values[i];
    }
    return result;
}
/**
 * @brief Apply the operator * between \b v and \b f.
 * @param[in] v The Vecf to operate with.
 * @param[in] f The value to multiply.
 * @return A copy of the result as a Vecf.
 */
template<typename T, uint32_t N>
Vecf<T, N> operator*(const Vecf<T, N>& v, float f)
{
    Vecf<T, N> result;
    for(uint32_t i=0;i<N;++i)
    {
        result.values[i] = v.values[i] * f;
    }
    return result;
}
/**
 * @brief Apply the other case of the operator *, with commutativity.
 * @param[in] f The value to multiply.
 * @param[in] v The Vecf to operate with.
 * @return A copy of the result as a Vecf.
 */
template<typename T, uint32_t N>
Vecf<T, N> operator*(float f, const Vecf<T, N>& v)
{
    return v*f;
}
/**
 * @brief Apply the operator / between \b v and \b f.
 * @param[in] v The Vecf to operate with.
 * @param[in] f The value to divide with.
 * @return A copy of the result as a Vecf.
 */
template<typename T, uint32_t N>
Vecf<T, N> operator/(const Vecf<T, N>& v, float f)
{
    Vecf<T, N> result;
    for(uint32_t i=0;i<N;++i)
    {
        result.values[i] = v.values[i] / f;
    }
    return result;
}
/**
 * @brief Apply \b self + \b other , by modifying \b self.
 * @param[in,out] self  The Vecf to modify with the sum operator.
 * @param[in]     other The other Vecf for the operation.
 * @return A reference to \b self for further operations.
 */
template<typename T, uint32_t N>
Vecf<T, N>& operator+=(Vecf<T, N>& self, const Vecf<T, N>& other)
{
    for(uint32_t i=0;i<N;++i)
    {
        self.values[i] += other.values[i];
    }
    return self;
}
/**
 * @brief Apply \b self - \b other , by modifying \b self.
 * @param[in,out] self  The Vecf to modify with the difference operator.
 * @param[in]     other The other Vecf for the operation.
 * @return A reference to \b self for further operations.
 */
template<typename T, uint32_t N>
Vecf<T, N>& operator-=(Vecf<T, N>& self, const Vecf<T, N>& other)
{
    for(uint32_t i=0;i<N;++i)
    {
        self.values[i] -= other.values[i];
    }
    return self;
}
/**
 * @brief Multiply \b self by \b f by modifying \b self' content.
 * @param[in,out] self The Vecf to modify.
 * @param[in]     f The value to multiply with.
 * @return A reference to \b self for further operations.
 */
template<typename T, uint32_t N>
Vecf<T, N>& operator*=(Vecf<T, N>& self, float f)
{
    for(uint32_t i=0;i<N;++i)
    {
        self.values[i] *= f;
    }
    return self;
}
/**
 * @brief Divide \b self by \b f by modifying \b self' content.
 * @param[in,out] self The Vecf to modify.
 * @param[in]     f The value to divide with.
 * @return A reference to \b self for further operations.
 */
template<typename T, uint32_t N>
Vecf<T, N>& operator/=(Vecf<T, N>& self, float f)
{
    for(uint32_t i=0;i<N;++i)
    {
        self.values[i] /= f;
    }
    return self;
}
/**
 * @brief Compare the values of \b v1 and \b v2 for equality.
 * @param[in] v1 The first  Vecf to compare.
 * @param[in] v2 The second Vecf to compare.
 * @return true if \b v1 is close to \b v2, false otherwise.
 */
template<typename T, uint32_t N>
bool operator==(const Vecf<T, N>& v1, const Vecf<T, N>& v2)
{
    const float EPSILON = 0.0001;
    for(uint32_t i=0;i<N;++i)
    {
        if (std::abs(v1.values[i] - v2.values[i]) > EPSILON)
        {
            return false;
        }
    }
    return true;
}
/**
 * @brief Compare the values of \b v1 and \b v2 for inequality.
 * @param[in] v1 The first  Vecf to compare.
 * @param[in] v2 The second Vecf to compare.
 * @return true if \b v1 is not close to \b v2, false otherwise.
 */
template<typename T, uint32_t N>
bool operator!=(const Vecf<T, N>& v1, const Vecf<T, N>& v2)
{
    return !(v1 == v2);
}
/**
 * @brief Display the content of \b v into \b os.
 * It doesn't display a newline.
 * @param[in,out] os The outputstream to display into.
 * @param[in]     v  The current vec* to display.
 * @return A reference into \b os .
 */
template<typename TT, uint32_t V>
std::ostream& operator<<(std::ostream& os, const Vecf<TT, V>& v)
{
    os << "{" << std::showpoint;
    for(uint32_t i=0;i<V;++i)
    {
        os << ' ' << v.values[i];
    }
    os << " }";
    return os;
}

typedef Vecf<float,    2>  vec2; //!< To manipulate a  float  vec2.
typedef Vecf<float,    3>  vec3; //!< To manipulate a  float  vec3.
typedef Vecf<float,    4>  vec4; //!< To manipulate a  float  vec4.
typedef Vecf<double,   2> dvec2; //!< To manipulate a  double vec2.
typedef Vecf<double,   3> dvec3; //!< To manipulate a  double vec3.
typedef Vecf<double,   4> dvec4; //!< To manipulate a  double vec4.
typedef Vecf<int32_t,  2> ivec2; //!< To manipulate an int    vec2.
typedef Vecf<int32_t,  3> ivec3; //!< To manipulate an int    vec3.
typedef Vecf<int32_t,  4> ivec4; //!< To manipulate an int    vec4.
typedef Vecf<uint32_t, 2> uvec2; //!< To manipulate an uint   vec2.
typedef Vecf<uint32_t, 3> uvec3; //!< To manipulate an uint   vec3.
typedef Vecf<uint32_t, 4> uvec4; //!< To manipulate an uint   vec4.

typedef vec2    Texcoords; //!< To manipulate something more clear than a vec2.
typedef vec3    Vertex;    //!< To manipulate something more clear than a vec3.
typedef vec3    Normal;    //!< To manipulate something more clear than a vec3.
typedef vec4    Color;     //!< To manipulate something more clear than a vec4.

#endif
