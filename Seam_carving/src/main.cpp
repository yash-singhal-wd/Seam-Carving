#include <iostream>
#include <fstream>
#include<math.h>


using namespace std;

void gradient(double **grad,int ***rgb, int H, int W, int C)
{
  

   for(int i=0;i<H;i++)
    {
         for(int j=0;j<W;j++)
         {
            int x_grad=0,y_grad=0;
              for(int k=0;k<C;k++)
              {
               int x_=0,y_=0;
               if(j-1<0)
                 x_=rgb[i][W-1][k]-rgb[i][j+1][k];
               else if (j+1>=W)
                 x_=rgb[i][0][k]-rgb[i][j-1][k];
               else
                 x_=rgb[i][j-1][k]-rgb[i][j+1][k];

              if(i-1<0)
                 y_=rgb[H-1][j][k]-rgb[i+1][j][k];
                else if (i+1>=H)
                 y_=rgb[0][j][k]-rgb[i-1][j][k];
                else
                 y_=rgb[i-1][j][k]-rgb[i+1][j][k];

               x_grad+= x_*x_;
               y_grad+= y_*y_;
               }
                grad[i][j]=sqrt(x_grad+y_grad);
            
         }
     
        }
}

int minleft(int a,int b,int &min)
{   
    if(a<b)
    {
        min=a;
        return 0;
    }
    else
    {
        min=b;
        return 1;
    }
}

int minright(int a,int b,int &min)
{   
    if(a<b)
    {
        min=a;
        return -1;
    }
    else
    {
        min=b;
        return 0;
    }
}

int minIdx(int a, int b, int c,int &min)
{   int idx=-1;
     min = a;

    if (b < min){
        min = b;
        idx = 0;}

    if (c < min){
        min = c;
        idx = 1;}
    return idx;
}


void shiftrgb(int ***rgb, int H, int W, int C,int r,int c)
{   
    
    for(int j = (c+1); j < W; j++)
        {
            for(int k = 0; k < C; k++)
            {  
              int temp = rgb[r][j-1][k];
              rgb[r][j-1][k] =  rgb[r][j][k];
              rgb[r][j][k] = temp;
            } 

        }
    
}

void shiftrgbv(int ***rgb, int H, int W, int C,int r,int c)
{   
    
    for(int j = (r+1); j < H; j++)
        {
            for(int k = 0; k < C; k++)
            {  
              int temp = rgb[j-1][c][k];
              rgb[j-1][c][k] =  rgb[j][r][k];
              rgb[j][r][k] = temp;
            } 

        }
    
}

// void costcalv(double **cost,double **grad,double **bt, int H, int W, int C)
// {
//     for(int j=0;j<H;j++)
//     {
//         for(int i=0;i<W;i++)
//         {
//             if(j == 0)
//                 cost[j][i] = grad[i][j];

//             else if(j==1)
//                 {
//                     if(i==0)
//                         {
//                             int min;
//                             int idx = 
//                         }









//                 }

//         }
//     }

// }


void costcal(double **cost,double **grad,double **bt, int H, int W, int C)
{
     for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){
            if(i==0)
            {
                cost[i][j] = grad [i][j];
                bt[i][j] = 0;
            }

            else if( i==1 )
            {  
                if(j==0)
                    {
                     int min;
                     int idx = minleft(grad[i-1][j],grad[i-1][j+1],min);
                     cost[i][j] = grad[i][j] + min;
                     bt[i][j] = j + idx;
                    }
                else if(j == W-1)
                    {
                     int min;
                     int idx = minright(grad[i-1][j-1],grad[i-1][j],min);
                     cost[i][j] = grad[i][j] + min;
                     bt[i][j] = j + idx;
                    }
                else
                    {
                     int min;
                     int idx = minIdx(grad[i-1][j-1],grad[i-1][j],grad[i-1][j+1],min);
                     cost[i][j] = grad[i][j] + min;
                     bt[i][j] = j + idx;
                    }        
                
            }

            else 
            {   
                 if(j==0)
                    {
                     int min;
                     int idx = minleft(cost[i-1][j],cost[i-1][j+1],min);
                     cost[i][j] = grad[i][j] + min;
                     bt[i][j] = j + idx;
                    }
                else if(j == W-1)
                    {
                     int min;
                     int idx = minright(cost[i-1][j-1],cost[i-1][j],min);
                     cost[i][j] = grad[i][j] + min;
                     bt[i][j] = j + idx;
                    }
                else
                    {
                     int min;
                     int idx = minIdx(cost[i-1][j-1],cost[i-1][j],cost[i-1][j+1],min);
                     cost[i][j] = grad[i][j] + min;
                     bt[i][j] = j + idx;
                    }   


            }
        }
    }
}


void rotate90(int ***rgb,int ***temp,int H,int W,int C)
{
    for(int i=0;i<H;i++)
    {
        for(int j=0;j<W;j++)
        {
            for(int k=0;k<C;k++)
            {
                temp[j][H-1-i][k] = rgb[i][j][k];
            }
        }
    }
}

void rotateanti90(int ***rgb,int ***temp,int H,int W,int C)
{

    for( int i =0; i<W; i++)
        {
            for(int j=0;j<H;j++)
            {
                for(int k=0;k<C;k++)
                {
                    rgb[i][j][k] = temp[j][W-1-i][k];
                }
            }
        }
}


void solve(int ***rgb, int H, int W, int C, int H_, int W_, int C_) 
{
    
    
           { int l=0;
            for(int k =W_;k<W;k++)
            {  

            double **grad,**cost,**bt;
            grad = new double*[H];
            cost = new double*[H];
            bt = new double*[H];

            for (int i = 0; i < H; i++) {
                grad[i] = new double[W -l];
                cost[i] = new double[W -l];
                bt[i] =   new double[W -l];
            }
    
                
            gradient(grad,rgb, H, W - l, C);
            costcal(cost,grad,bt,H,W - l,C);

            int m = cost[H-1][0];
            int i_idx = H-1;
            int j_idx = 0;

            for(int j = 0;j < (W - l); j++)
            {
              if( cost[H-1][j] < m )
                {
                    m = cost[H-1][j];
                    i_idx = H-1;
                    j_idx = j;
                } 
            
            }
          shiftrgb(rgb,H,W - l,C,i_idx,j_idx);
                
               

                for(int i = H - 1;i > 0;i--) 
                { 
                  
                  j_idx = bt[i][j_idx];
                  shiftrgb(rgb,H,W - l,C,i-1,j_idx);   
                
                }
                l++;
            for(int i = 0;i < H;i++)
            {
                delete [] grad[i];
                delete [] cost[i];
                delete [] bt[i];
            }
            delete [] grad;
            delete [] cost;
            delete [] bt;
            

            }
            
            
            
            
            
            
            
            }


        
          int ***temp;
            temp = new int**[W_];
            for (int i = 0; i < W_; i++) {
                temp[i] = new int*[H];
                for (int j = 0; j < H; j++) {
                    temp[i][j] = new int[C];
                }
            }
   
            

            rotate90(rgb,temp,H,W_,C);

            int r_H = W_;
            int r_W = H;
            int a_W = W;
            int a_H = H;
           
            H = r_H;
            W = r_W;
            

        

           { 
            int l=0;
            for(int k =H_;k<W;k++)
            {  

            double **grad,**cost,**bt;
            grad = new double*[H];
            cost = new double*[H];
            bt = new double*[H];

            for (int i = 0; i < H; i++) {
                grad[i] = new double[W -l];
                cost[i] = new double[W -l];
                bt[i] =   new double[W -l];
            }

                
            gradient(grad,temp, H, W - l, C);
            costcal(cost,grad,bt,H,W - l,C);

            int m = cost[H-1][0];
            int i_idx = H-1;
            int j_idx = 0;

            for(int j = 0;j < (W - l); j++)
            {
              if( cost[H-1][j] < m )
                {
                    m = cost[H-1][j];
                    i_idx = H-1;
                    j_idx = j;
                }
            
            }
            shiftrgb(temp,H,W - l,C,i_idx,j_idx);
                
               

                for(int i = H - 1;i > 0;i--) 
                { 
                  
                  j_idx = bt[i][j_idx];
                  shiftrgb(temp,H,W - l,C,i-1,j_idx);   
                
                }
                l++;
                for(int i = 0;i < H;i++)
            {
                delete [] grad[i];
                delete [] cost[i];
                delete [] bt[i];
            }
            delete [] grad;
            delete [] cost;
            delete [] bt;

            }
        }
            rotateanti90(rgb,temp,W_,H_,C);
            H = a_H;

            W = a_W;















             
    
}

int main() {
    string ip_dir = "./data/input/";
    string ip_file = "rgb_in.txt";
    ifstream fin(ip_dir + ip_file);

    int H, W, C;
    fin >> H >> W >> C;

    int ***rgb;
    rgb = new int **[H];
    for(int i = 0; i < H; ++i) {
        rgb[i] = new int *[W];
        for(int j = 0; j < W; ++j) {
            rgb[i][j] = new int[C];
            for(int k = 0; k < C; ++k)
                fin >> rgb[i][j][k];
        }
    }
    fin.close();

    int H_, W_, C_;
    cout << "Enter new value for H (must be less than " << H << "): ";
    cin >> H_;
    cout << "Enter new value for W (must be less than " << W << "): ";
    cin >> W_;
    cout << '\n';
    C_ = C;

    solve(rgb, H, W, C, H_, W_, C_);

    string op_dir = "./data/output/";
    string op_file = "rgb_out.txt";
    ofstream fout(op_dir + op_file);
    
    fout << H_ << " " << W_ << " " << C_ << endl;
    for(int i = 0; i < H_; ++i) {
        for(int j = 0; j < W_; ++j) {
            for(int k = 0; k < C_; ++k) {
                fout << rgb[i][j][k] << " ";
            }
        }
        fout << '\n';
    }
    fout.close();

    return 0;
}