#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <Windows.h>
int main()
{
	int A = 0, B = 0, C = 0, D = 0, E = 0, F = 0, G = 0, H = 0, I = 0, J = 0, K = 0, L = 0, M = 0, N = 0, O = 0, P = 0, Q = 0, R = 0, S = 0, T = 0, U = 0, V = 0, W = 0, X = 0, Y = 0, Z = 0;

	while (1)
	{
		char ch = getchar();
		if (ch == '\n')
		{
			break;
		}
		int tmp = ch;
		switch (tmp)
		{
		case 65:
		case 97:
			A++;
			break;
		case 66:
		case 98:
			B++;
			break;
		case 67:
		case 99:
			C++;
			break;
		case 68:
		case 100:
			D++;
			break;
		case 69:
		case 101:
			E++;
			break;
		case 70:
		case 102:
			F++;
			break;
		case 71:
		case 103:
			G++;
			break;
		case 72:
		case 104:
			H++;
			break;
		case 73:
		case 105:
			I++;
			break;
		case 74:
		case 106:
			J++;
			break;
		case 75:
		case 107:
			K++;
			break;
		case 76:
		case 108:
			L++;
			break;
		case 77:
		case 109:
			M++;
			break;
		case 78:
		case 110:
			N++;
			break;
		case 79:
		case 111:
			O++;
			break;
		case 80:
		case 112:
			P++;
			break;
		case 81:
		case 113:
			Q++;
			break;
		case 82:
		case 114:
			R++;
			break;
		case 83:
		case 115:
			S++;
			break;
		case 84:
		case 116:
			T++;
			break;
		case 85:
		case 117:
			U++;
			break;
		case 86:
		case 118:
			V++;
			break;
		case 87:
		case 119:
			W++;
			break;
		case 88:
		case 120:
			X++;
			break;
		case 89:
		case 121:
			Y++;
			break;
		case 90:
		case 122:
			Z++;
			break;
		}
	}
	printf("A:%d\nB:%d\nC:%d\nD:%d\nE:%d\nF:%d\nG:%d\nH:%d\nI:%d\nJ:%d\nK:%d\nL:%d\nM:%d\nN:%d\nO:%d\nP:%d\nQ:%d\nR:%d\nS:%d\nT:%d\nU:%d\nV:%d\nW:%d\nZ:%d\nY:%d\nZ:%d\n",A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z);
	return 0;
}