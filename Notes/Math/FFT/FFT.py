def FFT(P):
    # P - [p0, p1, ..., pn-1] coeff representation
    n = len(P) # n is a power of 2
    if n == 1:
        return P
    w = exp(2 * pi * i / n)
    p_even, p_odd = P[::2], P[1::2]
    y_even, y_odd = FFT(p_even), FFT(p_odd)
    y = [0] * n
    for j in range(n/2):
        y[j] = y_even[j] + w**j * y_odd[j]
        y[j + n/2] = y_even[j] - w**j * y_odd[j]
    return y
    
def IFFT(P):
    # P - [p(w0), p(w1), ..., p(wn-1)] value representation
    n = len(P) # n is a power of 2
    if n == 1:
        return P
    w = (1/n) * exp(-2 * pi * i / n)
    p_even, p_odd = P[::2], P[1::2]
    y_even, y_odd = IFFT(p_even), IFFT(p_odd)
    y = [0] * n
    for j in range(n/2):
        y[j] = y_even[j] + w**j * y_odd[j]
        y[j + n/2] = y_even[j] - w**j * y_odd[j]
    return y