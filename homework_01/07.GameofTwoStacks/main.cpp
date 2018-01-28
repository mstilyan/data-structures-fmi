#include <iostream>
#include <vector>

using namespace std;

int main()
{
	int gamesCount;
	cin >> gamesCount;

	for (int currGame = 0; currGame < gamesCount; currGame++)
	{
		int fstStackSize, secStackSize, limit;
		cin >> fstStackSize >> secStackSize >> limit;

		vector<int> fstStack(fstStackSize);
		for (int i = 0; i < fstStackSize; i++)
			cin >> fstStack[i];

		vector<int> secStack(secStackSize);
		for (int i = 0; i < secStackSize; i++)
			cin >> secStack[i];

		int sum = 0, maxCount = 0, temp = 0, fstStackInd = 0, secStackInd = 0;

		//Take from fstStack while sum is in limit
		while (fstStackInd < fstStackSize && sum + fstStack[fstStackInd] <= limit)
		{
			sum += fstStack[fstStackInd];
			fstStackInd++;
		}
		maxCount = fstStackInd;

		while (secStackInd < secStackSize && fstStackInd >= 0)
		{
			sum += secStack[secStackInd];
			secStackInd++;
			//Remove used from fstStack while sum is greater than limit
			while (sum > limit && fstStackInd > 0)
			{
				fstStackInd--;
				sum -= fstStack[fstStackInd];
			}

			//Update maxCount
			if (sum <= limit && fstStackInd + secStackInd > maxCount)
				maxCount = fstStackInd + secStackInd;
		}

		cout << maxCount << endl;
	}
	return 0;
}