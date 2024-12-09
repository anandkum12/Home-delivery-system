#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<stdlib.h>
#define name "bays29.txt"
#define maxit0 100
#define maxit 1000
#define nn 29
#define ns 40
#define maxit1 2000
#define maxit3 100
#define fclim 200
#define pc 0.8
#define pm 0.6
#define name1 "writebays29.txt"
//minimum cost 42029
typedef struct 
	{
		int n; 
		int ss[10000][2];
	}swapsequence;
typedef struct 
	{
		int x[nn];
		float cost;
		int fc;
		//int fc1;
		float fitness;
		float prob;
		float commu_prob;
	}path;
	path p[ns],best,p1[ns];
	float ran(float a, float b);
	void read_data();
	void initialize();
	void create_path(int i);
	float cost(int x[nn]);
	void result();
	swapsequence path_diff(path p1,path p2);
	swapsequence mul(float a,swapsequence d1);
	path swap(path p, swapsequence ss);
	float c[nn][nn];
	int a[nn],a1[nn],b[nn],c1[nn],lo[4],mr[nn],d[nn],ra[nn],rb[nn],rc[nn],rd[nn];
	void stagnant();
	path opt_3( path k1);
	void mer(int[],int ,int[],int,int[],int,int[],int);
	void EmployedBees();
	void OnlookerBee();
	void ScoutBee();
	void ABC();	
	void selection();
	void crossover();
	void mutation();
	void GA();
	void write_data(path,int);
int main()
	{
		int i,j,seed,count,a;
		path pp;
		printf("\n Enter seed:");
		scanf("%d",&seed);
		srand(seed);
		read_data();
		initialize();
		result();
		for(i=0;i<maxit0;i++)
			{
				GA();
				if(i%10==0)
					{
						best=opt_3(best);
						printf("\n GA Iteration %d with the value of a %d  ",i,a);
						result();
					}
			}
		result();
		write_data(best,seed);
	}

	void GA()
		{
			selection();
			crossover();
			mutation();
		}
	void read_data()
		{
			int i,j;		
			FILE *fptr;
			fptr=fopen(name,"r");
			for(i=0;i<nn;i++)
				for(j=0;j<nn;j++)
					fscanf(fptr,"%f",&c[i][j]);
			fclose(fptr);
		}
	void initialize()
		{
			int i,p1,p2,t;
			for(i=0;i<ns;i++)
				{
					create_path(i);
					p[i].cost=cost(p[i].x);	
				}
			best=p[0];
			for(i=1;i<ns;i++)
				if(p[i].cost<best.cost)
					best=p[i];
		}
	void create_path(int k)
		{
			int i,m=0,n=nn,x[nn],pos;
			float min;
			for(i=0;i<nn;i++)
				x[i]=i;
			pos=rand()%nn;
			p[k].fc=0;
			p[k].x[m]=pos;
	step1:  n--;
			for(i=pos;i<n;i++)
				x[i]=x[i+1];
			pos=0;
			min=c[p[k].x[m]][x[0]];
			for(i=1;i<n;i++)
				{
					if(c[p[k].x[m]][x[i]]<min)
						{
							min=c[p[k].x[m]][x[i]];
							pos=i;
						}
				}
			p[k].x[++m]=x[pos];
			if(m<nn-1)
				goto step1;
			p[k].cost=cost(p[k].x);
		}

	float cost(int x[nn])
		{
			int i;
			float val=0;
			for(i=0;i<nn-1;i++)
				val+=c[x[i]][x[i+1]];
			val+=c[x[nn-1]][x[0]];
			return val;
		}
	void result()
		{
			int i,j;
			/*printf("Final solution set is presented below:\n");
			for(i=0;i<ns;i++)
				{
					for(j=0;j<nn;j++)
						printf(" %d ",p[i].x[j]);
					printf(" cost=%4.2f\n",p[i].cost);
				}
			printf("\nBest path found:\n");
			for(j=0;j<nn;j++)
				printf(" %d ",best.x[j]);*/
			printf(" cost=%4.2f\n",best.cost);
		}




	float ran(float a, float b)
		{
			return a+(b-a)*(rand()%10000)/10000.;
		}



	path opt_3( path k1)
  		{
			path t1,t2,t3,t4, l_best;
		    l_best=t1=k1;
			int i,j=0,l1,l2,l3,l,seed,p0,p1,p2,p3,r1,r2,r3,tem,arr[nn],h,k,u,v;
		    for(i=0;i<nn;i++)
		       a1[i]=k1.x[i];
		    for( h=0;h<maxit;h++)
		       {
		       		t4=t1;
			   		lo[0]=r1=rand()%nn;
		       		lo[1]=r2=rand()%nn;
		       		lo[2]=r3=rand()%nn;
		        for(i=0;i<2;i++)
		            for(j=0;j<2;j++)
		             	{   
			         		if(lo[j]>lo[j+1])
		      	       			{
		      	  	    			tem=lo[j+1];
		      	  	    			lo[j+1]=lo[j];
		      	  	    			lo[j]=tem;	
					  			}
		            	}
			       l1=lo[0];
			       l2=lo[1];
			       l3=lo[2];
			       p0=0;
			       for(i=0;i<l1;i++)
			          a[p0++]=a1[i];
			       p1=0;
			       for(i=l1;i<l2;i++)
			          b[p1++]=a1[i];
			       p2=0;
			       for(i=l2;i<l3;i++)
			          c1[p2++]=a1[i];
			       p3=0;
			       for(i=l3;i<nn;i++)
			          d[p3++]=a1[i];
			       j=0;
			       for(i=p0-1;i>=0;i--)
				      ra[j++]=a[i];
			       k=0;
			 	   for(i=p1-1;i>=0;i--)
			 	      rb[k++]=b[i];
			       u=0;
			 	   for(i=p2-1;i>=0;i--)
			 	       rc[u++]=c1[i];
			       v=0;
			 	   for(i=p3-1;i>=0;i--)
			          rd[v++]=d[i];
		       
				   mer(a,p0,rb,p1,c1,p2,d,p3);
			       for(i=0; i<nn;i++)
			           t3.x[i]=mr[i];
			        t3.cost=cost(t3.x);
			       if(t1.cost>t3.cost)
			          t1=t3;
			           
			       mer(a,p0,b,p1,rc,p2,d,p3);     
			       for(i=0; i<nn;i++)
			           t3.x[i]=mr[i];
			           t3.cost=cost(t3.x);
			       if(t1.cost>t3.cost)
			          t1=t3;
			          
			       mer(a,p0,rc,p2,rb,p1,d,p3);
			       for(i=0; i<nn;i++)
			           t3.x[i]=mr[i];
			           t3.cost=cost(t3.x);
			       if(t1.cost>t3.cost)
			          t1=t3; 
			       mer(a,p0,c1,p2,rb,p1,d,p3);
			       for(i=0; i<nn;i++)
			           t3.x[i]=mr[i];
			           t3.cost=cost(t3.x);
			       if(t1.cost>t3.cost)
			          t1=t3; 
			       mer(a,p0,rc,p2,b,p1,d,p3);
			       for(i=0; i<nn;i++)
			           t3.x[i]=mr[i];
			           t3.cost=cost(t3.x);
			       if(t1.cost>t3.cost)
			          t1=t3;
			       mer(a,p0,rb,p1,rc,p2,d,p3);
			       for(i=0; i<nn;i++)
			           t3.x[i]=mr[i];
			           t3.cost=cost(t3.x);
			       if(t1.cost>t3.cost)
			          t1=t3;
			       mer(a,p0,rc,p2,b,p1,d,p3);
			       for(i=0; i<nn;i++)
			           t3.x[i]=mr[i];
			           t3.cost=cost(t3.x);
			       if(t1.cost>t3.cost)
			          t1=t3;
			       if(t4.cost>t1.cost)
			        {
			          break;
					}
			  }
			return t1;
		}
	void mer(int p1[],int l1, int p2[],int l2,int p3[],int l3,int p4[],int l4)
		{
			int i,j;
			for(i=0;i<l1;i++)
			    mr[i]=p1[i];
			j=0;
			for(i=l1;i<l2+l1;i++)
			    mr[i]=p2[j++];
			int k=0;
			for(i=l2+l1;i<l1+l2+l3;i++)
			    mr[i]=p3[k++];
			int l=0;
			for(i=l2+l1+l3;i<nn;i++)
			    mr[i]=p4[l++]; 
		}
	void selection()
		{
			int i,j,z=0;
			float sum=0,r1;
	//calculate fitness
			for(i=0;i<ns;i++)
				{
					p[i].fitness=1;	
					for(j=0;j<ns;j++)
							{
								if(p[i].cost<p[j].cost)
									p[i].fitness++;
							}
					sum=sum+p[i].fitness;	
				}
//calculate probablity
			for(i=0;i<ns;i++)
				p[i].prob=p[i].fitness/sum;
				
//calculate commulative probablity
			p[0].commu_prob=p[0].prob;
			for(i=1;i<ns;i++)
				p[i].commu_prob=p[i-1].commu_prob+p[i].prob;		
				
			for(j=0;j<ns;j++)
				{
					r1=ran(0,1);
					for(i=0;i<ns-1;i++)
		   	        	{	
		   	        		if(r1<p[0].commu_prob)
								{
									p1[j]=p[0];
									break;
								}
							else if(r1>p[i].commu_prob && r1<=p[i+1].commu_prob)
								{
									p1[j]=p[i+1];
									break;
								}
				    	}
				}
			/*for(i=0;i<ns;i++)
				p[i]=p1[i];*/
		}

	void crossover()
		{
			int f,k,w=0,w1,u,c[nn],pos,i,j,pp,flag=0,z,m,n,l,l1;
			path tem3,p3[3*ns],q[ns],p_ch[ns],p_ch1[ns];
			for(i=0;i<ns;i++)
				q[i]=p1[i];
			l=ns;
			for(i=0;i<ns;i++)
				{
					if(ran(0,1)<pc)
						{
							for(j=0;j<ns;j++)
								if(j>i)
									{
										if(ran(0,1)<pc)
											{	
												flag++;
												int p=rand()%3+1;
												for(int b=0;b<p;b++)
													{
														pos=rand()%nn;
														pp=pos;
														k=0;
														c[k]=pp;
														while(p1[i].x[pos]!=q[j].x[pos] && q[j].x[pos]!=p1[i].x[pp])
															{		
													     		for(z=0;z<nn;z++)
																   	{
																		if(q[j].x[pos]==p1[i].x[z])
																	        {
																	        	k++;
																				pos=z;
																				c[k]=z;
																				break;
																		    }
																		
																	}
															}
														for(m=0;m<nn;m++)
															{
																f=0;
																for(n=0;n<=k;n++)
																	{
																		if(m==c[n])
																			{
																				f=1;
																				break;
																			}
																	}
																if(f==0)
																	{
																		p_ch[w].x[m]=q[j].x[m];
																		p_ch1[w].x[m]=p1[i].x[m];
																		
																	}
																else
																	{
																		p_ch[w].x[m]=p1[i].x[m];
																		p_ch1[w].x[m]=q[j].x[m];
																	}
															}
														for(int h=0;h<nn;h++)
															{
																p1[i].x[h]=p_ch[w].x[h];
																q[j].x[h]=p_ch1[w].x[h];
															}
													}
										
												p_ch[w].cost=cost(p_ch[w].x);
												p_ch1[w].cost=cost(p_ch1[w].x);		
												w++;				
												break;
											}				
									}
								if(i==ns-1)
									{
										int p=rand()%3+1;
										for(int b=0;b<p;b++)
											{
												pos=rand()%nn;
												pp=pos;
												k=0;
												c[k]=pp;
												while(best.x[pos]!=q[i].x[pos] && q[i].x[pos]!=best.x[pp])
												   {
														for( int e=0;e<nn;e++)
												        	{
																if(q[i].x[pos]==best.x[e])
																	{
																		k++;
																		pos=e;
																		c[k]=e;
																		break;
														            }						
													        }
													}
												for(m=0;m<nn;m++)
													{
														f=0;
														for(n=0;n<=k;n++)
															{
																if(m==c[n])
																	{
																		f=1;
																		break;
																	}
															}
														if(f==0)
															{
																p_ch[w].x[m]=best.x[m];
																p_ch1[w].x[m]=q[i].x[m];
															}
														else
															{
																p_ch[w].x[m]=q[i].x[m];
																p_ch1[w].x[m]=best.x[m];
															}
													}
												for(int h=0;h<nn;h++)
													{
														best.x[h]=p_ch[w].x[h];
														q[i].x[h]=p_ch1[w].x[h];
													}
											}
										flag++;
										p_ch[w].cost=cost(p_ch[w].x);
										p_ch1[w].cost=cost(p_ch1[w].x);
										w++;
									}
							}
				}
	//merged parents and new child
			for (i=0;i<ns;i++)
				p3[i] = p[i];
			for (i=0,j=ns;j<ns+flag && i<ns;i++,j++)
				p3[j]=p_ch1[i];	
			for (i=0,j=ns+flag;j<2*flag+ns && i<ns;i++,j++)
				p3[j]=p_ch[i];
	//Assending elements	
			for (i = 0; i <2*flag+ns; ++i)
			  	{
				    for (j=i+1;j<2*flag+ns;++j)
					  	{
						    if (p3[i].cost> p3[j].cost)
								{
							        tem3= p3[i];
							        p3[i] =p3[j];
								    p3[j] =tem3;
						        }
					    }
				}
	//delete same elements	
			l1=2*flag+ns;
			for(i=0; i<2*flag+ns; i++)
	   	 		{
	        		for(j=i+1;j<l1;j++)
	      				{
	            			if(p3[i].cost==p3[j].cost)
	            				{
	                				for(k=j;k<l1-1;k++)
	               					 	{
	                  		 				p3[k]=p3[k+1];
	               						 }
	               					l1--;
	               					j--;
	            				}
	      				}
	    		}
	    	//	printf(" l value is =%d\n",l1);	
			if(l1<ns)
				{
				//	printf(" l value is =%d\n",l1);	
				//	printf("\nhellllllo\n\n\n");
				//	getch();
					for(i=0;i<ns-l1;i++)
						{
							create_path(l1+i);
							p3[l1+i].cost=cost(p[l1+i].x);
						}
					/*for(u=0;u<ns;u++)
						p[u]=p3[u];	
					result();
					getch();*/
				}
//take best1111111 path  
  			/*printf("\nafter crossover Final11111111111111 solution set is presented below:\n");
			for(i=0;i<ns;i++)
				{
					for(j=0;j<nn;j++)
						printf(" %d ",p3[i].x[j]);
					printf(" cost=%4.2f\n",p3[i].cost);
				}
			printf("\nBest path found:\n");
			for(j=0;j<nn;j++)
				printf(" %d ",best.x[j]);
			printf(" cost=%4.2f\n",best.cost);*/
			for(u=0;u<ns;u++)
				{
				//	if(p[u].cost>p3[u].cost)
						p[u]=p3[u];
				}
			//	p[u]=p3[u];	
		//	result();
			//	getch();
		}

	void mutation()
		{
			path tem1;
			int i,j;
			for(i=0;i<ns;i++)
				{
					if(ran(0,1)<pm)
						{
							tem1=p[i];
							tem1=opt_3(tem1);
							if(tem1.cost<p[i].cost)
								p[i]=tem1;	
						}
					if(best.cost>p[i].cost)
						best=p[i];		
				}	
		}
	void write_data(path best,int seed)
		{
			int i,j;		
			FILE *fptr;
			fptr=fopen(name1,"a");
			if ( fptr == NULL )
	           	{
				   puts ("Cannot open source file");
	             	exit(0);
				}
			fprintf(fptr,"\n in seed %d\n",seed);
			fprintf(fptr," best cost is \t %lf\n",best.cost);
			fprintf(fptr," best PATH is \n");
			for(i=0;i<nn;i++)
				fprintf(fptr,"%d\t",best.x[i]);
			fclose(fptr);
		}
