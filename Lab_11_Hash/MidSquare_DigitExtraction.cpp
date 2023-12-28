long int midSquare(long int seed)
{
    int square = seed * seed;
    return (square / 100) % 10000; // Bo 2 cuoi lay 4 cai tiep theo
}
long int moduloDivision(long int seed, long int mod)
{
    return seed % mod; // chia lay du thoi
}
long int digitExtraction(long int seed,int* extractDigits,int size)
{
    vector<int> digits;
    while(seed > 0) {
        digits.push_back(seed % 10);
        seed /= 10;
    }
    std::reverse(digits.begin(), digits.end()); 
    long int sum = 0;
    for (int i = 0; i < size; ++i) {
        if (extractDigits[i] < int(digits.size()))
            sum = sum * 10 + digits[extractDigits[i]];
    }
    return sum;
}
