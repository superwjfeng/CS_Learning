#include <algorithm>
#include <cfloat>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <vector>

const int sched_prio_to_weight[40] = {
    /* -20 */ 88761, 71755, 56483, 46273, 36291,
    /* -15 */ 29154, 23254, 18705, 14949, 11916,
    /* -10 */ 9548,  7620,  6100,  4904,  3906,
    /*  -5 */ 3121,  2501,  1991,  1586,  1277,
    /*   0 */ 1024,  820,   655,   526,   423,
    /*   5 */ 335,   272,   215,   172,   137,
    /*  10 */ 110,   87,    70,    56,    45,
    /*  15 */ 36,    29,    23,    18,    15,
};

double calPow(int nice) { return 1024 / (pow(1.25, double(nice))); }

int main() {
    std::vector<std::vector<double>> matrix(8, std::vector(5, 0.0));
    int m = matrix.size();
    int n = matrix[0].size();
    int nice = -20;

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = calPow(nice++);
        }
    }
    // 设置浮点数输出的小数位数
    std::cout << std::fixed << std::setprecision(2);

    // 找到最大的数字，以便确定字段宽度
    double maxNumber = DBL_MIN;
    for (int i = 0; i < m; ++i) {
        double rowMax = *std::max_element(matrix[i].begin(), matrix[i].end());
        maxNumber = rowMax > maxNumber ? rowMax : maxNumber;
    }
    int fieldWidth = std::to_string(static_cast<int>(maxNumber)).length() +
                     3; // 小数点及小数位

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << std::setw(fieldWidth) << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;

    double sum = 0.0;
    for (int i = 0; i < m; ++i) {
        sum += std::accumulate(matrix[i].begin(), matrix[i].end(), 0.0);
    }

    std::vector<std::vector<double>> percent(8, std::vector(5, 0.0));

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            percent[i][j] = matrix[i][j] / sum;
        }
    }
    // 找到最大的数字，以便确定字段宽度
    double maxNumberPercent = DBL_MIN;
    for (int i = 0; i < m; ++i) {
        double rowMax = *std::max_element(matrix[i].begin(), matrix[i].end());
        maxNumberPercent = rowMax > maxNumber ? rowMax : maxNumber;
    }
    int fieldWidth2 =
        std::to_string(static_cast<int>(maxNumberPercent)).length() +
        3; // 小数点及小数位

    std::cout << std::fixed << std::setprecision(5);

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << percent[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;

    return 0;
}
