#ifndef H_UTILS
#define H_UTILS

template<typename T>
T clamp(T value, T a, T b)
{
	if (a > b)
	{
		T temp = a;
		a = b;
		b = temp;
	}

	if (value < a)
	{
		return a;
	}
	if (value > b)
	{
		return b;
	}
	return value;
}


#endif // !H_UTILS
