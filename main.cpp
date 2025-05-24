#include <iostream>
#include <matplot/matplot.h>

using namespace matplot;

int main() {
    std::vector<double> x, y;
    for (int i = 0; i < 5000; i++) {
        x.push_back(i * 0.001);
        y.push_back(std::sin(2 * pi * 2 * i * 0.001));
    }
    int N = y.size();
    std::vector<std::complex<double>> fourier(N);
    //plot(x, y);
    for (int k = 0; k < N; k++) {
        for (int n = 0; n < N; n++) {
            double angle = 2 * M_PI * k * n / N;
            fourier[k] += y[n] * std::polar(1.0, -angle);
        }
        y[k] = std::min(static_cast<int>(std::abs(fourier[k])), 1000000);
    }
    plot(x, y);
    //plot(x, fourier);
    title("Wykres");
    xlabel("Czas");
    ylabel("y");

    show();

    return 0;
}