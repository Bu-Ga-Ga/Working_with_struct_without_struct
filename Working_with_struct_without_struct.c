#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//---------------------
#define G(st,i) (*(int*)(st[i])) //Группа
#define R(st,i) (*(double*)(sizeof(int)+st[i]))//Рейтинг
#define N(st,i) (sizeof(int)+sizeof(double)+st[i])//Имя студента
//--------------------

typedef struct S1_ //Тип называется struct S1_ //при использовании typedef тип стал просто S1_.(Например typedef int ii делает ii синонимом int)
	{
		int group;       //Обращение к элементам структуры через точку(.).Если указатель на структуру то обращение через стрелку(=>)
		double rate;
		char name[100];
	}S1; // Имя переменной S1.//После написания typedef S1 не имя переменной а тип того чем было struct S1_ до слова typedef.


typedef struct S2_  //Структура S2 для старосты(leader)(номер телефона есть только у старосты)
	{
		int group;
		double rate;
		char phone[20];
		char name[100];
	}S2;

//----------------------СЛОЖНО------------------

typedef enum SType_   //(SType-student type)Создали новый тип который может принимать значения student либо leader
	{
		student=1,leader=2
	}SType;
typedef struct SS_  //Задаем структруру которую можно интерпретировать как S1 А\а можно как S2.
	{
		SType type;
		union
			{
				S1 s1;
				S2 s2;
			};
	}SS;

//--------------------

int main(void)
	{ 
		printf("sz=%d\n",(int)sizeof(S1));
//----------------------------------------------------Работа со структурами без структур.----------------------------------------------
			{
				char (*st)[120],stmp[120],*s; //st массив-студентов
				int nst,itmp,l,i;// nst-количество студентов//l-это номер первого символа сразу после завершени рейтинга.
				double dtmp;
				FILE *f;
				f=fopen("text.txt","r");

				for(nst=0;fgets(stmp,sizeof(stmp),f)!=NULL && sscanf(stmp,"%d %lg",&itmp,&dtmp)==2;nst++);//этот цикл считает, сколько студентов записано в файле. После && проверяется что строка не пустая. Для этого считываем из строки целое и вещественное число. Если удалось то засчитываем строку.

				fclose(f);
				st=(char (*)[120])malloc(nst*sizeof(st[0]));//Отводим память.
				f=fopen("text.txt","r");

				for(nst=0;fgets(stmp,sizeof(stmp),f)!=NULL && sscanf(stmp,"%d %lg%n",&itmp,&dtmp,&l)==2;nst++)
					{
						if((s=strchr(stmp,'\n'))!=NULL)*s='\0';//Чтоб не было лишнего символа перехода не новую строку
						G(st,nst)=itmp;
						R(st,nst)=dtmp;
						strcpy(N(st,nst),stmp+l+1);
					}
				fclose(f);

				for(i=0;i<nst;i++)
					{
						printf("%d %lg '%s'\n",G(st,i),R(st,i),N(st,i));
					}

				free(st);
			}
//------------------------------------------------------------------------------------------------------------------------------------

			printf("--------------------------------------\n");
				{
					S1 *st; //st-указатель на S1
					char stmp[120], *s;
					int nst,itmp,l,i;
					double dtmp;
					FILE *f;
					f=fopen("text.txt","r");

					for(nst=0;fgets(stmp,sizeof(stmp),f)!=NULL && sscanf(stmp,"%d %lg",&itmp,&dtmp)==2;nst++);
					fclose(f);

					st=(S1*)malloc(nst*sizeof(S1));
					f=fopen("text.txt","r");

					for(nst=0;fgets(stmp,sizeof(stmp),f)!=NULL && sscanf(stmp,"%d %lg%n",&itmp,&dtmp,&l)==2;nst++)//%n показывает сколько символов прочитано предыдущими форматными опереторами
						{
							if((s=strchr(stmp,'\n'))!=NULL)*s='\0';
							st[nst].group=itmp;
							st[nst].rate=dtmp;
							strcpy(st[nst].name,stmp+l+1);
						}
					fclose(f);
					for(i=0;i<nst;i++) printf("%d %lg '%s'\n",st[i].group, st[i].rate,st[i].name);
					free(st);

				}

			printf("----------------------------------------\n");
				{
					SS *st;
					char stmp[120], *s;
					int nst,itmp,l,i,l2;
					double dtmp;
					FILE *f;
					f=fopen("text.txt","r");

					for(nst=0;fgets(stmp,sizeof(stmp),f)!=NULL && sscanf(stmp,"%d %lg",&itmp,&dtmp)==2;nst++);
					fclose(f);

					st=(SS*)malloc(nst*sizeof(S1));
					f=fopen("text.txt","r");

					for(nst=0;fgets(stmp,sizeof(stmp),f)!=NULL && sscanf(stmp,"%d %lg%n",&itmp,&dtmp,&l)==2;nst++)
						{
							if((s=strchr(stmp,'\n'))!=NULL)*s='\0';
								if(nst==0)//У нас первый это староста.
									{
										sscanf(stmp+l+1,"%s%n",st[nst].s2.phone,&l2);//l2 количество использованных символов
										st[nst].type=leader;
										st[nst].s2.group=itmp;
										st[nst].s2.rate=dtmp;
										strcpy(st[nst].s2.name,stmp+l+1+l2+1);
									}
								else
									{
										st[nst].type=student;
										st[nst].s1.group=itmp;
										st[nst].s1.rate=dtmp;
										strcpy(st[nst].s1.name,stmp+l+1);

									}
						}
					fclose(f);

					for(i=0;i<nst;i++)
						{
							if(st[i].type==leader) 
								printf("%d %lg {%s} '%s'\n",st[i].s2.group, st[i].s2.rate, st[i].s2.phone, st[i].s2.name);
							else
								printf("%d %lg '%s'\n",st[i].s1.group, st[i].s1.rate,st[i].s1.name);
						}
							free(st);			
				}
				printf("--------------------\n");
				return 0;
	}		
























