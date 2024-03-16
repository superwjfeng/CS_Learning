#include <immintrin.h>
#include <stdio.h>

int main() {
    __m256d a = _mm256_set_pd(4.0, 3.0, 2.0, 1.0);
    __m256d b = _mm256_set_pd(2.5, 3.5, 1.5, 0.5);

    // 执行小于等于比较
    __m256d result = _mm256_cmp_pd(a, b, 0x02);

    // result 的每个元素对应于相应的比较结果
    // 如果 a[i] <= b[i]，则 result[i] 的对应位为 1，否则为 0

    // 打印比较结果
    double resultArray[4];
    _mm256_storeu_pd(resultArray, result);

    printf("Comparison result:\n");
    for (int i = 0; i < 4; i++) {
        printf("%d ", (int)resultArray[i]);
    }

    return 0;
}
