#include <cmath>
#include <cstddef>
#include <algorithm>
#include <iostream>
#include <memory>
#include <type_traits>
#include <numeric>
#include <cstdlib>
#include <arm_neon.h>

/*!
 * @brief アラインメントされたメモリを動的確保する関数
 * @tparam T  確保するメモリの要素型．この関数の返却値はT*
 * @param [in] nBytes     確保するメモリサイズ (単位はbyte)
 * @param [in] alignment  アラインメント (2のべき乗を指定すること)
 * @return  アラインメントし，動的確保されたメモリ領域へのポインタ
 */
template <typename T = void>
static inline T *
alignedMalloc(std::size_t nBytes, std::size_t alignment = alignof(T)) noexcept
{
	void *p;
	return reinterpret_cast<T *>(::posix_memalign(&p, alignment, nBytes) == 0 ? p : nullptr);
}

/*!
 * @brief アラインメントされたメモリを動的確保する関数．配列向けにalignedMallocの引数指定が簡略化されている
 * @tparam T  確保する配列の要素型．この関数の返却値はT*
 * @param [in] size       確保する要素数．すなわち確保するサイズは size * sizeof(T)
 * @param [in] alignment  アラインメント (2のべき乗を指定すること)
 * @return  アラインメントし，動的確保されたメモリ領域へのポインタ
 */
template <typename T>
static inline T *
alignedAllocArray(std::size_t size, std::size_t alignment = alignof(T)) noexcept
{
	return alignedMalloc<T>(size * sizeof(T), alignment);
}

/*!
 * @brief アラインメントされたメモリを解放する関数
 * @param [in] ptr  解放対象のメモリの先頭番地を指すポインタ
 */
static inline void
alignedFree(void *ptr) noexcept
{
	std::free(ptr);
}

/*!
 * @brief std::unique_ptr で利用するアラインされたメモリ用のカスタムデリータ
 */
struct AlignedDeleter
{
	void
	operator()(void *p) const noexcept
	{
		alignedFree(p);
	}
};

static constexpr int ALIGN = alignof(float32x4_t);

/*!
 * @brief 内積計算を行う関数
 * @param [in] a  ベクトルその1
 * @param [in] b  ベクトルその2
 * @param [in] n  ベクトルのサイズ
 * @return  内積
 */
static inline float
innerProduct(const float *a, const float *b, std::size_t n)
{

	static constexpr std::size_t INTERVAL = sizeof(float32x4_t) / sizeof(float);
	alignas(ALIGN) float s[INTERVAL] = {0};
	float32x4_t sumx4 = {0};
	for (std::size_t i = 0; i < n; i += INTERVAL)
	{
		float32x4_t ax4 = vld1q_f32(&a[i]);
		float32x4_t bx4 = vld1q_f32(&b[i]);
		sumx4 = vmlaq_f32(sumx4, ax4, bx4);
	}

	std::size_t offset = n - n % INTERVAL;
	return std::inner_product(
		a + offset,
		a + n,
		b + offset,
		std::accumulate(std::begin(s), std::end(s), 0.0f));
}

int main()
{
	static constexpr int N_ELEMENT = 256;

	std::unique_ptr<float[], AlignedDeleter> a(alignedAllocArray<float>(N_ELEMENT, ALIGN));
	std::unique_ptr<float[], AlignedDeleter> b(alignedAllocArray<float>(N_ELEMENT, ALIGN));
	for (int i = 0; i < N_ELEMENT; i++)
	{
		a[i] = static_cast<float>(i);
		b[i] = static_cast<float>(i);
	}
	std::cout << innerProduct(a.get(), b.get(), N_ELEMENT) << std::endl;

	return 0;
}
