// Ivan Tymoshchenko 206620
// Maciej Lewandowski 203353

#include <matplot/matplot.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

std::pair<std::vector<double>, std::vector<double>> dft(std::vector<double> y, double fs){
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

std::pair<std::vector<double>, std::vector<double>> idft(std::vector<double> y, double fs){
    using namespace matplot;
    int N = y.size();
    std::vector<std::complex<double>> fourier(N);
    std::vector<double> fourier_x(N), fourier_real(N);
    for (int k = 0; k < N; k++) {
        fourier_x[k] = k / fs;
        for (int n = 0; n < N; n++) {
            double angle = 2 * M_PI * k * n / N;
            fourier[k] += y[n] * std::polar(1.0, angle);
        }
        fourier_real[k] = std::real(fourier[k]);
    }
    return {fourier_x, fourier_real};
}

std::pair<std::vector<double>, std::vector<double>> generate_sine(double f, double fs, double length){
    std::vector<double> x, y;
    int x_size = static_cast<int>(fs * length);
    for (int i = 0; i < x_size; i++){
        x.push_back(i / fs);
        y.push_back(std::sin(2 * M_PI * i * f / fs));
    }
    return {x, y};
}

std::pair<std::vector<double>, std::vector<double>> generate_cosine(double f, double fs, double length){
    std::vector<double> x, y;
    int x_size = static_cast<int>(fs * length);
    for (int i = 0; i < x_size; i++){
        x.push_back(i / fs);
        y.push_back(std::cos(2 * M_PI * i * f / fs));
    }
    return {x, y};
}

std::pair<std::vector<double>, std::vector<double>> generate_square(double f, double fs, double length, double fill){
    std::vector<double> x, y;
    int x_size = static_cast<int>(fs * length);
    for (int i = 0; i < x_size; i++){
        x.push_back(i / fs);
        double y_temp = i * f / fs;
        if (y_temp - std::floor(y_temp) >= fill) y.push_back(1);
        else y.push_back(0);
    }
    return {x, y};
}

std::pair<std::vector<double>, std::vector<double>> generate_saw(double f, double fs, double length){
    std::vector<double> x, y;
    int x_size = static_cast<int>(fs * length);
    for (int i = 0; i < x_size; i++){
        x.push_back(i / fs);
        double y_temp = i * f / fs;
        y.push_back(y_temp - std::floor(y_temp));
    }
    return {x, y};
}


PYBIND11_MODULE(signal_lib, m) {
    m.doc() = "Biblioteka do generowania, przetwarzania oraz wyswietlania sygnalow";

    m.def("plot",
            [](const std::vector<double>& x, const std::vector<double>& y) {
                  matplot::plot(x, y);
            },
            "Funkcja 'plot' z biblioteki matplot++. Jako argumenty potrzebuje wektor x oraz wektor y.");

    m.def("show",
            []() {
                  matplot::show();
            },
            "Funkcja 'show' z biblioteki matplot++. Nie potrzebuje argumentow.");
            
    m.def("save",
            [](const std::string& filename) {
                matplot::save(filename);
            },
            "Funkcja 'save' z biblioteki matplot++. Jako argumenty potrzebuje nazwe pliku");

    m.def("dft", &dft,
            "Transformata DFT. Argumenty to wektor y oraz czestotliwosc probkowania.");

    m.def("idft", &idft,
            "Odwrotna ransformata DFT. Argumenty to wektor y oraz czestotliwosc probkowania.");

    m.def("generate_sine", &generate_sine,
            "Tworzenie wykresu sinus. Argumenty to czestotliwosc, czestotliwosc probkowania oraz dlugosc.");

    m.def("generate_cosine", &generate_cosine,
            "Tworzenie wykresu cosinus. Argumenty to czestotliwosc, czestotliwosc probkowania oraz dlugosc.");

    m.def("generate_square", &generate_square,
            "Tworzenie wykresu kwadratowego. Argumenty to czestotliwosc, czestotliwosc probkowania, dlugosc oraz wypelnienie od 0 do 1.");

    m.def("generate_saw", &generate_saw,
            "Tworzenie wykresu pilowego. Argumenty to czestotliwosc, czestotliwosc probkowania oraz dlugosc.");

}