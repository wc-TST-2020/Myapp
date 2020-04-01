# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <windows.h>
# include <ctime>



typedef struct LinNode{//结构体，包含有参与运算的数字、运算符的代号、括号的编号
   float num;
   int sign;
   int tag;
   struct LinNode *next;
}LinNode, *LinkedList;

int creat_LinkedList(LinkedList &List){//创建一个空的单循环链表
	List = (LinkedList)malloc(sizeof(LinNode));
	if(List == NULL) return -1;
	List->next = List;
	return 1;
}

int  insert_LinkedList(LinkedList &List,float num,int sign,int tag){//向单循环链表里插入节点
	LinkedList temp;
	temp = (LinkedList)malloc(sizeof(LinNode));
	if(temp == NULL) return -1;
	temp->num  = num;
	temp->sign = sign;
	temp->tag = tag;
	temp->next = List->next;
	List->next = temp;
	List = temp;
	return 1;
}

int common_divisor(int n,int m){//求最大公因数 
	int temp,r;//把大的数放在n里面 
	if(n<m){
		temp=n;
		n=m;
		m=temp;
	}
	while(m!=0){ 
		r=n%m;
		n=m;
		m=r; 
	}
	return n;//返回最大公因数
}

char *creat_term(int max_num,int term_length){/* 生成项的函数 */
	int i, j, type, num1, num2;//num1、num2是随机生成的整数，type用来指明参与运算的数的类型
	char *term;//term用来存放最终拼接成的项
	char num_term[20];//num_term用来存放整数转换成的字符串
	char part[5][20];
	//二维数组part用来存放这次生成的项的各个组成部分
	//0、2、4列存放项，1、3列存放运算符
	term = (char *)malloc(20 * sizeof(char));//为term申请空间
	memset(term, 0x00, sizeof (char) * 20);//初始化term
	if (term_length) strcpy(term,"(");//如果这个项被分配有运算符则在项的开头加上'('
	srand((unsigned)time(NULL));//生成随机数的种子
    for(i = 0;i < term_length; i++){/* 生成项的运算符 */
        j = rand() % 4;	//生成并项的运算符
		switch(j){
			case 0: strcpy(part[2 * i + 1],"+"); break;
			case 1: strcpy(part[2 * i + 1],"-"); break;
			case 2: strcpy(part[2 * i + 1],"x"); break;
			case 3: strcpy(part[2 * i + 1],"/"); break;
		}
	}
    for(i = 0;i < term_length + 1; i++){/* 生成参与运算的数 */
	    //Sleep(1000);
	    //srand((unsigned)time(NULL));
		type = rand() % 10;//用随机来判定生成参与运算的数的类型
		switch(type){
			case 8://生成小于一的分数
			    do{
                    strcpy(part[2 * i],"(");//在分数前加上'('来区分分数和除运算
                    //srand((unsigned)time(NULL));
                    do{
                        num1 = rand() % max_num + 1;//生成分母
                        num2 = rand() % num1 + 1;//生成分子
						num1 = num1 / common_divisor(num1,num2);//化简
						num2 = num2 / common_divisor(num1,num2);
                    }while(num1 <= num2);/*避免生成非真分数*/
					
                    itoa(num2,num_term,10);//将分子转换成字符串
                    strcat(part[2 * i],num_term);//将二维数组的相应列与生成的字符串拼接起来
                    strcat(part[2 * i],"/");//将二维数组的相应列与'/'拼接起来
                    itoa(num1,num_term,10);//将分母转换成字符串
                    strcat(part[2 * i],num_term);//将二维数组的相应列与生成的字符串拼接起来
                    strcat(part[2 * i],")");//在分数前加上')'来区分分数和除运算
                }while(num1 == num2);/*避免生成 m/m 类型的分数*/
			    break;
			case 9://生成大于一的分数
                do{
                    strcpy(part[2 * i],"(");//在分数前加上'('来区分分数和除运算
                    //srand((unsigned)time(NULL));
                    do{
                        num1 = rand() % max_num + 1;//随机生成分数的小数部分
                    }while(num1 >= max_num);/*保证生成的分数在指定范围内*/
                    itoa(num1,num_term,10);//将生成的整数转换成字符串
                    strcat(part[2 * i],num_term);//将二维数组的相应列与生成的字符串拼接起来
                    strcat(part[2 * i],"'");//将二维数组的相应列与'''拼接起来
                    //srand((unsigned)time(NULL));/*以下与生成小于一的分数类似*/
                    do{
                        num1 = rand() % max_num + 1;
                        num2 = rand() % num1 + 1;
						num1 = num1 / common_divisor(num1,num2);//化简
						num2 = num2 / common_divisor(num1,num2);
                    }while(num1 <= num2);/*避免生成非真分数*/
					
                    itoa(num2,num_term,10);
                    strcat(part[2 * i],num_term);
                    strcat(part[2 * i],"/");
                    itoa(num1,num_term,10);
                    strcat(part[2 * i],num_term);
                    strcat(part[2 * i],")");//在分数前加上')'来区分分数和除运算
                }while(num1 == num2);/*避免生成 m/m 类型的分数*/
				break;
			default://随机数为0~7则生成整数
				//srand((unsigned)time(NULL));
				num1 = rand() % max_num + 1;//随机生成指定范围内的整数
				itoa(num1,part[2 * i],10);//将生成的整数转换成字符串并将其存放在二维数组part的相应位置上
				break;
		}
	}
	for(i = 0; i < 2 * term_length + 1; i++){/* 将二维数组中的各列拼接成项 */
		if(i) strcat(term," ");//在运算符前面加一个空格
		strcat(term,part[i]);
	}
	if (term_length) strcat(term,")");
	return term;
}
//我将不是项里面的运算符成为主干运算符
char *creat_operation(int max_num){//系统会把空格读成第一个元素//int argc,char *argv[]
	int formula_length, i, j;//formula_length指的是生成的运算式的长度，即运算的运算符数目
	int term_length[5];
	//term指的是运算式各部分被分配的运算符数目，
	//term_length[0]是运算式主干被分配的运算符数目，
	//term_length[1~4]是运算式第1到第4项被分配的运算符数目
	char *term;//term用来存放最终生成的运算式
	char part[7][100];
	//二维数组part用来存放生成的运算式的各个部分，
	//0、2、4、6列存放项，1、3、5列存放运算符
	term = (char *)malloc(100 * sizeof(char));//为term申请空间
	memset(term, 0x00, sizeof (char) * 100);//初始化term
	//库函数memset(<字符指针>,<命令(0x00是将字符数组置空)>,<长度>)是用来初始化字符数组的
	strcpy(term," ");//本来是用来初始化
	srand((unsigned)time(NULL));//生成随机数的种子
	formula_length = rand() % 3 + 1;
	for(i = 0; i < 7; i++){//初始二维数组part
		strcpy(part[i]," ");//起初写这个语句是因为输出的字符串出现了乱码
	}						//不过后来才清楚出现乱码是因为term没有初始化
	for(i = 0; i < 5; i++){//初始term_length，这一步是必要的
		term_length[i] = 0;
	}
	++term_length[0];//主干运算符必须要有一个
	//srand((unsigned)time(NULL));
	for(i = formula_length - 1; i ; i--){//随机分配运算符
		j = rand() % 5;
		++term_length[j];
	}
	//srand((unsigned)time(NULL));
	for(i = 0;i < term_length[0]; i++){ /* 为运算式生成运算符(主干运算符) */
		j = rand() % 4;
		switch(j){
			case 0: strcpy(part[2 * i + 1],"+"); break;
			case 1: strcpy(part[2 * i + 1],"-"); break;
			case 2: strcpy(part[2 * i + 1],"x"); break;
			case 3: strcpy(part[2 * i + 1],"/"); break;
		}
	}
	for(i = 0; i < term_length[0] + 1; i++){ /* 生成项 */
        Sleep(1000);//延迟一秒，不然输出的项是相同的
		strcpy(part[2 * i],creat_term(max_num,term_length[i + 1]));
	}
	for(i = 0; i < 2 * term_length[0] + 1; i++){ /* 拼接成运算式 */
		if(i) strcat(term," ");//运算符前后加上空格
		strcat(term,part[i]);
	}
	strcat(term," = ");//在运算式的最后加上'='
    return term;
}


float  calculate(float num1,float num2,int tepy){//简单的用于四则运算的函数
	switch (tepy) {
		case 1: return num1 + num2; break;
		case 2: return num1 - num2; break;
		case 3: return num1 * num2; break;
		case 4: return num1 / num2; break;
	}
}

float fraction(float num1,float num2,float num3){//计算非真分数的函数
	num2 = num2 / num3;
	return num1 + num2;
}

float creat_part_answer(LinkedList &List){//关键函数，已经验证过，可以使用。但是没有释放掉无用的动态空间，有可能会发生内存泄漏，未来需要改进这一点
    LinkedList temp1, temp2, temp3, PartList;
    creat_LinkedList(PartList);
    temp1 = List->next;//temp1用来检查节点
    temp1 = temp1->next;//初始化指向
    while(temp1 != List->next){
        if(temp1->sign == 6){//若找到（
            temp2 = temp1->next;//temp2寻找相应的temp1指向的（对应的）
            while(1){
                if(temp2->sign == 7 && temp1->tag - temp2->tag == 1) break;
                insert_LinkedList(PartList,temp2->num,temp2->sign,temp2->tag);//将成对的括号里的内容截取到另一个独立的单循环链表里
                temp2 = temp2->next;
            }
            temp1->num = creat_part_answer(PartList);//将括号里的计算结果放入（所在的节点
            temp1->sign = 0;//将temp1转化成存放数字的节点
            temp1->tag = 0;//
            if(List == temp2) List = temp1;//如果参与运算的内容有运算式末端的数字或运算符，则将List指向存放运算结果的节点
            temp1->next = temp2->next;//删除已经参与运算的内容
        }
        temp1 = temp1->next;
    }
    temp1 = List->next;
    temp2 = temp1;
    temp1 = temp1->next;
    while(temp1 != List->next){//寻找非真分数的标志'
        if(temp1->sign == 5){//以2'3/4为例，temp1指向的是’，temp2指向的是2
            temp1 = temp1->next;//将temp1的指向改为3
            temp3 = temp1->next->next;//temp3指向4
            temp2->num = fraction(temp2->num,temp1->num,temp3->num);//将运算结果存放在temp2指向的节点
            if(temp3 == List) List = temp2;
            temp2->next = temp3->next;//去除运算式中已经参与运算的部分
            temp1 = temp2->next;//调整temp1,为下一次循环做准备
            continue;
        }
        temp2 = temp1;
        temp1 = temp1->next;
    }
    temp1 = List->next;
    temp2 = temp1;
    temp1 = temp1->next;
    while(temp1 != List->next){
        if(temp1->sign == 3 || temp1->sign == 4){//检测到有运算符乘或除，temp1指向运算符，temp2指向被乘数或被除数
            temp3 = temp1->next;//temp3指向乘数或除数
            temp2->num = calculate(temp2->num,temp3->num,temp1->sign);//将运算结果存放在temp2指向的节点
            if(List == temp3) List = temp2;
            temp2->next = temp3->next;//去除运算式中已经参与运算的部分
            temp1 = temp2->next;//调整temp1,为下一次循环做准备
            continue;
        }
        temp2 = temp1;
        temp1 = temp1->next;
    }
    temp1 = List->next;
    temp2 = temp1;
    temp1 = temp1->next;
    while(temp1 != List->next){
        if(temp1->sign == 1 || temp1->sign == 2){//检测到有运算符加或减，temp1指向运算符，temp2指向被加数或被减数
            temp3 = temp1->next;//temp3指向加数或减数
            temp2->num = calculate(temp2->num,temp3->num,temp1->sign);
            if(List == temp3) List = temp2;
            temp2->next = temp3->next;//去除运算式中已经参与运算的部分
            temp1 = temp2->next;//调整temp1,为下一次循环做准备
            continue;
        }
        temp2 = temp1;
        temp1 = temp1->next;
    }
    return List->num;
}

float create_answer(char *operation){
	LinkedList List;//存放运算式的链表
	char *TempOperation;//存放运算式的字符串
	char TempPart[20];//存放被截取的一部分的运算式的字符串
	int flag;//控制是否将数字字符串转换成整型的开关
	int sign;//运算符的抽象代表
	int tag = 1;//括号的编号
	int IntNum;//转换成整型的字符串
	float FloatNum;//转换成浮点型的字符串
	int i, j;//你懂的
	TempOperation = (char *)malloc(100 * sizeof(char));
	memset(TempOperation, 0x00, sizeof (char) * 100);//初始化
	creat_LinkedList(List);//初始化链表
	strcpy(TempOperation,operation);//如果输入的字符串就是运算式
	for(i = 0; i < 20; i++){TempPart[i] = '\0';}
	i = 0;
	j = 0;
	flag = 0;
	while(TempOperation[i] != '\0'){//将运算式拆散并装入链表
		if(TempOperation[i] >= '0' &&TempOperation[i] <= '9'){//获取数字字符
			TempPart[j] = TempOperation[i];
			j++;
		}
		if(j > 0 && (TempOperation[i + 1] < '0' || TempOperation[i + 1] > '9')) {//获取字符完毕，将其转换换成字符串
			TempPart[j] = '\0';
			flag = 1;
		}
		if(flag == 1){//将获取的数字字符串转换成整型，进而转换成浮点型
			IntNum = atoi(TempPart);
			FloatNum = (float) IntNum;
			insert_LinkedList(List,FloatNum,0,0);
			//sign是运算符（0是数字，1是加，2是减，3是乘，4是除，5是'，6是（，7是））
			//tag是括号的编号
			flag = 0;
			j = 0;
		}
		//将运算符装入单循环链表
		if(TempOperation[i] == '+' || TempOperation[i] == '-' || TempOperation[i] == 'x' || TempOperation[i] == '/' || TempOperation[i] == 39 || TempOperation[i] == '(' || TempOperation[i] == ')'){
			switch (TempOperation[i]) {
				case '+':
					sign = 1;
					insert_LinkedList(List,0.0,sign,0);//装入加号
					break;
				case '-':
					sign = 2;
					insert_LinkedList(List,0.0,sign,0);//装入减号
					break;
				case 'x':
					sign = 3;
					insert_LinkedList(List,0.0,sign,0);//装入乘号
					break;
				case '/':
					sign = 4;
					insert_LinkedList(List,0.0,sign,0);//装入除号
					break;
				case 39:
					sign = 5;
					insert_LinkedList(List,0.0,sign,0);//装入字符 '
					break;
				case '(':
					sign = 6;
					tag++;//设置括号编号
					insert_LinkedList(List,0.0,sign,tag);//装入括号（，和对应编号
					break;
				case ')':
					sign = 7;
					tag--;//设置括号编号
					insert_LinkedList(List,0.0,sign,tag);//装入括号），和对应编号
					break;
			}
		}
		i++;
	}
	return creat_part_answer(List);
}

//将计算结果从小数（浮点型）转化成分数（字符串）
char* creat_char_answer(float answer, int max_num){//answer是输入的小数答案，max_num本来是控制参与运算的数的范围，如今用来控制分数精度
	char *char_answer;//存放最终结果的字符串
	char part_num[20];
	int IntAnswer;
	int num1, num2, i, j;
	float FloatAnswer;
	IntAnswer = (int) answer;//截取整数部分
	FloatAnswer = answer - (float)IntAnswer;//截取小数部分（有误差）
	char_answer = (char *)malloc(20 * sizeof(char));
	memset(char_answer, 0x00, sizeof (char) * 20);
	for(i = 0; i < 20; i++){//初始化存放一部分整数的字符数组
		part_num[i] = '\0';
	}
	if(FloatAnswer == 0.0 || (FloatAnswer == 0.0 && IntAnswer == 0)){//如果答案为零就输出0
		itoa(IntAnswer,char_answer,10);
		return char_answer; 
	}
	if(IntAnswer == 0){//如果答案为小于一的小数
		for(i = 1; i <= max_num; i++){
			num2 = i;
			for(j = 1; j <= max_num; j++){
				num1 = j;
				if(answer == (float)num1 / (float)num2){//重新计算，挑选出结算结果和答案一致的两个整数
					break;
				}
			}
			if(answer == (float)num1 / (float)num2){
				break;
			}
		}
		itoa(num1,char_answer,10);
		itoa(num2,part_num,10);
		strcat(char_answer,"/");
		strcat(char_answer,part_num);
	}
	if(IntAnswer != 0 && FloatAnswer != 0.0){//如果答案为大于一的小数
		itoa(IntAnswer,char_answer,10);
		strcat(char_answer,"'");
		for(i = 1; i <= max_num; i++){
			num2 = i;
			for(j = i; j <= max_num; j++){
				num1 = j;
				if(answer == (float)num1 / (float)num2){//重新计算，挑选出结算结果和答案一致的两个整数
					break;
				}
			}
			if(answer == (float)num1 / (float)num2){
				break;
			}
		}
		/*num1 = num1 / common_divisor(num1,num2);//化简
		num2 = num2 / common_divisor(num1,num2);*/
		if(answer == (float)num1 / (float)num2){
			num1 = num1 - num2 * IntAnswer;
		}
		
		itoa(num1,part_num,10);
		strcat(char_answer,part_num);
		strcat(char_answer,"/");
		itoa(num2,part_num,10);
		strcat(char_answer,part_num);
	}
	if(num1 == num2){//如果转换失败则返回ERROR字符串
		strcpy(char_answer,"ERROR");
		return char_answer;
	}
	return char_answer;
}

int main(int argc,char *argv[]){//主函数
	int i, number = 10000;//number用来控制生成题目的数量，默认是10000
	int Max = 0; //Max用来控制生成参与运算的数字的最大值
	int flag = 0;//flag用来检测是否有输入参与运算的数的最大值
	char *term;//term用来存放完成初次处理的字符串
	char times[100];//times用来存放完成最终处理的字符串
	for(i = 0; i < argc; i++){//检测输入的指令
		if(strcmp(argv[i],"-n") == 0){//检测到有输入指令 -n
			number = atoi(argv[++i]);//将生成题目的数量改成输入的数
		}
		if(strcmp(argv[i],"-r") == 0){//检测到有输入指令 -r
			Max = atoi(argv[++i]);//将Max设置为输入的数
			flag = 1;//设置已经输入Max的标志
		}
	}
	if(flag == 0){//如果没有输入Max的指令
		printf("input the max number\n");//提示
		return -1;//结束运行
	}
	FILE *fpWrite1 = fopen("Exercises.txt","w");//创建存放运算的文件
	FILE *fpWrite2 = fopen("Answers.txt","w");//创建存放计算结果的文件
	if(fpWrite1 == NULL || fpWrite1 == NULL){//创建失败，则提示异常并结束程序的运行
		printf("fail to open file\n");
		return -1;
	}
	for(i = 0; i < 100; i++){//初始化存放最终结果的字符数组
		times[i] = '\0';
	}
	term = (char *)malloc(100 * sizeof(char));//申请动态空间
	memset(term, 0x00, sizeof (char) * 100);//初始化存放完成初步处理的字符串的字符指针
	for(i = 0; i < number; i++){//开始生成运算式
		do{
			strcpy(term,creat_operation(Max));//将生成的运算式复制到term
		}while(create_answer(term) < 0 || strcmp(creat_char_answer(create_answer(term),1000),"ERROR") == 0);//如果生成的运算式不符合要求则重新生成
		itoa(i+1,times,10);//将运算式序号转化成字符串
		strcat(times," :");
		strcat(times,term);//将序号和运算式连接起来
		strcat(times,"\n");
		puts(times);//输出运算式
		fputs(times, fpWrite1);//将完成最终处理的运算式存入指定文件中
		itoa(i+1,times,10);//将答案序号转化成字符串
		strcat(times," :");
		strcat(times,creat_char_answer(create_answer(term),1000));//将序号和答案连接起来
		strcat(times,"\n");
		puts(times);//输出答案
		fputs(times, fpWrite2);//将完成最终处理的答案存入指定文件中
	}
	fclose(fpWrite1);//关闭存放运算式的文件
	fclose(fpWrite2);//关闭存放答案的文件
	return 0;
}
