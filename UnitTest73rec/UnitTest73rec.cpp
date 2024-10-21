#include "pch.h"
#include "CppUnitTest.h"
#include "../7.3_rec/7.3_rec.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest73rec
{
	TEST_CLASS(UnitTest73rec)
	{
	public:

		// ���� ��� �������� ��������� ���������� �������
		TEST_METHOD(TestShiftMatrix)
		{
			const int n = 3;
			const int k = 1;

			// ��������� ������� ������� 3x3
			int** a = new int* [n];
			for (int i = 0; i < n; i++)
				a[i] = new int[n];

			// ����������� �������
			int init[3][3] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					a[i][j] = init[i][j];

			// ���������� ��������� ���� ��������� ����� �� 1 �������
			int expected[3][3] = { {6, 2, 3}, {4, 5, 1}, {7, 8, 9} };

			// ��������� ������� ��� ��������� ����������
			ShiftMatrix(a, n, k);

			// �������� ����������
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					Assert::AreEqual(expected[i][j], a[i][j]);

			// ��������� ���'��
			for (int i = 0; i < n; i++)
				delete[] a[i];
			delete[] a;
		}
	};
}
