#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int find(int frame_size, int *queue, int page_num)
{
	int i, found = 0;
	for (i = 1; i <= frame_size; i++)
	{
		if (queue[i] == page_num)
			found = 1;
	}
	return found;
}

void display(int *queue, int frame_size)
{
	int p;

	printf("\n   Khung:  \t");
	for (p = 1; p <= frame_size; p++)
	{
		printf("%d ", queue[p]);
	}
}

int nxt_ref_lru(char* reference_string, int distinct[], int type, int start, int page_frames[], int frame_size)
{
	int i, v, victim = 0, ref[10], j, page_num, min;
	char c[1];
	//ref=(int*)calloc(type,sizeof(int));

	for (i = 1; i <= type; i++)
	{
		for (j = 1; j <= frame_size; j++)
		{
			if (page_frames[j] == distinct[i])
			{
				ref[i] = 0;               //if present in page_frames
				break;
			}
			else
			{
				ref[i] = 50;                //if not present
			}
		}
	}

	for (i = 0; i <= start; i++)
	{
		c[0] = reference_string[i];
		page_num = atoi(c);

		for (j = 1; j <= type; j++)
		{
			if ((distinct[j] == page_num) && (ref[j] >= 0) && (ref[j] != 50))
			{
				ref[j] = i + 1;
			}
		}
	}

	min = 20;
	v = 0;
	for (j = 1; j <= type; j++)
	{
		if (ref[j]<min)
		{
			min = ref[j];
			v = distinct[j];
		}
	}

	for (j = 1; j <= frame_size; j++)
	{
		if (page_frames[j] == v)
		{
			victim = j;
			break;
		}
	}

	return victim;
}

int nxt_ref_opt(char* reference_string, int distinct[], int type, int start, int queue[], int frame_size)
{
	int i, v, victim = 0, length, *ref, j, page_num, max, victim_flag = 1;
	char c[1];
	ref = (int*)calloc(type, sizeof(int));

	for (i = 1; i <= type; i++)
	{
		for (j = 1; j <= frame_size; j++)
		{
			if (queue[j] == distinct[i])
			{
				ref[i] = 0;               //if present in queue
				break;
			}
			else
			{
				ref[i] = -1;                //if not present
			}
		}
	}

	length = strlen(reference_string);

	for (i = start; i<length; i++)
	{
		c[0] = reference_string[i];
		page_num = atoi(c);

		for (j = 1; j <= type; j++)
		{
			if ((distinct[j] == page_num) && (ref[j] == 0))
			{
				ref[j] = (i - start) + 1;
				break;
			}
		}
	}

	for (j = 1; j <= type; j++)
	{
		if (ref[j] == 0)
		{
			victim_flag = 0;
			v = j;
			break;
		}
	}

	if (victim_flag == 0)
	{
		for (j = 1; j <= frame_size; j++)
		{
			if (queue[j] == distinct[v])
			{
				victim = j;
				break;
			}
		}
	}
	else
	{
		max = -1;
		v = 0;
		for (j = 1; j <= type; j++)
		{
			if (ref[j]>max)
			{
				max = ref[j];
				v = distinct[j];
			}
		}

		for (j = 1; j <= frame_size; j++)
		{
			if (queue[j] == v)
			{
				victim = j;
				break;
			}
		}
	}
	return victim;
}

int nxt_ref_lfu(char* reference_string, int distinct[], int type, int start, int page_frames[], int frame_size)
{
	int i, v, victim = 0, ref[10], j, page_num, max;
	char c[1];
	for (i = 1; i <= type; i++)
	{
		for (j = 1; j <= frame_size; j++)
		{
			if (page_frames[j] == distinct[i])
			{
				ref[i] = 0;               //if present in page_frames
				break;
			}
			else
			{
				ref[i] = -1;                //if not present
			}
		}
	}

	for (i = 0; i <= start; i++)
	{
		c[0] = reference_string[i];
		page_num = atoi(c);

		for (j = 1; j <= type; j++)
		{
			if ((distinct[j] == page_num) && (ref[j] == 0))
			{
				ref[j] = ref[j] + 1;
			}
		}
	}

	max = -1;
	v = 0;
	for (j = 1; j <= type; j++)
	{
		if (ref[j]>max)
		{
			max = ref[j];
			v = distinct[j];
		}
	}

	for (j = 1; j <= frame_size; j++)
	{
		if (page_frames[j] == v)
		{
			victim = j;
			break;
		}
	}

	return victim;
}

void LFU(int frame_size, char* reference_string)
{
	int i, page_frames[10], page_num, available, victim = 1, distinct[10], type;
	int page_fault = 0, length, j, flag = 0, k, p;
	char c[1];

	for (i = 1; i <= frame_size; i++)
	{
		page_frames[i] = -1;
	}
	length = strlen(reference_string);

	type = 1;
	for (j = 0; j<length; j++)
	{
		flag = 0;
		c[0] = reference_string[j];
		page_num = atoi(c);

		for (k = 1; k <= type; k++)
		{
			if (distinct[k] == page_num)
			{
				flag = 1;
				break;
			}
		}

		if (flag == 0)
		{
			distinct[type] = page_num;
			type++;
		}
	}
	type = type - 1;

	for (j = 0; j<length; j++)
	{
		flag = 0;
		c[0] = reference_string[j];
		page_num = atoi(c);
		printf("\n\n%d] Trang=%d", j + 1, page_num);
		available = find(frame_size, page_frames, page_num);

		if (available == 0)
		{
			for (p = 1; p <= frame_size; p++)
			{
				if (page_frames[p] == -1)
				{
					flag = p;
					break;
				}
			}
			if (flag != 0)
			{
				page_frames[flag] = page_num;
				page_fault++;
			}
			else if (flag == 0)
			{
				victim = nxt_ref_lfu(reference_string, distinct, type, j, page_frames, frame_size);
				printf("\tLoi Trang");
				printf(", Thay The Trang So %d", page_frames[victim]);
				page_frames[victim] = page_num;
				page_fault++;
			}
		}
		else
		{
			printf("\tTrang Da Ton Tai Trong Khung");
		}
		display(page_frames, frame_size);
		getch();
	}
	printf("\n \tTong So Trang Loi: %d", page_fault);
}
void Second(int frame_size, char* reference_string)
{
	int i, page_frames[10], page_num, available, victim = 1;
	int page_fault = 0, length, j, flag = 0, p, v_page = 1, dist, fnd, ref[10][2], x;
	char c[1];

	for (i = 1; i <= frame_size; i++)
	{
		page_frames[i] = -1;
	}
	length = strlen(reference_string);

	for (j = 0; j<length; j++)
	{
		flag = 0;
		c[0] = reference_string[j];
		page_num = atoi(c);
		printf("\n\n%d] Trang=%d", j + 1, page_num);
		available = find(frame_size, page_frames, page_num);

		if (available == 0)
		{
			for (p = 1; p <= frame_size; p++)
			{
				if (page_frames[p] == -1)
				{
					flag = p;
					break;
				}
			}
			if (flag != 0)
			{
				page_frames[flag] = page_num;
				ref[flag][1] = page_num;
				ref[flag][2] = 0;
				page_fault++;
			}
			else if (flag == 0)
			{
				fnd = 0;

				while (fnd != 1)
				{
					for (i = 1; i <= frame_size; i++)
					{
						if (ref[v_page][2] == 1)
						{
							victim = v_page;
							v_page++;
							if (v_page == frame_size + 1)
								v_page = 1;
							fnd = 1;
							break;
						}
						else if (ref[v_page][2] == 0)
						{
							ref[i][2] = 1;
							v_page++;
							if (v_page == frame_size + 1)
								v_page = 1;
						}
					}
				}
				printf("\tLoi Trang");
				printf(", Thay The Trang So %d", page_frames[victim]);
				page_frames[victim] = page_num;
				ref[victim][1] = page_num;
				ref[victim][2] = 0;
				page_fault++;
			}
		}
		else
		{
			printf("\tTrang Da Ton Tai Trong Khung");
		}
		display(page_frames, frame_size);
		getch();
	}
	printf("\n \tTong So Trang Loi: %d", page_fault);
}

void FIFO(int frame_size, char* reference_string)
{
	int i, *queue, page_num, available, victim = 1;
	int page_fault = 0, length, j;
	char c[1];

	queue = (int*)calloc(frame_size, sizeof(int));
	for (i = 1; i <= frame_size; i++)
	{
		queue[i] = -1;
	}
	length = strlen(reference_string);

	for (j = 0; j<length; j++)
	{
		c[0] = reference_string[j];
		page_num = atoi(c);
		printf("\n\n%d] Trang=%d", j + 1, page_num);
		available = find(frame_size, queue, page_num);

		if (available == 0)
		{
			printf("\tLoi Trang");
			printf(", Thay The Trang So %d", victim);
			queue[victim] = page_num;
			victim++;
			if (victim == frame_size + 1)
				victim = 1;
			page_fault++;
		}
		else
			printf("\tTrang Da Ton Tai Trong Khung");
		display(queue, frame_size);
		getch();
	}
	printf("\n \tTong So Trang Loi: %d", page_fault);
}

void Optimal(int frame_size, char* reference_string)
{
	int i, queue[6], page_num, available, victim = 1, distinct[10], type;
	int page_fault = 0, length, j, flag = 0, k, p;
	char c[1];

	for (i = 1; i <= frame_size; i++)
	{
		queue[i] = -1;
	}
	length = strlen(reference_string);

	type = 1;
	for (j = 0; j<length; j++)
	{
		flag = 0;
		c[0] = reference_string[j];
		page_num = atoi(c);

		for (k = 1; k <= type; k++)
		{
			if (distinct[k] == page_num)
			{
				flag = 1;
				break;
			}
		}

		if (flag == 0)
		{
			distinct[type] = page_num;
			type++;
		}
	}
	type = type - 1;

	for (j = 0; j<length; j++)
	{
		flag = 0;
		c[0] = reference_string[j];
		page_num = atoi(c);
		printf("\n\n%d] Trang=%d", j + 1, page_num);
		available = find(frame_size, queue, page_num);

		if (available == 0)
		{
			for (p = 1; p <= frame_size; p++)
			{
				if (queue[p] == -1)
				{
					flag = p;
					break;
				}
			}
			if (flag != 0)
			{
				queue[flag] = page_num;
				page_fault++;
			}
			else if (flag == 0)
			{
				victim = nxt_ref_opt(reference_string, distinct, type, j + 1, queue, frame_size);
				printf("\tLoi Trang");
				printf(", Thay The Trang So %d", victim);
				queue[victim] = page_num;
				page_fault++;
			}
		}
		else
		{
			printf("\tTrang Da Ton Tai Trong Khung");
		}
		display(queue, frame_size);
		getch();
	}
	printf("\n \tTong So Trang Loi: %d", page_fault);
}

void LRU(int frame_size, char* reference_string)
{
	int i, page_frames[10], page_num, available, victim = 1, distinct[10], type;
	int page_fault = 0, length, j, flag = 0, k, p;
	char c[1];

	for (i = 1; i <= frame_size; i++)
	{
		page_frames[i] = -1;
	}
	length = strlen(reference_string);

	type = 1;
	for (j = 0; j<length; j++)
	{
		flag = 0;
		c[0] = reference_string[j];
		page_num = atoi(c);

		for (k = 1; k <= type; k++)
		{
			if (distinct[k] == page_num)
			{
				flag = 1;
				break;
			}
		}

		if (flag == 0)
		{
			distinct[type] = page_num;
			type++;
		}
	}
	type = type - 1;

	for (j = 0; j<length; j++)
	{
		flag = 0;
		c[0] = reference_string[j];
		page_num = atoi(c);
		printf("\n\n%d] Trang=%d", j + 1, page_num);
		available = find(frame_size, page_frames, page_num);

		if (available == 0)
		{
			for (p = 1; p <= frame_size; p++)
			{
				if (page_frames[p] == -1)
				{
					flag = p;
					break;
				}
			}
			if (flag != 0)
			{
				page_frames[flag] = page_num;
				page_fault++;
			}
			else if (flag == 0)
			{
				victim = nxt_ref_lru(reference_string, distinct, type, j, page_frames, frame_size);
				printf("\tLoi Trang");
				printf(", Thay The Trang So %d", page_frames[victim]);
				page_frames[victim] = page_num;
				page_fault++;
			}
		}
		else
		{
			printf("\tTrang Da Ton Tai Trong Khung");
		}
		display(page_frames, frame_size);
		getch();
	}
	printf("\n \tTong So Trang Loi: %d", page_fault);
}

int main()
{
	int frame_size;
	char reference_string[50];

	printf("\n Nhap kich thuoc khung trang: ");
	scanf("%d", &frame_size);

	printf("\n Nhap chuoi trang se thay the: ");
	scanf("%s", &reference_string);
	while (1){
		system("cls");
		int chon;
		printf("-->Chon giai thuat thay the trang<--\n\n");
		printf("1. FIFO (FirstInFirstOut)\n");
		printf("2. SecondChance (CoHoiThu2)\n");
		printf("3. Optimal (ToiUuHoa)\n");
		printf("4. LRU (LeastRecentlyUsed)\n");
		printf("5. LFU (LeastFrequentlyUsed)\n\n");
		printf("Ban chon: ");
		scanf("%d", &chon);
		printf("\nKich thuoc khung trang = %d\n", frame_size);
		printf("Chuoi trang thay the: %s", reference_string);
		switch (chon){
		case 1:
			FIFO(frame_size, reference_string);
			break;
		case 2:
			Second(frame_size, reference_string);
			break;
		case 3:
			Optimal(frame_size, reference_string);
			break;
		case 4:
			LRU(frame_size, reference_string);
			break;
		case 5:
			LFU(frame_size, reference_string);
			break;
		}
		getch();
	}
}



