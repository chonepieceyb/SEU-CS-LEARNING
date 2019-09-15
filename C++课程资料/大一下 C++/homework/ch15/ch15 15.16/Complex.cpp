#include"Complex.h"
Complex::Complex(const int t_iReal, const int t_iImaginary)
{
	m_iFlag = 1;
	m_iReal = t_iReal;
	m_iImaginary = t_iImaginary;
}
ostream& operator<<(ostream& output, const Complex& t_C)
{
	if (t_C.m_iFlag == 0)
		return output;
	else
	{
		if (t_C.m_iReal == 0)
		{
			if (t_C.m_iImaginary < 0)
			{
				output << "- " << t_C.m_iImaginary << "i";
				return output;
			}
			else if (t_C.m_iImaginary > 0)
			{
				output << t_C.m_iImaginary << "i";
				return output;
			}
			else
			{
				output << 0;
				return output;
			}
		}
		else
		{
			output << t_C.m_iReal << " ";
			if (t_C.m_iImaginary < 0)
			{
				output << "- " << abs(t_C.m_iImaginary) << "i";
				return output;
			}
			else if (t_C.m_iImaginary > 0)
			{
				output << "+ " << t_C.m_iImaginary << "i";
				return output;
			}
			else
				return output;
		}
	}

}
istream& operator >> (istream& input, Complex& m_C)
{
	((input >> m_C.m_iReal).ignore(3) >> m_C.m_iImaginary).ignore();
	if (input.fail())
	{
		cout << "improper input!\n";
		m_C.m_iReal = 0;
		m_C.m_iImaginary = 0;
		m_C.m_iFlag = 0;
		return input;
	}
	else
	{
		m_C.m_iFlag = 1;
		return input;
	}
		
}