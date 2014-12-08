#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node{
	int a,b,depth;
	char *code;
	struct node *left,*right,*next;
	};
struct node *memstate(struct node *root,int sa,int sb,int depth,char *code)
{
	if(root==NULL){
		root=malloc(sizeof(struct node));
		root->a=sa;
		root->b=sb;
		root->depth=depth;
		root->code=malloc(sizeof(char));
		strcpy(root->code,code);
		root->left=root->right=root->next=NULL;
	}
	else if(root->a==sa&&root->b==sb){
		if(root->depth>depth){
			root->depth=depth;
			strcpy(root->code,code);
		}
	}
	else 
		root->next=memstate(root->next,sa,sb,depth,code);
	return root;
}
int find(struct node *r,int a,int b,int depth)
{
	while(r!=NULL){
		if(a==r->a&&b==r->b&&r->depth<=depth)
			return 1;
		r=r->next;
	}
	return 0;
}
struct node* tree(struct node *r,struct node *mem,int wa,int wb,int want,int sa,int sb,int depth,char *code,char *lr)
{
	r->a=sa;
	r->b=sb;
	r->depth=depth;
	depth++;
//	printf("%d\t%d\t%d\n",r->a,r->b,r->depth);
	r->code=malloc(sizeof(struct node));
	strcpy(r->code,code);
	strcat(r->code,lr);
	int pa=r->a,pb=r->b;
	int seta=0;
	if(seta==0&&pa>0&&pb<wb){
		while(pa>0&&pb<wb){
			pa--;
			pb++;
		}
		if(find(mem,pa,pb,depth)==0)
		seta=1;
		else pa=r->a,pb=r->b;
	}
	if(seta==0&&pb>0&&pa<wa){
                while(pb>0&&pa<wa){
                        pb--;
                        pa++;
                }
		if(find(mem,pa,pb,depth)==0)
                seta=1;
		else pa=r->a,pb=r->b;
        }
	if(seta==0&&pb==0){
		pb=wb;
		if(find(mem,pa,pb,depth)==0)
		seta=1;
		else pa=r->a,pb=r->b;
	}
	if(seta==0&&pb==wb){
		pb=0;
		if(find(mem,pa,pb,depth)==0)
		seta=1;
		else pa=r->a,pb=r->b;
	}
	if(seta==1){
		mem=memstate(mem,pa,pb,depth,r->code);
		r->right=malloc(sizeof(struct node));
//		if(want==r->a)
//		printf("l  %d\t%d\t%d\t%d\n",r->a,r->b,pa,pb);
		tree(r->right,mem,wa,wb,want,pa,pb,depth,r->code,"1");
	}
	pa=sa;pb=sb;seta=0;
	if(seta==0&&pb>0&&pa<wa){
                while(pb>0&&pa<wa){
                        pb--;
                        pa++;
                }
                if(find(mem,pa,pb,depth)==0)
                seta=1;
                else pa=r->a,pb=r->b;
        }
	if(seta==0&&pa>0&&pb<wb){
                while(pa>0&&pb<wb){
                        pa--;
                        pb++;
                }
                if(find(mem,pa,pb,depth)==0)
                seta=1;
                else pa=r->a,pb=r->b;
        }
        if(seta==0&&pa==0){
                pa=wa;
                if(find(mem,pa,pb,depth)==0)
                seta=1;
                else pa=r->a,pb=r->b;
        }
        if(seta==0&&pa==wa){
                pa=0;
                if(find(mem,pa,pb,depth)==0)
                seta=1;
                else pa=r->a,pb=r->b;
        }
        if(seta==1){
                mem=memstate(mem,pa,pb,depth,r->code);
		r->left=malloc(sizeof(struct node));
//		if(want==r->a)
//		printf("r  %d\t%d\t%d\t%d\n",r->a,r->b,pa,pb);
                tree(r->left,mem,wa,wb,want,pa,pb,depth,r->code,"0");
	}
}
int print(struct node *r,int want,int i)
{
	int s=0;
	if(r!=NULL){
	if((r->a==want||r->b==want)&&r->depth==i){
		printf("%d\t%d\t%d\n",r->a,r->b,i);
		return 1;}
	if(s==0) s=print(r->right,want,i);
	if(s==0) s=print(r->left,want,i);
	if(s==1) printf("%d\t%d\n",r->a,r->b);
	if(s==1) return 1;
	else return 0;}
	return 0;
}
void pp(struct node *r){
	if(r!=NULL){
		printf("%d\t%d\t%d\t%s\n",r->a,r->b,r->depth,r->code);
		pp(r->next);
	}
}
int findd(struct node *m,int w)
{
	int pos;
	while(m!=NULL){
		if(m->a==w||m->b==w)
			return m->depth;
		m=m->next;
	}
	return -1;
}		
main()
{
	int wa=7,wb=11,want=6;
	struct node *root=malloc(sizeof(struct node));
	struct node *mem=NULL;
	mem=memstate(mem,0,0,0,"0");
	tree(root,mem,wa,wb,want,0,0,0,"0","");
	InsertSort(&mem);
	print(root,want,findd(mem,want));
//	pp(mem);	
}
