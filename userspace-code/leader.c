#include <stdio.h>
int main() {
	int size, i;
	printf("Enter the size of the list: ");
	scanf("%d", &size);
	int arr[size];
	for(i=0; i<size; i++)
		scanf("%d", &arr[i]);
	int j, k;
	for(j=0; j<size-1; j++)
	{
		int flag=1;
		for(k=j+1; k<size; k++)
		{
			if(arr[k]>arr[j])
			{
				flag=0;
				break;
			}
		}
		if(flag==1)
			printf("\n%d is a LEADER!", arr[j]);
	}
	printf("\n");
	return 0;
}
