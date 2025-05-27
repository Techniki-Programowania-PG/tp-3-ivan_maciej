#include <iostream>
#include <matplot/matplot.h>

using namespace matplot;

void mppp_plot(auto x, auto y){
    matplot::plot(x, y);
}

void mppp_show(){
    matplot::show();
}

std::pair<std::vector<double>, std::vector<double>> dft(auto y, double fs){
    using namespace matplot;
    int N = y.size();
    std::vector<std::complex<double>> fourier(N);
    std::vector<double> fourier_x(N), fourier_magnitude(N);
    for (int k = 0; k < N >> 1; k++) {
        fourier_x[k] = fs * k / N;
        for (int n = 0; n < N; n++) {
            double angle = 2 * M_PI * k * n / N;
            fourier[k] += y[n] * std::polar(1.0, -angle);
        }
        fourier_magnitude[k] = std::abs(fourier[k]) * 2 / N;
    }
    return {fourier_x, fourier_magnitude};
}

std::pair<std::vector<double>, std::vector<double>> idft(auto y, double fs, double length){
    using namespace matplot;
    int N = y.size();
    std::vector<std::complex<double>> fourier(N);
    std::vector<double> fourier_x(N), fourier_magnitude(N);
    for (int k = 0; k < N; k++) {
        fourier_x[k] = k / (fs * N);
        for (int n = 0; n < N; n++) {
            double angle = 2 * M_PI * k * n / N;
            fourier[k] += y[n] * std::polar(1.0, angle);
        }
        fourier_magnitude[k] = std::real(fourier[k]);
    }
    return {fourier_x, fourier_magnitude};
}

std::pair<std::vector<double>, std::vector<double>> sin(double f, double fs, double length){
    std::vector<double> x, y;
    int x_size = static_cast<int>(fs * length);
    for (int i = 0; i < x_size; i++){
        x.push_back(i / fs);
        y.push_back(std::sin(2 * M_PI * i * f / fs));
    }
    return {x, y};
}

int main() {
    /*std::vector<double> x, y;
    for (int i = 0; i < 10000; i++) {
        x.push_back(i * 0.001);
        y.push_back(std::sin(2 * pi * 10 * i * 0.001) + std::cos(2 * pi * 14 * i * 0.001) * 2);
    }*/
    auto [dft_x, dft_y] = dft(sin(10, 1000, 8).second, 1000);
    //auto [dft_x, dft_y] = dft(y, 1000);
    auto [idft_x, idft_y] = idft(dft_y, 1000, 8);
    //mppp_plot(sin(10, 1000, 8).first, sin(10, 1000, 8).second);
    mppp_plot(idft_x, idft_y);
    //mppp_plot(x, y);
    mppp_show();

    return 0;
}