#include<iostream>
#include<math.h>
#include <fstream>
using namespace std;
struct p{
    double re;
    double im;
};
p operator +(p a,p b){
	p c;
	c.re=a.re+b.re;
	c.im=a.im+b.im;
	return c;
};
p operator -(p a,p b){
	p c;
	c.re=a.re-b.re;
	c.im=a.im-b.im;
	return c;
};
p operator *(p a,p b){
	p c;
	c.re=a.re*b.re-a.im*b.im;
    c.im=a.re*b.im+a.im*b.re;
    return c;
};
p operator/(p b,p a){
	p c;
    c.re=(a.re*b.re+a.im*b.im)/(pow(a.re,2)+pow(a.im,2));
    c.im=(a.re*b.im-a.im*b.re)/(pow(a.re,2)+pow(a.im,2));
    return c;
}
bool doi_xung(p a[15][15],int n)	
{
 	for(int i=0;i<n;i++)
 		for(int j=0;j<n;j++)
 			if(a[i][j].re != a[j][i].re)
 			return 0;
			return 1;
}
void tam_giac( p a[15][15],p b[15][15],int n)	
{ 
	int i,j,k;
	b[0][0].re = sqrt(a[0][0].re);
	for(i=1;i<n;i++)
	b[0][i].re = a[0][i].re / b[0][0].re;
	for(i=1;i<n;i++)
	{
		p z;
		z.re = 0;
		z.im = 0;
		for(k=0;k<i;k++)
		{
			z = z + b[k][i] * b[k][i];
		}
		if((a[i][i].re - z.re) < 0)	 
		b[i][i].im = sqrt(z.re - a[i][i].re);
		else b[i][i].re = sqrt(a[i][i].re - z.re);
		if (b[i][i].im == 0 && b[i][i].re == 0)
		{
			cout<<"Ma tran khong kha nghich\n\n";
			break;
		}
		for( j=i+1;j<n;j++)
		{
			p z;
			z.re = 0;
			z.im = 0;
			for( k=0;k<i;k++)
			{
				z = z + b[k][i] * b[k][j];
			}
				b[i][j] = (a[i][j] - z) / b[i][i];
		}
    }
	}
void nghich_dao(p b[15][15],p b1[15][15],int n )
{
   int i,j,k;
 	for(i=0;i<n;i++)
 	{
		p x;
		x.re = 1;
		b1[i][i] = x/b[i][i];
	}
 	    for(j=1; j<n; j++)
		for(i=0; i<j; i++)
 	 	{   
			p x;
			x.re = -1;
		    p z;
				z.im = 0;
				z.re = 0;
 	 		for(k = 0; k<j; k++)
 	 		{
				z = z + b1[i][k] * b[k][j];
 	 		}	
 	   		b1[i][j] = x * (z/b[j][j]);
		}
}
void chuyen_vi(p b1[15][15], p bt[15][15],int n)
{
	int i,j,k;
	for(i = 0; i<n; i++)
		for(j=0; j<n; j++)
			bt[i][j] = b1[j][i];
}
void nhan_ma_tran(p b1[15][15], p bt[15][15], p c[15][15],int n)
{    
	int i,j,k,h;
	for(h=0; h<n; h++)
	{
		for(k=0; k<n; k++)
    	{ 
			c[h][k].im = 0;
			c[h][k].re = 0;
			for(i=0; i<n; i++)
   			{
				c[h][k] = b1[h][i] * bt[i][k] + c[h][k];
			}
		}
	}
}
void in_ma_tran(p c[15][15], int n)
{
	for(int i=0; i<n; i++)
 	{	
		{
			for(int j=0; j<n ;j++)
			cout <<  c[i][j].re<<" \t";
		}
 	cout<<endl;
 	}
}
void in_ma_tran_so_phuc(p c[15][15],int n)
{
	for(int i=0; i<n; i++)
 	{	
		{
			for(int j=0; j<n ;j++)
			cout <<c[i][j].re<<"+"<<c[i][j].im<<"i\t";
		}
 	cout<<endl;
 	}
}
void read(int &n,p a[15][15])
{   
	ifstream  f("C:/Users/DELL 5584/Desktop/input.txt" );
	f>> n;
	for(int i=0; i<n; i++)
	{
		for(int j = 0; j<n; j++)
		f>>a[i][j].re;
    }
	f.close();		 
}	
void nhan2(int n, double a[15][15], double b[15][15], double c[15][15])
{
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			c[i][j] = 0;
			for(int k=0; k<n; k++)
			{
				c[i][j] += a[i][k]*b[k][j];
			}
		}
	}
}
int main()
{
    p a[15][15];
    int n;
    read(n,a);
	if(doi_xung(a,n))
	{
		p b[15][15],b1[15][15],bt[15][15],a1[15][15];
	    tam_giac(a, b, n);
	    nghich_dao(b, b1, n);
	    chuyen_vi(b1, bt, n);
	    nhan_ma_tran(b1, bt, a1, n);
		cout<<" Ma tran tam giac tren la\n"<<endl;
		in_ma_tran_so_phuc(b, n);
	    cout<<"\n Ma tran nghich dao la\n"<<endl;
	    in_ma_tran(a1, n);
	}
    else 
	{ 
		p at[15][15],b[15][15],b2[15][15],b3[15][15],bt[15][15],b1[15][15],a1[15][15];
	    chuyen_vi(a, at, n);
	    nhan_ma_tran(at, a, b, n);
	    tam_giac(b, b2 ,n);
	    nghich_dao(b2, b3, n);
	    chuyen_vi(b3, bt, n);
	    nhan_ma_tran(b3, bt, b1, n);
	    nhan_ma_tran(b1, at, a1, n);
		cout<<" Ma tran tam giac tren la\n"<<endl;
		in_ma_tran_so_phuc(b2, n);
	    cout<<"\n Ma tran nghich dao la\n"<<endl;
	    in_ma_tran(a1, n);
	}
}
