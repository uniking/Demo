#include <cstdio>
#include <cstring>
using namespace std;
long long twist(long long u,long long v)
{
	return (((u & 0x80000000L) | (v & 0x7fffffffL)) >> 1) ^ ((v & 1) == 1 ? 0x9908b0dfL : 0);
}
long long state[624];
int left=1;

void next_state()
{
	int p = 0;
	left = 624;
	for (int j = 228; --j > 0; p++) 
		state[p] = state[p+397] ^ twist(state[p], state[p + 1]);

	for (int j=397;--j>0;p++) 
		state[p] = state[p-227] ^ twist(state[p], state[p + 1]);

	state[p] = state[p-227] ^ twist(state[p], state[0]);
}
long long next()
{
	if (--left == 0) next_state();
	return state[624-left];
}
int main()
{
	for(int j=1;j<624;j++)
	{
		state[j] = (1812433253L * (state[j - 1] ^ (state[j - 1] >> 30)) + j);
		state[j] &= 0xffffffffL;
	}
	//for(long long  i=0;i<5000000000L;i++)
	for(long long  i=0;i<20000000L;i++)
	{
		printf("%lld\n",next());
	}
	return 0;
}

