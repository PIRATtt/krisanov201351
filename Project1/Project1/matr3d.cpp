#pragma once
#include "Matr3d.h"

Matr3Diag::Matr3Diag()
{
	n = 0;
	elem = nullptr;
}

Matr3Diag::Matr3Diag(const Matr3Diag& temp)
{
	this->n = temp.n;
	this -> elem = new double[3 * this->n];
	for (int i = 0; i < 3 * this->n; i++)
		this->elem[i] = temp.elem[i];
}

Matr3Diag::~Matr3Diag()
{
	if (this->elem != nullptr)
		delete[]this->elem;
}

double Matr3Diag::get_elem(int i, int j) const
{
	/*
					 a[n + i]	i == j
		elem[i, j] = a[2n + i]	i == j + 1
					 a[i]	i + 1 == j
					 0	else
	*/
	if (i == j) 
		return this->elem[this->n + i];
	else if (i == j+1)
		return this->elem[2*this->n + i];
	else if (i == j-1)
		return this->elem[i];
	else
		return 0.0;
}

Matr3Diag Matr3Diag::sum(const Matr3Diag& temp)
{
	if (this->n != temp.n)
		return *this;
	Matr3Diag res(temp);
	for (int i = 0; i < 3*this->n; i++)
		res.elem[i] += this->elem[i];
	return res;
}

Matr3Diag Matr3Diag::mult(const Matr3Diag& temp)						//Демонстрация умножения только если вызвать его через отдельный метод, простые вычисления делаются без демонстрации
{
	if (this->n != temp.n)
		return *this;

	std::cout << "Multiplying matix A :" << '\n';
	this->print();
	std::cout << "With matrix B :" << '\n';
	temp.print();
	double* res = new double[3 * this->n];								//Стандартное умножение
	int cnt = 0;
	for (int i = 0; i < this->n; i++)
	{
		for (int j = 0; j < this->n; j++)
		{
			double sum=0;
			
			for (int k = 0; k < this->n; k++)
			{
				sum += this->get_elem(i,j) * temp.get_elem(k,i);
			}
			std::cout << "Sum of row " << i << " from matrix A and column " << j << " from matrix B is " << sum << '\n';
			//std::cout << sum<<' ';
			if (abs(sum - 0) >= 0.0000001)
			{
				res[cnt] = sum;												//Результат в неотсортированном виде
				cnt++;
			}

		}
		std::cout << '\n';
	}
	//for (int i = 0; i < 3*this->n; i++) { std::cout << res[i] << ' '; } std::cout << '\n';
	double* res1 = new double[3 * this->n];

	cnt = 1;
	int cnt1 = 0;
	while (cnt < 3 * this->n)													//Сортировка результата
	{
		res1[cnt1] = res[cnt];
		cnt1++;
		cnt += 3;
	}
	
	//cnt1++;
	cnt = 0;
	while (cnt < 3 * this->n)
	{
		res1[cnt1] = res[cnt];
		cnt1++;
		cnt += 3;
	}
	
	cnt1++;
	cnt = 2;
	while (cnt < 3 * this->n)
	{
		res1[cnt1] = res[cnt];
		cnt1++;
		cnt += 3;
	}
	res1[this->n - 1] = 0;
	res1[2 * this->n] = 0;
	
	//for (int i = 0; i < 3 * this->n; i++) { std::cout << res1[i] << ' '; } std::cout << '\n';
	//
	Matr3Diag out(temp);
	for (int i = 0; i < 3 * this->n; i++)
	{
		out.elem[i] = res1[i];
	}
	std::cout << "Result is :" << '\n';
	out.print();
	delete[] res;
	return out;
}


void Matr3Diag::print() const
{
	for (int i = 0; i < this->n; i++)
	{
		for (int j = 0; j < this->n; j++)
			std::cout << this->get_elem(i, j) << "\t";
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Matr3Diag::input(int size)
{
	this->n = size;
	if(this->elem != nullptr)
		delete[]this->elem;
	this->elem = new double[3 * this->n];
	for (int i = 0; i < 3 * this->n; i++)
		this->elem[i] = i+1;
	this->elem[this->n - 1] = 0;
	this->elem[2*this->n] = 0;
}

void Matr3Diag::operator+=(const Matr3Diag& temp)
{
	//*this = this->sum(temp);
	if (this->n == temp.n)
	{
		for (int i = 0; i < 3*this->n; i++)
			this->elem[i] += temp.elem[i];
	}
}

void Matr3Diag::operator*=(const Matr3Diag& temp)
{
	double* res = new double[3*this->n];								//Стандартное умножение
	int cnt = 0;
	for (int i = 0; i < this->n; i++)
	{
		for (int j = 0; j < this->n; j++)
		{
			double sum = 0;
			for (int k = 0; k < this->n; k++)
			{
				sum += this->get_elem(i,j) * temp.get_elem(k,i);
			}
			if (abs(sum - 0) >= 0.0000001)
			{
				res[cnt] = sum;												//Результат в неотсортированном виде
				cnt++;
			}
			
		}

	}
	double* res1 = new double[3 * this->n];

	cnt = 1;
	int cnt1 = 0;
	while (cnt < 3 * this->n)													//Сортировка результата
	{
		res1[cnt1] = res[cnt];
		cnt1++;
		cnt += 3;
	}

	//cnt1++;
	cnt = 0;
	while (cnt < 3 * this->n)
	{
		res1[cnt1] = res[cnt];
		cnt1++;
		cnt += 3;
	}

	cnt1++;
	cnt = 2;
	while (cnt < 3 * this->n)
	{
		res1[cnt1] = res[cnt];
		cnt1++;
		cnt += 3;
	}
	res1[this->n - 1] = 0;
	res1[2 * this->n] = 0;

	for (int i = 0; i < 3*this->n; i++)									
	{
		this->elem[i] = res1[i];
	}
	delete[] res;
	return;

}

std::ostream& operator<<(std::ostream& out, const Matr3Diag& temp)
{
	//std::cout << 'a';
	for (int i = 0; i < temp.n; i++)
	{
		for (int j = 0; j < temp.n; j++)
			out << temp.get_elem(i, j) << "\t";
		out << std::endl;
	}
	out << std::endl;
	return out;
}

std::istream& operator>>(std::istream& in, Matr3Diag& temp) //Не уверен, что тебе нужно от перегрузки cin, поэтому сделал чтение диагоналей по-очереди 
{
	for (int i = 0; i < temp.get_n()-1; i++)
	{
		in >> temp.elem[i];
	}
	temp.elem[temp.get_n() - 1] = 0;
	for (int i = temp.get_n(); i < 2*temp.get_n(); i++)
	{
		in >> temp.elem[i];
	}
	temp.elem[2 * temp.get_n()] = 0;
	for (int i = 2*temp.get_n()+1; i < 3 * temp.get_n(); i++)
	{
		in >> temp.elem[i];
	}
	//temp.elem[3*temp.get_n() - 1] = 0;
	return in;
}