import sys
sys.path.append('./build')
import signal_lib as sgn


frequency = 1.7
length = 4
frequency_ofsampling = 1000

[x_vec, y_vec] = sgn.generate_sine(frequency, frequency_ofsampling, length)

sgn.plot(x_vec, y_vec)
sgn.save("sine_plot.png")


frequency = 1.7
length = 4
frequency_ofsampling = 1000

[x_vec, y_vec] = sgn.generate_sine(frequency, frequency_ofsampling, length)

[x_vec_dft, y_vec_dft] = sgn.dft(y_vec, frequency_ofsampling)

sgn.plot(x_vec, y_vec)
sgn.save("sin_ft.png")

sgn.plot(x_vec_dft, y_vec_dft)
sgn.save("sin_ft_fft.png")


frequency = 1.7
length = 4
frequency_ofsampling = 1000

[x_vec, y_vec] = sgn.generate_sine(10 * frequency, frequency_ofsampling, length)

[x_vec_dft, y_vec_dft] = sgn.dft(y_vec, frequency_ofsampling)

sgn.plot(x_vec, y_vec)
sgn.save("sin_10_ft.png")

sgn.plot(x_vec_dft, y_vec_dft)
sgn.save("sin_10_ft_fft.png")



frequency = 4
length = 4
frequency_ofsampling = 1000

[x_vec, y_vec] = sgn.generate_saw(frequency, frequency_ofsampling, length)
sgn.plot(x_vec, y_vec)
sgn.save("saw.png")

[x_vec, y_vec] = sgn.generate_square(frequency, frequency_ofsampling, length, 0.5)

[x_vec_dft, y_vec_dft] = sgn.dft(y_vec, frequency_ofsampling)

[x_vec_idft, y_vec_idft] = sgn.idft(y_vec_dft, frequency_ofsampling)

sgn.plot(x_vec, y_vec)
sgn.save("square_05.png")

sgn.plot(x_vec_dft, y_vec_dft)
sgn.plot(x_vec_idft, y_vec_idft)

sgn.save("test.png")

sgn.show()